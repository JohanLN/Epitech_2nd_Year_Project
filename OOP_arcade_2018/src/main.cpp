/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Main file
*/

#include <iostream>
#include <string>
#include "Core.hpp"

int main(int ac, char **av)
{
    try {
        if (ac < 2 || ac > 2) {
            std::cerr << "Usage : ./arcade [path to the library]" << std::endl;
            return 84;
        }
        Core arcade(av[1]);
        arcade.load();
        return 0;
    }

    catch (std::exception const& error){
        std::cerr << error.what() << std::endl;
        return 84;
    }
}
