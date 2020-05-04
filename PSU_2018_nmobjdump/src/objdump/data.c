/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/

#include <stdio.h>
#include "my_objdump.h"

void print_content(uint8_t *header, int j)
{
    for (int i = 0; i < 16; i++) {
        if (i < j)
            printf("%02x", header[i]);
        else
            printf("  ");
        if (!((i + 1) %4))
            printf(" ");
    }
    printf(" ");
    for (int i = 0; i < 16; i++) {
        if (i < j) {
            if (header[i] >= ' ' && header[i] <= '~')
                printf("%c", header[i]);
            else
                printf(".");
        }
        else
            printf(" ");
    }
    printf("\n");
}

void display_data64(obj_t *dump)
{
    for (int i = 1; i < dump->elf64_ehdr->e_shnum; ++i) {
        printf("Contents of section %s:\n",
                &dump->tab[dump->elf64_shdr[i].sh_name]);
        for (unsigned int j = dump->elf64_shdr[i].sh_offset;
        j < dump->elf64_shdr[i].sh_offset + dump->elf64_shdr[i].sh_size;
        j += 16) {
            printf(" %04x ", (int) (dump->elf64_shdr[i].sh_addr + j
            - dump->elf64_shdr[i].sh_offset));
            print_content((unsigned char *)dump->elf64_ehdr + j,
                    dump->elf64_shdr[i].sh_offset
                    + dump->elf64_shdr[i].sh_size - j);
        }
    }
}

void display_data32(obj_t *dump)
{
    for (int i = 1; i < dump->elf32_ehdr->e_shnum - 3; ++i) {
        printf("Contents of section %s:\n",
                &dump->tab[dump->elf32_shdr[i].sh_name]);
        for (unsigned int j = dump->elf32_shdr[i].sh_offset;
        j < dump->elf32_shdr[i].sh_offset + dump->elf32_shdr[i].sh_size;
        j += 16) {
            printf(" %04x ", (int) (dump->elf32_shdr[i].sh_addr + j
            - dump->elf32_shdr[i].sh_offset));
            print_content((unsigned char *)dump->elf32_ehdr + j,
                    dump->elf32_shdr[i].sh_offset
                    + dump->elf32_shdr[i].sh_size - j);
        }
    }
}