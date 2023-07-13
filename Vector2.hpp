#ifndef VEC2_H
#define VEC2_H 1

#include <iostream>

struct Vector2
{
    // Members
    int x;
    int y;

    // Constructor templates
    Vector2();
    Vector2(int _x, int _y);

    // Method templates
    void set(int _x, int _y);
    int distTo(Vector2 *vec);
    bool operator==(const Vector2);
    bool operator!=(const Vector2);
    void operator+=(const Vector2);
    Vector2 *operator+(const Vector2);
    Vector2 *operator-(const Vector2);

    // Static methods
    static bool isZero(Vector2 *v2)
    {
        return v2->x == 0 && v2->y == 0;
    }

    static void print(Vector2 *v2)
    {
        std::cout << "(" << v2->x << ", " << v2->y << ")" << std::endl;
    }
};

#endif