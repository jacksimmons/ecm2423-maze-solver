// Commented fully
#include <fstream>
#include <algorithm>
#include <ctime>
#include <stack>

#include "DFS.hpp"
#include "Constants.hpp"

// Commented
void runDFS(char mazeType, bool outputMaze)
{
    // Initialise the maze and visited arrays
    char* maze;
    bool* visited = new bool[getRows(mazeType) * getCols(mazeType)];

    // Make the visited array full of "false"
    for (int i = 0; i < getRows(mazeType); i++)
    {
        for (int j = 0; j < getCols(mazeType); j++)
        {
            visited[i * getCols(mazeType) + j] = false;
        }
    }

    // Initialise the vectors used to control the search
    Vector2 *start;
    Vector2 *goal;

    // Read the vectors from the read maze
    std::tuple<char *, Vector2 *, Vector2 *> mazeInfo = readMaze(mazeType);
    maze = std::get<0>(mazeInfo);
    start = std::get<1>(mazeInfo);
    goal = std::get<2>(mazeInfo);

    // Output start and goal positions
    std::cout << "Start: " << std::endl;
    Vector2::print(*start);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*goal);

    // Complete the search, and get the output from it
    Path directionPath = dfs(mazeType, start, goal, maze, visited);

    std::vector<Vector2 *> finalPath;

    // directionPath contains the start position, followed by a series of directions.
    // The sum of all directions up to index i gives the intended position at that index.
    // Final path output (converting a vector of cardinal directions into one of positions)
    for (int i = directionPath.size()-1; i >= 0; i--)
    {
        // Calculate the position of the ith element in the path
        Vector2 *calcPos = calculatePos(directionPath, i);
        finalPath.push_back(calcPos);
    }

    // File output
	outputPathToFile("--- DFS SEARCH " + getName(mazeType) + " [" + getFilename(mazeType) + "] ---", finalPath);
    if (outputMaze)
        outputMazeToFile(mazeType, maze, finalPath, visited);

	// Calculate the number of visited nodes
	int numNodes = 0;
	for (int i = 0; i < getRows(mazeType) * getCols(mazeType); i++)
	{
		if (visited[i])
		{
			numNodes++;
		}
	}

	// Execution statistics
	std::cout << "Number of nodes visited: " << numNodes << std::endl;
	std::cout << "Number of steps in final path: " << finalPath.size() << std::endl;
    
    // Garbage collection for positions
    for (Vector2 *vec : finalPath)
        delete vec;

    // Garbage collection
    delete start;
    delete goal;
    
    delete[] maze;
    delete[] visited;
}

// Commented
Path dfs(char mazeType, Vector2 *start, Vector2 *goal, char* maze, bool* visited)
{
    // Mark starting node as visited as we start here
    visited[calculatePosIndex(mazeType, start)] = true;

    // Initialise direction and pos
    Vector2 *direction = new Vector2();
    Vector2 *pos = new Vector2(start->x, start->y); // Copy start into pos

    // Initialise the path
    Path path;
    path.push_back(start);

    // Initialise the dfs stack
    std::stack<Vector2 *> dfs_stack;
    dfs_stack.push(start);

    while (!dfs_stack.empty())
    {
        // Check if the direction has been assigned, if not calculate it
        if (Vector2::isZero(*direction))
        {
            // Calculate position from the most recent visited node
            Vector2 *calcedPos = calculatePos(path, path.size() - 1);
            pos->set(calcedPos->x, calcedPos->y);
            delete calcedPos;

            // The next direction to travel in
            Vector2 *selectedDir;

            // Initialise positions in every cardinal direction from pos
            Vector2 *posUp = *pos + *UP;
            Vector2 *posLeft = *pos + *LEFT;
            Vector2 *posDown = *pos + *DOWN;
            Vector2 *posRight = *pos + *RIGHT;

            // Find a valid direction to travel down that hasn't been explored and doesn't lead into a wall
            if (pos->y > 0 && maze[calculatePosIndex(mazeType, posUp)] != WALL && !visited[calculatePosIndex(mazeType, posUp)])
                selectedDir = UP;
            else if (pos->x > 0 && maze[calculatePosIndex(mazeType, posLeft)] != WALL && !visited[calculatePosIndex(mazeType, posLeft)])
                selectedDir = LEFT;
            else if (pos->y < getRows(mazeType)-1 && maze[calculatePosIndex(mazeType, posDown)] != WALL && !visited[calculatePosIndex(mazeType, posDown)])
                selectedDir = DOWN;
			else if (pos->x < getCols(mazeType)-1 && maze[calculatePosIndex(mazeType, posRight)] != WALL && !visited[calculatePosIndex(mazeType, posRight)])
                selectedDir = RIGHT;
            else
            {
                // No direction has been assigned, and none are possible (or beneficial), so we backtrack until one is found.
                // This is the BREADTH part of the search (Depth first, then Breadth)
                selectedDir = ZERO;
                visited[calculatePosIndex(mazeType, pos)] = true;

                // Backtracking, so remove most recent node
                dfs_stack.pop();
                path.pop_back();
            }
            
            // The direction has been set, need to restart block
            direction->set(selectedDir->x, selectedDir->y);

            // Garbage collection
            delete posUp;
            delete posLeft;
            delete posDown;
            delete posRight;

            continue;
        }
        else
        {
            // A proper direction has been assigned, so check if that direction leads into a wall, backtrack if so
            // This is the DEPTH part; a direction has been assigned, and we travel along it until a wall is reached, where the direction is removed.
            // When the direction is removed, the above block (BREADTH and BACKTRACKING) begins
            Vector2 *posPlusDirection = *pos + *direction;

            bool adjacent_in_maze_bounds = posPlusDirection->x >= 0 && posPlusDirection->y >= 0 && posPlusDirection->x <= getCols(mazeType)-1 && posPlusDirection->y <= getRows(mazeType)-1;

            // Check if the next node is in the maze
            if (adjacent_in_maze_bounds)
            {
                bool adjacent_not_wall = (maze[calculatePosIndex(mazeType, posPlusDirection)] != WALL && !visited[calculatePosIndex(mazeType, posPlusDirection)]);
                delete posPlusDirection;
                // If the adjacent node is not a wall, we can assign to the adjacent std::vector
                if (adjacent_not_wall)
                {
                    // Add the direction to the position
                    pos->set(pos->x + direction->x, pos->y + direction->y);
                    visited[calculatePosIndex(mazeType, pos)] = true;

                    // Add a pointer to the correct direction to the path
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
                }
                else
                {
                    direction->set(0, 0);
                    continue;
                }
            }
            // If it isn't EMPTY (i.e. is a wall), we need to change the direction or backtrack (both are handled by resetting the direction)
            else
            {
                // If the next position isn't in the maze bounds, the position is at the goal or an invalid maze was provided
                // This is because the only place to go from the goal is out of bounds
                if (*pos == *goal)
                {
                    std::cout << "Found the goal!" << std::endl;
                    delete posPlusDirection;
                    break;
                }
            }
        }
    }

    delete pos;
    delete direction;

    return path;
}