//
// Created by jeremyquemener on 17/03/19.
//
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <iostream>
#include <lib_arcade_ncurses.hpp>

#include "lib_arcade_ncurses.hpp"

lib_arcade_ncurses::lib_arcade_ncurses() : _name("ncurses"), _height(1920),
                                           _widht(1080), _posx(), _posy() {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color();
    init_pair(30, COLOR_RED, COLOR_BLACK);
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);
    init_pair(7, COLOR_WHITE, COLOR_WHITE);
}

lib_arcade_ncurses::~lib_arcade_ncurses() {
    endwin();
}

lib_arcade_ncurses& lib_arcade_ncurses::operator=(const lib_arcade_ncurses& oldLib)
{
//    if (oldLib != this) {
        sizex = oldLib.sizex;
        sizey = oldLib.sizey;
        _gameWin = oldLib._gameWin;
        _name = oldLib._name;
        _height = oldLib._height;
        _widht = oldLib._widht;
        _posx = oldLib._posx;
        _posy = oldLib._posy;
        _colorD = oldLib._colorD;
        _color = oldLib._color;
//    }
    return *this;
}


void lib_arcade_ncurses::errorNcurses(std::string error) {
    (void)error;
}

void lib_arcade_ncurses::displayWin(int frame)
{
    _gameWin = newwin(LINES, COLS, 0, 0);
    box(_gameWin, 0, 0);
    keypad(_gameWin, TRUE);
    nodelay(_gameWin, TRUE);
    wtimeout(_gameWin, 1000/frame);
    _state = 1;
}

void lib_arcade_ncurses::destroyWin() {
    delwin(_gameWin);
    endwin();
}

Lib::inputKey lib_arcade_ncurses::bindKey() {
    int key = wgetch(_gameWin);

    if (key == KEY_BACKSPACE)
        return Lib::inputKey::BACKSPACE;
    if (key == '\n')
        return Lib::inputKey::ENTER;
    if (key == 27)
        return Lib::inputKey::ESCAPE;
    if (key == KEY_UP)
        return Lib::inputKey::UP_KEY;
    if (key == KEY_DOWN)
        return Lib::inputKey::DOWN_KEY;
    if (key == KEY_LEFT)
        return Lib::inputKey::LEFT_KEY;
    if (key == KEY_RIGHT)
        return Lib::inputKey::RIGHT_KEY;
    if (key == 'a')
        return Lib::inputKey::A_KEY;
    if (key == 'b')
        return Lib::inputKey::B_KEY;
    if (key == 'c')
        return Lib::inputKey::C_KEY;
    if (key == 'd')
        return Lib::inputKey::D_KEY;
    if (key == 'e')
        return Lib::inputKey::E_KEY;
    if (key == 'f')
        return Lib::inputKey::F_KEY;
    if (key == 'g')
        return Lib::inputKey::G_KEY;
    if (key == 'h')
        return Lib::inputKey::H_KEY;
    if (key == 'i')
        return Lib::inputKey::I_KEY;
    if (key == 'j')
        return Lib::inputKey::J_KEY;
    if (key == 'k')
        return Lib::inputKey::K_KEY;
    if (key == 'l')
        return Lib::inputKey::L_KEY;
    if (key == 'm')
        return Lib::inputKey::M_KEY;
    if (key == 'n')
        return Lib::inputKey::N_KEY;
    if (key == 'o')
        return Lib::inputKey::O_KEY;
    if (key == 'p')
        return Lib::inputKey::P_KEY;
    if (key == 'q')
        return Lib::inputKey::Q_KEY;
    if (key == 'r')
        return Lib::inputKey::R_KEY;
    if (key == 's')
        return Lib::inputKey::S_KEY;
    if (key == 't')
        return Lib::inputKey::T_KEY;
    if (key == 'u')
        return Lib::inputKey::U_KEY;
    if (key == 'v')
        return Lib::inputKey::V_KEY;
    if (key == 'w')
        return Lib::inputKey::W_KEY;
    if (key == 'x')
        return Lib::inputKey::X_KEY;
    if (key == 'y')
        return Lib::inputKey::Y_KEY;
    if (key == 'z')
        return Lib::inputKey::Z_KEY;
    if (key == KEY_F(1))
        return Lib::inputKey::KEY_F1;
    if (key == KEY_F(2))
        return Lib::inputKey::KEY_F2;
    if (key == KEY_F(3))
        return Lib::inputKey::KEY_F3;
    if (key == KEY_F(4))
        return Lib::inputKey::KEY_F4;
    if (key == KEY_F(5))
        return Lib::inputKey::KEY_F5;
    if (key == KEY_F(6))
        return Lib::inputKey::KEY_F6;
    if (key == KEY_F(7))
        return Lib::inputKey::KEY_F7;
    if (key == KEY_F(8))
        return Lib::inputKey::KEY_F8;
    if (key == KEY_F(9))
        return Lib::inputKey::KEY_F9;
    if (key == KEY_F(10))
        return Lib::inputKey::KEY_F10;
    if (key == KEY_F(11))
        return Lib::inputKey::KEY_F11;
    if (key == KEY_F(12))
        return Lib::inputKey::KEY_F12;
    return Lib::inputKey::NOIN;
}

void lib_arcade_ncurses::bindColor() {
    if (_color == Lib::colorDisplay::RED)
        _color = 1;
    else if (_color == Lib::colorDisplay::YELLOW)
        _color = 3;
    else if (_color == Lib::colorDisplay::CYAN)
        _color = 6;
    else if (_color == Lib::colorDisplay::BLUE)
        _color = 4;
    else if (_color == Lib::colorDisplay::MAGENTA)
        _color = 5;
    else if (_color == Lib::colorDisplay::GREEN)
        _color = 2;
    else if (_color == Lib::colorDisplay::BLACK)
        _color = 0;
    else if (_color == Lib::colorDisplay::WHITE)
        _color = 7;
    else if (_color == Lib::colorDisplay::NOCO)
        _color = -1;
}

void lib_arcade_ncurses::drawPixel(float posx, float posy, Lib::colorDisplay color) {
    _color = color;
    bindColor();
    wattron(_gameWin, COLOR_PAIR(_color));
    mvwprintw(_gameWin, posy, posx, ".");
    wattroff(_gameWin, COLOR_PAIR(_color));
}

void lib_arcade_ncurses::printText(Lib::t_Text &txt, Lib::colorDisplay color) {
    _color = color;
    bindColor();
    if (_color != Lib::WHITE) {
        wattron(_gameWin, COLOR_PAIR(30));
        mvwprintw(_gameWin, txt.posy, txt.posx, "%s", txt.txt.c_str());
        wattroff(_gameWin, COLOR_PAIR(30));
    }
    else
        mvwprintw(_gameWin, txt.posy, txt.posx, "%s", txt.txt.c_str());
}

void lib_arcade_ncurses::updateWin(float sec) {
    (void)sec;
    wrefresh(_gameWin);
}

void lib_arcade_ncurses::clearWin() {
    wclear(_gameWin);
}

void lib_arcade_ncurses::drawImage(std::string file) {
    (void)file;
}

void lib_arcade_ncurses::loadImage(std::string file) {
    (void)file;
}

void lib_arcade_ncurses::loadMusic(std::string file) {
    (void)file;
}

void lib_arcade_ncurses::launchMusic() {

}

extern "C" lib_arcade_ncurses *entryPoint(void) {
    return new lib_arcade_ncurses;
}

extern "C" void deletePoint(lib_arcade_ncurses *ptr)
{
    delete ptr;
}
