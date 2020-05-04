/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AMenu
*/

#ifndef AMENU_HPP_
#define AMENU_HPP_

#include <string>

#define RESOURCE_PATH "Resources"
#define MEDIA_PATH RESOURCE_PATH + "/Media/"

class AMenu {
    public:
        explicit AMenu(std::string &menuName);
        virtual ~AMenu();

        virtual void launchGame();
        virtual void startNewGame();
        virtual void quitGame();
        virtual void saveGame();
        virtual void settings();
};

#endif /* !AMENU_HPP_ */
