/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Core header
*/

#include <string>
#include <vector>
#include "DLLoader.hpp"
#include "interfaces/IGames.hpp"
#include "interfaces/ILib.hpp"
#pragma once

class Core {
public:
    Core(std::string libName);
    ~Core() = default;
    void checkLoad();
    void load();
    void menu(DLLoader<Lib::ILib> loaderLib);
    void nextGraphical();
    void previousGraphical();
    void nextGame(DLLoader<Lib::ILib> loaderLib);
    void previousGame(DLLoader<Lib::ILib> loaderLib);
    void loadGame(DLLoader<Lib::ILib> loaderLib);
    void launchGame(DLLoader<Lib::ILib> loaderLib, DLLoader<IGames> loaderGame);
    void selectGame(DLLoader<Lib::ILib> loaderLib);
    void printHelpKey();
    std::string username();
private:
    int _menu;
    std::string _libName;
    std::string _gameName;
    Lib::ILib *_lib;
    IGames *_game;
    int _choiceGame;
    int _selectLib;
    int _frame;
    bool _exit;
    int _key;
    std::string _name;
    std::vector<std::string> _libList;
    std::vector<std::string> _gameList;
};