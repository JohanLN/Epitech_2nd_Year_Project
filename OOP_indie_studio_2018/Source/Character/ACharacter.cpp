/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#include <Character/ACharacter.hpp>
#include <iostream>
#include "Bomb.hpp"
#include "Potion.hpp"
#include "ACharacter.hpp"

using namespace irrklang;

ACharacter::ACharacter(const std::string &name, int posx, int posy) : _name(name), _posx(posx), _posy(posy)
{
    _bombType = new Bomb("Petite", posx, posy);//puissance
    _bombs = 3;
    _hp = 1;
    _shield = 0;
    _name = name;
    _key = {0,
            KEY_KEY_Z,
            KEY_KEY_S,
            KEY_KEY_D,
            KEY_KEY_Q,
            KEY_KEY_A,
            KEY_KEY_T,
            KEY_KEY_G,
            KEY_KEY_H,
            KEY_KEY_F,
            KEY_KEY_R,
            KEY_KEY_O,
            KEY_KEY_L,
            KEY_KEY_M,
            KEY_KEY_K,
            KEY_KEY_I,
            KEY_UP,
            KEY_DOWN,
            KEY_RIGHT,
            KEY_LEFT,
            KEY_RSHIFT};
    _engineItem = createIrrKlangDevice();
}

ACharacter::~ACharacter() = default;

void ACharacter::movement(IrrlichtDevice *device, scene::ISceneManager *manager, video::IVideoDriver *driver, Map *map)
{

}

void ACharacter::useBomb() 
{

}

void ACharacter::setName(const std::string &name) {
    _name = name;
}

void ACharacter::setBombs(int bombs) {
    _bombs = bombs;
}

void ACharacter::setHp(int hp) {
    _hp = hp;
}

void ACharacter::setShield(int shield) {
    _shield = shield;
}

void ACharacter::setPosx(int posx) {
    _posx = posx;
}

void ACharacter::setPosy(int posy) {
    _posy = posy;
}

int ACharacter::getBombRange()
{
    Bomb *bomb = getBombType();
    return (bomb->getRange());
}

Bomb *ACharacter::getBombType()
{
    return (_bombType);
}

int ACharacter::getHp()
{
    return (_hp);
}

int ACharacter::getBombNb()
{
    return (_bombs);
}

int ACharacter::getShield()
{
    return (_shield);
}

//Fonction qui check quel item le joueur vien de drop
bool ACharacter::checkItem(AItem *item) {
    if (item->getName() == "Petite" || item->getName() == "Moyen" || item->getName() == "Grand") {
        auto toto = std::unique_ptr<Bomb>(static_cast<Bomb *>(item));
        if (_bombType->getRange() < toto->getRange()) {
            _bombType->setRange(toto->getRange());
            return true;
        }
        return false;
    }

    if (item->getName() == "StackBomb_potion" || item->getName() == "Strength_potion" || item->getName() == "Shield_potion") {
        auto toto = std::unique_ptr<Potion>(static_cast<Potion *>(item));
        if (toto->isShield()) {
            _shield += 1;
            return true;
        }
        if (toto->isStrength()) {
            _bombType->setRange(_bombType->getRange() + 1);
            return true;
        }
        if (toto->isStackBomb()) {
            _bombs += 5;
            return true;
        }
        return false;
    }
    return false;
}

core::vector3df ACharacter::getPlayerPos() {
    return core::vector3df(0,0,0);
}

std::string ACharacter::getName() {
    return _name;
}

void ACharacter::setNbPlayer(int nbPlayer) {
    _nbPlayer = nbPlayer;
}

irr::scene::IParticleSystemSceneNode *
ACharacter::setParticlesExplosion(const std::string &path, core::vector3df particlePos, scene::ISceneManager *manager,
                                  video::IVideoDriver *driver) {
    _particlesStock = 0;
    _particlesStock = manager->addParticleSystemSceneNode(false);

    _particlesStock->setPosition(particlePos);
    _particlesStock->setScale(core::vector3df(2, 2, 2));

    scene::IParticleEmitter *emit = _particlesStock->createBoxEmitter(
            core::aabbox3d<f32>(-60, 0, -60, 60, 60, 60),
            core::vector3df(0.f, 0.25f, 0.f),
            3000, 3500, video::SColor(255, 0, 0, 0),
            video::SColor(255, 250, 250, 250),
            500, 700);
    emit->setMinStartSize(core::dimension2d<f32>(30.0f, 20.0f));
    _particlesStock->setEmitter(emit);
    emit->drop();

    scene::IParticleAffector *pa = _particlesStock->createFadeOutParticleAffector();

    _particlesStock->addAffector(pa);
    pa->drop();

    _particlesStock->setMaterialFlag(video::EMF_LIGHTING, false);
    _particlesStock->setMaterialTexture(0, driver->getTexture(path.c_str()));
    _particlesStock->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

    _particles.push_back(_particlesStock);

    return (_particlesStock);
}
