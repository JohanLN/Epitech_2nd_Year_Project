/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/

#include <stdio.h>
#include "my_objdump.h"

void display_header64(obj_t *dump)
{
    char format[5][30] = {"UNKNOW",
    "HAS_RELOC, HAS_SYMS",
    "EXEC_P, HAS_SYMS, D_PAGED",
    "HAS_SYMS, DYNAMIC, D_PAGED",
    "CORE_FILE"};
    int flags[5] = {UNKNOW, HAS_RELOC + HAS_SYMS, EXEC_P + HAS_SYMS + D_PAGED,
                    HAS_SYMS + DYNAMIC + D_PAGED, CORE_FILE};
    printf("\n%s:     file format %s\n", dump->filename, dump->architecture);
    printf("architecture: i386:x86-64, flags 0x%08d:\n",
    flags[dump->elf64_ehdr->e_type]);
    printf("%s\n", format[dump->elf64_ehdr->e_type]);
    printf("start address 0x%016lx\n\n", dump->elf64_ehdr->e_entry);
}

void display_header32(obj_t *dump)
{
    char format[5][30] = {"UNKNOW",
    "HAS_RELOC, HAS_SYMS",
    "EXEC_P, HAS_SYMS, D_PAGED",
    "HAS_SYMS, DYNAMIC, D_PAGED",
    "CORE_FILE"};
    int flags[5] = {UNKNOW, HAS_RELOC + HAS_SYMS, EXEC_P + HAS_SYMS + D_PAGED,
                    HAS_SYMS + DYNAMIC + D_PAGED, CORE_FILE};
    printf("\n%s:  file format %s\n", dump->filename, dump->architecture);
    printf("architecture: i386, flags 0x%08d:\n",
    flags[dump->elf32_ehdr->e_type]);
    printf("%s\n", format[dump->elf32_ehdr->e_type]);
    printf("start address 0x%016x\n\n", dump->elf32_ehdr->e_entry);
}