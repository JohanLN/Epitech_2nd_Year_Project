//
// Created by jeremyquemener on 26/03/19.
//

#ifndef OOP_ARCADE_2018_VECTOR_HPP
#define OOP_ARCADE_2018_VECTOR_HPP

namespace Utils {
    typedef  short pos;
    class Vector {
    public:
        Vector() : x(0), y(0) {};
        Vector(Utils::pos x, Utils::pos y) : x(x), y(y) {};
        Utils::pos x;
        Utils::pos y;
    public:
        bool operator==(const Vector &rhs) const {
            return x == rhs.x && y == rhs.y;
        }
        bool operator!=(const Vector &rhs) const {
            return !(rhs == *this);
        }
    };
}

#endif //OOP_ARCADE_2018_VECTOR_HPP
