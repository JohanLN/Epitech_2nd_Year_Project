/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <irrKlang.h>
#include "Tank.hpp"
#include "Adc.hpp"
#include "RandomPlayer.hpp"
#include "Rapido.hpp"
#include "IGame.hpp"
#include "Map.hpp"
#include "EventReceiver.hpp"
#include "Map.hpp"
#include "Menu.hpp"

class Game : public IGame {
	public:
		Game();
		~Game();

		void initGame();
		bool coreGame(int id);
		void changeCameraView(core::vector3df cameraPos, core::vector3df cameraLook);
		void setNbPlayer(int nbPlayer);
		void setPlayerName(std::string name);
		void initCharacter();
		void manageCharacter(Map *map);
		void createBox(int posx, int posy);
        void createBoxUnbreakable(int posx, int posy);
        void gamePause();
        void setGame();
        void updateMap(Map map);

private:
    Menu _menu;
    Map _map;
	IrrlichtDevice *_device;
	video::IVideoDriver *_driver;
	scene::ISceneManager *_manager;
	gui::IGUIEnvironment *_gui;
	irrklang::ISoundEngine* _engine;
	
    irr::scene::IAnimatedMeshSceneNode* _node_map;
    irr::scene::IAnimatedMeshSceneNode* _node_box_tmp;
    std::vector<irr::scene::IAnimatedMeshSceneNode*> _node_box;
	int _nbPlayer = 1;
	int _counter;
	std::string _name1;
	std::string _name2;
	std::string _name3;
	std::string _name4;
    RandomPlayer _player1N = {"1", 960,960};
    RandomPlayer _player2N = {"2", 960,-960};
    RandomPlayer _player3N = {"3", -960, -960};
    RandomPlayer _player4N = {"4", -960, 960};
    Adc _player1A = {"1", 960,960};
    Adc _player2A = {"2", 960, -960};
    Adc _player3A = {"3", -960, -960};
    Adc _player4A = {"4", -960, 960};
    Rapido _player1R = {"1", 960,960};
    Rapido _player2R = {"2", 960, -960};
    Rapido _player3R = {"3", -960, -960};
    Rapido _player4R = {"4", -960, 960};
    Tank _player1T = {"1", 960,960};
    Tank _player2T = {"2", 960, -960};
    Tank _player3T = {"3", -960, -960};
    Tank _player4T = {"4", -960, 960};
	bool _load;
	bool _update;
    core::vector3df _camLook;
    core::vector3df _camPos;
};

#endif /* !GAME_HPP_ */
