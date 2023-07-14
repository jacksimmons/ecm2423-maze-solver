#include <fstream>
#include <algorithm>
#include <ctime>
#include <stack>

#include "DFS.hpp"
#include "Constants.hpp"


DFS::DFS(char mMazeType, bool outputMaze) : SearchAlg(mMazeType, outputMaze)
{
    bool* mVisited = new bool[getRows(mMazeType) * getCols(mMazeType)];

    // Make the visited array full of "false"
    for (int i = 0; i < getRows(mMazeType); i++)
    {
        for (int j = 0; j < getCols(mMazeType); j++)
        {
            mVisited[i * getCols(mMazeType) + j] = false;
        }
    }
}

void DFS::run()
{
    // Output start and goal positions
    std::cout << "Start: " << std::endl;
    Vector2::print(mStart);
    std::cout << "Goal: " << std::endl;
    Vector2::print(mGoal);

    // Complete the search
    this->dfs();

    Path directionPath = mPath;
    mPath.clear();

    // directionPath contains the start position, followed by a series of directions.
    // The sum of all directions up to index i gives the intended position at that index.
    // Final path output (converting a vector of cardinal directions into one of positions)
    for (int i = directionPath.size()-1; i >= 0; i--)
    {
        // Calculate the position of the ith element in the path
        Vector2 *calcPos = calculatePos(directionPath, i);
        mPath.push_back(calcPos);
    }

    // File output
	outputPathToFile("--- DFS SEARCH " + getName(mMazeType) + " [" + getFilename(mMazeType) + "] ---", mPath);
    if (mOutputMazeToFile)
        outputMazeToFile(mMazeType, mMaze, mPath, mVisited);

	// Calculate the number of visited nodes
	int numNodes = 0;
	for (int i = 0; i < getRows(mMazeType) * getCols(mMazeType); i++)
	{
		if (mVisited[i])
		{
			numNodes++;
		}
	}

	// Execution statistics
	std::cout << "Number of nodes visited: " << numNodes << std::endl;
	std::cout << "Number of steps in final path: " << mPath.size() << std::endl;
}

DFS::~DFS()
{
    // Garbage collection for positions
    for (Vector2 *vec : mPath)
        delete vec;
    delete[] mVisited;

    delete mStart;
    delete mGoal;
}

void DFS::dfs()
{
    // Mark starting node as visited as we start here
    mVisited[calculatePosIndex(mMazeType, mStart)] = true;

    // Initialise direction and pos
    Vector2 *direction = new Vector2();
    Vector2 *pos = new Vector2(mStart->x, mStart->y); // Copy start into pos

    // Push the start to start the path
    mPath.push_back(mStart);

    // Initialise the dfs stack
    std::stack<Vector2 *> dfs_stack;
    dfs_stack.push(mStart);

    while (!dfs_stack.empty())
    {
        // Check if the direction has been assigned, if not calculate it
        if (Vector2::isZero(direction))
        {
            // Calculate position from the most recent visited node
            Vector2 *calcedPos = calculatePos(mPath, mPath.size() - 1);
            pos->set(calcedPos->x, calcedPos->y);
            delete calcedPos;

            // The next direction to travel in
            Vector2 *selectedDir;

            // Initialise positions in every cardinal direction from pos
            Vector2 *posUp = *pos + *g_UP;
            Vector2 *posLeft = *pos + *g_LEFT;
            Vector2 *posDown = *pos + *g_DOWN;
            Vector2 *posRight = *pos + *g_RIGHT;

            // Find a valid direction to travel down that hasn't been explored and doesn't lead into a wall
            if (pos->y > 0 && mMaze[calculatePosIndex(mMazeType, posUp)] != WALL && !mVisited[calculatePosIndex(mMazeType, posUp)])
                selectedDir = g_UP;
            else if (pos->x > 0 && mMaze[calculatePosIndex(mMazeType, posLeft)] != WALL && !mVisited[calculatePosIndex(mMazeType, posLeft)])
                selectedDir = g_LEFT;
            else if (pos->y < getRows(mMazeType)-1 && mMaze[calculatePosIndex(mMazeType, posDown)] != WALL && !mVisited[calculatePosIndex(mMazeType, posDown)])
                selectedDir = g_DOWN;
			else if (pos->x < getCols(mMazeType)-1 && mMaze[calculatePosIndex(mMazeType, posRight)] != WALL && !mVisited[calculatePosIndex(mMazeType, posRight)])
                selectedDir = g_RIGHT;
            else
            {
                // No direction has been assigned, and none are possible (or beneficial), so we backtrack until one is found.
                // This is the BREADTH part of the search (Depth first, then Breadth)
                selectedDir = g_ZERO;
                mVisited[calculatePosIndex(mMazeType, pos)] = true;

                // Backtracking, so remove most recent node
                dfs_stack.pop();
                mPath.pop_back();
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

            bool adjacent_in_maze_bounds = posPlusDirection->x >= 0 && posPlusDirection->y >= 0 && posPlusDirection->x <= getCols(mMazeType)-1 && posPlusDirection->y <= getRows(mMazeType)-1;

            // Check if the next node is in the maze
            if (adjacent_in_maze_bounds)
            {
                bool adjacent_not_wall = (mMaze[calculatePosIndex(mMazeType, posPlusDirection)] != WALL && !mVisited[calculatePosIndex(mMazeType, posPlusDirection)]);
                delete posPlusDirection;
                // If the adjacent node is not a wall, we can assign to the adjacent std::vector
                if (adjacent_not_wall)
                {
                    // Add the direction to the position
                    pos->set(pos->x + direction->x, pos->y + direction->y);
                    mVisited[calculatePosIndex(mMazeType, pos)] = true;

                    // Add a pointer to the correct direction to the path
                    if (*direction == *g_LEFT)
                    {
                        dfs_stack.push(g_LEFT);
                        mPath.push_back(g_LEFT);
                    }
                    else if (*direction == *g_UP)
                    {
                        dfs_stack.push(g_UP);
                        mPath.push_back(g_UP);
                    }
                    else if (*direction == *g_RIGHT)
                    {
                        dfs_stack.push(g_RIGHT);
                        mPath.push_back(g_RIGHT);
                    }
                    else if (*direction == *g_DOWN)
                    {
                        dfs_stack.push(g_DOWN);
                        mPath.push_back(g_DOWN);
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
                if (*pos == *mGoal)
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
}