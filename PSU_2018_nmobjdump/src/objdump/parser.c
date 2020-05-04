/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "my_objdump.h"

bool check_elf(obj_t *dump)
{
    if (dump->elf64_ehdr->e_ident[EI_MAG0] != ELFMAG0
        || dump->elf64_ehdr->e_ident[EI_MAG1] != ELFMAG1
        || dump->elf64_ehdr->e_ident[EI_MAG2] != ELFMAG2
        || dump->elf64_ehdr->e_ident[EI_MAG3] != ELFMAG3
        || dump->elf64_ehdr->e_ident[EI_CLASS] == ELFCLASSNONE) {
        fprintf(stderr, "objdump: %s: File format not recognized\n",
                dump->filename);
        return false;
    }
    if (dump->elf32_ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
        dump->architecture = strdup("elf32-i386");
        dump->value_arch = 32;
    }
    else if (dump->elf64_ehdr->e_ident[EI_CLASS] == ELFCLASS64) {
        dump->architecture = strdup("elf64-x86-64");
        dump->value_arch = 64;
    }
    return true;
}

bool check_format(obj_t *dump, struct stat s)
{
    if (s.st_size == 4096) {
        fprintf(stderr, "objdump: Warning: '%s' is not an ordinary file\n",
                dump->filename);
        return false;
    }
    if (!check_elf(dump)) {
        return false;
    }
    if (dump->value_arch == 64) {
        dump->elf64_shdr = (void *) dump->elf64_ehdr
        + dump->elf64_ehdr->e_shoff;
        dump->tab = (char *) (void *) dump->elf64_ehdr
        + dump->elf64_shdr[dump->elf64_ehdr->e_shstrndx].sh_offset;
    }
    else if (dump->value_arch == 32) {
        dump->elf32_shdr = (void *) dump->elf32_ehdr
        + dump->elf32_ehdr->e_shoff;
        dump->tab = (char *) (void *) dump->elf32_ehdr
                    + dump->elf32_shdr[dump->elf32_ehdr->e_shstrndx].sh_offset;
    }
    return true;
}

bool init_elf(obj_t *dump, struct stat *s)
{
    int fd;
    void *buff;

    if ((fd = open(dump->filename, O_RDONLY)) != -1) {
        fstat(fd, s);
        if ((buff = mmap(NULL, s->st_size, PROT_READ, MAP_SHARED, fd, 0))) {
            dump->elf64_ehdr = buff;
            dump->elf32_ehdr = buff;
        }
        else {
            perror("mmap");
            close(fd);
            return false;
        }
    }
    else {
        fprintf(stderr, "objdump: '%s': No such file\n", dump->filename);
        return false;
    }
    close(fd);
    return true;
}

bool parse_file(char *filename, obj_t *dump)
{
    struct stat s;

    dump->filename = strdup(filename);
    if (!(init_elf(dump, &s)))
        return false;
    return check_format(dump, s);
}
