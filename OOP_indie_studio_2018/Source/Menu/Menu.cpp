//
// Created by jeremy-quemener on 10/06/19.
//

#include "Menu.hpp"
#include "EventButton.hpp"
#include "EventReceiver.hpp"
#include "irrKlang.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace irrklang;


Menu::Menu() {
    _skin = {"Resources/Media/player_white.png",
             "Resources/Media/player_black.png",
             "Resources/Media/player_blue.png",
             "Resources/Media/player_green.png",
             "Resources/Media/player_pink.png"};
    _name = {"Resources/Font/Normal2.png",
             "Resources/Font/Adc2.png",
             "Resources/Font/Rapido2.png",
             "Resources/Font/Tank2.png"};
    _load = false;
}

void Menu::setMainMenu(IrrlichtDevice *device, IVideoDriver *driver, ISceneManager *manager, IGUIEnvironment *gui, ISoundEngine* engine)
{
    if (_load == false) {
        gui->addImage(driver->getTexture("Resources/Media/source.png"), position2d<int>(0, 0));

        createButton(gui, driver, "Resources/Font/Play.png",
                     core::position2di(PLAY_POSX, PLAY_POSY),
                     core::dimension2di(PLAY_DIMX, PLAY_DIMY),
                     GUI_ID_PREGAME_BUTTON);
        createButton(gui, driver, "Resources/Font/LearnToPlay.png",
                     core::position2di(LTP_POSX, LTP_POSY),
                     core::dimension2di(LTP_DIMX, LTP_DIMY),
                     GUI_ID_LTP_BUTTON);
        createButton(gui, driver, "Resources/Font/QuitGame.png",
                     core::position2di(QUIT_POSX, QUIT_POSY),
                     core::dimension2di(QUIT_DIMX, QUIT_DIMY),
                     GUI_ID_QUIT_BUTTON);
        engine->stopAllSounds();
        engine->play2D("Resources/Sound/hm-deep-cover.wav");
    }
    _load = true;
    driver->beginScene(true, true, video::SColor(0,0,0,255));
    gui->drawAll();
    driver->endScene();
}

void Menu::createButton(gui::IGUIEnvironment *gui, video::IVideoDriver* driver, std::string fontPath, core::position2di pos, core::dimension2di dim, int id)
{
    ITexture* Font = driver->getTexture(fontPath.c_str());

    gui->addImage(Font, pos);
    gui::IGUIButton *button = gui->addButton(core::rect<s32>(pos, dim), 0,
            id,0, 0);
    button->setDrawBorder(false);
}


void Menu::selectCharacter(IrrlichtDevice *device, IVideoDriver *driver, ISceneManager *manager, IGUIEnvironment *gui, int nbPlayer)
{
    if (_load == false) {
        gui->addImage(driver->getTexture("Resources/Media/source.png"),
                      position2d<int>(0, 0));

        _character = manager->addAnimatedMeshSceneNode(
                manager->getMesh("Resources/Media/player_idle.md2"));

        core::vector3df cameraPos = { -700, 200, 0 };
        core::vector3df cameraLook = { 0, 380, 0 };

        manager->addCameraSceneNode(0, cameraPos, cameraLook);

        _character->setMaterialFlag(video::EMF_LIGHTING, false);
        _character->setMaterialTexture(0,
                                      driver->getTexture(_skin[0].c_str()));
        _character->setScale(core::vector3df(1, 1, 1));
        createButton(gui, driver, _name[0], core::position2di(500, 90),
                     core::dimension2di(0, 0), 0);
        createButton(gui, driver, "Resources/Font/Enter.png",
                     core::position2di(1920 / 2 - 220, 1080 - 150),
                     core::dimension2di(0, 0), 0);
        createButton(gui, driver, "Resources/Font/P1.png",
                     core::position2di(0, 0), core::dimension2di(0, 0), 0);
        _nbPlayer = nbPlayer;
    }
    _load = true;
    static float i = 0;
    static int j = 0;
    static int check = 0;

    if (((EventButton *)device->getEventReceiver())->IsKeyDown(KEY_RIGHT)) {
        j++;
        if (j > 3)
            j = 0;
        device->sleep(100);
        _character->setMaterialTexture(0, driver->getTexture(
                _skin[j].c_str()));
        createButton(gui, driver, _name[j], core::position2di(500, 90), core::dimension2di(0, 0), 0);
    }
    if (((EventButton *)device->getEventReceiver())->IsKeyDown(KEY_LEFT)) {
        j--;
        if (j < 0)
            j = 3;
        device->sleep(100);
        _character->setMaterialTexture(0, driver->getTexture(
                _skin[j].c_str()));
        createButton(gui, driver, _name[j], core::position2di(500, 90), core::dimension2di(0, 0), 0);
    }
    if (((EventButton *)device->getEventReceiver())->IsKeyDown(KEY_RETURN)) {
        check++;
        device->sleep(100);
        ((EventButton *)device->getEventReceiver())->Context.game->setPlayerName(_name[j]);
        if (check == 1)
            createButton(gui, driver, "Resources/Font/P2.png", core::position2di(200, 0), core::dimension2di(0, 0), 0);
        if (check == 2)
            createButton(gui, driver, "Resources/Font/P3.png", core::position2di(400, 0), core::dimension2di(0, 0), 0);
        if (check == 3)
            createButton(gui, driver, "Resources/Font/P4.png", core::position2di(600, 0), core::dimension2di(0, 0), 0);
        if (check == _nbPlayer) {
            manager->clear();
            gui->clear();
            _load = false;
            check = 0;
            ((EventButton *)device->getEventReceiver())->Context.game->setNbPlayer(_nbPlayer);
            _nbPlayer = 0;
            j = 0;
            i = 0;
            ((EventButton *)device->getEventReceiver())->Context.game->coreGame(6);
        }
    }
    if (((EventButton *)device->getEventReceiver())->IsKeyDown(KEY_ESCAPE)) {
        manager->clear();
        _load = true;
        check = 0;
        _nbPlayer = 0;
        j = 0;
        i = 0;
        ((EventButton *)device->getEventReceiver())->Context.game->coreGame(1);
    }
    _character->setRotation(core::vector3df(0, i, 0));
    driver->beginScene(true, true, video::SColor(0,0,0,0));
    gui->drawAll();
    manager->drawAll();
    driver->endScene();
    i++;
}

void Menu::selectNbPlayer(IrrlichtDevice *device, IVideoDriver *driver, ISceneManager *manager, IGUIEnvironment *gui)
{
    if (_load == true) {
        gui->addImage(driver->getTexture("Resources/Media/source.png"),
                      position2d<int>(0, 0));

        createButton(gui, driver, "Resources/Font/Nbplayer.png",
                     core::position2di(50, PLAY_POSY),
                     core::dimension2di(0, 0), 0);
        createButton(gui, driver, "Resources/Font/P1.png",
                     core::position2di(550, PLAY_POSY + 250),
                     core::dimension2di(185, 150), GUI_ID_P1_BUTTON);
        createButton(gui, driver, "Resources/Font/P2.png",
                     core::position2di(750, PLAY_POSY + 250),
                     core::dimension2di(185, 150), GUI_ID_P2_BUTTON);
        createButton(gui, driver, "Resources/Font/P3.png",
                     core::position2di(950, PLAY_POSY + 250),
                     core::dimension2di(185, 150), GUI_ID_P3_BUTTON);
        createButton(gui, driver, "Resources/Font/P4.png",
                     core::position2di(1150, PLAY_POSY + 250),
                     core::dimension2di(185, 150), GUI_ID_P4_BUTTON);
        createButton(gui, driver, "Resources/Font/return.png",
                     core::position2di(50, 50), core::dimension2di(100, 100),
                     GUI_ID_RETURN_NBPLAYER_BUTTON);
    }
    _load = false;
    driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
    gui->drawAll();
    driver->endScene();
}

void Menu::learnToPlay(IrrlichtDevice *device, IVideoDriver *driver, ISceneManager *manager, IGUIEnvironment *gui)
{
    if (_load == true) {
        gui->addImage(driver->getTexture("Resources/Media/source.png"),
                      position2d<int>(0, 0));
        gui->addImage(driver->getTexture("Resources/Media/keymap.png"),
                      position2d<int>(550, 350));
        createButton(gui, driver, "Resources/Font/return.png",
                      position2di(50, 50), dimension2di(100, 100),
                     GUI_ID_RETURN_NBPLAYER_BUTTON);
    }
    _load = false;
    driver->beginScene(true, true, video::SColor(0,0,0,255));
    gui->drawAll();
    driver->endScene();
}

Menu::~Menu() = default;
