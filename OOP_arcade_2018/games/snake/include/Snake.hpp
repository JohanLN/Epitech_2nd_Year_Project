/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** header of the snake game
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "interfaces/IGames.hpp"
#include "Vector.hpp"
#include "AFruit.hpp"
#include "BodySnake.hpp"

namespace Snake {

    class Snake : public IGames {
    public:
        Snake();
        ~Snake() override = default;
        void CreatePlayer(int sizeSnake);
        std::string getName() override;
        void printMap() override;
        void updatePos() override;
        void setLib(Lib::ILib *lib) override;
        void games() override;
        void drawSnake();
        void snakeMove();
        void setKey(int key) override;
        void Wall();
        bool TouchWall();
        bool TouchBody();
        void growSnake();
        void popFruit();
        void printScore();
        void update();
        void displayLoose() override;
        void saveScore();
        int getScore() const override;
        void setUser(std::string user) override;
    private:
        std::string _name;
        Lib::ILib *_lib;
        std::vector<Fruit::AFruit> _fruit;
        std::vector<bodySnake> _body;
        Utils::Vector _player;
        Utils::Vector _pos;
        int _score;
        int _key;
        int _checkFruit;
        bool _loose;
        bool _saveScore;
        std::string _user;
    };
}