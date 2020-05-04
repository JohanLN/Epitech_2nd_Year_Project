//
// Created by jeremyquemener on 17/03/19.
//

#include <iostream>
#include "lib_arcade_sdl.hpp"

lib_arcade_sdl::lib_arcade_sdl() : sizex(20), sizey(20), _window(nullptr), _renderer(nullptr), _font(
        nullptr), _surface(nullptr), _texture(nullptr) ,_sizeTTF(20) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        errorsdl("Fail SDL init");
        exit(84);
    }
    bindColor();
    if(TTF_Init() != 0) {
        errorsdl("Fail TTF init");
        exit(84);
    }
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        errorsdl("Fail Init Audio");
        exit (84);
    }
    _font = TTF_OpenFont("libs/Retro.ttf", 20);
}

lib_arcade_sdl::~lib_arcade_sdl() {
    SDL_DestroyTexture(_imageTexture);
    SDL_FreeSurface(_surface);
    SDL_FreeSurface(_image);
    TTF_CloseFont(_font);
    SDL_FreeWAV(_wavBuffer);
    TTF_Quit();
    SDL_Quit();
    //destroyWin();
}

lib_arcade_sdl& lib_arcade_sdl::operator=(const lib_arcade_sdl& oldLib)
{
 //   if (oldLib != this) {
        sizex = oldLib.sizex;
        sizey = oldLib.sizey;
        _window = oldLib._window;
        _renderer = oldLib._renderer;
        _pixel = oldLib._pixel;
        _font = oldLib._font;
        _surface = oldLib._surface;
        _texture = oldLib._texture;
        _exit = oldLib._exit;
        _height = oldLib._height;
        _widht = oldLib._widht;
        _posx = oldLib._posx;
        _posy = oldLib._posy;
        _sizeTTF = oldLib._sizeTTF;
        _image = oldLib._image;
        _imageTexture = oldLib._imageTexture;
        _color = oldLib._color;
 //   }
    return *this;
}


void lib_arcade_sdl::errorsdl(std::string error) {
    std::cerr << error << std::endl;
    exit(EXIT_FAILURE);
}

void lib_arcade_sdl::displayWin(int frame) {
    (void)frame;
    _widht = 1920;
    _height = 1080;
    _exit = false;

    SDL_CreateWindowAndRenderer(_widht, _height, SDL_WINDOW_RESIZABLE, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "Arcade SDL2");
}

void lib_arcade_sdl::destroyWin() {
    _exit = true;
    SDL_DestroyWindow(_window);
    _window = nullptr;
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    SDL_CloseAudioDevice(_deviceId);
}

Lib::inputKey lib_arcade_sdl::bindKey() {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT)
            return (Lib::inputKey::QUIT_EVENT);
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT :
                    return Lib::inputKey::RIGHT_KEY;
                case SDLK_LEFT :
                    return Lib::inputKey::LEFT_KEY;
                case SDLK_DOWN :
                    return Lib::inputKey::DOWN_KEY;
                case SDLK_UP :
                    return Lib::inputKey::UP_KEY;
                case SDLK_ESCAPE :
                    return Lib::inputKey::ESCAPE;
                case SDLK_BACKSPACE :
                    return Lib::inputKey::BACKSPACE;
                case SDLK_RETURN :
                    return Lib::inputKey::ENTER;
                case SDLK_SPACE :
                    return Lib::inputKey::SPACE;
                case SDLK_a :
                    return Lib::inputKey::A_KEY;
                case SDLK_b :
                    return Lib::inputKey::B_KEY;
                case SDLK_c :
                    return Lib::inputKey::C_KEY;
                case SDLK_d :
                    return Lib::inputKey::D_KEY;
                case SDLK_e :
                    return Lib::inputKey::E_KEY;
                case SDLK_f :
                    return Lib::inputKey::F_KEY;
                case SDLK_g :
                    return Lib::inputKey::G_KEY;
                case SDLK_h :
                    return Lib::inputKey::H_KEY;
                case SDLK_i :
                    return Lib::inputKey::I_KEY;
                case SDLK_j :
                    return Lib::inputKey::J_KEY;
                case SDLK_k :
                    return Lib::inputKey::K_KEY;
                case SDLK_l :
                    return Lib::inputKey::L_KEY;
                case SDLK_m :
                    return Lib::inputKey::M_KEY;
                case SDLK_n :
                    return Lib::inputKey::N_KEY;
                case SDLK_o :
                    return Lib::inputKey::O_KEY;
                case SDLK_p :
                    return Lib::inputKey::P_KEY;
                case SDLK_q :
                    return Lib::inputKey::Q_KEY;
                case SDLK_r :
                    return Lib::inputKey::R_KEY;
                case SDLK_s :
                    return Lib::inputKey::S_KEY;
                case SDLK_t :
                    return Lib::inputKey::T_KEY;
                case SDLK_u :
                    return Lib::inputKey::U_KEY;
                case SDLK_v :
                    return Lib::inputKey::V_KEY;
                case SDLK_w :
                    return Lib::inputKey::W_KEY;
                case SDLK_x :
                    return Lib::inputKey::X_KEY;
                case SDLK_y :
                    return Lib::inputKey::Y_KEY;
                case SDLK_z :
                    return Lib::inputKey::Z_KEY;
                case SDLK_F1 :
                    return Lib::inputKey::KEY_F1;
                case SDLK_F2 :
                    return Lib::inputKey::KEY_F2;
                case SDLK_F3 :
                    return Lib::inputKey::KEY_F3;
                case SDLK_F4 :
                    return Lib::inputKey::KEY_F4;
                case SDLK_F5 :
                    return Lib::inputKey::KEY_F5;
                case SDLK_F6 :
                    return Lib::inputKey::KEY_F6;
                case SDLK_F7 :
                    return Lib::inputKey::KEY_F7;
                case SDLK_F8 :
                    return Lib::inputKey::KEY_F8;
                case SDLK_F9 :
                    return Lib::inputKey::KEY_F9;
                case SDLK_F10 :
                    return Lib::inputKey::KEY_F10;
                case SDLK_F11 :
                    return Lib::inputKey::KEY_F11;
                case SDLK_F12 :
                    return Lib::inputKey::KEY_F12;
                default :
                    return Lib::inputKey::NOIN;
            }
        }
    }
    return Lib::inputKey::NOIN;
}

short lib_arcade_sdl::get_sizeTTF() const {
    return _sizeTTF;
}


void lib_arcade_sdl::bindColor() {
    _color.emplace(Lib::colorDisplay::RED, std::array<unsigned char,3 >{255, 0, 0});
    _color.emplace(Lib::colorDisplay::GREEN, std::array<unsigned char,3 >{0, 255, 0});
    _color.emplace(Lib::colorDisplay::BLUE, std::array<unsigned char,3 >{0, 0, 255});
    _color.emplace(Lib::colorDisplay::BLACK, std::array<unsigned char,3 >{0, 0, 0});
    _color.emplace(Lib::colorDisplay::WHITE, std::array<unsigned char,3 >{255, 255, 255});
    _color.emplace(Lib::colorDisplay::YELLOW, std::array<unsigned char,3 >{255, 255, 0});
    _color.emplace(Lib::colorDisplay::MAGENTA, std::array<unsigned char,3 >{255, 0, 255});
    _color.emplace(Lib::colorDisplay::CYAN, std::array<unsigned char,3 >{0, 255, 255});
}

void lib_arcade_sdl::drawPixel(float posx, float posy, Lib::colorDisplay color) {
    (void)color;
    _pixel.x = static_cast<int>(posx) * 20;
    _pixel.y = static_cast<int>(posy) * 20;
    _pixel.w = sizex;
    _pixel.h = sizey;

    SDL_SetRenderDrawColor(_renderer, _color[color][0], _color[color][1], _color[color][2], 255);
    SDL_RenderFillRect(_renderer, &_pixel);
}

void lib_arcade_sdl::set_sizeTTF(short _sizeTTF) {
    lib_arcade_sdl::_sizeTTF = _sizeTTF;
}

void lib_arcade_sdl::printText(Lib::t_Text &txt, Lib::colorDisplay color) {
    SDL_Color colorText = {_color[color][0], _color[color][1], _color[color][2], 255};
    _surface = TTF_RenderText_Blended(_font, txt.txt.c_str(), colorText);
    _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
    int txtW = 100;
    int txtH = 100;
    int x = txt.posx * 20;
    int y = txt.posy * 20;
    SDL_QueryTexture(_texture, NULL, NULL, &txtW, &txtH);
    SDL_Rect dstrect = {x, y, txtW, txtH};
    SDL_RenderCopy(_renderer, _texture, NULL, &dstrect);
}

void lib_arcade_sdl::clearWin() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void lib_arcade_sdl::updateWin(float sec) {
    SDL_Delay(static_cast<Uint32>(sec * 1000));
    SDL_RenderPresent(_renderer);
}

void lib_arcade_sdl::drawImage(std::string file) {
    (void)file;
    SDL_RenderCopy(_renderer, _imageTexture, NULL, NULL);
}

void lib_arcade_sdl::loadImage(std::string file) {
    if (file.empty())
        errorsdl("Error load image");
    _image = IMG_Load(file.c_str());
    _imageTexture = SDL_CreateTextureFromSurface(_renderer, _image);
}

void lib_arcade_sdl::loadMusic(std::string file) {
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;

    SDL_LoadWAV(file.c_str(), &wavSpec, &_wavBuffer, &wavLength);
    SDL_AudioDeviceID _deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    SDL_QueueAudio(_deviceId, _wavBuffer, wavLength);
    SDL_PauseAudioDevice(_deviceId, 0);
}

void lib_arcade_sdl::launchMusic() {

}

extern "C" lib_arcade_sdl *entryPoint(void) {
    return new lib_arcade_sdl;
}

extern "C" void deletePoint(lib_arcade_sdl *ptr)
{
    delete ptr;
}
