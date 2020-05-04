/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** RandomPlayer
*/

#include <iostream>
#include <Character/RandomPlayer.hpp>

#include "RandomPlayer.hpp"
#include "EventReceiver.hpp"
#include <iostream>
#include <unistd.h>
#include <ITimer.h>
#include <chrono>
#include <thread>
#include "EventButton.hpp"

RandomPlayer::RandomPlayer(std::string playerNb, int x, int y) : ACharacter("RandomPlayer", x, y)
{
    _playerNb = playerNb;
    _playerPos = {(float)x,0,(float)y};
    _playerPosTmp = {(float)x,0,(float)y};
    _bombPos = {(float)x,0,(float)y};
    _rotation = {0,0,0};
    _scale = {1,1,1};
    _bombType = new Bomb("Petite", x, y);
    _bombs = 3;
    _hp = 1;
    _shield = 0;
    _checkBomb = false;
    _checkParticule = false;
}

void RandomPlayer::particulesExplosion(scene::ISceneManager *manager, video::IVideoDriver *driver)
{
    _playerPosTmp = _bombPos;

    int range = _bombType->getRange();

    for (int i = 0; i != range; i++) {
        _playerPosTmp.X -= 250;
        if (_playerPosTmp.X > -1000)
            setParticlesExplosion("Resources/Media/terrain3.jpg", _playerPosTmp, manager, driver);
    }
    _playerPosTmp = _bombPos;
    for (int i = 0; i != range; i++) {
        _playerPosTmp.X += 250;
        if (_playerPosTmp.X < 1000)
            setParticlesExplosion("Resources/Media/terrain3.jpg", _playerPosTmp, manager, driver);
    }
    _playerPosTmp = _bombPos;
    for (int i = 0; i != range; i++) {
        _playerPosTmp.Z -= 195;
        if (_playerPosTmp.Z > -980)
            setParticlesExplosion("Resources/Media/terrain3.jpg", _playerPosTmp, manager, driver);
    }
    _playerPosTmp = _bombPos;
    for (int i = 0; i != range; i++) {
        _playerPosTmp.Z += 195;
        if (_playerPosTmp.Z < 980)
            setParticlesExplosion("Resources/Media/terrain3.jpg", _playerPosTmp, manager, driver);
    }
}

bool RandomPlayer::timeBeforeExplode()
{
    auto moment = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = moment - _start;

    if (elapsedTime.count() > 3)
        return (1);
    return (0);
}


bool RandomPlayer::timeBeforeMove()
{
    auto moment = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = moment - _start;

    if (elapsedTime.count() > 3)
        return (1);
    return (0);
}


bool RandomPlayer::timeBeforeParticules()
{
    auto moment = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = moment - _start;

    if (elapsedTime.count() > 5)
        return (1);
    return (0);
}

bool RandomPlayer::moveTop(Map *map, bool check)
{
    _mesh->setVisible(false);
    _run->setVisible(true);
    usleep(100000);
    _tmp.X = getPlayePos().X + 195;
    _tmp.Y = getPlayePos().Y;
    _tmp.Z = getPlayePos().Z;
    setPlayerPos(_tmp);
    check = true;
    _rotation.Y = 180;
    if (_playerPos.X >= 980) {
        _playerPos.X -= 195;
    }
    if (check == true)
        run();
    return (check);
}

bool RandomPlayer::moveBot(Map *map, bool check)
{
    _mesh->setVisible(false);
    _run->setVisible(true);
    usleep(100000);
    _tmp.X = getPlayePos().X - 195;
    _tmp.Y = getPlayePos().Y;
    _tmp.Z = getPlayePos().Z;
    setPlayerPos(_tmp);
    check = true;
    _rotation.Y = 0;
    if (_playerPos.X <= -980) {
        _playerPos.X += 195;
    }
    if (check == true)
        run();
    return (check);
}

bool RandomPlayer::moveRight(Map *map, bool check)
{
    _mesh->setVisible(false);
    _run->setVisible(true);
    usleep(100000);
    _tmp.X = getPlayePos().X;
    _tmp.Y = getPlayePos().Y;
    _tmp.Z = getPlayePos().Z - 250;
    setPlayerPos(_tmp);
    check = true;
    _rotation.Y = -90;
    if (_playerPos.Z <= -980) {
        _playerPos.Z += 250;
    }
    if (check == true)
        run();
    
    return (check);
}

bool RandomPlayer::moveLeft(Map *map, bool check)
{
    
    _mesh->setVisible(false);
    _run->setVisible(true);
    usleep(100000);
    _tmp.X = getPlayePos().X;
    _tmp.Y = getPlayePos().Y;
    _tmp.Z = getPlayePos().Z + 250;
    setPlayerPos(_tmp);
    check = true;
    _rotation.Y = 90;
    if (_playerPos.Z >= 980) {
        _playerPos.Z -= 250;
    }
    if (check == true)
        run();
    
    return (check);
}

void RandomPlayer::movement(IrrlichtDevice *device, scene::ISceneManager *manager, video::IVideoDriver *driver, Map *map) {
    bool check = false;
    int bombPress = 0;
    static int bombDrop = 0;
    static int limBomb = 0;
    
    bool putBomb = false;
    static int canMove = 0;
    
    if (_playerNb == "1")
        _nbplayer = PLAYER_1;
    if (_playerNb == "2")
        _nbplayer = PLAYER_2;
    if (_playerNb == "3")
        _nbplayer = PLAYER_3;
    if (_playerNb == "4")
        _nbplayer = PLAYER_4;

    std::cout << _playerNb << std::endl;
    if (_playerNb == "1") {
        if (canMove == 100 && map->canMovePlayer(_nbplayer, SOUTH)) {
            check = moveBot(map, check);
            putBomb = true;
        }
        if (canMove == 200 && !map->canMovePlayer(_nbplayer, SOUTH)) {
            check = moveTop(map, check);
        } if (canMove == 300 && !map->canMovePlayer(_nbplayer, WEST)) {
            check = moveRight(map, check);
            putBomb = true; 
        } if (canMove == 350 && !map->canMovePlayer(_nbplayer, EAST)) {
            check = moveLeft(map, check);
            canMove = 0;
        } if (canMove == 450 && !map->canMovePlayer(_nbplayer, NORTH)) {
            check = moveBot(map, check);
            canMove = 0;
        }
    }
    canMove++;
    if (_checkParticule == true) {
        if (timeBeforeExplode() == 1 && _checkBomb == true) {
            particulesExplosion(manager, driver);
            _bomb->remove();
            _checkBomb = false;
            _isBombPosed = 0;
        }
        if (timeBeforeParticules() == 1 && _checkParticule == true) {
            for (int i = 0 ; i != _particles.size() ; i++) {
                _particles[i]->remove();
            }
            _checkParticule = false;
        }
    }
    if (_checkParticule == false) {
        _particles.clear();
    }
    if (putBomb) {
        bombPress = 1;
        _start = std::chrono::system_clock::now();
        if (bombPress == 1 && bombDrop == 0 && limBomb < _bombs && _isBombPosed < 1) {
            _engineItem->play2D("Resources/Sound/creeper.wav");
            _checkBomb = true;
            _checkParticule = true;
            _isBombPosed++;
            _bombPos = _playerPos;
            _bomb = manager->addAnimatedMeshSceneNode(
                    manager->getMesh("Resources/Media/good_bomb.obj"));
            _bomb->setMaterialFlag(video::EMF_LIGHTING, false);
            _bomb->setMaterialTexture(0, driver->getTexture(
                    "Resources/Media/marron_bomb.jpg"));
            _bomb->setMaterialTexture(0, driver->getTexture(
                    "Resources/Media/noir_bomb.jpg"));
            _bomb->setScale(core::vector3df(100, 100, 100));
            _bomb->setPosition(_playerPos);
            bombDrop = 1;
            limBomb++;
        }
    }
    if (!((EventButton *) device->getEventReceiver())->IsKeyDown(
            _key[4 + _idxKey]))
        bombDrop = 0;
    if (check == false) {
        _mesh->setVisible(true);
        _run->setVisible(false);
    }
}

core::vector3df RandomPlayer::getPlayePos() {
    return _playerPos;
}

void RandomPlayer::run()
{
    _run->setPosition(_playerPos);
    _run->setRotation(_rotation);
    _run->setAnimationSpeed(300);
}

void RandomPlayer::setPlayerAt() {
    _mesh->setPosition(_playerPos);
    _mesh->setRotation(_rotation);
    _mesh->setAnimationSpeed(100);
}

void RandomPlayer::createMesh(scene::ISceneManager *manager, video::IVideoDriver *driver, int nbPlayer) {
    _mesh = manager->addAnimatedMeshSceneNode(manager->getMesh("Resources/Media/player_idle.md2"));
    _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    _mesh->setMaterialTexture(0, driver->getTexture("Resources/Media/player_white.png"));
    _mesh->setScale(_scale);
    _run = manager->addAnimatedMeshSceneNode(manager->getMesh("Resources/Media/player_walk.md2"));
    _run->setMaterialFlag(video::EMF_LIGHTING, false);
    _run->setMaterialTexture(0, driver->getTexture("Resources/Media/player_white.png"));
    _run->setScale(_scale);
    _run->setVisible(false);
    _nbPlayer = nbPlayer;
    setKey();
}

RandomPlayer::~RandomPlayer()
{
    delete(_bombType);
}

void RandomPlayer::setKey() {
    _playerNb == "1" ? _idxKey = 1 : 0;
    _playerNb == "2" ? _idxKey = 6 : 0;
    _playerNb == "3" ? _idxKey = 11 : 0;
    _playerNb == "4" ? _idxKey = 16 : 0;
}

scene::IAnimatedMeshSceneNode *RandomPlayer::getMesh() const {
    return _mesh;
}

void RandomPlayer::setPlayerPos(const core::vector3df &playerPos) {
    _playerPos = playerPos;
}
