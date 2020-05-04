/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/

#include <memory>
#include <map>
#include <iostream>
#include <functional>
#include <Item/Bomb.hpp>
#include <Item/Potion.hpp>
#include "AItem.hpp"
#include "Map.hpp"

typedef std::function<std::unique_ptr<AItem>(std::string name, int posx, int posy)> itemcreator_t;

std::map<std::string, itemcreator_t> itemRecipe = {
        {"Bomb", [](std::string name, int posx, int posy) -> std::unique_ptr<AItem> {return std::make_unique<Bomb>(name, posx, posy); } },
        {"Potion", [](std::string name, int posx, int posy) -> std::unique_ptr<AItem> {return std::make_unique<Potion>(name, posx, posy); } },
};

/*
 * retourn un pointer unique de AItem
 * apelle itemRecipe[la clée unique](paramétre)
 */

std::unique_ptr <AItem> itemFactory(std::string type,std::string name, int posx, int posy)
{
    try {
        return itemRecipe[type](name, posx, posy);
    }
	// unreferenced local variable ( const std::exception &e)
    catch (...) {
        exit(1);
    }
}

AItem *createItem(std::string name, int posx, int posy)
{
	// Windows time not recognized
	Map map;
    int item = map.generateRandomNumberByInterval(0, 3);
    int elem = map.generateRandomNumberByInterval(0, 3);
    if (item == 0) {
        if (elem == 0)
            return itemFactory("Bomb", "Petite", posx, posy).release();
        if (elem == 1)
            return itemFactory("Bomb", "Moyen", posx, posy).release();
        if (elem == 2)
            return itemFactory("Bomb", "Grand", posx, posy).release();
    }
    if (item == 2) {
        if (elem == 0)
            return itemFactory("Potion", "StackBomb_potion", posx, posy).release();
        if (elem == 1)
            return itemFactory("Potion", "Strength_potion", posx, posy).release();
        if (elem == 2)
            return itemFactory("Potion", "Shield_potion", posx, posy).release();
    }
	// need return to windows compile
	return (nullptr);
}


