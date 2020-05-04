//
// Created by jeremyquemener on 26/03/19.
//

#include <BodySnake.hpp>

#include "BodySnake.hpp"

const Utils::Vector &bodySnake::getPos() const {
    return _position;
}

const Utils::Vector &bodySnake::getDir() const {
    return _direction;
}

void bodySnake::setDir(const Utils::Vector &_direction) {
    bodySnake::_direction = _direction;
}

void bodySnake::move() {
    _position.x += _direction.x;
    _position.y += _direction.y;
}
