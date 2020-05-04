/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** PauseMenu
*/

#ifndef PAUSEMENU_HPP_
#define PAUSEMENU_HPP_

#include "AMenu.hpp"

class PauseMenu : public AMenu {
	public:
		PauseMenu(std::string &menuName);
		~PauseMenu();

        void launchGame() override;
        void startNewGame() override;
        void quitGame() override;
        void saveGame() override;
        void settings() override;

    private:
        std::string _menuName;    
};

#endif /* !PAUSEMENU_HPP_ */
