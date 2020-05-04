/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** RandomPlayer
*/

#ifndef RANDOMPLAYER_HPP_
#define RANDOMPLAYER_HPP_

#include <chrono>
#include "ACharacter.hpp"

class RandomPlayer : public ACharacter {
	public:
		RandomPlayer(std::string playerNb, int x, int y);
		~RandomPlayer() override;

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
    scene::IAnimatedMeshSceneNode *_run;

    scene::IAnimatedMeshSceneNode *_mesh;
    scene::IAnimatedMeshSceneNode *getMesh() const;

    bool moveTop(Map *map, bool check);
    bool moveBot(Map *map, bool check);
    bool moveLeft(Map *map, bool check);
    bool moveRight(Map *map, bool check);
    
    bool timeBeforeMove();



private:
    core::vector3df _playerPos;
    core::vector3df _playerPosTmp;
    core::vector3df _rotation;
    core::vector3df _scale;
    core::vector3df _bombPos;
    scene::ISceneManager *_manager;
    std::chrono::time_point<std::chrono::system_clock> _start;
    scene::IAnimatedMeshSceneNode * _bomb;
	int _idxKey;
    std::string _playerNb;
    bool _checkBomb;
    bool _checkParticule;
    int _isBombPosed;
    mapEntity _nbplayer;
    core::vector3df _tmp = { 0, 0, 0 };
};


#endif /* !RANDOMPLAYER_HPP_ */
