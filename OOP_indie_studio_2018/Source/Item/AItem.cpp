/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AItem
*/

#include "Potion.hpp"
#include "AItem.hpp"
#include "Bomb.hpp"

AItem::AItem(const std::string &name, int posx, int posy)
{
    _name = name;
    _posx = posx;
    _posy = posy;
}

const std::string &AItem::getName() const {
    return _name;
}

void AItem::setName(const std::string &name) {
    _name = name;
}

int AItem::getPosx() const {
    return _posx;
}

void AItem::setPosx(int posx) {
    _posx = posx;
}

int AItem::getPosy() const {
    return _posy;
}

void AItem::setPosy(int posy) {
    _posy = posy;
}

