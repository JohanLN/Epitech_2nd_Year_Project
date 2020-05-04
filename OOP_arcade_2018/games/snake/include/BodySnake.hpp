//
// Created by jeremyquemener on 26/03/19.
//

#ifndef OOP_ARCADE_2018_BODYSNAKE_HPP
#define OOP_ARCADE_2018_BODYSNAKE_HPP


#include <Vector.hpp>
#include <ILib.hpp>

class bodySnake {
public:
    bodySnake(Utils::Vector position, Lib::colorDisplay color) : _color(color), _position(position)  {}
    Lib::colorDisplay _color;
    const Utils::Vector &getPos() const;
    const Utils::Vector &getDir() const;
    void setDir(const Utils::Vector &_direction);
    void move();
    void draw(Lib::ILib *lib) {lib->drawPixel(_position.x, _position.y, _color);}
private:
    Utils::Vector _position;
    Utils::Vector _direction;
};


#endif //OOP_ARCADE_2018_BODYSNAKE_HPP
