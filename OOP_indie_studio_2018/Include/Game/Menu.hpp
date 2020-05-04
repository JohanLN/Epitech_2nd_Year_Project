//
// Created by jeremy-quemener on 10/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_MENU_HPP
#define OOP_INDIE_STUDIO_2018_MENU_HPP


#include <string>
#include <irrlicht.h>
#include <vector>
#include <irrKlang.h>
#include "EventReceiver.hpp"

#define PLAY_POSX 1920/2 - 190
#define PLAY_POSY 1080/2 - 150
#define PLAY_DIMX 350
#define PLAY_DIMY 120

#define LTP_POSX 1920/2 - 500
#define LTP_POSY 1080/2 + 50
#define LTP_DIMX 1000
#define LTP_DIMY 120

#define QUIT_POSX 1920/2 - 370
#define QUIT_POSY 1080/2 + 250
#define QUIT_DIMX 800
#define QUIT_DIMY 120


using namespace irr;

class Menu {
public:
    Menu();
    ~Menu();

    void setMainMenu(IrrlichtDevice *device, video::IVideoDriver *driver, scene::ISceneManager *manager, gui::IGUIEnvironment *gui, irrklang::ISoundEngine* engine);
    void createButton(gui::IGUIEnvironment *gui, video::IVideoDriver* driver, std::string fontPath, core::position2di pos, core::dimension2di dim, int id);
    void selectCharacter(IrrlichtDevice *device, video::IVideoDriver *driver, scene::ISceneManager *manager, gui::IGUIEnvironment *gui, int nbPlayer);
    void selectNbPlayer(IrrlichtDevice *device, video::IVideoDriver *driver, scene::ISceneManager *manager, gui::IGUIEnvironment *gui);
    void learnToPlay(IrrlichtDevice *device, video::IVideoDriver *driver, scene::ISceneManager *manager, gui::IGUIEnvironment *gui);
private:
    int _nbPlayer;
    bool _load;
    std::string _Play;
    std::string _Options;
    std::string _Quit;
    std::vector<std::string> _skin;
    std::vector<std::string> _name;
    scene::IAnimatedMeshSceneNode *_character;
};


#endif //OOP_INDIE_STUDIO_2018_MENU_HPP
