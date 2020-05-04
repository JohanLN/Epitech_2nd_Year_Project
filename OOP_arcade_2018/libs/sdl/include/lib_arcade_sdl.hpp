//
// Created by jeremyquemener on 17/03/19.
//

#ifndef OOP_ARCADE_2018_LIB_ARCADE_sdl_HPP
#define OOP_ARCADE_2018_LIB_ARCADE_sdl_HPP

#include <interfaces/IGames.hpp>
#include <map>
#include <interfaces/ILib.hpp>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <unordered_map>
#include <SDL2/SDL_mixer.h>

class lib_arcade_sdl : public Lib::ILib {
public:
    lib_arcade_sdl();
    ~lib_arcade_sdl() override;
    lib_arcade_sdl& operator=(const lib_arcade_sdl& oldLib);
    void errorsdl(std::string error);
    void displayWin(int frame) override;
    void destroyWin() override;
    Lib::inputKey bindKey() override;
    void bindColor() override;
    void drawPixel(float posx, float posy, Lib::colorDisplay color) override;
    void printText(Lib::t_Text &txt, Lib::colorDisplay color) override;
    void clearWin() override;
    void updateWin(float sec) override;
    void set_sizeTTF(short _sizeTTF);
    short get_sizeTTF() const;
    void drawImage(std::string file) override;
    void loadImage(std::string file) override;
    void loadMusic(std::string file) override;
    void launchMusic() override;
protected:
    int sizex;
    int sizey;
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    SDL_Rect _pixel;
    TTF_Font *_font;
    SDL_Surface *_surface;
    SDL_Texture *_texture;
    bool _exit;
    short _height;
    short _widht;
    float _posx;
    float _posy;
    short _sizeTTF;
    SDL_Surface *_image;
    SDL_Texture *_imageTexture;
    SDL_AudioDeviceID _deviceId;
    Uint8 *_wavBuffer;

    std::map<Lib::colorDisplay, std::array<unsigned char, 3>> _color;
};

#endif //OOP_ARCADE_2018_LIB_ARCADE_sdl_HPP
