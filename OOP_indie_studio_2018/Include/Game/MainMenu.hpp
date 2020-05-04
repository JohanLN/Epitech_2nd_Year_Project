/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "AMenu"

class MainMenu {
	public:
		MainMenu(std::string &menuName);
		~MainMenu();

        void launchGame() override;
        void startNewGame() override;
        void quitGame() override;
        void saveGame() override;
        void settings() override;

	private:
        std::string _menuName;
};

#endif /* !MAINMENU_HPP_ */
