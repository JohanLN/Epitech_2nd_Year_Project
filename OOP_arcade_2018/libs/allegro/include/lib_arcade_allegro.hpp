//
// Created by jeremyquemener on 17/03/19.
//

#ifndef OOP_ARCADE_2018_LIB_ARCADE_ALLEGRO_HPP
#define OOP_ARCADE_2018_LIB_ARCADE_ALLEGRO_HPP

#include <interfaces/IGames.hpp>
#include <map>
#include <interfaces/ILib.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>



class lib_arcade_allegro : public Lib::ILib {
public:
    lib_arcade_allegro();
    ~lib_arcade_allegro() override;
    lib_arcade_allegro& operator=(const lib_arcade_allegro& oldLib);
    void errorAllegro(std::string error);
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
protected:
    int sizex;
    int sizey;
private:
    std::string _name;
    short _height;
    short _widht;
    ALLEGRO_DISPLAY *_display;
    ALLEGRO_EVENT_QUEUE *_eventKeyQ;
    ALLEGRO_EVENT_QUEUE *_eventWinQ;
    ALLEGRO_EVENT _event;
    ALLEGRO_BITMAP* _bmp;
    ALLEGRO_COLOR _color;
    ALLEGRO_FONT *_font;
    ALLEGRO_KEYBOARD_STATE _key;
    float _posx;
    float _posy;
    Lib::colorDisplay _colorD;
    std::map<Lib::colorDisplay, ALLEGRO_COLOR>_Color;
};

#endif //OOP_ARCADE_2018_LIB_ARCADE_ALLEGRO_HPP
