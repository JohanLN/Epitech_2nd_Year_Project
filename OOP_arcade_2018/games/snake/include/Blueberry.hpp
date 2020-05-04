//
// Created by jeremyquemener on 26/03/19.
//

#ifndef OOP_ARCADE_2018_BLUEBERRY_HPP
#define OOP_ARCADE_2018_BLUEBERRY_HPP


#include "AFruit.hpp"

class Blueberry : public Fruit::AFruit {
public:
    Blueberry() : AFruit(Lib::BLUE, 100) {};
};


#endif //OOP_ARCADE_2018_BLUEBERRY_HPP
