/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** APotion
*/

#ifndef APOTION_HPP_
#define APOTION_HPP_

#include "AItem.hpp"

class Potion : public AItem {
	public:
		Potion(const std::string &name, int _posx, int _posy);
	protected:
        bool _Strength;
        bool _StackBomb;
        bool _Shield;
    public:
        bool isStrength() const;
        bool isStackBomb() const;
        bool isShield() const;
};

#endif /* !APOTIONAPotion_HPP_ */
