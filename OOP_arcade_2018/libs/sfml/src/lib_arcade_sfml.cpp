//
// Created by gurvan menguy on 17/03/19.
//

#include <iostream>
#include "../include/lib_arcade_sfml.hpp"

lib_arcade_sfml::lib_arcade_sfml() {
    _font.loadFromFile("libs/Retro.ttf");
    bindColor();
}

lib_arcade_sfml::~lib_arcade_sfml() = default;

lib_arcade_sfml& lib_arcade_sfml::operator=(const lib_arcade_sfml& oldLib)
{
//    if (oldLib != this) {
        sizex = oldLib.sizex;
        sizey = oldLib.sizey;
        _window = oldLib._window;
        _font = oldLib._font;
        _event = oldLib._event;
        _color = oldLib._color;
        _name = oldLib._name;
        _height = oldLib._height;
        _widht = oldLib._widht;
        _posx = oldLib._posx;
        _posy = oldLib._posy;
//    }
    return *this;
}


void lib_arcade_sfml::errorsfml(std::string error) {
    std::cerr << error << std::endl;
    exit(EXIT_FAILURE);
}

void lib_arcade_sfml::displayWin(int frame) {
    (void)frame;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "arcade");
    _window->setFramerateLimit(6);
    _window->display();
}

void lib_arcade_sfml::destroyWin() {
    _window->close();
}

Lib::inputKey lib_arcade_sfml::bindKey() {

    if (!_window->isOpen()) {
        _window->close();
        exit(1);
    }
    _window->pollEvent(_event);
    if (_event.type == sf::Event::Closed) {
        _window->close();
        exit(1);
    }
    if (_event.type != sf::Event::KeyPressed)
        return (Lib::NOIN);
    switch (_event.key.code)
    {
        case sf::Keyboard::Escape :
            return (Lib::inputKey::ESCAPE);
        case sf::Keyboard::BackSpace :
            return (Lib::inputKey::BACKSPACE);
        case sf::Keyboard::Return :
            return (Lib::inputKey::ENTER);
        case sf::Keyboard::Up :
            return Lib::inputKey::UP_KEY;
        case sf::Keyboard::Down :
            return Lib::inputKey::DOWN_KEY;
        case sf::Keyboard::Left :
            return Lib::inputKey::LEFT_KEY;
        case sf::Keyboard::Right :
            return Lib::inputKey::RIGHT_KEY;
        case sf::Keyboard::A :
            return Lib::inputKey::A_KEY;
        case sf::Keyboard::B :
            return Lib::inputKey::B_KEY;
        case sf::Keyboard::C :
            return Lib::inputKey::C_KEY;
        case sf::Keyboard::D :
            return Lib::inputKey::D_KEY;
        case sf::Keyboard::E :
            return Lib::inputKey::E_KEY;
        case sf::Keyboard::F :
            return Lib::inputKey::F_KEY;
        case sf::Keyboard::G :
            return Lib::inputKey::G_KEY;
        case sf::Keyboard::H :
            return Lib::inputKey::H_KEY;
        case sf::Keyboard::I :
            return Lib::inputKey::I_KEY;
        case sf::Keyboard::J :
            return Lib::inputKey::J_KEY;
        case sf::Keyboard::K :
            return Lib::inputKey::K_KEY;
        case sf::Keyboard::L :
            return Lib::inputKey::L_KEY;
        case sf::Keyboard::M :
            return Lib::inputKey::M_KEY;
        case sf::Keyboard::N :
            return Lib::inputKey::N_KEY;
        case sf::Keyboard::O :
            return Lib::inputKey::O_KEY;
        case sf::Keyboard::P :
            return Lib::inputKey::P_KEY;
        case sf::Keyboard::Q :
            return Lib::inputKey::Q_KEY;
        case sf::Keyboard::R :
            return Lib::inputKey::R_KEY;
        case sf::Keyboard::S :
            return Lib::inputKey::S_KEY;
        case sf::Keyboard::T :
            return Lib::inputKey::T_KEY;
        case sf::Keyboard::U :
            return Lib::inputKey::U_KEY;
        case sf::Keyboard::V :
            return Lib::inputKey::V_KEY;
        case sf::Keyboard::W :
            return Lib::inputKey::W_KEY;
        case sf::Keyboard::X :
            return Lib::inputKey::X_KEY;
        case sf::Keyboard::Y :
            return Lib::inputKey::Y_KEY;
        case sf::Keyboard::Z :
            return Lib::inputKey::Z_KEY;
        case sf::Keyboard::F1 :
            return Lib::inputKey::KEY_F1;
        case sf::Keyboard::F2 :
            return Lib::inputKey::KEY_F2;
        case sf::Keyboard::F3 :
            return Lib::inputKey::KEY_F3;
        case sf::Keyboard::F4 :
            return Lib::inputKey::KEY_F4;
        case sf::Keyboard::F5 :
            return Lib::inputKey::KEY_F5;
        case sf::Keyboard::F6 :
            return Lib::inputKey::KEY_F6;
        case sf::Keyboard::F7 :
            return Lib::inputKey::KEY_F7;
        case sf::Keyboard::F8 :
            return Lib::inputKey::KEY_F8;
        case sf::Keyboard::F9 :
            return Lib::inputKey::KEY_F9;
        case sf::Keyboard::F10 :
            return Lib::inputKey::KEY_F10;
        case sf::Keyboard::F11 :
            return Lib::inputKey::KEY_F11;
        case sf::Keyboard::F12 :
            return Lib::inputKey::KEY_F12;
        default:
            return Lib::inputKey::NOIN;
    }
    return Lib::inputKey::NOIN;
}

void lib_arcade_sfml::bindColor() {
    _color.emplace(Lib::colorDisplay::RED, sf::Color::Red);
    _color.emplace(Lib::colorDisplay::GREEN, sf::Color::Green);
    _color.emplace(Lib::colorDisplay::BLUE, sf::Color::Blue);
    _color.emplace(Lib::colorDisplay::BLACK, sf::Color::Black);
    _color.emplace(Lib::colorDisplay::WHITE, sf::Color::White);
    _color.emplace(Lib::colorDisplay::YELLOW, sf::Color::Yellow);
    _color.emplace(Lib::colorDisplay::MAGENTA, sf::Color::Magenta);
    _color.emplace(Lib::colorDisplay::CYAN, sf::Color::Cyan);
}

void lib_arcade_sfml::drawPixel(float posx, float posy, Lib::colorDisplay color) {
    sf::RectangleShape rectangle;

    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setFillColor(_color[color]);
    rectangle.setPosition(posx * 20, posy * 20);
    _window->draw(rectangle);
}

void lib_arcade_sfml::printText(Lib::t_Text &txt, Lib::colorDisplay color) {
    auto *text = new sf::Text;

    text->setFont(_font);
    text->setCharacterSize((unsigned int) 20);
    text->setFillColor(_color[color]);
    text->setString(txt.txt);
    text->setPosition(txt.posx * 20, txt.posy * 20);
    _window->draw(*text);
}

void lib_arcade_sfml::clearWin() {
    _window->clear(sf::Color::Black);
}

void lib_arcade_sfml::updateWin(float sec) {
    if (!_window->isOpen())
        _window->close();

    if (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window->close();
            exit(1);
        }
    }
    (void)sec;

    _window->display();
    _window->clear(sf::Color::Black);
}

void lib_arcade_sfml::drawImage(std::string file) {
    (void)file;

    _window->draw(_sprites);
}

void lib_arcade_sfml::loadImage(std::string file) {
    if (!_texture.loadFromFile(file))
    {
        std::cerr << "Error with the file : " + file << std::endl;
        return;
    }

    _sprites.setTexture(_texture);
    _sprites.setPosition(sf::Vector2f(0, 0));
}

void lib_arcade_sfml::loadMusic(std::string file) {
    (void)file;
}

void lib_arcade_sfml::launchMusic() {

}

extern "C" lib_arcade_sfml *entryPoint(void) {
    return new lib_arcade_sfml;
}

extern "C" void deletePoint(lib_arcade_sfml *ptr)
{
    delete ptr;
}
