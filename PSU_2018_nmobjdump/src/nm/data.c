/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/

#include <stdlib.h>
#include <string.h>
#include "my_nm.h"

void write_data(nm_t *dump, Elf64_Sym *tmp, symbol_t *symbol, int i)
{
    if (tmp->st_name > 0 && tmp->st_info != STT_FILE) {
        get_symbol(dump, tmp, &symbol[i]);
        if (symbol[i].value ||
            (symbol[i].symbol_type != 'U' && symbol[i].symbol_type != 'w'))
            printf("%016x %c %s\n",
            symbol[i].value,
            symbol[i].symbol_type, symbol[i].section_name);
        else
            printf("%18c %s\n",
            symbol[i].symbol_type, symbol[i].section_name);
    }
}

void display_data(nm_t *dump)
{
    int i = 0;
    Elf64_Sym *tmp;
    symbol_t *symbol;

    for (i = 0; i != dump->elf64_ehdr->e_shnum; i++) {
        if (dump->elf64_shdr[i].sh_type == SHT_SYMTAB) {
            dump->sym64_begin = (void *)dump->elf64_ehdr
            + dump->elf64_shdr[i].sh_offset;
            dump->sym64_end = (void *)dump->sym64_begin
            + dump->elf64_shdr[i].sh_size;
            dump->tab = (char *)dump->elf64_ehdr
            + dump->elf64_shdr[dump->elf64_shdr[i].sh_link].sh_offset;
        }
    }
    symbol = malloc(sizeof(symbol_t) * (dump->sym64_end - dump->sym64_begin));
    memset(symbol, 0, sizeof(symbol_t)
    * (dump->sym64_end - dump->sym64_begin));
    tmp = dump->sym64_begin;
    for (int i = 0; tmp < dump->sym64_end; tmp++, i++)
        write_data(dump, tmp, symbol, i);
}
