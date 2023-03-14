#ifndef VEC2_H
#define VEC2_H

#include <iostream>

using namespace std;

struct Vector2
{
    int x;
    int y;

    Vector2();
    Vector2(int _x, int _y);
    void set(int _x, int _y);
    bool operator==(const Vector2 vec);
    bool operator!=(const Vector2 vec);
    void operator+=(const Vector2 vec);
    Vector2 *operator+(const Vector2 vec);
    Vector2 *operator-(const Vector2 vec);

    static bool isZero(Vector2 v2)
    {
        return v2.x == 0 && v2.y == 0;
    }

    static void print(Vector2 v2)
    {
        std::cout << "(" << v2.x << ", " << v2.y << ")" << std::endl;
    }
};

#endif