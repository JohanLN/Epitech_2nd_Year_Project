//
// Created by jeremyquemener on 17/03/19.
//

#ifndef OOP_ARCADE_2018_LIB_ARCADE_NCURSES_HPP
#define OOP_ARCADE_2018_LIB_ARCADE_NCURSES_HPP

#include <interfaces/IGames.hpp>
#include <map>
#include <interfaces/ILib.hpp>
#include <ncurses.h>



class lib_arcade_ncurses : public Lib::ILib {
public:
    lib_arcade_ncurses();
    ~lib_arcade_ncurses() override;
    lib_arcade_ncurses& operator=(const lib_arcade_ncurses& oldLib);
    void errorNcurses(std::string error);
    void displayWin(int frame) override;
    void destroyWin() override;
    Lib::inputKey bindKey() override;
    void bindColor() override;
    void drawPixel(float posx, float posy, Lib::colorDisplay color) override;
    void printText(Lib::t_Text &txt, Lib::colorDisplay color) override;
    void clearWin() override;
    void updateWin(float sec) override;
    void drawImage(std::string file) override;
    void loadImage(std::string file) override;
    void loadMusic(std::string file) override;
    void launchMusic() override;
    int _state;
protected:
    int sizex;
    int sizey;
private:
    WINDOW *_gameWin;
    std::string _name;
    short _height;
    short _widht;
    float _posx;
    float _posy;
    Lib::colorDisplay _colorD;
    int _color;
};

#endif //OOP_ARCADE_2018_LIB_ARCADE_NCURSES_HPP
