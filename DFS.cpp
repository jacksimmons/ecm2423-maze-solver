#include <fstream>
#include <iostream>
#include <ctime>
#include <stack>

#include "DFS.hpp"
#include "Maze.hpp"


DFS::DFS(std::string fileName, bool c_out, bool p_out, bool m_out)
 : Search(fileName, c_out, p_out, m_out)
{
    mSearchName = "DFS";

    for (int i = 0; i < mRows * mCols; i++)
    {
        mVisited.push_back(-1);
    }

    // Mark starting node as visited as we start here (visited is != -1, see InformedSearch.cpp)
    mVisited[mStart] = 0;
    mPath.push_back(mStart);

    setup();
}


void DFS::run()
{
    // Initialise direction and pos
    int dirX = 0;
    int dirY = 0;
    int current = mStart;

    while (!mPath.empty())
    {
        // Check if we have reached the goal
        if (current == mGoal)
        {
            mPath.push_back(current);
            break;
        }

        // Check if the direction has been assigned, if not calculate it
        if (dirX == 0 && dirY == 0)
        {
            int selectedDirX;
            int selectedDirY;

            // Create position vectors for all cardinal directions
            int up = getPosPlusDir(current, 0, -1);
            int down = getPosPlusDir(current, 0, 1);
            int left = getPosPlusDir(current, -1, 0);
            int right = getPosPlusDir(current, 1, 0);

            // Current row
            int currentX = getPosX(current);
            int currentY = getPosY(current);

            // Find a valid direction to travel down that hasn't been explored and doesn't lead into a wall
            // ! Prefers UP !
            if (currentY > 0 && (mMaze[up] != WALL) && mVisited[up] == -1)
                { selectedDirX = 0; selectedDirY = -1; }            
            else if (currentY < mRows - 1 && (mMaze[down] != WALL) && mVisited[down] == -1)
                { selectedDirX = 0; selectedDirY = 1; }
            else if (currentX > 0 && (mMaze[left] != WALL) && mVisited[left] == -1)
                { selectedDirX = -1, selectedDirY = 0; }
			else if (currentX < mCols - 1 && (mMaze[right] != WALL) && mVisited[right] == -1)
                { selectedDirX = 1; selectedDirY = 0; }
            else
            {
                // No direction has been assigned, and none are possible (or beneficial), so we backtrack until one is found.
                // This is the BREADTH part of the search (Depth first, then Breadth)
                dirX = 0; dirY = 0;
                mVisited[current] = 0;

                // Move back element into pos and pop from the stack
                current = mPath.back();
                mPath.pop_back();
            }
            
            dirX = selectedDirX; dirY = selectedDirY;

            // The direction has been set, need to restart block
            continue;
        }
        else
        {
            // A proper direction has been assigned, so check if that direction leads into a wall, backtrack if so
            // This is the DEPTH part; a direction has been assigned, and we travel along it until a wall is reached, where the direction is removed.
            // When the direction is removed, the above block (BREADTH and BACKTRACKING) begins

            int next = getPosPlusDir(current, dirX, dirY);
            int nextX = getPosX(next);
            int nextY = getPosY(next);
            bool nextInMazeBounds = nextX >= 0 && nextY >= 0 && nextX <= mCols - 1 && nextY <= mRows - 1;

            // Check if the next node is in the maze
            if (nextInMazeBounds)
            {
                bool nextTraversable = mMaze[next] != WALL && mVisited[next] == -1;
                // If the next node is not a wall, and hasn't been visited, we can add it to the path.
                if (nextTraversable)
                {
                    // Note that pos has been visited
                    mVisited[current] = 0;

                    // Push pos onto the stack, and assign posPlusDirection to pos
                    mPath.push_back(current);
                    current = next;
                }
                else
                {
                    dirX = 0; dirY = 0;
                }
            }
        }
    }

    // Remove the duplicate start element
    mPath.pop_front();
}