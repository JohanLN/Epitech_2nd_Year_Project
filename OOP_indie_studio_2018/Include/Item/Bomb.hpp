/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#ifndef ABOMB_HPP_
#define ABOMB_HPP_

#include "AItem.hpp"

class Bomb : public AItem {
	public:
		Bomb(const std::string &name, int _posx, int _posy);
		~Bomb() = default;
        int getRange();
        void setRange(int range);
    private:
        int _Range;
};

#endif /* !ABOMB_HPP_ */
