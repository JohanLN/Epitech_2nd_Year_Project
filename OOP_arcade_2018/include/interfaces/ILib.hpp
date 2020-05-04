/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Lib interface
*/

#ifndef OOP_ARCADE_2018_ILIB_HPP
#define OOP_ARCADE_2018_ILIB_HPP

#include <string>

namespace Lib {
    typedef enum {
        NOIN = -1,
        A_KEY = 'a',
        B_KEY = 'b',
        C_KEY = 'c',
        D_KEY = 'd',
        E_KEY = 'e',
        F_KEY = 'f',
        G_KEY = 'g',
        H_KEY = 'h',
        I_KEY = 'i',
        J_KEY = 'j',
        K_KEY = 'k',
        L_KEY = 'l',
        M_KEY = 'm',
        N_KEY = 'n',
        O_KEY = 'o',
        P_KEY = 'p',
        Q_KEY = 'q',
        R_KEY = 'r',
        S_KEY = 's',
        T_KEY = 't',
        U_KEY = 'u',
        V_KEY = 'v',
        W_KEY = 'w',
        X_KEY = 'x',
        Y_KEY = 'y',
        Z_KEY = 'z',
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

    class ILib {
    public:
        virtual ~ILib() = default;
        //virtual ILib& operator=(const ILib& oldILib) = 0;
        virtual void displayWin(int frame) = 0;
        virtual void destroyWin() = 0;
        virtual inputKey bindKey() = 0;
        virtual void bindColor() = 0;
        virtual void drawPixel(float posx, float posy, Lib::colorDisplay color) = 0;
        virtual void printText(Lib::t_Text &text, Lib::colorDisplay color) = 0;
        virtual void clearWin() = 0;
        virtual void updateWin(float sec) = 0;
        virtual void loadImage(std::string file) = 0;
        virtual void drawImage(std::string file) = 0;
        virtual void loadMusic(std::string file) = 0;
        virtual void launchMusic() = 0;
    };
}

#endif //OOP_ARCADE_2018_ILIB_HPP