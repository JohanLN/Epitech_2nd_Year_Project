//
// Created by jeremyquemener on 26/03/19.
//

#ifndef OOP_ARCADE_2018_AFRUIT_HPP
#define OOP_ARCADE_2018_AFRUIT_HPP

#include <ILib.hpp>
#include "Vector.hpp"

namespace Fruit {
    class AFruit {
    public:
        AFruit(Lib::colorDisplay color, int score1) : score(score1),
                                                     color(color) {
            fruit.x = rand() % 82 + 1;
            fruit.y = rand() % 35 + 1;
        };
        Utils::Vector fruit;
        int score;
        Lib::colorDisplay color;
        void draw(Lib::ILib *lib) {lib->drawPixel(fruit.x, fruit.y, color);}
        //int getScore() const {return score;}
        int getScore() const {
            return score;
        }
    };
}

#endif //OOP_ARCADE_2018_AFRUIT_HPP
