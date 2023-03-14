#include <fstream>
#include <tuple>

#include "Maze.h"
#include "Vector2.h"

using namespace std;

std::tuple<char *, Vector2 *, Vector2 *> readMaze()
{
    //*maze needs to be freed in calling block
    char *maze = new char[MAZE(ROWS) * MAZE(COLS)];
    Vector2 *start = new Vector2();
    Vector2 *goal = new Vector2();

    // Create input file stream
    ifstream fin;
    fin.open(MAZE(FILENAME));

    for (int i = 0; i < MAZE(ROWS); i++)
    {
        for (int j = 0; j < MAZE(COLS); j++)
        {
            char c;
            fin >> c;
            maze[i * MAZE(COLS) + j] = c;

            if (i == 0 && c == EMPTY)
            {
                start->x = j;
                start->y = i;
            }

            else if (i == MAZE(ROWS) - 1 && c == EMPTY)
            {
                goal->x = j;
                goal->y = i;
            }
        }
    }

    // Input into maze 2D arr
    fin.close();

    return std::make_tuple(maze, start, goal);
}
