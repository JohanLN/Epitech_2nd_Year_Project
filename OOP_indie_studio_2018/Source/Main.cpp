/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** TODO: add description
*/

#include <iostream>
#include <memory>
#include "Map.hpp"
#include "AItem.hpp"
#include "Tank.hpp"
#include "Bomb.hpp"
#include "Error.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "irrlicht.h"

AItem *createItem(std::string name, int posx, int posy);
using namespace irr;

int main(int ac, char **av)
{
    if (ac > 1)
        return 84;
    Game game;

    game.initGame();
    return 0;
}
