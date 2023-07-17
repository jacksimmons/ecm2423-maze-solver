#include <fstream>
#include <algorithm>
#include <ctime>
#include <stack>

#include "DFS.hpp"
#include "Constants.hpp"


DFS::DFS(std::string fileName, bool outputMaze) : SearchAlg(fileName, outputMaze)
{    
    // Make the visited array full of "false"
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            mVisited.push_back(false);
        }
    }
}

void DFS::run()
{
    // Output start and goal positions
    std::cout << "Start: " << std::endl;
    Vector2::print(*mStart);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*mGoal);

    // Complete the search
    this->dfs();

    // Remove the duplicate start element
    mPath.pop_front();

    // // directionPath contains the start position, followed by a series of directions.
    // // The sum of all directions up to index i gives the intended position at that index.
    // // Final path output (converting a vector of cardinal directions into one of positions)
    // for (int i = directionPath.size()-1; i >= 0; i--)
    // {
    //     // Calculate the position of the ith element in the path
    //     mPath.push_back(calculatePos(directionPath, i));
    // }

    // File output
	outputPathToFile();
    if (mOutputMazeToFile)
        outputMazeToFile();

	// Calculate the number of visited nodes
	int numNodes = 0;
	for (int i = 0; i < mRows * mCols; i++)
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

void DFS::dfs()
{
    // Mark starting node as visited as we start here
    mVisited[posToIndex(*mStart)] = true;

    // Initialise direction and pos
    std::unique_ptr<Vector2> direction = std::make_unique<Vector2>();
    std::shared_ptr<Vector2> pos = std::make_shared<Vector2>(mStart->x, mStart->y);

    // Push ZERO to start the path
    mPath.push_back(pos);


    while (!mPath.empty())
    {
        // Check if the direction has been assigned, if not calculate it
        if (Vector2::isZero(*direction))
        {
            // The next direction to travel in
            Vector2 selectedDir;

            // Create position vectors for all cardinal directions
            std::unique_ptr<Vector2> posUp = *pos + *g_UP;
            std::unique_ptr<Vector2> posDown = *pos + *g_DOWN;
            std::unique_ptr<Vector2> posLeft = *pos + *g_LEFT;
            std::unique_ptr<Vector2> posRight = *pos + *g_RIGHT;

            // Find a valid direction to travel down that hasn't been explored and doesn't lead into a wall
            // ! Prefers UP !
            if (pos->y > 0 && mMaze[posToIndex(*posUp)] != WALL && !mVisited[posToIndex(*posUp)])
                selectedDir = *g_UP;
            else if (pos->x > 0 && mMaze[posToIndex(*posLeft)] != WALL && !mVisited[posToIndex(*posLeft)])
                selectedDir = *g_LEFT;
            else if (pos->y < mRows - 1 && mMaze[posToIndex(*posDown)] != WALL && !mVisited[posToIndex(*posDown)])
                selectedDir = *g_DOWN;
			else if (pos->x < mCols - 1 && mMaze[posToIndex(*posRight)] != WALL && !mVisited[posToIndex(*posRight)])
                selectedDir = *g_RIGHT;
            else
            {
                // No direction has been assigned, and none are possible (or beneficial), so we backtrack until one is found.
                // This is the BREADTH part of the search (Depth first, then Breadth)
                selectedDir = *g_ZERO;
                mVisited[posToIndex(*pos)] = true;

                // Move back element into pos and pop from the stack
                pos = std::move(mPath.back());
                mPath.pop_back();
            }
            
            // The direction has been set, need to restart block
            direction->set(selectedDir.x, selectedDir.y);
            continue;
        }
        else
        {
            // A proper direction has been assigned, so check if that direction leads into a wall, backtrack if so
            // This is the DEPTH part; a direction has been assigned, and we travel along it until a wall is reached, where the direction is removed.
            // When the direction is removed, the above block (BREADTH and BACKTRACKING) begins

            std::unique_ptr<Vector2> posPlusDirection = *pos + *direction;

            bool adjacent_in_maze_bounds = posPlusDirection->x >= 0 && posPlusDirection->y >= 0 && posPlusDirection->x <= mCols - 1 && posPlusDirection->y <= mRows - 1;

            // If it isn't EMPTY (i.e. is a wall), we need to change the direction or backtrack (both are handled by resetting the direction)
            if (!adjacent_in_maze_bounds)
            {
                // If the next position isn't in the maze bounds, the position is at the goal or an invalid maze was provided
                // This is because the only place to go from the goal is out of bounds
                if (*pos == *mGoal)
                {
                    std::cout << "Found the goal!" << std::endl;
                    mPath.push_back(std::move(pos));
                    break;
                }
            }
            // Check if the next node is in the maze
            else
            {
                bool adjacent_valid = mMaze[posToIndex(*posPlusDirection)] != WALL && !mVisited[posToIndex(*posPlusDirection)];
                // If the adjacent node is not a wall, and hasn't been visited, we can add it to the path.
                if (adjacent_valid)
                {
                    // Note that pos has been visited
                    mVisited[posToIndex(*pos)] = true;

                    // Push pos onto the stack, and assign posPlusDirection to pos
                    mPath.push_back(std::move(pos));
                    pos = std::move(posPlusDirection);
                }
                else
                {
                    direction->set(0, 0);
                }
            }

        }
    }
}

void DFS::outputPathToFile()
{
    std::string fileName = "PathOutput.txt";
    std::ofstream file;
    file.open(fileName);
    file << "--- DFS SEARCH " << "[" << mFileName << "]" << std::endl;
    if (mPath.empty())
    {
        file << "Search failed!" << std::endl;
    }
    else
    {
        // Print each position in (x,y) format
        for (int i = 0; i < mPath.size(); i++)
        {
            file << "(" << mPath[i]->x << ", " << mPath[i]->y << ")" << std::endl;
        }   
    }
    file.close();
}

void DFS::outputMazeToFile()
{
    std::string fileName = "MazeOutput.txt";
    std::ofstream file;
    file.open(fileName);

    // Iterate over every character in the maze array
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            // Empty by default
            char c = '-';
            Vector2 pos(j, i);
            if (mMaze[i * mCols + j] == WALL)
                c = '#';
            else
            {
                if (mVisited[i * mCols + j])
                    c = 'v';
                else
                    c = '-';

                // Overwrite the above if on the path with *
                for (int i = 0; i < mPath.size(); i++)
                {
                    if (pos == *mPath[i])
                    {
                        c = '*';
                    }
                }
            }
            // Output the character c to file
            file << c;
        }
        // Newline for next row
        file << std::endl;
    }

    file.close();
}