//
// Created by jeremyquemener on 17/03/19.
//

#include <iostream>
#include <lib_arcade_allegro.hpp>

#include "lib_arcade_allegro.hpp"


lib_arcade_allegro::lib_arcade_allegro() : _name("allegro"), _height(1920),
                                           _widht(1080), _display(nullptr), _color(), _posx(), _posy() {
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    int size = 20;
    _font = al_load_font("../Retro.ttf", size, 0);
    if (!_font)
        errorAllegro("al_load_font");
}

lib_arcade_allegro::~lib_arcade_allegro() {
    al_uninstall_system();
}

lib_arcade_allegro& lib_arcade_allegro::operator=(const lib_arcade_allegro& oldLib) {
//    if (oldLib != this) {
        sizex = oldLib.sizex;
        sizey = oldLib.sizey;
        _name = oldLib._name;
        _height = oldLib._height;
        _widht = oldLib._widht;
        _display = oldLib._display;
        _eventKeyQ = oldLib._eventKeyQ;
        _eventWinQ = oldLib._eventWinQ;
        _event = oldLib._event;
        _bmp = oldLib._bmp;
        _color = oldLib._color;
        _font = oldLib._font;
        _key = oldLib._key;
        _posx = oldLib._posx;
        _posy = oldLib._posy;
        _colorD = oldLib._colorD;
        _Color = oldLib._Color;
//    }
    return *this;
}


void lib_arcade_allegro::errorAllegro(std::string error) {
    _display = al_is_system_installed() ? al_get_current_display() : nullptr;
    al_show_native_message_box(_display, "Error: ", error.c_str(), NULL, NULL, 0);
    exit(EXIT_FAILURE);
}

void lib_arcade_allegro::displayWin(int frame) {
    (void) frame;
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    _display = al_create_display(_height, _widht);
    al_set_window_title(_display, "Arcade");
    _eventKeyQ = al_create_event_queue();
    al_register_event_source(_eventKeyQ, al_get_keyboard_event_source());
    _eventWinQ = al_create_event_queue();
    al_register_event_source(_eventWinQ,
                             al_get_display_event_source(_display));
}

void lib_arcade_allegro::destroyWin() {
    al_destroy_bitmap(_bmp);
    al_destroy_display(_display);
    al_destroy_event_queue(_eventKeyQ);
    al_destroy_event_queue(_eventWinQ);
    exit(EXIT_SUCCESS);
}

Lib::inputKey lib_arcade_allegro::bindKey() {
    ALLEGRO_EVENT event;

    if (al_get_next_event(_eventWinQ, &event)
        && _event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return Lib::inputKey::QUIT_EVENT;
    if (al_get_next_event(_eventKeyQ, &event)) {
        switch (_event.keyboard.keycode) {
            case ALLEGRO_KEY_BACKSPACE :
                return Lib::inputKey::BACKSPACE;
            case ALLEGRO_KEY_ENTER :
                return Lib::inputKey::ENTER;
            case ALLEGRO_KEY_ESCAPE :
                return Lib::inputKey::ESCAPE;
            case ALLEGRO_KEY_UP :
                return Lib::inputKey::UP_KEY;
            case ALLEGRO_KEY_DOWN :
                return Lib::inputKey::DOWN_KEY;
            case ALLEGRO_KEY_LEFT :
                return Lib::inputKey::LEFT_KEY;
            case ALLEGRO_KEY_RIGHT :
                return Lib::inputKey::RIGHT_KEY;
            case ALLEGRO_KEY_A :
                return Lib::inputKey::A_KEY;
            case ALLEGRO_KEY_B :
                return Lib::inputKey::B_KEY;
            case ALLEGRO_KEY_C :
                return Lib::inputKey::C_KEY;
            case ALLEGRO_KEY_D :
                return Lib::inputKey::D_KEY;
            case ALLEGRO_KEY_E :
                return Lib::inputKey::E_KEY;
            case ALLEGRO_KEY_F :
                return Lib::inputKey::F_KEY;
            case ALLEGRO_KEY_G :
                return Lib::inputKey::G_KEY;
            case ALLEGRO_KEY_H :
                return Lib::inputKey::H_KEY;
            case ALLEGRO_KEY_I :
                return Lib::inputKey::I_KEY;
            case ALLEGRO_KEY_J :
                return Lib::inputKey::J_KEY;
            case ALLEGRO_KEY_K :
                return Lib::inputKey::K_KEY;
            case ALLEGRO_KEY_L :
                return Lib::inputKey::L_KEY;
            case ALLEGRO_KEY_M :
                return Lib::inputKey::M_KEY;
            case ALLEGRO_KEY_N :
                return Lib::inputKey::N_KEY;
            case ALLEGRO_KEY_O :
                return Lib::inputKey::O_KEY;
            case ALLEGRO_KEY_P :
                return Lib::inputKey::P_KEY;
            case ALLEGRO_KEY_Q :
                return Lib::inputKey::Q_KEY;
            case ALLEGRO_KEY_R :
                return Lib::inputKey::R_KEY;
            case ALLEGRO_KEY_S :
                return Lib::inputKey::S_KEY;
            case ALLEGRO_KEY_T :
                return Lib::inputKey::T_KEY;
            case ALLEGRO_KEY_U :
                return Lib::inputKey::U_KEY;
            case ALLEGRO_KEY_V :
                return Lib::inputKey::V_KEY;
            case ALLEGRO_KEY_W :
                return Lib::inputKey::W_KEY;
            case ALLEGRO_KEY_X :
                return Lib::inputKey::X_KEY;
            case ALLEGRO_KEY_Y :
                return Lib::inputKey::Y_KEY;
            case ALLEGRO_KEY_Z :
                return Lib::inputKey::Z_KEY;
            case ALLEGRO_KEY_F1 :
                return Lib::inputKey::KEY_F1;
            case ALLEGRO_KEY_F2 :
                return Lib::inputKey::KEY_F2;
            case ALLEGRO_KEY_F3 :
                return Lib::inputKey::KEY_F3;
            case ALLEGRO_KEY_F4 :
                return Lib::inputKey::KEY_F4;
            case ALLEGRO_KEY_F5 :
                return Lib::inputKey::KEY_F5;
            case ALLEGRO_KEY_F6 :
                return Lib::inputKey::KEY_F6;
            case ALLEGRO_KEY_F7 :
                return Lib::inputKey::KEY_F7;
            case ALLEGRO_KEY_F8 :
                return Lib::inputKey::KEY_F8;
            case ALLEGRO_KEY_F9 :
                return Lib::inputKey::KEY_F9;
            case ALLEGRO_KEY_F10 :
                return Lib::inputKey::KEY_F10;
            case ALLEGRO_KEY_F11 :
                return Lib::inputKey::KEY_F11;
            case ALLEGRO_KEY_F12 :
                return Lib::inputKey::KEY_F12;
            default:
                return Lib::NOIN;
        }
    }
    return Lib::NOIN;
}

void lib_arcade_allegro::bindColor() {
    _color.r = 255;
    _Color.emplace(Lib::colorDisplay::RED, _color);
    _color.g = 255;
    _Color.emplace(Lib::colorDisplay::YELLOW, _color);
    _color.b = 255;
    _Color.emplace(Lib::colorDisplay::WHITE, _color);
    _color.r = 0;
    _Color.emplace(Lib::colorDisplay::CYAN, _color);
    _color.g = 0;
    _Color.emplace(Lib::colorDisplay::BLUE, _color);
    _color.r = 255;
    _Color.emplace(Lib::colorDisplay::MAGENTA, _color);
    _color.r = 255;
    _color.b = 0;
    _color.g = 255;
    _Color.emplace(Lib::colorDisplay::GREEN, _color);
    _color.g = 255;
    _Color.emplace(Lib::colorDisplay::BLACK, _color);
}

void lib_arcade_allegro::drawPixel(float posx, float posy, Lib::colorDisplay color) {
    (void) color;
    al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
    _bmp = al_create_bitmap(sizex, sizey);
    if (!_bmp)
        errorAllegro("al_allegro_bitmap");
    al_set_target_bitmap(_bmp);
    al_clear_to_color(_color);
    al_put_pixel(sizex, sizey, _color);
    al_set_target_backbuffer(_display);
    al_draw_bitmap(_bmp ,posx, posy, 0);
}

void lib_arcade_allegro::printText(Lib::t_Text &txt, Lib::colorDisplay color) {
    if (!al_init_font_addon())
        errorAllegro("al_init_font_addon");
    al_draw_text(_font, _color, txt.posx, txt.posy, 0, txt.txt.c_str());
}

void lib_arcade_allegro::updateWin(float sec) {
    (void)sec;
    al_flip_display();
}

void lib_arcade_allegro::clearWin() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void lib_arcade_allegro::drawImage(std::string file) {
    (void)file;
}

void lib_arcade_allegro::loadImage(std::string file) {
    (void)file;
}

void lib_arcade_allegro::loadMusic(std::string file) {

}

void lib_arcade_allegro::launchMusic() {

}

extern "C" lib_arcade_allegro *entryPoint(void) {
    return new lib_arcade_allegro;
}

extern "C" void deletePoint(lib_arcade_allegro *ptr)
{
    delete ptr;
}