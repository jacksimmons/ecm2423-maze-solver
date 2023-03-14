#include <fstream>
#include <tuple>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Maze.h"
#include "Vector2.h"

using namespace std;

// Convert the maze file into a char array
// Also provides start and goal vectors
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

// Print the maze in console, with colour coding:
// Blue - Wall node
// Grey - Unvisited empty node
// Red - Visited empty node
// Green - Visited empty node, and in the path
void printMaze(char* maze, std::vector<Vector2 *> path, bool* visited)
{
    #ifdef _WIN32
    HANDLE hConsole;
    int c = 0;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < MAZE(ROWS); i++)
    {
        for (int j = 0; j < MAZE(COLS); j++)
        {
            Vector2 *pos = new Vector2(j, i);
            if (maze[i * MAZE(COLS) + j] == WALL)
                c = 9; // Blue, for all walls
            else
            {
                if (visited[i * MAZE(COLS) + j])
                    c = 12; // Red, for all visited nodes not on the path (they have been excluded)
                else
                    c = 0; // Grey, for all unvisited nodes

                for (int i = 0; i < path.size(); i++)
                {
                    Vector2 *calcedPos = calculatePos(path, i);
                    if (*pos == *calcedPos)
                    {
                        c = 10; // Lime, for all nodes on the path
                    }
                    delete calcedPos;
                }
            }
            delete pos;
            
            // Set the colour of the console for this char only
            SetConsoleTextAttribute(hConsole, c);
            std::cout << maze[i * MAZE(COLS) + j];
        }
        //.Newline for next row
        std::cout << std::endl;
    }

    // Reset colour for other output later on
    SetConsoleTextAttribute(hConsole, 0);
    #endif
}
