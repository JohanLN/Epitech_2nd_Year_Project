/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** TODO: add description
*/

#include <map>
#include <list>
#include <string>

#ifndef OOP_INDIE_STUDIO_2018_MAP_HPP
#define OOP_INDIE_STUDIO_2018_MAP_HPP

#define SPAWN_AREA 3

enum cardinalPoint {
    NORTH = 0,
    WEST,
    SOUTH,
    EAST
};

enum mapEntity {

    PLAYER_1 = '0' - 4,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    GROUND,
    WALL,
    BOX,
};

typedef struct s_vector {
    unsigned int x;
    unsigned int y;
}vector_t;

typedef struct s_player {
    mapEntity player;
    vector_t _position;
}player_t;

class Map {
    public:
        Map();
        ~Map();

        std::list<std::string> getMap();
        void loadMap();
        void generateProceduralMap(unsigned int x, unsigned int y);
        void initClassicGround(unsigned int x, unsigned int y);
        void addBoxes(unsigned int percentage);
        bool percentageIsAchieved(unsigned int percentage);
        void addBoxAtPosition(unsigned int x, unsigned int y);
        bool isValidPosition(unsigned int x, unsigned int y);
        bool checkValidPlayerSpawn(unsigned int x, unsigned int y);
        bool spawnTopLeft(unsigned int x, unsigned int y);
        bool spawnTopRight(unsigned int x, unsigned int y);
        bool spawnDownRight(unsigned int x, unsigned int y);
        bool spawnDownLeft(unsigned int x, unsigned int y);
        int generateRandomNumberByInterval(unsigned int min, unsigned int max);
        bool canBoxBeAdded();
        void calculateMaxGround();
        void printMap();
        void setPlayerNb(int playerNb);
        bool putAtPosition(unsigned int x, unsigned int y, mapEntity entity);
        bool canMovePlayer(mapEntity player, cardinalPoint direction);
        bool canMoveAtDirection(vector_t &position, cardinalPoint direction, mapEntity player);
        void addPlayer(unsigned int x, unsigned int y, mapEntity player);

    private:
        int _playerNb;
        std::list<player_t> _playerList;
        std::list<std::string> _map;
        vector_t _size;
        unsigned int _maxGround;
};


#endif //OOP_INDIE_STUDIO_2018_MAP_HPP
