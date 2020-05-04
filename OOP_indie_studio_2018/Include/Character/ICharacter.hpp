/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ICharacter
*/

#ifndef ICHARACTER_HPP_
#define ICHARACTER_HPP_

#include <irrlicht.h>
#include "AItem.hpp"
#include "IGame.hpp"
#include "Map.hpp"

using namespace irr;

class ICharacter {
	public:
		virtual ~ICharacter() = default;

        virtual void movement(IrrlichtDevice *device, scene::ISceneManager *manager, video::IVideoDriver *driver, Map *map) = 0;
        virtual void useBomb() = 0;
        virtual bool checkItem(AItem *item) = 0;

};

#endif /* !ICHARACTER_HPP_ */
