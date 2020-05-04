/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Snake class
*/

#include <Snake.hpp>
#include "Core.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <Blueberry.hpp>
#include <Strawberry.hpp>
#include <zconf.h>

Snake::Snake::Snake() : _name("Snake") {
    CreatePlayer(4);
    popFruit();
    _score = 0;
    _loose = false;
}

void Snake::Snake::CreatePlayer(int sizeSnake) {
    _player.x = 50;
    _player.y = 20;
    srand(time(NULL));
    _body.emplace_back(_player, Lib::YELLOW);
    for (int i = 0; i <= sizeSnake; i++) {
        _body.emplace_back(_player, Lib::GREEN);
    }

    Utils::Vector dirTmp;
    dirTmp = Utils::Vector(-1, 0);
    _body[0].setDir(dirTmp);
}


void Snake::Snake::printMap() {
    for (size_t i = 0; i != _fruit.size() ; i++) {
        _fruit[i].draw(_lib);
        if (_body[0].getPos() == _fruit[i].fruit) {
            popFruit();
            _fruit.erase(_fruit.begin() + i);
            _score += _fruit[_checkFruit].score;
            growSnake();
            i--;
        }
    }
}


void Snake::Snake::setLib(Lib::ILib* lib) {
    _lib = lib;
}

void Snake::Snake::games() {
    if (_key != Lib::R_KEY) {
        if (_loose)
            displayLoose();
        else {
            snakeMove();
            drawSnake();
            Wall();
            printMap();
            printScore();
        }
    } else
        update();
    TouchWall();
    TouchBody();
    getScore();
}

void Snake::Snake::updatePos() {

}

void Snake::Snake::drawSnake() {
    for (size_t i = _body.size(); i != 0 ; i--)
        _body[i - 1].draw(_lib);
}

void Snake::Snake::snakeMove() {
    Utils::Vector tmpdir = _body[0].getDir();
    Utils::Vector dir;
    for (int i = static_cast<int>(_body.size() - 1) ; i >= 0; i--) {
        _body[i].move();
        if (i > 0)
            _body[i].setDir(_body[i - 1].getDir());
    }
    if (_key == Lib::RIGHT_KEY)
        dir = Utils::Vector(1, 0);
    if (_key == Lib::LEFT_KEY)
        dir = Utils::Vector(-1, 0);
    if (_key == Lib::UP_KEY)
        dir = Utils::Vector(0, -1);
    if (_key == Lib::DOWN_KEY)
        dir = Utils::Vector(0, 1);
    if (dir.x == tmpdir.x * -1 || dir.y == tmpdir.y * -1)
        return;
    if (dir.x == 0 && dir.y == 0)
        return;
    _body[0].setDir(dir);
}

void Snake::Snake::setKey(int key) {
    _key = key;
}

void Snake::Snake::Wall() {
    for (int i = 0; i < 96; i++) {
        for (int j = 0; j < 51; j++) {
            if (i == 0 || j == 0 || i == 95 || j == 50)
                _lib->drawPixel(i, j, Lib::WHITE);
        }
    }
}

bool Snake::Snake::TouchWall() {
    _pos = _body[0].getPos();
    for (size_t i = 0; i != _body.size(); i++) {
        if (_pos.x == 0 || _pos.y == 0 || _pos.x == 95 || _pos.y == 50) {
            _loose = true;
            return true;
        }
    }
    return false;
}

bool Snake::Snake::TouchBody() {
    _pos = _body[0].getPos();
    for (size_t i = 1; i != _body.size(); i++) {
        if (_pos == _body[i].getPos()) {
            _loose = true;
            return true;
        }
    }
    return false;
}

std::string Snake::Snake::getName() {
    return _name;
}

void Snake::Snake::growSnake() {
    bodySnake tmp = _body[_body.size() - 1];
    Utils::Vector pos = tmp.getPos();

    pos.x -= tmp.getDir().x;
    pos.y -= tmp.getDir().y;
    _body.emplace_back(pos, Lib::GREEN);
    _body[_body.size() - 1].setDir(tmp.getDir());
}

void Snake::Snake::popFruit() {
    int fruit = rand() % 2;
    if (fruit == 0) {
        _fruit.push_back(Blueberry());
        _checkFruit = 0;
    }
    else {
        _fruit.push_back(Strawberry());
        _checkFruit = 1;
    }
}

void Snake::Snake::printScore() {
    Lib::t_Text score;
    score.posx = 1;
    score.posy = 1;
    score.txt = "Score: " + std::to_string(_score);
    _lib->printText(score, Lib::RED);
}

void Snake::Snake::update() {
    if (_key == Lib::R_KEY) {
        _fruit.clear();
        _body.clear();
        CreatePlayer(4);
        popFruit();
        _loose = false;
        _score = 0;
        snakeMove();
        drawSnake();
        Wall();
        printMap();
        printScore();
    }
}

void Snake::Snake::displayLoose() {
    Lib::t_Text text;
    _lib->loadImage("utils/gameover.png");
    _lib->drawImage("utils/gameover.png");
    text.posx = 45;
    text.posy = 17;
    text.txt = "Game Over";
    _lib->printText(text, Lib::WHITE);
    text.posy = 19;
    text.txt = "Score : " + std::to_string(_score);
    _lib->printText(text, Lib::WHITE);
    text.posx = 34;
    text.posy = 23;
    text.txt = "Press R to reload or press T to back to menu";
    _lib->printText(text, Lib::WHITE);
    if (!_saveScore)
        saveScore();
}

int Snake::Snake::getScore() const {
    return _score;
}

void Snake::Snake::setUser(std::string user) {
    _user = user;
}

void Snake::Snake::saveScore() {
    std::ifstream file("utils/Snake_high_score.txt", std::ios::in);
    std::string buff_tmp;
    std::string buff;

    if(!file)
        return;
    while (getline(file, buff_tmp)) {
        buff += buff_tmp + "\n";
    }
    std::ofstream file2("utils/Snake_high_score.txt", std::ios::out);

    file2 << buff << _user << ": " << _score << std::endl;
    file.close();
    _saveScore = true;
}

extern "C" Snake::Snake *entryPoint(void)
{
    return new Snake::Snake;
}

extern "C" void deletePoint(Snake::Snake *ptr)
{
    delete ptr;
}

