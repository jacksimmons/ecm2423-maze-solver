#include <iostream>
#include <fstream>
#include <algorithm>

#include <windows.h>

#include "Main.h"

int main()
{
    char maze[MAZE(ROWS)][MAZE(COLS)];
    Vector2 *start = new Vector2(0, 0);
    Vector2 *goal = new Vector2(0, 0);

    ifstream fin;
    fin.open("mazes/maze-Easy.txt");

    // Input into maze 2D arr
    for (int i = 0; i < MAZE(ROWS); i++)
    {
        for (int j = 0; j < MAZE(COLS); j++)
        {
            char c;
            fin >> c;
            maze[i][j] = c;

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

    fin.close();

    cout << "Start: (" << start->x << "," << start->y << ")";
    cout << "Goal: (" << goal->x << "," << goal->y << ")";

    if (!(start->x == goal->x && start->y == goal->y))
    {
        cout << "Valid" << endl;
    }

    std::vector<Vector2> path;
    std::vector<Vector2> visited;

    path.push_back(*new Vector2(1,0));
    path.push_back(*new Vector2(1,1));
    visited.push_back(*new Vector2(1,1));

    printMaze(maze, path, visited);
    //std::vector<Vector2> finalPath = dfs(start, goal, maze, path);

    return 0;
}

// Recursive Depth First Search
std::vector<Vector2> dfs(Vector2 *start, Vector2 *goal, char maze[MAZE(ROWS)][MAZE(COLS)], std::vector<Vector2> path)
{
    std::vector<Vector2> adjacent;

    Vector2 *left = new Vector2(-1, 0);
    Vector2 *right = new Vector2(1, 0);
    Vector2 *up = new Vector2(0, 1);
    Vector2 *down = new Vector2(0, -1);

    Vector2 pos = path.back();

    if (start->y > 0)
        adjacent.push_back(pos + *up);
    adjacent.push_back(pos + *left);
    adjacent.push_back(pos + *right);
    adjacent.push_back(pos + *down);

    for (Vector2 vec : adjacent)
    {
        if (maze[vec.y][vec.x] == EMPTY)
        {

        }
    }
}

void printMaze(char maze[MAZE(ROWS)][MAZE(COLS)], std::vector<Vector2> path, std::vector<Vector2> visited)
{
    HANDLE hConsole;
    int c = 0;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < MAZE(ROWS); i++)
    {
        for (int j = 0; j < MAZE(COLS); j++)
        {
            Vector2 *pos = new Vector2(j, i);
            if (maze[i][j] == WALL)
                c = 9; // Blue, for all walls
            else if (std::find(path.begin(), path.end(), *pos) != path.end())
                c = 10; // Lime, for all nodes on the path
            else if (std::find(visited.begin(), visited.end(), *pos) != visited.end())
                c = 12; // Red, for all visited nodes not on the path (they have been excluded)
            else
                c = 0; // Grey, for all unvisited nodes
            
            // Set the colour of the console for this char only
            SetConsoleTextAttribute(hConsole, c);
            cout << maze[i][j];
        }
        //.Newline for next row
        cout << endl;
    }

    // Reset colour for other output later on
    SetConsoleTextAttribute(hConsole, 0);
}