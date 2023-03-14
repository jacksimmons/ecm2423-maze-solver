#include "Vector2.h"

Vector2::Vector2()
{
    set(0, 0);
}

Vector2::Vector2(int _x, int _y)
{
    set(_x, _y);
}

void Vector2::set(int _x, int _y)
{
    x = _x;
    y = _y;
}

bool Vector2::operator==(const Vector2 v2)
{
    return x == v2.x && y == v2.y;
}

bool Vector2::operator!=(const Vector2 v2)
{
    return !Vector2::operator==(v2);
}

void Vector2::operator+=(const Vector2 v2)
{
    set(x + v2.x, y + v2.y);
}

Vector2 *Vector2::operator+(const Vector2 v2)
{
    return new Vector2(x + v2.x, y + v2.y);
}

Vector2 *Vector2::operator-(const Vector2 v2)
{
    return new Vector2(x - v2.x, y - v2.y);
}