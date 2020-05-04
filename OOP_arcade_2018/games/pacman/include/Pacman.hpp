/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** header of the pacman game
*/

#ifndef OOP_ARCADE_2018_PACMAN_HPP
#define OOP_ARCADE_2018_PACMAN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include "interfaces/ILib.hpp"
#include "interfaces/IGames.hpp"

#define goUP 0
#define goDOWN 1
#define goRIGHT 2
#define goLEFT 3

namespace pac_man {
    enum states {
        BLOCK = 'B',
        PAC_GOMME = '.',
        SUPER_PAC_GOMME = 'o',
        EMPTY = ' ',
        MOB_START = 'M',
        PLAYER_START = 'P',
        INVISIBLE_BLOCK = 'w'
    };

    typedef struct {
        float pos_x;
        float pos_y;
        bool isAlive;
        int way;
        int wayWanted;
    } t_Mob;
}

class Pacman : public IGames {
public:
    Pacman();
    ~Pacman() override = default;
    std::string getName() override;
    void printMap() override;
    void updatePos() override;
    void setLib(Lib::ILib* lib) override;
    void games() override;
    void displayLoose() override;
    int getScore() const override;
    void printPixel40_40(float pos_x, float pos_y, Lib::colorDisplay color);
    void setKey(int key) override;
    void move(pac_man::t_Mob &mob, bool isPlayer);
    void moveAI();
    void hitbox();
    void isWin();
    void loadGame();
    void saveScore();
    void setUser(std::string user) override;
private:
    std::clock_t _start;
    Lib::ILib* _lib;
    std::string _name;
    std::vector<std::map<int, pac_man::states>> _map;
    std::vector<pac_man::t_Mob> _mobs;
    pac_man::t_Mob _player;
    Lib::inputKey _key;
    bool _canEat;
    bool _loose;
    std::clock_t _startEat;
    unsigned int _score;
    std::string _userName;
    bool _saveScore;
};


#endif //OOP_ARCADE_2018_Pacman.hpp