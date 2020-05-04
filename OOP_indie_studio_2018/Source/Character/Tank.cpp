/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Tank
*/

#include <unistd.h>
#include "EventButton.hpp"
#include "Tank.hpp"
#include "EventReceiver.hpp"

Tank::Tank(std::string playerNb, int x, int y) : ACharacter("Tank", x, y)
{
    _playerNb = playerNb;
    _playerPos = {(float)x,0,(float)y};
    _playerPosTmp = {(float)x,0,(float)y};
    _bombPos = {(float)x,0,(float)y};
    _rotation = {0,0,0};
    _scale = {1,1,1};
    _bombType = new Bomb("Petite", 0, 0);
    _bombs = 3;
    _hp = 2;
    _shield = 0;
    _checkBomb = false;
    _checkParticule = false;
    _isBombPosed = 0;
}

void Tank::particulesExplosion(scene::ISceneManager *manager, video::IVideoDriver *driver)
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

bool Tank::timeBeforeExplode()
{
    auto moment = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = moment - _start;

    if (elapsedTime.count() > 3)
        return (1);
    return (0);
}

bool Tank::timeBeforeParticules()
{
    auto moment = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = moment - _start;

    if (elapsedTime.count() > 5)
        return (1);
    return (0);
}

void Tank::movement(IrrlichtDevice *device, scene::ISceneManager *manager, video::IVideoDriver *driver, Map *map)
{
    bool check = false;
    int bombPress = 0;
    static int bombDrop = 0;
    static int limBomb = 0;
    core::vector3df tmp = {0,0,0};
    mapEntity nbplayer;

    if (_playerNb == "1")
        nbplayer = PLAYER_1;
    if (_playerNb == "2")
        nbplayer = PLAYER_2;
    if (_playerNb == "3")
        nbplayer = PLAYER_3;
    if (_playerNb == "4")
        nbplayer = PLAYER_4;


    if (((EventButton*) device->getEventReceiver())->IsKeyDown(_key[0 + _idxKey])) {
        _mesh->setVisible(false);
        _run->setVisible(true);
        usleep(100000);
        tmp.X = getPlayePos().X + 195;
        tmp.Y = getPlayePos().Y;
        tmp.Z = getPlayePos().Z;
        setPlayerPos(tmp);
        check = true;
        _rotation.Y = 180;
        if (_playerPos.X >= 980 || !map->canMovePlayer(nbplayer, NORTH)) {
            _playerPos.X -= 195;
        }
        if (check == true)
            run();
    }
    if (((EventButton*) device->getEventReceiver())->IsKeyDown(_key[1 + _idxKey])) {
        _mesh->setVisible(false);
        _run->setVisible(true);
        usleep(100000);
        tmp.X = getPlayePos().X - 195;
        tmp.Y = getPlayePos().Y;
        tmp.Z = getPlayePos().Z;
        setPlayerPos(tmp);
        check = true;
        _rotation.Y = 0;
        if (_playerPos.X <= -980 || !map->canMovePlayer(nbplayer, SOUTH)) {
            _playerPos.X += 195;
        }
        if (check == true)
            run();
    }
    if (((EventButton*) device->getEventReceiver())->IsKeyDown(_key[2 + _idxKey])) {
        _mesh->setVisible(false);
        _run->setVisible(true);
        usleep(100000);
        tmp.X = getPlayePos().X;
        tmp.Y = getPlayePos().Y;
        tmp.Z = getPlayePos().Z - 250;
        setPlayerPos(tmp);
        check = true;
        _rotation.Y = -90;
        if (_playerPos.Z <= -980 || !map->canMovePlayer(nbplayer, EAST)) {
            _playerPos.Z += 250;
        }
        if (check == true)
            run();
    }
    if (((EventButton*) device->getEventReceiver())->IsKeyDown(_key[3 + _idxKey])) {
        _mesh->setVisible(false);
        _run->setVisible(true);
        usleep(100000);
        tmp.X = getPlayePos().X;
        tmp.Y = getPlayePos().Y;
        tmp.Z = getPlayePos().Z + 250;
        setPlayerPos(tmp);
        check = true;
        _rotation.Y = 90;
        if (_playerPos.Z >= 980 || !map->canMovePlayer(nbplayer, WEST)) {
            _playerPos.Z -= 250;
        }
        if (check == true)
            run();
    }

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

    if (((EventButton*) device->getEventReceiver())->IsKeyDown(_key[4 + _idxKey])) {
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
    if (!((EventButton*) device->getEventReceiver())->IsKeyDown(_key[4 + _idxKey]))
        bombDrop = 0;
    if (check == false) {
        _mesh->setVisible(true);
        _run->setVisible(false);
    }
}

core::vector3df Tank::getPlayePos() {
    return _playerPos;
}

void Tank::run()
{
    _run->setPosition(_playerPos);
    _run->setRotation(_rotation);
    _run->setAnimationSpeed(300);
}

void Tank::setPlayerAt() {
    _mesh->setPosition(_playerPos);
    _mesh->setRotation(_rotation);
    _mesh->setAnimationSpeed(100);
}

void Tank::createMesh(scene::ISceneManager *manager, video::IVideoDriver *driver, int nbPlayer) {
    _mesh = manager->addAnimatedMeshSceneNode(manager->getMesh("Resources/Media/player_idle.md2"));
    _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    _mesh->setMaterialTexture(0, driver->getTexture("Resources/Media/player_green.png"));
    _mesh->setScale(_scale);
    _run = manager->addAnimatedMeshSceneNode(manager->getMesh("Resources/Media/player_walk.md2"));
    _run->setMaterialFlag(video::EMF_LIGHTING, false);
    _run->setMaterialTexture(0, driver->getTexture("Resources/Media/player_green.png"));
    _run->setScale(_scale);
    _nbPlayer = nbPlayer;
    _run->setVisible(false);
    setKey();
}

Tank::~Tank()
{
    delete(_bombType);
}

void Tank::setKey() {
    _playerNb == "1" ? _idxKey = 1 : 0;
    _playerNb == "2" ? _idxKey = 6 : 0;
    _playerNb == "3" ? _idxKey = 11 : 0;
    _playerNb == "4" ? _idxKey = 16 : 0;
}

void Tank::setPlayerPos(const core::vector3df &playerPos) {
    _playerPos = playerPos;
}
