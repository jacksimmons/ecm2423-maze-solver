#include <math.h>

#include "Vector2.hpp"
#include "Constants.hpp"

// Vector2 stands for 2D vector (x and y components)
// It is a struct used to represent positions in the maze

// Indices and Vector2:
// Due to the way 2D arrays were implemented, the components of Vector2 and the array indices
// are swapped. The "y" component of the 2D arrays map to the "x" component of the Vector2
// in the `maze` array, for example.

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

int Vector2::distTo(Vector2 v2)
{
    return (abs(x - v2.x) + abs(y - v2.y));
}

bool Vector2::operator==(const Vector2& v2)
{
    return x == v2.x && y == v2.y;
}

bool Vector2::operator!=(const Vector2& v2)
{
    return !Vector2::operator==(v2);
}

void Vector2::operator+=(const Vector2& v2)
{
    set(x + v2.x, y + v2.y);
}

std::unique_ptr<Vector2> Vector2::operator+(const Vector2& rhs)
{
    return std::make_unique<Vector2>(x + rhs.x, y + rhs.y);
}

std::unique_ptr<Vector2> Vector2::operator-(const Vector2& rhs)
{
    return std::make_unique<Vector2>(x - rhs.x, y - rhs.y);
}