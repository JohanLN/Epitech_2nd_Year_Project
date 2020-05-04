/*
** EPITECH PROJECT, 2019
** fghjk
** File description:
** fghjkl
*/

#pragma once

#include <elf.h>
#include <stdbool.h>

#define UNKNOW 0
#define HAS_RELOC 1
#define HAS_SYMS 10
#define EXEC_P 2
#define DYNAMIC 40
#define D_PAGED 100
#define CORE_FILE 84

typedef struct obj_s {
    char *filename;
    Elf64_Ehdr *elf64_ehdr;
    Elf32_Ehdr *elf32_ehdr;
    Elf64_Shdr *elf64_shdr;
    Elf32_Shdr *elf32_shdr;
    char *tab;
    char *architecture;
    int value_arch;
} obj_t;

void display_data64(obj_t *dump);
void display_data32(obj_t *dump);
void display_header64(obj_t *dump);
void display_header32(obj_t *dump);
bool parse_file(char *filename, obj_t *dump);
