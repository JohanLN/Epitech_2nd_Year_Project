/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <irrlicht.h>
#include <string>

using namespace irr;

namespace NsGame {
	typedef enum {
        NOIN = -1,
        A_KEY,
        B_KEY,
        C_KEY,
        D_KEY,
        E_KEY,
        F_KEY,
        G_KEY,
        H_KEY,
        I_KEY,
        J_KEY,
        K_KEY,
        L_KEY,
        M_KEY,
        N_KEY,
        O_KEY,
        P_KEY,
        Q_KEY,
        R_KEY,
        S_KEY,
        T_KEY,
        U_KEY,
        V_KEY,
        W_KEY,
        X_KEY,
        Y_KEY,
        Z_KEY,
        ENTER,
        BACKSPACE,
        SPACE,
        ESCAPE,
        UP_KEY,
        DOWN_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,
        QUIT_EVENT
    } inputKey;

    typedef enum {
        NOCO = -1,
        RED,
        YELLOW,
        CYAN,
        BLUE,
        MAGENTA,
        GREEN,
        BLACK,
        WHITE
    }colorDisplay;

    typedef struct {
        int posx;
        int posy;
        std::string txt;
    } t_Text;
}

class IGame {
	public:
		virtual ~IGame() = default;
        
        virtual bool coreGame(int id) = 0;
};


#endif /* !IGAME_HPP_ */
