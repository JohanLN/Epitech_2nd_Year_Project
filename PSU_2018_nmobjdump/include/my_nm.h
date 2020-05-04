/*
** EPITECH PROJECT, 2019
** nm/objdump
** File description:
** nm header
*/

#pragma once

#include <stdbool.h>
#include <elf.h>
#include <stdio.h>

typedef struct nm_s {
    char *filename;
    Elf64_Ehdr *elf64_ehdr;
    Elf64_Shdr *elf64_shdr;
    Elf64_Sym *sym64_begin;
    Elf64_Sym *sym64_end;
    char *tab;
} nm_t;

typedef struct symbol_s {
    char *section_name;
    unsigned int value;
    char symbol_type;
} symbol_t;

bool parse_file(char *filename, nm_t *dump);
void display_data(nm_t *dump);
bool get_symbol(nm_t *dump, Elf64_Sym *tmp, symbol_t *symbol);