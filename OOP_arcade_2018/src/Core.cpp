/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/

#include <utility>
#include <Core.hpp>
#include <dirent.h>
#include <cstring>

Core::Core(std::string libName) : _menu(1),
                                  _libName(std::move(libName)),
                                  _gameName("games/lib_arcade_nibbler.so"),
                                  _lib(nullptr),
                                  _game(nullptr),
                                  _choiceGame(0),
                                  _frame(60),
                                  _name("")
{
    checkLoad();
    std::string lib = "libs/";
    std::string game = "games/";
    int len = 0;
    DIR *fileLib = opendir("libs/");
    struct dirent *readLib;
    while ((readLib = readdir(fileLib))) {
        len = static_cast<int>(strlen(readLib->d_name));
        if (readLib->d_name[len - 2] == 's'
            && readLib->d_name[len - 1] == 'o') {
            lib += readLib->d_name;
            _libList.push_back(lib);
            lib = "libs/";
        }
    }
    DIR *fileGame = opendir("games/");
    struct dirent *read;
    while ((read = readdir(fileGame))) {
        len = static_cast<int>(strlen(read->d_name));
        if (read->d_name[len - 2] == 's' && read->d_name[len - 1] == 'o') {
            game += read->d_name;
            _gameList.push_back(game);
            game = "games/";
        }
    }
    int i = 0;
    for (; _libName != _libList[i]; i++);
    _selectLib = i;
}

std::string Core::username() {
    Lib::t_Text name;
    name.posx = 45;
    name.posy = 20;
    if (_key >= Lib::A_KEY && _key <= Lib::Z_KEY)
        _name += static_cast<char>(_key);
    if (_key == Lib::BACKSPACE && _name.size() != 0)
        _name.pop_back();
    name.txt = "name :" + _name;
    _lib->printText(name, Lib::WHITE);
    return _name;
}


void Core::menu(DLLoader<Lib::ILib> loaderLib)
{
    Lib::t_Text jeu1 = {45, 7, "Nibbler"};
    Lib::t_Text jeu2 = {45, 10, "Pacman"};
    Lib::t_Text jeu3 = {45, 13, "Solar Fox"};
    _lib->displayWin(_frame);
    _lib->loadImage("utils/background.png");
    while (_key != Lib::ESCAPE) {
        _lib->loadMusic("utils/sn.wav");
        _key = _lib->bindKey();
        _lib->clearWin();
        printHelpKey();
        username();
        if (_choiceGame == 0) {
            _lib->printText(jeu1, Lib::RED);
            _lib->printText(jeu2, Lib::WHITE);
            _lib->printText(jeu3, Lib::WHITE);
        }
        if (_choiceGame == 1) {
            _lib->printText(jeu2, Lib::RED);
            _lib->printText(jeu1, Lib::WHITE);
            _lib->printText(jeu3, Lib::WHITE);
        }
        if (_choiceGame == 2) {
            _lib->printText(jeu3, Lib::RED);
            _lib->printText(jeu2, Lib::WHITE);
            _lib->printText(jeu1, Lib::WHITE);
        }
        selectGame(loaderLib);
        if (_key == Lib::KEY_F2)
            nextGraphical();
        else if (_key == Lib::KEY_F1)
            previousGraphical();
        _lib->updateWin(0.08f);
    }
    _lib->clearWin();
    _lib->destroyWin();
    loaderLib.DLCloseLib();
}

void Core::selectGame(DLLoader<Lib::ILib> loaderLib) {
    if (_key == Lib::DOWN_KEY) {
        _choiceGame++;
    }
    else if (_key == Lib::UP_KEY) {
        _choiceGame--;
    }
    else if (_key == Lib::ENTER) {
        _choiceGame == 0 ? _frame = 10 : 0;
        _choiceGame == 1 ? _frame = 10 : 0;
        _choiceGame == 2 ? _frame = 10 : 0;
        _lib->clearWin();
        _lib->destroyWin();
        _menu = 0;
        loadGame(loaderLib);
    }
    if (_choiceGame < 0) {
        _choiceGame = static_cast<int>(_gameList.size() - 1);
    }
    if (_choiceGame == static_cast<int>(_gameList.size())) {
        _choiceGame = 0;
    }
}

void Core::checkLoad()
{
    DLLoader<Lib::ILib> loader(_libName);

    loader.DLOpenLib();
}

void Core::load()
{
    DLLoader<Lib::ILib> loader(_libList[_selectLib]);
    DLLoader<IGames> loaderGame(_gameList[_choiceGame]);

    if (loader._handle)
        loader.DLCloseLib();
    loader.DLOpenLib();
    _lib = loader.getInstance();
    if (_menu == 0) {
        loadGame(loader);
        launchGame(loader, loaderGame);
    }
    else
        menu(loader);
}

void Core::loadGame(DLLoader<Lib::ILib> loaderLib)
{
    DLLoader<IGames> loader(_gameList[_choiceGame]);

    if (loader._handle)
        loader.DLCloseLib();
    loader.DLOpenLib();
    _game = loader.getInstance();
    _game->setLib(_lib);
    launchGame(loaderLib, loader);
}

void Core::launchGame(DLLoader<Lib::ILib> loaderLib, DLLoader<IGames> loaderGame)
{
    _lib->displayWin(_frame);
    _game->setUser(_name);

    while (_key != Lib::ESCAPE) {
        _key = _lib->bindKey();
        _game->setKey(_key);
        _lib->clearWin();
        _game->games();
        if (_key == Lib::KEY_F2)
            nextGraphical();
        else if (_key == Lib::KEY_F1)
            previousGraphical();
        else if (_key == Lib::KEY_F4)
            nextGame(loaderLib);
        else if (_key == Lib::KEY_F3)
            previousGame(loaderLib);
        else if (_key == Lib::T_KEY) {
            _frame = 60;
            _lib->clearWin();
            _lib->destroyWin();
            _menu = 1;
            load();
        }
        _lib->updateWin(0.08f);
    }
    _lib->clearWin();
    _lib->destroyWin();
    loaderGame.DLCloseLib();
    loaderLib.DLCloseLib();
    exit(0);
}

void Core::nextGraphical()
{
    _selectLib++;
    if (_selectLib == static_cast<int>(_libList.size()))
        _selectLib = 0;
    _lib->clearWin();
    _lib->destroyWin();
    load();

}

void Core::previousGraphical()
{
    _selectLib--;
    if (_selectLib < 0)
        _selectLib = static_cast<int>(_libList.size() - 1);
    _lib->clearWin();
    _lib->destroyWin();
    load();
}

void Core::nextGame(DLLoader<Lib::ILib> loaderLib)
{
    _choiceGame++;
    if (_choiceGame == static_cast<int>(_gameList.size()))
        _choiceGame = 0;
    if (_choiceGame == 0)
        _frame = 10;
    else if (_choiceGame == 1)
        _frame = 30;
    else if (_choiceGame == 2)
        _frame = 10;
    _lib->clearWin();
    _lib->destroyWin();
    loadGame(loaderLib);
}

void Core::previousGame(DLLoader<Lib::ILib> loaderLib)
{
    _choiceGame--;
    if (_choiceGame < 0)
        _choiceGame = static_cast<int>(_gameList.size() - 1);
    if (_choiceGame == 0)
        _frame = 10;
    else if (_choiceGame == 1)
        _frame = 10;
    else if (_choiceGame == 2)
        _frame = 10;
    _lib->clearWin();
    _lib->destroyWin();
    loadGame(loaderLib);
}

void Core::printHelpKey() {
    Lib::t_Text lib;
    if (!_libList[_selectLib].compare("libraries/lib_arcade_sdl2.so")) {
        lib = { 43, 5, "Arcade - SDL2" };
    } else if (!_libList[_selectLib].compare("libraries/lib_arcade_ncurses.so")) {
        lib = { 43, 5, "Arcade - ncurses" };
    } else if (!_libList[_selectLib].compare("libraries/lib_arcade_sfml.so")) {
        lib = { 43, 5, "Arcade - SFML" };
    }
    _lib->drawImage("utils/background.png");
    Lib::t_Text controls = {5, 38, "CONTROLS:"};
    Lib::t_Text menu = {0, 40, "Press R to reload the game"};
    Lib::t_Text escape = {0, 41, "Press ESCAPE to close window."};
    Lib::t_Text reload = {0, 42, "Press T to back to the menu."};
    Lib::t_Text nextLibrairy = {0, 43, "Press F2 to next graphical librairy."};
    Lib::t_Text previousLibrairy = {0, 44, "Press F1 to previous graphical librairy."};
    Lib::t_Text nextGame = {0, 45, "Press F4 to Next Game."};
    Lib::t_Text previousGame = {0, 46, "Press F3 to Previous Game."};
    Lib::t_Text enter = {0, 47, "Press Enter to select game."};
    Lib::t_Text downKey = {0, 48, "Press DownKey to move the cursor."};
    Lib::t_Text UpKey = {0, 49, "Press UpKey to move the cursor."};
    _lib->printText(lib, Lib::WHITE);
    _lib->printText(controls, Lib::WHITE);
    _lib->printText(menu, Lib::WHITE);
    _lib->printText(escape, Lib::WHITE);
    _lib->printText(reload, Lib::WHITE);
    _lib->printText(nextLibrairy, Lib::WHITE);
    _lib->printText(previousLibrairy, Lib::WHITE);
    _lib->printText(nextLibrairy, Lib::WHITE);
    _lib->printText(nextGame, Lib::WHITE);
    _lib->printText(previousGame, Lib::WHITE);
    _lib->printText(enter, Lib::WHITE);
    _lib->printText(downKey, Lib::WHITE);
    _lib->printText(UpKey, Lib::WHITE);

}
