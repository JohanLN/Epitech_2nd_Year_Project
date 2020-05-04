/*
** EPITECH PROJECT, 2019
** nm/objdump
** File description:
** my_nm
*/

#include "my_nm.h"

bool nm(char *filename)
{
    nm_t dump;

    if (!parse_file(filename, &dump))
        return false;
    display_data(&dump);
    return true;
}

int main(int ac, char **av)
{
    if (ac <= 1)
        if (!nm("a.out"))
            return 84;
    for (int i = 1; av[i]; i++)
        if (!nm(av[i]))
            return 84;
    return 0;
}
