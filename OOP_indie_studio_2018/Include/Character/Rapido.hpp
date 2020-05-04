/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Rapido
*/

#ifndef RAPIDO_HPP_
#define RAPIDO_HPP_

#include <chrono>
#include "ACharacter.hpp"
#include "Map.hpp"

class Rapido : public ACharacter {
	public:
		Rapido(std::string playerNb, int x, int y);
		~Rapido() override;

    void movement(IrrlichtDevice *device, scene::ISceneManager *manager, video::IVideoDriver *driver, Map *map);
	core::vector3df getPlayePos();
    void particulesExplosion(scene::ISceneManager *manager, video::IVideoDriver *driver);
    bool timeBeforeExplode();
    bool timeBeforeParticules();
    void setPlayerPos(const core::vector3df &playerPos);
	void setPlayerAt();
	void createMesh(scene::ISceneManager *manager, video::IVideoDriver *driver, int nbPlayer);
	void run();
	void setKey();


private:
	core::vector3df _playerPos;
    core::vector3df _playerPosTmp;
	core::vector3df _rotation;
	core::vector3df _scale;
    core::vector3df _bombPos;
    std::chrono::time_point<std::chrono::system_clock> _start;
    scene::IAnimatedMeshSceneNode * _bomb;
	scene::IAnimatedMeshSceneNode *_mesh;
	scene::IAnimatedMeshSceneNode *_run;
	int _idxKey;
	std::string _playerNb;
    bool _checkBomb;
    bool _checkParticule;
    int _isBombPosed;
};

#endif /* !RAPIDO_HPP_ */