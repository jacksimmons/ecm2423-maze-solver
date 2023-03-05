#ifndef MAIN_H
#define MAIN_H
#include <vector>
using namespace std;

#define E_COLS 20
#define E_ROWS 10

#define M_COLS 400
#define M_ROWS 100

#define L_COLS 600
#define L_ROWS 600

#define VL_COLS 4000
#define VL_ROWS 1000

#define JOIN(a, b) a ## b
#define MAZE(suffix) JOIN(E_, suffix)

#define EMPTY '-'
#define WALL '#'

struct Vector2
{
    int x;
    int y;

    Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    bool operator==(const Vector2 v2)
    {
        return x == v2.x && y == v2.y;
    }

    bool operator!=(const Vector2 v2)
    {
        return !operator==(v2);
    }

    Vector2 operator+(const Vector2 v2)
    {
        int new_x = x + v2.x;
        int new_y = y + v2.y;

        Vector2 *new_v = new Vector2(new_x, new_y);
        return *new_v;
    }
};

std::vector<Vector2> dfs(Vector2 *start, Vector2 *goal, char maze[MAZE(ROWS)][MAZE(COLS)], std::vector<Vector2> path);
void printMaze(char maze[MAZE(ROWS)][MAZE(COLS)], std::vector<Vector2> path, std::vector<Vector2> visited);

#endif