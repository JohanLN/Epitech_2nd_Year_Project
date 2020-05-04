/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(const std::string &name, int _posx, int _posy) : AItem(name, _posx,
                                                                  _posy) {
    _Range = 0;
    if (name == "Petite")
        _Range = 2;
    if (name == "Moyen")
        _Range = 3;
    if (name == "Grand")
        _Range = 4;
}

void Bomb::setRange(int range) {
    _Range = range;
}

int Bomb::getRange() {
    return _Range;

}
