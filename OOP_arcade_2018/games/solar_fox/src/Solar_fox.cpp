/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Snake class
*/

#include <Solar_fox.hpp>

#include "../include/Solar_fox.hpp"

SolarFox::SolarFox() : _name("Solar Fox"), _launch(0),
                       _verti_r(0), _verti_l(0),
                       _horiz_u(0), _horiz_d(0),
                       _end1(0),_end2(0),_end3(0),_end4(0),
                       _alive(0), _goal(0), _lives(3), _score(0)
{
}

std::string SolarFox::getName()
{
    return _name;
}

void SolarFox::setLib(Lib::ILib* lib)
{
    _lib = lib;
}

void SolarFox::printMap()
{
    if (_launch == 0) {
        loadMap();
    }
    _launch = 1;
    if (_key == Lib::R_KEY) {
        _map.clear();
        loadMap();
    }
    int posx = 10;
    int posy = 5;
    _alive = 0;
    _goal = 0;
    lives();
    for (int i = 0; _map[i]; i++, posx++) {
        if (_map[i] == '+') {
            _lib->drawPixel(posx, posy, Lib::BLUE);
            _goal = 1;
        }
        if (_map[i] == '!')
            _lib->drawPixel(posx, posy, Lib::WHITE);
        if (_map[i] == '.')
            _lib->drawPixel(posx, posy, Lib::BLACK);
        if (_map[i] == 'm' || _map[i] == 'n' || _map[i] == 'l' || _map[i] == 'k' || _map[i] == 't')
            _lib->drawPixel(posx, posy, Lib::GREEN);
        if (_map[i] == 'p') {
            _lib->drawPixel(posx, posy, Lib::RED);
            _alive = 1;
        }
        if (_map[i] == 's')
            _lib->drawPixel(posx, posy, Lib::MAGENTA);
        if (_map[i] == '\n') {
            posy++;
            posx = 10;
        }
    }
    if (_alive == 0 || _goal == 0) {
        _lib->clearWin();
        displayLoose();
    }
    ennemiesMove();
}

void SolarFox::games() {
    printMap();
    updatePos();
    printMap();
}

void SolarFox::updatePos() {
    unsigned int i ,j;
    if (_key == Lib::RIGHT_KEY && _verti_r == 0) {
        _verti_l = 1;
        _horiz_d = 0;
        _horiz_u = 0;
        for (i = 0; i < _map.size(); i++) {
            if (_map[i] == 'p') {
                if (_map[i+2] == '!' || _map[i+2] == 'm')
                    break;
                _map[i] = '.';
                _map[i+2] = 'p';
                break;
            }
        }
    }
    else if (_key == Lib::LEFT_KEY && _verti_l == 0) {
        _verti_r = 1;
        _horiz_d = 0;
        _horiz_u = 0;
        for (i = 0; i < _map.size(); i++) {
            if (_map[i] == 'p') {
                if (_map[i-2] == '!' || _map[i-2] == 'm')
                    break;
                _map[i] = '.';
                _map[i-2] = 'p';
                break;
            }
        }
    }
    else if (_key == Lib::UP_KEY && _horiz_u == 0) {
        _horiz_d = 1;
        _verti_r = 0;
        _verti_l = 0;
        for (i = 0, j = 2; i < _map.size(); i++, j++) {
            if (_map[i] == 'p') {
                if (_map[j-_size-3] == '!' || _map[j-_size-3] == 'm')
                    break;
                _map[i] = '.';
                _map[j - _size - 3] = 'p';
                break;
            }
        }
    }
    else if (_key == Lib::DOWN_KEY && _horiz_d == 0) {
        _horiz_u = 1;
        _verti_r = 0;
        _verti_l = 0;
        for (i = 0, j = 2; i < _map.size(); i++, j++) {
            if (_map[i] == 'p') {
                if (_map[j+_size-1] == '!' || _map[j+_size-1] == 'm')
                    break;
                _map[i] = '.';
                _map[j+_size-1] = 'p';
                break;
            }
        }
    }
}

void SolarFox::loadMap() {
    char c;
    std::ifstream file("utils/map_solarFox/map_solar.txt", std::ios::in);

    if (!file && std::ios::in) {
        std::cerr << "Error no map available" << std::endl;
        _lib->clearWin();
        _lib->destroyWin();
        exit(84);
    }
    _map.push_back(' ');
    while (!file.eof()) {
        c = static_cast<char>(file.get());
        _map.push_back(' ');
        if (c == '\n') {
            _map.push_back('\n');
        }
        _map.push_back(c);
    }
    int i = 0;
    for (i = 0; _map[i] != '\n'; i++);
    _size = i;
}

void SolarFox::setKey(int key) {
    _key = key;
}

void SolarFox::ennemiesMove() {
    for (int i = 0; _map[i] != '\0'; i++) {
        if (_map[i] == 'm') {
            shootEn1(i);
            if (_end1 == 0 && _map[i + 2] == '!' && _map[i + 4] == '!') {
                _map[i + 2] = 'm';
                _map[i] = '!';
                break;
            } else
                _end1 = 1;
            if (_end1 == 1 && _map[i - 2] == '!' && _map[i - 4] == '!') {
                _map[i - 2] = 'm';
                _map[i] = '!';
                break;
            } else
                _end1 = 0;
        }
    }
    for (int i = 0; _map[i] != '\0'; i++) {
        if (_map[i] == 'n') {
            shootEn2(i);
            if (_end2 == 0 && _map[i + 2] == '!' && _map[i + 4] == '!') {
                _map[i + 2] = 'n';
                _map[i] = '!';
                break;
            } else
                _end2 = 1;
            if (_end2 == 1 && _map[i - 2] == '!' && _map[i - 4] == '!') {
                _map[i - 2] = 'n';
                _map[i] = '!';
                break;
            } else
                _end2 = 0;
        }
    }
    for (int i = 0, j = 2; _map[i] != '\0'; i++, j++) {
        if (_map[i] == 'k') {
            shootEn3(i);
            if (_end3 == 0 && _map[j+_size-1] == '!' && _map[j+_size+_size] == '!') {
                _map[j+_size-1] = 'k';
                _map[i] = '!';
                break;
            } else {
                _end3 = 1;
            }
            if (_end3 == 1 && _map[j-_size-3] == '!' && _map[j-_size-_size-4] == '!') {
                _map[j-_size-3] = 'k';
                _map[i] = '!';
                break;
            } else {
                _end3 = 0;
            }
        }
    }
    for (int i = 0, j = 2; _map[i] != '\0'; i++, j++) {
        if (_map[i] == 'l') {
            shootEn4(i);
            if (_end4 == 0 && _map[j+_size-1] == '!' && _map[j+_size+_size] == '!') {
                _map[j+_size-1] = 'l';
                _map[i] = '!';
                break;
            } else
                _end4 = 1;
            if (_end4 == 1 && _map[j-_size-3] == '!' && _map[j-_size-_size-4] == '!') {
                _map[j-_size-3] = 'l';
                _map[i] = '!';
                break;
            } else
                _end4 = 0;
        }
    }
}

void SolarFox::shootEn1(int i) {
    static int way = i;
    static int dist = _size+_size+2;
    if (_map[way+dist] == '!' || _map[way+dist] == 'l' || _map[way+dist] == '+') {
        _map[way+dist-_size-1] = '.';
        way = i;
        dist = _size+_size+2;
    }
    if (_map[way+dist] == '.') {
        _map[way+dist-_size-1] = '.';
        _map[way+dist] = 't';
    }
    if (_map[way+dist] == 'p') {
        _map[way+dist-_size-1] = '.';
        _map[way+dist+_size-1] = '.';
        _map[way+dist] = '.';
    }
    if (_map[way+dist] == 'p' && _lives == 1) {
        _map[way+dist-_size-1] = '.';
        way = i;
        dist = _size+_size+2;
        _map[way+dist] = '.';
        _lives--;
    }
    dist+=_size+1;
}

void SolarFox::shootEn2(int i) {
    static int way = i;
    static int dist = _size+1;
    if (_map[way-dist] == '!' || _map[way-dist] == 'l' || _map[way-dist] == '+') {
        _map[way-dist+_size+1] = '.';
        way = i;
        dist = _size+1;
    }
    if (_map[way-dist] == '.') {
        _map[way-dist] = 't';
        _map[way-dist+_size+1] = '.';
    }
    if (_map[way-dist] == 'p' && _lives == 1) {
        _map[way-dist] = '.';
        _map[way-dist+_size+1] = '.';
        _map[way-dist-_size-1] = '.';
    }
    if (_map[way-dist] == 'p') {
        _map[way-dist] = '.';
        _map[way-dist+_size+1] = '.';
        way = i;
        dist = _size+1;
        _lives--;
    }
    dist += _size+1;
}

void SolarFox::shootEn3(int i) {
    static int way = i;
    static int dist = 2;
    if (_map[way+dist+2] == '!' || _map[way+dist+2] == 'l' || _map[way+dist+2] == '+') {
        _map[way+dist-2] = '.';
        way = i;
        dist = 4;
    }
    if (_map[way+dist+2] == '.') {
        _map[way+dist] = 't';
        _map[way+dist-2] = '.';
    }
    if (_map[way+dist+2] == 'p' && _lives == 1) {
        _map[way+dist] = '.';
        _map[way+dist-2] = '.';
        _map[way+dist+2] = '.';
    }
    if (_map[way+dist+2] == 'p') {
        _map[way+dist] = '.';
        _map[way+dist-2] = '.';
        way = i;
        dist = 4;
        _lives--;
    }
    dist++;
}

void SolarFox::shootEn4(int i) {
    static int way = i;
    static int dist = 2;
    if (_map[way-dist-2] == '!' || _map[way-dist-2] == 'l' || _map[way-dist-2] == '+') {
        _map[way-dist+2] = '.';
        way = i;
        dist = 4;
    }
    if (_map[way-dist-2] == '.') {
        _map[way-dist] = 't';
        _map[way-dist+2] = '.';
    }
    if (_map[way-dist-2] == 'p' && _lives == 1) {
        _map[way-dist] = '.';
        _map[way-dist+2] = '.';
        _map[way-dist-2] = '.';
    }
    if (_map[way-dist-2] == 'p') {
        _map[way-dist] = '.';
        _map[way-dist+2] = '.';
        way = i;
        dist = 4;
        _lives--;
    }
    dist++;
}

void SolarFox::lives() {
    Lib::t_Text lives = { 0, 7, "Lives:" };
    if (_lives == 3) {
        _lib->printText(lives, Lib::WHITE);
        _lib->drawPixel(3, 10, Lib::RED);
        _lib->drawPixel(3, 13, Lib::RED);
        _lib->drawPixel(3, 16, Lib::RED);
    }
    if (_lives == 2) {
        _lib->printText(lives, Lib::WHITE);
        _lib->drawPixel(3, 10, Lib::RED);
        _lib->drawPixel(3, 13, Lib::RED);
    }
    if (_lives == 1) {
        _lib->printText(lives, Lib::WHITE);
        _lib->drawPixel(3, 10, Lib::RED);
    }
}

void SolarFox::displayLoose() {
    Lib::t_Text text;

    text.posx = 45;
    text.posy = 17;
    text.txt = "Game Over";
    _lib->printText(text, Lib::WHITE);
    text.posy = 19;
    text.txt = "Score : " + std::to_string(_score);
    _lib->printText(text, Lib::WHITE);
    text.posx = 43;
    text.posy = 23;
    text.txt = "Press R to reload";
    _lib->printText(text, Lib::WHITE);
}

int SolarFox::getScore() const {
    return (_score);
}

void SolarFox::setUser(std::string user) {
    _user = user;
}

extern "C" SolarFox *entryPoint(void)
{
    return new SolarFox;
}

extern "C" void deletePoint(SolarFox *ptr)
{
    delete ptr;
}
