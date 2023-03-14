#include <fstream>
#include <algorithm>
#include <ctime>
#include <stack>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Maze.h"
#include "DFS.h"

// Indices and Vector2:
// Due to the way 2D arrays were implemented, the components of Vector2 and the array indices
// are swapped. The "y" component of the 2D arrays map to the "x" component of the Vector2
// in the `maze` array, for example.

const bool pauseForInput = false;
const bool outputEveryCycle = false;
const bool suppressFinalDiagram = false;
const bool suppressFinalPath = true;
const bool suppressOutput = true;

// Every element in path is stored as either a pointer to start, or to the following vectors (so don't garbage collect them!)
// Global variables so they can be garbage collected at the end of the program
Vector2 *LEFT = new Vector2(-1, 0);
Vector2 *UP = new Vector2(0, -1);
Vector2 *RIGHT = new Vector2(1, 0);
Vector2 *DOWN = new Vector2(0, 1);
Vector2 *ZERO = new Vector2(0, 0);

int loop_count = 0;

int main()
{
    const clock_t startTime = clock();

    char* maze;
    bool* visited = new bool[MAZE(ROWS) * MAZE(COLS)];

    // Make the visited array full of "false"
    for (int i = 0; i < MAZE(ROWS); i++)
    {
        for (int j = 0; j < MAZE(COLS); j++)
        {
            visited[i * MAZE(COLS) + j] = false;
        }
    }

    Vector2 *start = new Vector2();
    Vector2 *goal = new Vector2();
    Vector2 *direction = new Vector2();
    tuple<char *, Vector2 *, Vector2 *> mazeInfo = readMaze();
    maze = std::get<0>(mazeInfo);
    start = std::get<1>(mazeInfo);
    goal = std::get<2>(mazeInfo);

    std::cout << "Start: " << std::endl;
    Vector2::print(*start);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*goal);

    std::vector<Vector2 *> finalPath = dfs(start, goal, maze, visited);

    if (!suppressFinalPath)
    {
        cout << "Final path: " << std::endl;
        for (int i = 0; i < finalPath.size(); i++)
        {
            Vector2 *calcPos = calculatePos(finalPath, i);
            Vector2::print(*calcPos);
            delete calcPos;
        }
    }
    
    int numNodes = 0;
    for (int i = 0; i < MAZE(ROWS) * MAZE(COLS); i++)
    {
        if (visited[i])
        {
            numNodes++;
        }
    }

    std::cout << "Number of nodes visited: " << numNodes << endl;
    std::cout << "Number of steps in final path: " << finalPath.size() << endl;
    std::cout << "Execution time: " <<  float(clock() - startTime) / CLOCKS_PER_SEC << "s" << endl;
    std::cout << "Loop count: " << loop_count;

    // Garbage collection
    delete start;
    delete goal;
    delete direction;
    
    delete maze;
    delete visited;
    
    delete UP;
    delete DOWN;
    delete LEFT;
    delete RIGHT;
    delete ZERO;

    return 0;
}

std::vector<Vector2 *> dfs(Vector2 *start, Vector2 *goal, char* maze, bool* visited)
{
    visited[calculatePosIndex(start)] = true;

    Vector2 *direction = new Vector2();
    Vector2 *pos = new Vector2(start->x, start->y); // Copy start into pos

    std::vector<Vector2 *> path;
    path.push_back(start);

    std::stack<Vector2 *> dfs_stack;
    dfs_stack.push(start);

    while (!dfs_stack.empty())
    {
        loop_count++;

        if (pauseForInput)
            cin.get();

        // Check if the direction has been assigned, if not calculate it
        if (Vector2::isZero(*direction))
        {

            Vector2 *calcedPos = calculatePos(path, path.size() - 1);
            pos->set(calcedPos->x, calcedPos->y);
            delete calcedPos;

            Vector2 *selectedDir;

            Vector2 *posUp = *pos + *UP;
            Vector2 *posLeft = *pos + *LEFT;
            Vector2 *posDown = *pos + *DOWN;
            Vector2 *posRight = *pos + *RIGHT;

            // Find a valid direction to travel down that hasn't been explored
            if (pos->y > 0 && maze[calculatePosIndex(posUp)] != WALL && !visited[calculatePosIndex(posUp)])
                selectedDir = UP;
            else if (pos->x > 0 && maze[calculatePosIndex(posLeft)] != WALL && !visited[calculatePosIndex(posLeft)])
                selectedDir = LEFT;
            else if (pos->y < MAZE(ROWS)-1 && maze[calculatePosIndex(posDown)] != WALL && !visited[calculatePosIndex(posDown)])
                selectedDir = DOWN;
            else if (pos->x < MAZE(COLS)-1 && maze[calculatePosIndex(posRight)] != WALL && !visited[calculatePosIndex(posRight)])
                selectedDir = RIGHT;
            else
            {
                // No direction has been assigned, and none are possible (or beneficial), so we backtrack until one is found.
                // This is the BREADTH part of the search (Depth first, then Breadth)
                selectedDir = ZERO;
                if (!suppressOutput)
                    std::cout << "No directions are possible... backtracking" << std::endl;
                visited[calculatePosIndex(pos)] = true;

                dfs_stack.pop();
                path.pop_back();

                if (outputEveryCycle)
                    printMaze(maze, path, visited);
            }
            
            // The direction has been set, need to restart block
            direction->set(selectedDir->x, selectedDir->y);

            delete posUp;
            delete posLeft;
            delete posDown;
            delete posRight;

            continue;
        }
        else
        {
            if (!suppressOutput)
                std::cout << "Going along direction for depth..." << std::endl;
            // A proper direction has been assigned, so check if that direction leads into a wall, backtrack if so
            // This is the DEPTH part; a direction has been assigned, and we travel along it until a wall is reached, where the direction is removed.
            // When the direction is removed, the above block (BREADTH and BACKTRACKING) begins
            bool adjacent_in_maze_bounds = pos->x + direction->x >= 0 && pos->y + direction->y >= 0 && pos->x + direction->x <= MAZE(COLS)-1 && pos->y + direction->y <= MAZE(ROWS)-1;
            
            Vector2 *posPlusDirection = *pos + *direction;
            bool adjacent_not_wall = (maze[calculatePosIndex(posPlusDirection)] != WALL && !visited[calculatePosIndex(posPlusDirection)]);
            delete posPlusDirection;

            // Check if the next node is a wall
            if (adjacent_not_wall)
            {
                // If the adjacent node is in the bounds, we can assign to the adjacent std::vector
                if (adjacent_in_maze_bounds)
                {
                    pos->set(pos->x + direction->x, pos->y + direction->y);
                    visited[calculatePosIndex(pos)] = true;

                    if (*direction == *LEFT)
                    {
                        dfs_stack.push(LEFT);
                        path.push_back(LEFT);
                    }
                    else if (*direction == *UP)
                    {
                        dfs_stack.push(UP);
                        path.push_back(UP);
                    }
                    else if (*direction == *RIGHT)
                    {
                        dfs_stack.push(RIGHT);
                        path.push_back(RIGHT);
                    }
                    else if (*direction == *DOWN)
                    {
                        dfs_stack.push(DOWN);
                        path.push_back(DOWN);
                    }

                    if (outputEveryCycle)
                        printMaze(maze, path, visited);
                }
                // If not, we may have reached the goal, as the goal can only be reached with a DOWN direction traversal
                // If we are on the goal, the adjacent tile will be below the goal, out of bounds.
                else
                {
                    if (*pos == *goal)
                    {
                        if (!suppressFinalDiagram)
                            printMaze(maze, path, visited);
                        std::cout << "Found the goal!" << std::endl;
                        break;
                    }
                }
            }
            // If it isn't EMPTY (i.e. is a wall), we need to change the direction or backtrack (both are handled by resetting the direction)
            else
            {
                if (!suppressOutput)
                    std::cout << "Calculating new direction..." << std::endl;
                direction->set(0, 0);
                continue;
            }
        }

        // Output for the path, adjacent node position and value, and the map at the end of every cycle
        if (!suppressOutput)
        {
            std::cout << "Path: " << std::endl;
            for (Vector2 *vec : path)
            {
                Vector2::print(*vec);
            }
            std::cout << "Pos: " << std::endl;
            Vector2::print(*pos);
            std::cout << "'" << maze[calculatePosIndex(pos)] << "'" << std::endl;
        }

        if (outputEveryCycle)
            printMaze(maze, path, visited);

        // An unexplainable error has occurred, exit
        if (!maze[calculatePosIndex(pos)] == EMPTY)
        {
            std::cout << "Somehow visited a non-empty, non-wall node" << std::endl;
            exit(1);
        }
    }

    delete pos;
    delete direction;
    return path;
}

Vector2 *calculatePos(std::vector<Vector2 *> &path, int index)
{
    Vector2 *pos = new Vector2();
    Vector2 *dir;
    for (int i = 0; i <= index; i++)
    {
        dir = path.at(i);
        pos->set(pos->x + dir->x, pos->y + dir->y);
    }
    return pos;
}

int calculatePosIndex(Vector2 *pos)
{
    return (pos->y) * MAZE(COLS) + pos->x;
}

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