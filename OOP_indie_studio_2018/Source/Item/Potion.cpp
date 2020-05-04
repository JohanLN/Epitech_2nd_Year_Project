/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** APotion
*/

#include "Potion.hpp"


Potion::Potion(const std::string &name, int _posx, int _posy) : AItem(name, _posx, _posy){
    _StackBomb = name == "StackBomb_potion";
    _Strength = name == "Strength_potion";
    _Shield = name == "Shield_potion";
}

bool Potion::isStrength() const {
    return _Strength;
}

bool Potion::isStackBomb() const {
    return _StackBomb;
}

bool Potion::isShield() const {
    return _Shield;
}
