/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ACharacter
*/

#ifndef ACHARACTER_HPP_
#define ACHARACTER_HPP_

#include <memory>
#include <vector>
#include <irrKlang.h>
#include "EventReceiver.hpp"
#include "Bomb.hpp"
#include "AItem.hpp"
#include "Map.hpp"
#include "ICharacter.hpp"


class ACharacter : public ICharacter {
	public:
        ACharacter(const std::string &name, int posx, int posy);
        ACharacter() = default;
        ~ACharacter() override;

        void movement(IrrlichtDevice *device, scene::ISceneManager *manager, video::IVideoDriver *driver, Map *map) override;
        void useBomb() override;
        bool checkItem(AItem *item) override;
        irr::scene::IParticleSystemSceneNode* setParticlesExplosion(const std::string &path, core::vector3df particlePos, scene::ISceneManager *manager, video::IVideoDriver *driver);
        int getHp();
        int getBombNb();
        int getShield();
        void setName(const std::string &name);
        void setBombs(int bombs);
        void setHp(int hp);
        void setShield(int shield);
        void setPosx(int posx);
        void setPosy(int posy);
        void setNbPlayer(int nbPlayer);
		    bool verifCanMoove(Map *map);

    protected:
        std::string getName();
        core::vector3df getPlayerPos();
        Bomb *getBombType();
        int getBombRange();

        std::string _name;
        Bomb *_bombType;
        int _bombs;
        int _hp;
        int _shield;
        int _posx;
        int _posy;
        int _nbPlayer;
        std::vector<int> _key;
        scene::IParticleSystemSceneNode *_particlesStock;
        std::vector<scene::IParticleSystemSceneNode *> _particles;
	irrklang::ISoundEngine* _engineItem;

};

#endif /* !ACHARACTER_HPP_ */
