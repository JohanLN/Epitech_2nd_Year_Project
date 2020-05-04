/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/

#include "my_nm.h"

char get_other_type(nm_t *dump, Elf64_Sym *tmp)
{
    if (dump->elf64_shdr[tmp->st_shndx].sh_type == SHT_PROGBITS &&
        dump->elf64_shdr[tmp->st_shndx].sh_flags == SHF_ALLOC)
        return ('R');
    if (dump->elf64_shdr[tmp->st_shndx].sh_type == SHT_PROGBITS &&
        dump->elf64_shdr[tmp->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        return ('D');
    if (dump->elf64_shdr[tmp->st_shndx].sh_flags == SHT_NULL &&
        dump->elf64_shdr[tmp->st_shndx].sh_flags == 0)
        return ('U');
    if (dump->elf64_shdr[tmp->st_shndx].sh_flags == SHT_NULL &&
        dump->elf64_shdr[tmp->st_shndx].sh_flags == DT_DEBUG)
        return ('N');
    if (dump->elf64_shdr[tmp->st_shndx].sh_type == SHT_PROGBITS &&
        dump->elf64_shdr[tmp->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        return ('T');
    if (dump->elf64_shdr[tmp->st_shndx].sh_type == SHT_PROGBITS &&
        dump->elf64_shdr[tmp->st_shndx].sh_flags == 0)
        return ('R');
    if (dump->elf64_shdr[tmp->st_shndx].sh_type == SHT_DYNAMIC)
        return ('D');
    return ('?');
}

char get_type(nm_t *dump, Elf64_Sym *tmp)
{
    if (tmp->st_shndx == SHN_UNDEF)
        return ('U');
    if (tmp->st_shndx == SHN_COMMON)
        return ('C');
    if (tmp->st_shndx == SHN_ABS)
        return ('A');
    if (dump->elf64_shdr[tmp->st_shndx].sh_type == SHT_NOBITS &&
    dump->elf64_shdr[tmp->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        return ('B');
    return (get_other_type(dump, tmp));
}

bool get_symbol(nm_t *dump, Elf64_Sym *tmp, symbol_t *symbol)
{
    symbol->value = (unsigned int)tmp->st_value;
    symbol->symbol_type = get_type(dump, tmp);
    if (ELF64_ST_BIND(tmp->st_info) == STB_WEAK) {
        if (tmp->st_shndx == SHN_UNDEF)
            symbol->symbol_type = 'w';
        else
            symbol->symbol_type = 'W';
    }
    else if (ELF64_ST_BIND(tmp->st_info) == STB_WEAK &&
    ELF64_ST_TYPE(tmp->st_info) == STT_OBJECT) {
        if (tmp->st_shndx == SHN_UNDEF)
            symbol->symbol_type = 'v';
        else
            symbol->symbol_type = 'V';
    }
    else if (symbol->symbol_type == '?')
        symbol->symbol_type = 'T';
    if (ELF64_ST_BIND(tmp->st_info) == STB_LOCAL)
            symbol->symbol_type += 32;
    symbol->section_name = &dump->tab[tmp->st_name];
    return true;
}
