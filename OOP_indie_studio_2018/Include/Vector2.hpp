/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** TODO: add description
*/

#ifndef OOP_ARCADE_2018_VECTOR2_HPP
#define OOP_ARCADE_2018_VECTOR2_HPP

template<typename T>
class Vector2 {
public:
    Vector2() : x(0), y(0) {
    }

    Vector2(const T &_x, const T &_y) : x(_x), y(_y) {
    }

    template<typename U>
    Vector2(const Vector2<U> &vector2)
            : x(vector2.x), y(vector2.y) {
    }

public:
    T x;
    T y;
};

template<typename T>
bool operator==(const Vector2<T> &a, const Vector2<T> &b) {
    return a.x == b.x && a.y == b.y;
}

template<typename T>
Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b) {
    return Vector2<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b) {
    return Vector2<T>(a.x - b.x, a.y - b.y);
}

using Vector2i = Vector2<int>;

#endif //OOP_ARCADE_2018_VECTOR2_HPP
