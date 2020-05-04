/*
** EPITECH PROJECT, 2019
** nm/objdump
** File description:
** my_objdump
*/

#include "my_objdump.h"

bool objdump(char *filename)
{
    obj_t dump;

    if (!parse_file(filename, &dump))
        return false;
    if (dump.value_arch == 64) {
        display_header64(&dump);
        display_data64(&dump);
    }
    else if (dump.value_arch == 32) {
        display_header32(&dump);
        display_data32(&dump);
    }
    return true;
}

int main(int ac, char **av)
{
    if (ac <= 1) {
        if (!objdump("a.out"))
            return 84;
    }
    for (int i = 1; av[i]; i++)
        if (!objdump(av[i]))
            return 84;
    return 0;
}
