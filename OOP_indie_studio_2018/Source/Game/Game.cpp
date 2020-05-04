/*
** EPITECH PROJECT, 2019
** $NAME_OF_THE_PROJECT
** File description:
** No file there, just an epitech header example
*/

#include <iostream>
#include "Menu.hpp"
#include "EventReceiver.hpp"
#include "EventButton.hpp"
#include "Game.hpp"
#include "Map.hpp"

using namespace irrklang;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


Game::Game() {
    _counter = 0;
    _load = false;
    _update = false;
}

void Game::createBox(int posx, int posy)
{
    core::vector3df posBox = {float(posx), 100, float(posy)};

    irr::scene::IAnimatedMesh* box = _manager->getMesh("Resources/Media/bloc.obj");
    _node_box_tmp = _manager->addAnimatedMeshSceneNode(box);

    if (_node_box_tmp)
    {
        _node_box_tmp->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	    _node_box_tmp->setFrameLoop(0, 310);
        _node_box_tmp->setPosition(posBox);
        _node_box_tmp->setMaterialTexture(0, _driver->getTexture("Resources/Media/boite.png"));
        _node_box_tmp->setScale(irr::core::vector3df(100, 100, 100));
        _node_box.push_back(_node_box_tmp);
    }
}

void Game::createBoxUnbreakable(int posx, int posy)
{
    core::vector3df posBox = {float(posx), 100, float(posy)};

    irr::scene::IAnimatedMesh* box = _manager->getMesh("Resources/Media/bloc.obj");
    _node_box_tmp = _manager->addAnimatedMeshSceneNode(box);

    if (_node_box_tmp)
    {
        _node_box_tmp->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _node_box_tmp->setFrameLoop(0, 310);
        _node_box_tmp->setPosition(posBox);
        _node_box_tmp->setMaterialTexture(0, _driver->getTexture("Resources/Media/metal_bloc.png"));
        _node_box_tmp->setScale(irr::core::vector3df(100, 100, 100));
        _node_box.push_back(_node_box_tmp);
    }
}

void Game::initGame()
{
    _device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(\
1920, 1080), 16, false, false, false);

    if (!_device)
        return;

    _device->setWindowCaption(L"BOMBERMAN GAME !!");

    _driver = _device->getVideoDriver();
    _manager = _device->getSceneManager();
    _gui = _device->getGUIEnvironment();
    _engine = createIrrKlangDevice();

    


    SAppContext context;

    context.device = _device;
    context.driver = _driver;
    context.manager = _manager;
    context.gui = _gui;
    context.menu = _menu;
    context.game = this;
    EventButton eventButton(context);

    _device->setEventReceiver(&eventButton);
    coreGame(0);
}

bool Game::coreGame(int id)
{
    //Map map;

    while (_device->run()) {
        if (_device->isWindowActive()) {
            if (id == 0)
                _menu.setMainMenu(_device, _driver, _manager, _gui, _engine);
            if (id == 1)
                _menu.selectNbPlayer(_device, _driver, _manager, _gui);
            if (id == 2)
                _menu.selectCharacter(_device, _driver, _manager, _gui, 1);
            if (id == 3)
                _menu.selectCharacter(_device, _driver, _manager, _gui, 2);
            if (id == 4)
                _menu.selectCharacter(_device, _driver, _manager, _gui, 3);
            if (id == 5)
                _menu.selectCharacter(_device, _driver, _manager, _gui, 4);
            if (id == 6)
                setGame();
            if (id == 7)
                gamePause();
            if (id == 8)
                _menu.learnToPlay(_device, _driver, _manager, _gui);
        }
    }
    _engine->drop();
    _device->drop();
    exit(0);
}

void Game::setGame()
{
    //bool update = false;

    /*if (_load == false && _update == false) {
        _map.setPlayerNb(_nbPlayer);
        _map.generateProceduralMap(9, 11);
    }*/

    if (_load == false) {
        int y = 0;
        int x = 0;
        _camPos = {-900, 2000, 0};
        _camLook = {0, 0, 0};

        _manager->addCameraSceneNode(0, _camPos, _camLook);
        _device->getCursorControl()->setVisible(false);

        irr::scene::IAnimatedMesh* mesh = _manager->getMesh("Resources/Media/map.obj");
        _node_map = _manager->addAnimatedMeshSceneNode(mesh);
        _gui = _device->getGUIEnvironment();
        irr::video::ITexture* images = _driver->getTexture("Resources/Media/wallpapergame.jpg");
        _gui->addImage(images, irr::core::position2d<int>(0, 0));
        initCharacter();

        _map.setPlayerNb(_nbPlayer);
        if (_load == false && _update == false) {
            _map.generateProceduralMap(9, 11);
        }
        std::list<std::string> map2D = _map.getMap();
        for (auto &it : map2D) {
            for (char &c : it) {
                if (c == '1') {
                    createBoxUnbreakable(980 - (195 * y), 1000 - (250 * x));
                }
                if (c == '2') {
                    createBox(980 - (195 * y), 1000 - (250 * x));
                }
                x++;
            }
            y++;
            x = 0;
        }
        if (_node_map)
        {
            _node_map->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            _node_map->setFrameLoop(0, 310);
            _node_map->setMaterialTexture(0, _driver->getTexture("Resources/Media/terrain2.jpg"));
            _node_map->setMaterialTexture(0, _driver->getTexture("Resources/Media/terrain3.jpg"));
            _node_map->setScale(irr::core::vector3df(130, 130, 110));
        }
        _engine->stopAllSounds();
        _engine->play2D("Resources/Sound/derezzed.wav");
    }
    _load = true;
    _update = false;
    changeCameraView(_camPos, _camLook);
    manageCharacter(&_map);
    if (((EventButton *)_device->getEventReceiver())->IsKeyDown(KEY_ESCAPE)) {
        coreGame(7);
    }
    _driver->beginScene(true, true, video::SColor(0,0,0,0));
    _gui->drawAll();
    _manager->drawAll();
    _driver->endScene();
}

void Game::changeCameraView(core::vector3df cameraPos, core::vector3df cameraLook) {
    if (((EventButton *)_device->getEventReceiver())->IsKeyDown(KEY_F1)) {
        cameraPos = { -900, 2000, 0 };
        _manager->addCameraSceneNode(0, cameraPos, cameraLook);
    }
    if (((EventButton *)_device->getEventReceiver())->IsKeyDown(KEY_F2)) {
        cameraPos = { 0, 2000, 0 };
        _manager->addCameraSceneNode(0, cameraPos, cameraLook);
    }
    if (((EventButton *)_device->getEventReceiver())->IsKeyDown(KEY_F3)) {
        cameraPos = { 1000, 2000, 0 };
        _manager->addCameraSceneNode(0, cameraPos, cameraLook);
    }
}

Game::~Game()
{
    this->_engine->drop();
}

void Game::setNbPlayer(int nbPlayer) {
    _nbPlayer = nbPlayer;
}

void Game::setPlayerName(std::string name) {
    if (_counter == 0)
        _name1 = name;
    if (_counter == 1)
        _name2 = name;
    if (_counter == 2)
        _name3 = name;
    if (_counter == 3)
        _name4 = name;
    _counter++;
}

void Game::manageCharacter(Map *map) {
    if (_name1 == "Resources/Font/Normal2.png") {
        _player1N.movement(_device, _manager, _driver, map);
        _player1N.setPlayerAt();
    }
    if (_name2 == "Resources/Font/Normal2.png") {
        _player2N.movement(_device, _manager, _driver, map);
        _player2N.setPlayerAt();
    }
    if (_name3 == "Resources/Font/Normal2.png") {
        _player3N.movement(_device, _manager, _driver, map);
        _player3N.setPlayerAt();
    }
    if (_name4 == "Resources/Font/Normal2.png") {
        _player4N.movement(_device, _manager, _driver, map);
        _player4N.setPlayerAt();
    }
    if (_name1 == "Resources/Font/Adc2.png") {
        _player1A.movement(_device, _manager, _driver, map);
        _player1A.setPlayerAt();
    }
    if (_name2 == "Resources/Font/Adc2.png") {
        _player2A.movement(_device, _manager, _driver, map);
        _player2A.setPlayerAt();
    }
    if (_name3 == "Resources/Font/Adc2.png") {
        _player3A.movement(_device, _manager, _driver, map);
        _player3A.setPlayerAt();
    }
    if (_name4 == "Resources/Font/Adc2.png") {
        _player4A.movement(_device, _manager, _driver, map);
        _player4A.setPlayerAt();
    }
    if (_name1 == "Resources/Font/Rapido2.png") {
        _player1R.movement(_device, _manager, _driver, map);
        _player1R.setPlayerAt();
    }
    if (_name2 == "Resources/Font/Rapido2.png") {
        _player2R.movement(_device, _manager, _driver, map);
        _player2R.setPlayerAt();
    }
    if (_name3 == "Resources/Font/Rapido2.png") {
        _player3R.movement(_device, _manager, _driver, map);
        _player3R.setPlayerAt();
    }
    if (_name4 == "Resources/Font/Rapido2.png") {
        _player4R.movement(_device, _manager, _driver, map);
        _player4R.setPlayerAt();
    }
    if (_name1 == "Resources/Font/Tank2.png") {
        _player1T.movement(_device, _manager, _driver, map);
        _player1T.setPlayerAt();
    }
    if (_name2 == "Resources/Font/Tank2.png") {
        _player2T.movement(_device, _manager, _driver, map);
        _player2T.setPlayerAt();
    }
    if (_name3 == "Resources/Font/Tank2.png") {
        _player3T.movement(_device, _manager, _driver, map);
        _player3T.setPlayerAt();
    }
    if (_name4 == "Resources/Font/Tank2.png") {
        _player4T.movement(_device, _manager, _driver, map);
        _player4T.setPlayerAt();
    }
}

void Game::initCharacter() {
    if (_name1 == "Resources/Font/Normal2.png")
        _player1N.createMesh(_manager, _driver, _nbPlayer);
    if (_name2 == "Resources/Font/Normal2.png")
        _player2N.createMesh(_manager, _driver, _nbPlayer);
    if (_name3 == "Resources/Font/Normal2.png")
        _player3N.createMesh(_manager, _driver, _nbPlayer);
    if (_name4 == "Resources/Font/Normal2.png")
        _player4N.createMesh(_manager, _driver, _nbPlayer);
    if (_name1 == "Resources/Font/Adc2.png")
        _player1A.createMesh(_manager, _driver, _nbPlayer);
    if (_name2 == "Resources/Font/Adc2.png")
        _player2A.createMesh(_manager, _driver, _nbPlayer);
    if (_name3 == "Resources/Font/Adc2.png")
        _player3A.createMesh(_manager, _driver, _nbPlayer);
    if (_name4 == "Resources/Font/Adc2.png")
        _player4A.createMesh(_manager, _driver, _nbPlayer);
    if (_name1 == "Resources/Font/Rapido2.png")
        _player1R.createMesh(_manager, _driver, _nbPlayer);
    if (_name2 == "Resources/Font/Rapido2.png")
        _player2R.createMesh(_manager, _driver, _nbPlayer);
    if (_name3 == "Resources/Font/Rapido2.png")
        _player3R.createMesh(_manager, _driver, _nbPlayer);
    if (_name4 == "Resources/Font/Rapido2.png")
        _player4R.createMesh(_manager, _driver, _nbPlayer);
    if (_name1 == "Resources/Font/Tank2.png")
        _player1T.createMesh(_manager, _driver, _nbPlayer);
    if (_name2 == "Resources/Font/Tank2.png")
        _player2T.createMesh(_manager, _driver, _nbPlayer);
    if (_name3 == "Resources/Font/Tank2.png")
        _player3T.createMesh(_manager, _driver, _nbPlayer);
    if (_name4 == "Resources/Font/Tank2.png")
        _player4T.createMesh(_manager, _driver, _nbPlayer);
}

void Game::gamePause() {
    _gui->addImage(_driver->getTexture("Resources/Font/Pause.png"), position2di(800, 1080/2-150));
    _gui->addImage(_driver->getTexture("Resources/Font/Resume.png"), position2di(560, 1080/2));
    _gui->addImage(_driver->getTexture("Resources/Font/Menu.png"), position2di(500, 1080/2+100));
    _gui->addImage(_driver->getTexture("Resources/Font/Quit.png"), position2di(570, 1080/2+200));
    _engine->stopAllSounds();
    // _engine->play2D("Resources/Sound/hm-deep-cover.wav");
    if (((EventButton *)_device->getEventReceiver())->IsKeyDown(KEY_RETURN)) {
        _gui->clear();
        _gui->addImage(_driver->getTexture("Resources/Media/wallpapergame.jpg"), irr::core::position2d<int>(0, 0));
        coreGame(6);
    }
    if (((EventButton *)_device->getEventReceiver())->IsKeyDown(KEY_KEY_Q)) {
        _device->drop();
        exit(0);
    }
    
    _driver->beginScene(true, true, video::SColor(0,0,0,0));
    _gui->drawAll();
    _driver->endScene();
}

void Game::updateMap(Map map) {
    int x = 0;
    int y = 0;
    std::list<std::string> map2D = map.getMap();

    for (auto &it : map2D) {
        for (char &c : it) {
            if (c == '1') {
                createBoxUnbreakable(960 - (237 * x), 1180 - (237 * y));
            }
            if (c == '2') {
                createBox(960 - (237 * x), 1180 - (237 * y));
            }
            x++;
        }
        y++;
        x = 0;
    }
}

