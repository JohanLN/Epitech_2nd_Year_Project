//
// Created by gurvan menguy on 17/03/19.
//

#ifndef OOP_ARCADE_2018_LIB_ARCADE_sfml_HPP
#define OOP_ARCADE_2018_LIB_ARCADE_sfml_HPP


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <map>
#include "interfaces/ILib.hpp"
#include "interfaces/IGames.hpp"

class lib_arcade_sfml : public Lib::ILib {
public:
    lib_arcade_sfml();
    ~lib_arcade_sfml() override;
    lib_arcade_sfml& operator=(const lib_arcade_sfml& oldLib);
    void errorsfml(std::string error);
    void displayWin(int frame) override;
    void destroyWin() override;
    Lib::inputKey bindKey() override;
    void bindColor() override;
    void drawPixel(float posx, float posy, Lib::colorDisplay color) override;
    void printText(Lib::t_Text &txt, Lib::colorDisplay color) override;
    void clearWin() override;
    void updateWin(float sec) override;
    void loadImage(std::string file) override;
    void drawImage(std::string file) override;
    void loadMusic(std::string file) override;
    void launchMusic() override;
protected:
    int sizex;
    int sizey;
private:
    sf::RenderWindow *_window;
    sf::Font _font;
    sf::Event _event;
    std::map<Lib::colorDisplay, sf::Color> _color;
    sf::Sprite _sprites;
    sf::Texture _texture;
    std::string _name;
    short _height;
    short _widht;
    float _posx;
    float _posy;
};

#endif //OOP_ARCADE_2018_LIB_ARCADE_sfml_HPP
