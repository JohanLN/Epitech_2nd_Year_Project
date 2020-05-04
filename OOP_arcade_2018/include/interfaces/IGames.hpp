/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Games interface
*/

#pragma once
#include <string>
#include <memory>
#include "ILib.hpp"

class IGames {
public:
    virtual ~IGames() = default;
    virtual std::string getName() = 0;
    virtual void updatePos() = 0;
    virtual void printMap() = 0;
    virtual void games() = 0;
    virtual void setLib(Lib::ILib *lib) = 0;
    virtual void setKey(int key) = 0;
    virtual void displayLoose() = 0;
    virtual int getScore() const = 0;
    virtual void setUser(std::string user) = 0;
};
