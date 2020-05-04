/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** header of the solar_fox game
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "interfaces/IGames.hpp"

class SolarFox : public IGames {
public:
    SolarFox();
    ~SolarFox() override = default;
    std::string getName() override;
    void updatePos() override;
    void printMap() override;
    void games() override;
    void setLib(Lib::ILib* lib) override;
    void displayLoose() override;
    int getScore() const override;
    void loadMap();
    void setKey(int key) override;
    void ennemiesMove();
    void shootEn1(int i);
    void shootEn2(int i);
    void shootEn3(int i);
    void shootEn4(int i);
    void lives();
    void setUser(std::string user) override;
    void saveScore();
private:
    std::string _name;
    Lib::ILib* _lib;
    std::vector<char> _map;
    int _launch;
    int _key;
    int _size;
    int _verti_r;
    int _verti_l;
    int _horiz_u;
    int _horiz_d;
    int _end1;
    int _end2;
    int _end3;
    int _end4;
    int _alive;
    int _goal;
    int _lives;
    int _score;
    bool _saveScore;
    std::string _user;
};
