/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** TODO: add description
*/

#include <iostream>
#include <random> //std::mt19937
#include <ctime>  //std::time
#include <algorithm>
#include "Map.hpp"
#include "Error.hpp"

/*
** CTOR & DTOR
*/

Map::Map()
{
    this->_playerNb = 1;
}

Map::~Map() {}

/*
** Getter & Setter
*/

std::list<std::string> Map::getMap()
{
    return (this->_map);
}

/*
** Member fcn
*/

void Map::initClassicGround(unsigned int x, unsigned int y)
{
    if (0 == x % 2) { // set even length as odd for the pattern generation
        x += 1;
    }
    if (0 == y % 2) {
        y += 1;
    }
    this->_size.x = x;
    this->_size.y = y;
    std::string temp(x, GROUND); // full clean path with wall for borders
    /*
     * set top and bottom with full wall
     * and alternate with clean path and "wall/ground" pattern for the filling
     */
    for (size_t count = 0 ; count < y ; count++) {
        if (0 == (count % 2)) {
            this->_map.push_back(temp);
            continue;
        }
        std::string pattern = {GROUND, WALL};
        auto it = pattern.begin();
        std::string plot(x, '\0');
        std::generate(plot.begin(), plot.end(),
                      [&]() -> char {
                          if(it == pattern.end()) {
                              it = pattern.begin();
                          }
                          return *it++;
                      });
        this->_map.push_back(plot);
    }
    this->_size.x = x;
    this->_size.y = y;
}

bool Map::percentageIsAchieved(unsigned int percentage)
{
    float count = 0;

    for (auto &it : this->_map) {
        count += std::count(it.begin(), it.end(), GROUND);
    }
    float ratio = count / this->_maxGround;
    float per = ratio * 100; // check if percentage with player spawn (3*4 cases)
    if (percentage < (100 - per)) {
        return (true);
    }
    return (false);
}

void Map::addBoxAtPosition(unsigned int x, unsigned int y)
{
    auto itY = this->_map.begin();
    std::advance(itY, y);
    auto itX = itY->begin();
    std::advance(itX, x);
    *itX = BOX;
}

bool Map::isValidPosition(unsigned int x, unsigned int y)
{
    // verify the position is ground in map
    auto itY = this->_map.begin();
    std::advance(itY, y);
    auto itX = itY->begin();
    std::advance(itX, x);
    if (*itX != GROUND) {
        return (false);
    }
    return (true);
}

bool Map::spawnTopLeft(unsigned int x, unsigned int y)
{
    if ((x == 0 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 0)) {
        return (false);
    }
    return (true);
}

bool Map::spawnDownRight(unsigned int x, unsigned int y)
{
    if ((x == this->_size.x - 1 && y == this->_size.y - 1) ||
        (x == this->_size.x - 1 && y == this->_size.y - 2) ||
        (x == this->_size.x - 2 && y == this->_size.y - 1)) {
        return (false);
    }
    return (true);
}

bool Map::spawnTopRight(unsigned int x, unsigned int y)
{
    if ((x == this->_size.x - 1 && y == 0) ||
        (x == this->_size.x - 1 && y == 1) ||
        (x == this->_size.x - 2 && y == 0)) {
        return (false);
    }
    return (true);
}

bool Map::spawnDownLeft(unsigned int x, unsigned int y)
{
    if ((x == 0 && y == this->_size.y - 1) ||
        (x == 0 && y == this->_size.y - 2) ||
        (x == 1 && y == this->_size.y - 1)) {
        return (false);
    }
    return (true);
}

bool Map::checkValidPlayerSpawn(unsigned int x, unsigned int y)
{
    // verify if new player can drag a bomb without die
    if (!spawnTopLeft(x, y)) {
        return (false);
    }
    if (2 <= this->_playerNb && !spawnTopRight(x, y)) {
        return (false);
    }
    if (3 <= this->_playerNb && !spawnDownRight(x, y)) {
        return (false);
    }
    if (4 == this->_playerNb && !spawnDownLeft(x, y)) {
        return (false);
    }
    return (true);
}

int Map::generateRandomNumberByInterval(unsigned int min, unsigned int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> distribution(min, max);
    return (distribution(rng));
}

bool Map::canBoxBeAdded()
{
    // verify if any box can be added although the percentage is not achieved
    int count = 0;

    for (auto &it : this->_map) {
        count += (int)std::count(it.begin(), it.end(), GROUND);
    }
    if (count <= (this->_playerNb * SPAWN_AREA)) {
        throw Error(NONE, "achieved", INFO);
    }
    return (true);
}

void Map::calculateMaxGround()
{
    this->_maxGround = ((this->_size.x - 2) * (this->_size.y - 2)) -
            (((this->_size.x - 2) / 2) * (this->_size.y - 2) / 2);
}

void Map::addBoxes(unsigned int percentage)
{
    unsigned int x, y;

    this->calculateMaxGround();
    // continue to add box while the percentage of boxes on the map is not achieved
    while (!percentageIsAchieved(percentage)) {
        /*
         * generate random position
         * then, check if box can be added at position
         * and check if position is valid for player spawn
         * check if no box can be added although percentage is not achieved
         */
        x = generateRandomNumberByInterval(0, this->_size.x - 1);
        y = generateRandomNumberByInterval(0, this->_size.y - 1);
        try {
            this->canBoxBeAdded();
            if (this->isValidPosition(x, y) &&
            this->checkValidPlayerSpawn(x, y)) {
                this->addBoxAtPosition(x, y);
            }
        } catch (const Error &e) {
            if (e.getMsg() == "achieved") {
                break;
            }
        }
    }
}

void Map::generateProceduralMap(unsigned int x, unsigned int y)
{
    // generate classic map as ground
    this->initClassicGround(x, y);

    // add boxes randomly on existing map with percentage of filling
    this->addBoxes((unsigned int)this->generateRandomNumberByInterval(40, 98));

    // init playerList , so player nb must set before generating
    if (this->_playerNb >= 1) {
        this->addPlayer(0, 0, PLAYER_1);
        if (!this->putAtPosition(0, 0, PLAYER_1)) {
            throw Error(DEFAULT, "impossible to set player 1", MAJOR);
        }
    }
    if (this->_playerNb >= 2) {
        this->addPlayer(this->_size.x - 1, 0, PLAYER_2);
        if (!this->putAtPosition(this->_size.x - 1, 0, PLAYER_2)) {
            throw Error(DEFAULT, "impossible to set player 2", MAJOR);
        }
    }
    if (this->_playerNb >= 3) {
        this->addPlayer(this->_size.x - 1, this->_size.y - 1, PLAYER_3);
        if (!this->putAtPosition(this->_size.x - 1, this->_size.y - 1, PLAYER_3)) {
            throw Error(DEFAULT, "impossible to set player 3", MAJOR);
        }
    }
    if (this->_playerNb == 4) {
        this->addPlayer(0, this->_size.y - 1, PLAYER_4);
        if (!this->putAtPosition(0, this->_size.y - 1, PLAYER_4)) {
            throw Error(DEFAULT, "impossible to set player 4", MAJOR);
        }
    }
}

void Map::printMap()
{
    for (auto &it : this->_map) {
        std::cout << it << std::endl;
    }
}

void Map::loadMap() {}

void Map::setPlayerNb(int playerNb)
{
    this->_playerNb = playerNb;
    std::cout << _playerNb << std::endl;
}

bool Map::putAtPosition(unsigned int x, unsigned int y, mapEntity entity)
{
    if (x > this->_size.x || y > this->_size.y) {
        return (false);
    }
    auto ity = this->_map.begin();
    std::advance(ity, y);
    auto c = ity->begin();
    std::advance(c, x);
    if (*c != GROUND && entity != GROUND) {
        return (false);
    }
    *c = entity;
    return (true);
}

bool Map::canMoveAtDirection(vector_t &position, cardinalPoint direction, mapEntity player)
{
    if (direction == NORTH) {
        if (!putAtPosition(position.x, (position.y - 1), player)) {
            return (false);
        }
        putAtPosition(position.x, position.y, GROUND);
        position.y -= 1;
    } else if (direction == WEST) {
        if (!putAtPosition(position.x - 1, position.y, player)) {
            return (false);
        }
        putAtPosition(position.x, position.y, GROUND);
        position.x -= 1;
    } else if (direction == SOUTH) {
        if (!putAtPosition(position.x, position.y + 1, player)) {
            return (false);
        }
        putAtPosition(position.x, position.y, GROUND);
        position.y += 1;
    } else if (direction == EAST) {
        if (!putAtPosition(position.x + 1, position.y, player)) {
            return (false);
        }
        putAtPosition(position.x, position.y, GROUND);
        position.x += 1;
    } else {
        return (false);
    }
    return (true);
}

bool Map::canMovePlayer(mapEntity player, cardinalPoint direction)
{
    auto p = this->_playerList.begin();

    if (player == PLAYER_1) {
        if (!canMoveAtDirection(p->_position, direction, player)) {
            return (false);
        }
    } else if (player == PLAYER_2) {
        std::advance(p, 1);
        if (!canMoveAtDirection(p->_position, direction, player)) {
            return (false);
        }
    }  else if (player == PLAYER_3) {
        std::advance(p, 2);
        if (!canMoveAtDirection(p->_position, direction, player)) {
            return (false);
        }
    }  else {
        std::advance(p, 3);
        if (!canMoveAtDirection(p->_position, direction, player)) {
            return (false);
        }
    }
    return (true);
}

void Map::addPlayer(unsigned int x, unsigned int y, mapEntity player)
{
    auto newPlayer = new player_t;
    auto position = new vector_t;

    position->x = x;
    position->y = y;
    newPlayer->_position = *position;
    newPlayer->player = player;
    this->_playerList.push_back(*newPlayer);
}