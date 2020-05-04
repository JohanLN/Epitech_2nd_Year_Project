/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AItem
*/

#ifndef AITEM_HPP_
#define AITEM_HPP_

#include <string>

class AItem {
    public:
        AItem(const std::string &name, int posx, int posy);

    protected:
        std::string _name;
        int _posx;
        int _posy;
    public:
        const std::string &getName() const;
        void setName(const std::string &name);
        int getPosx() const;
        void setPosx(int posx);
        int getPosy() const;
        void setPosy(int posy);
};

#endif /* !AITEM_HPP_ */
