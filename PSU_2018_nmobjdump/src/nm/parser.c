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
#include "my_nm.h"

bool check_elf(nm_t *dump)
{
    if (dump->elf64_ehdr->e_ident[EI_MAG0] != ELFMAG0
        || dump->elf64_ehdr->e_ident[EI_MAG1] != ELFMAG1
        || dump->elf64_ehdr->e_ident[EI_MAG2] != ELFMAG2
        || dump->elf64_ehdr->e_ident[EI_MAG3] != ELFMAG3
        || dump->elf64_ehdr->e_ident[EI_CLASS] == ELFCLASSNONE) {
        fprintf(stderr, "nm: %s: File format not recognized\n",
        dump->filename);
        return false;
    }
    return true;
}

bool check_format(nm_t *dump, struct stat s)
{
    if (s.st_size == 4096) {
        fprintf(stderr, "nm: Warning: '%s' is not an ordinary file\n",
        dump->filename);
        return false;
    }
    if (!check_elf(dump)) {
        return false;
    }
    dump->elf64_shdr = (void *)dump->elf64_ehdr + dump->elf64_ehdr->e_shoff;
    return true;
}

bool init_elf(nm_t *dump, struct stat *s)
{
    int fd;
    void *buff;

    if ((fd = open(dump->filename, O_RDONLY)) != -1) {
        fstat(fd, s);
        if ((buff = mmap(NULL, s->st_size, PROT_READ, MAP_SHARED, fd, 0)))
            dump->elf64_ehdr = buff;
        else {
            perror("mmap");
            close(fd);
            return false;
        }
    }
    else {
        fprintf(stderr, "nm: '%s': No such file\n", dump->filename);
        return false;
    }
    close(fd);
    return true;
}

bool parse_file(char *filename, nm_t *dump)
{
    struct stat s;

    dump->filename = strdup(filename);
    if (!(init_elf(dump, &s)))
        return false;
    return check_format(dump, s);
}
