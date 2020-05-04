//
// Created by jeremyquemener on 26/03/19.
//

#ifndef OOP_ARCADE_2018_STRAWBERRY_HPP
#define OOP_ARCADE_2018_STRAWBERRY_HPP

#include "AFruit.hpp"

class Strawberry : public Fruit::AFruit {
public:
    Strawberry() : AFruit(Lib::RED, 150) {};
};

#endif //OOP_ARCADE_2018_STRAWBERRY_HPP
