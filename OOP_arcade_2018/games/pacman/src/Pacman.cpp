/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Snake class
*/

#include <fstream>
#include <Pacman.hpp>

#include "../include/Pacman.hpp"

Pacman::Pacman() : _name("Pacman"), _score(0)
{
    srand (time(NULL));
    loadGame();
}

void Pacman::loadGame() {
    _canEat = false;
    _loose = false;
    _start = std::clock();
    _map.clear();
    _mobs.clear();

    int x = 0;
    int y = 0;
    std::map<int, pac_man::states> map_tmp;
    pac_man::t_Mob mob_tmp;
    std::string buff;
    std::string file;
    int i = rand();
    if (i % 3 == 1)
        file = "utils/map_pacman/map_1.txt";
    else if (i % 2 == 1)
        file = "utils/map_pacman/map_2.txt";
    else
        file = "utils/map_pacman/map_3.txt";
    std::ifstream fichier(file, std::ios::in);

    mob_tmp.isAlive = true;
    mob_tmp.way = -1;
    _player.isAlive = true;
    _player.way = -1;
    while (getline(fichier, buff)) {
        map_tmp.clear();
        for (x = 0; (unsigned int) x != buff.size(); x++) {
            if (buff[x] == 'M') {
                mob_tmp.pos_x = x;
                mob_tmp.pos_y = y;
                _mobs.push_back(mob_tmp);
                buff[x] = ' ';
            }
            else if (buff[x] == 'P') {
                _player.pos_x = x;
                _player.pos_y = y;
                buff[x] = ' ';
            }
            map_tmp.emplace(x, pac_man::states(buff[x]));
        }
        _map.push_back(map_tmp);
        y++;
    }
    fichier.close();
}

std::string Pacman::getName()
{
    return _name;
}

void Pacman::printMap() {
    int x = 0;
    int y = 0;
    Lib::t_Text score;

    score.posy = 2;
    score.posx = 2;
    score.txt = "Score : " + std::to_string(_score);
    _lib->printText(score, Lib::colorDisplay::WHITE);
    for (y = 0; (unsigned) y != _map.size() ; y++) {
        for (x = 0; (unsigned int) x != _map[y].size(); x++) {
            if (pac_man::states(_map[y][x]) == pac_man::BLOCK)
                printPixel40_40(x * 3 + 10, y * 3 + 5, Lib::colorDisplay::BLUE);
            if (pac_man::states(_map[y][x]) == pac_man::PAC_GOMME)
                _lib->drawPixel((float) x * 3 + 10, (float) y * 3 + 5, Lib::colorDisplay::WHITE);
            if (pac_man::states(_map[y][x]) == pac_man::SUPER_PAC_GOMME)
                printPixel40_40((float) x * 3 + 10, (float) y * 3 + 5, Lib::colorDisplay::WHITE);
        }
    }
    for (auto &_mob : _mobs)
        printPixel40_40(_mob.pos_x * 3 + 10, _mob.pos_y * 3 + 5, _canEat ? Lib::GREEN : Lib::RED);
    printPixel40_40(_player.pos_x * 3 + 10, _player.pos_y * 3 + 5, Lib::colorDisplay::YELLOW);
}

void Pacman::move(pac_man::t_Mob &mob, bool isPlayer)
{
    if (_loose)
        return;
    if (mob.pos_x == 0)
        mob.pos_x = 26;
    switch (mob.way) {
        case goUP :
            if (_map[(int)mob.pos_y - 1][(int)mob.pos_x] != 'B' && !(isPlayer && _map[(int)mob.pos_y - 1][(int)mob.pos_x] == 'w'))
                mob.pos_y--;
            break;
        case goDOWN :
            if (_map[(int)mob.pos_y + 1][(int)mob.pos_x] != 'B' && !(isPlayer && _map[(int)mob.pos_y + 1][(int)mob.pos_x] == 'w'))
                mob.pos_y++;
            break;
        case goRIGHT :
            if (_map[(int)mob.pos_y][(int)mob.pos_x + 1] != 'B' && !(isPlayer && _map[(int)mob.pos_y][(int)mob.pos_x + 1] == 'w'))
                mob.pos_x++;
            break;
        case goLEFT :
            if (_map[(int)mob.pos_y][(int)mob.pos_x - 1] != 'B' && !(isPlayer && _map[(int)mob.pos_y][(int)mob.pos_x - 1] == 'w'))
                mob.pos_x--;
            break;
        default:break;
    }
    if (mob.pos_x == 0)
        mob.pos_x = 26;
    else if (mob.pos_x == 26 || mob.pos_x == 27)
        mob.pos_x = 1;
}

void Pacman::updatePos() {
    if (_loose)
        return;
    if (_key == Lib::DOWN_KEY)
        _player.wayWanted = goDOWN;
    if (_key == Lib::UP_KEY)
        _player.wayWanted = goUP;
    if (_key == Lib::LEFT_KEY)
        _player.wayWanted = goLEFT;
    if (_key == Lib::RIGHT_KEY)
        _player.wayWanted = goRIGHT;
    if (_player.wayWanted == goRIGHT && _map[(int)_player.pos_y][(int)_player.pos_x + 1] != 'B')
        _player.way = _player.wayWanted;
    if (_player.wayWanted == goLEFT && _map[(int)_player.pos_y][(int)_player.pos_x - 1] != 'B')
        _player.way = _player.wayWanted;
    if (_player.wayWanted == goUP && _map[(int)_player.pos_y - 1][(int)_player.pos_x] != 'B')
        _player.way = _player.wayWanted;
    if (_player.wayWanted == goDOWN && _map[(int)_player.pos_y + 1][(int)_player.pos_x] != 'B')
        _player.way = _player.wayWanted;
}

void Pacman::games() {
    if (_key == Lib::R_KEY) {
        _score = 0;
        loadGame();
    }
    isWin();
    _key = _lib->bindKey();
    moveAI();
    hitbox();
    for (auto &_mob : _mobs) {
        move(_mob, false);
    }
    hitbox();
    updatePos();
    move(_player, true);
    if (_map[(int)_player.pos_y][(int)_player.pos_x] == pac_man::SUPER_PAC_GOMME) {
        _startEat = std::clock();
        _canEat = true;
    }
    if (_map[(int)_player.pos_y][(int)_player.pos_x] == pac_man::PAC_GOMME
    || _map[(int)_player.pos_y][(int)_player.pos_x] == pac_man::SUPER_PAC_GOMME) {
        _map[(int)_player.pos_y][(int)_player.pos_x] = pac_man::EMPTY;
        _score += 10;
    }
    if (_canEat && ((std::clock() - _startEat ) / (double) CLOCKS_PER_SEC) >  1)
        _canEat = false;
    if (_loose)
        displayLoose();
    else
        printMap();
}

void Pacman::setLib(Lib::ILib* lib) {
    _lib = lib;
}

extern "C" Pacman *entryPoint()
{
    return new Pacman;
}

extern "C" void deletePoint(Pacman *ptr)
{
    delete ptr;
}

void Pacman::printPixel40_40(float pos_x, float pos_y, Lib::colorDisplay color) {
    _lib->drawPixel((float)(pos_x - 0.5), (float)(pos_y - 0.5), color);
    _lib->drawPixel((float)(pos_x + 0.5), (float)(pos_y - 0.5), color);
    _lib->drawPixel((float)(pos_x - 0.5), (float)(pos_y + 0.5), color);
    _lib->drawPixel((float)(pos_x + 0.5), (float)(pos_y + 0.5), color);
}

void Pacman::setKey(int key) {
    _key = (Lib::inputKey) key;
}

void Pacman::moveAI() {
    int nb = 0;
    int i;
    if (((std::clock() - _start ) / (double) CLOCKS_PER_SEC) < 0.1)
        return;

    for (auto &_mob : _mobs) {
        i = rand();
        if (((std::clock() - _start ) / (double) CLOCKS_PER_SEC) < nb * 1)
            continue;
        if (_mob.way == goUP && _map[(int)_mob.pos_y][(int)_mob.pos_x + 1] != 'B' && i % 3 == 1)
            _mob.way = goRIGHT;
        else if (_mob.way == goUP && _map[(int)_mob.pos_y][(int)_mob.pos_x - 1] != 'B' && i % 2 == 1)
            _mob.way = goLEFT;
        else if (_mob.way == goRIGHT && _map[(int)_mob.pos_y + 1][(int)_mob.pos_x] != 'B' && i % 3 == 1)
            _mob.way = goDOWN;
        else if (_mob.way == goRIGHT && _map[(int)_mob.pos_y - 1][(int)_mob.pos_x] != 'B' && i % 2 == 1)
            _mob.way = goUP;
        else if (_mob.way == goDOWN && _map[(int)_mob.pos_y][(int)_mob.pos_x + 1] != 'B' && i % 3 == 1)
            _mob.way = goRIGHT;
        else if (_mob.way == goDOWN && _map[(int)_mob.pos_y][(int)_mob.pos_x - 1] != 'B' && i % 3 == 1)
            _mob.way = goLEFT;
        else if (_mob.way == goLEFT && _map[(int)_mob.pos_y - 1][(int)_mob.pos_x] != 'B' && i % 3 == 1)
            _mob.way = goUP;
        else if (_mob.way == goLEFT && _map[(int)_mob.pos_y + 1][(int)_mob.pos_x] != 'B' && i % 2 == 1)
            _mob.way = goDOWN;
        else if (_mob.way == -1)
            _mob.way = goUP;
        if (_mob.way == goLEFT && _map[(int)_mob.pos_y][(int)_mob.pos_x - 1] == 'B')
            _mob.way = goUP;
        if (_mob.way == goUP && _map[(int)_mob.pos_y - 1][(int)_mob.pos_x] == 'B')
            _mob.way = goRIGHT;
        if (_mob.way == goRIGHT && _map[(int)_mob.pos_y][(int)_mob.pos_x + 1] == 'B')
            _mob.way = goDOWN;
        if (_mob.way == goDOWN && _map[(int)_mob.pos_y + 1][(int)_mob.pos_x] == 'B')
            _mob.way = goUP;
        nb++;
    }
}

void Pacman::hitbox() {
    for (auto &_mob : _mobs) {
        if (_mob.pos_x == _player.pos_x && _mob.pos_y == _player.pos_y) {
            if (_canEat) {
                _mob.pos_x = 13;
                _mob.pos_y = 10;
                _score += 200;
            }
            else {
                _loose = true;
                if (!_saveScore)
                    saveScore();
            }
        }
    }
}

void Pacman::isWin() {
    int x;
    int y;
    int i = 0;

    for (y = 0; (unsigned int) y != _map.size() ; y++) {
        for (x = 0; (unsigned int) x != _map[y].size(); x++) {
            if (pac_man::states(_map[y][x]) == pac_man::PAC_GOMME)
                i++;
            if (pac_man::states(_map[y][x]) == pac_man::SUPER_PAC_GOMME)
                i++;
        }
    }
    if (i == 0)
        loadGame();
}

void Pacman::displayLoose() {
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

void Pacman::setUser(std::string user) {
     _userName = user;
}

int Pacman::getScore() const {
    return (_score);
}

void Pacman::saveScore() {
    std::ifstream file("utils/pacman_high_score.txt", std::ios::in);
    std::string buff_tmp;
    std::string buff;

    if(!file)
        return;
    while (getline(file, buff_tmp)) {
        buff += buff_tmp + "\n";
    }
    std::ofstream file2("utils/pacman_high_score.txt", std::ios::out);

    file2 << buff << _userName << ": " << _score << std::endl;
    file.close();
    _saveScore = true;
}


