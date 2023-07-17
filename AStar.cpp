#include <algorithm>
#include <queue>
#include <fstream>
#include <unordered_map>

#include <climits>
#include <cmath>

#include "AStar.hpp"
#include "Constants.hpp"


AStar::AStar(std::string filename, bool bOutputMazeToFile) : SearchAlg(filename, bOutputMazeToFile)
{
    mNumNodes = 0;
}

void AStar::run()
{
    // Output the start and end of the maze
    std::cout << "Start: " << std::endl;
    Vector2::print(*mStart);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*mGoal);

    // Complete the search
    this->astar();

    // Print each position in (x,y) format
    int iStart = posToIndex(*mStart);
    int iGoal = posToIndex(*mGoal);
    int index = iGoal;

    // Termination condition is executed after the step counter and output, so that iStart is included.
    // iStart points to a non -1 node, as mPath simply stores the shortest path to it.
    while (true)
    {
        mPath.push_front(index);

        if (index == iStart)
            break;

        index = mClosedList.at(index);
    }

    // Output the path and maze to files
    outputPathToFile();
    if (mOutputMazeToFile)
        outputMazeToFile();

    // Execution statistics
    std::cout << "Number of nodes visited: " << mNumNodes << std::endl;
    std::cout << "Number of steps in final path: " << mPath.size() << std::endl;
}

void AStar::astar()
{
    int iStart = posToIndex(*mStart);
    int iGoal = posToIndex(*mGoal);

    // Initial setup for the open list
    mOpenList.push_front(iStart);

    int current;

    for (int i = 0; i < mRows * mCols; i++)
    {
        mGCosts.push_back(INT_MAX);
        mFCosts.push_back(INT_MAX);
        mClosedList.push_back(-1);
    }

    mGCosts[iStart] = 0;

    // Loop the algorithm until the list is empty (invalid maze), or the algorithm terminates
    while (!mOpenList.empty())
    {        
        // Get current node
        current = mOpenList.front();

        // Check if the position is the goal early to save one pass
        // If this is the case, the goal has been reached and a path found
        // Terminate the loop
        if (current == iGoal)
        {
            break;
        }

        // Increment the numNodes counter
        // Since every loop is an atomic action - an exploration of a node.
        mNumNodes++;

        // Create position vectors for all cardinal directions
        int iUp = current - mCols;
        int iDown = current + mCols;
        int iLeft = current - 1;
        int iRight = current + 1;

        // Calculate whether or not each cardinal direction should be traversed
        // Uses node as a test case by setting its position to said cardinal direction

		std::vector<int> validNeighbours;

        if ((iUp > 0) && (mMaze[iUp] != WALL))
            validNeighbours.push_back(iUp);
        if ((iDown < mRows * mCols) && (mMaze[iDown] != WALL))
            validNeighbours.push_back(iDown);
        if ((iLeft > 0) && (iLeft % mCols != 0) && (mMaze[iLeft] != WALL))
            validNeighbours.push_back(iLeft);
        if ((iRight % mCols) != (mCols - 1) && iRight < mRows * mCols && (mMaze[iRight] != WALL))
            validNeighbours.push_back(iRight);

        // Remove node at the front and put its position in the explored list
        // Placed after goal checking, so that node doesn't get deleted on the final step
        mOpenList.pop_front();

        // Handle each direction to be added, delete the rest
        // Also carry out an insertion sort by cost after adding each one
        // This ensures the cheapest node is always explored first

		for (int i = 0; i < validNeighbours.size(); i++)
		{
            int iNeighbour = validNeighbours.at(i);
            
            // Distance from start to neighbour via current
            int tentativeGCost = mGCosts[current] + getIndexDistance(current, iNeighbour, mRows, mCols);

            if (tentativeGCost < mGCosts[iNeighbour])
            {
                mClosedList[iNeighbour] = current;

                mGCosts[iNeighbour] = tentativeGCost;
                mFCosts[iNeighbour] = tentativeGCost + getIndexDistance(iNeighbour, iGoal, mRows, mCols);

                if (std::count(mOpenList.begin(), mOpenList.end(), iNeighbour) == 0)
                {
                    insertIndexIntoOpenList(iNeighbour);
                }
            }
		}
    }
    
    mOpenList.clear();
}

// (Inplace) Performs one pass of insertion sort to place the front element into its
// correct position in the list.
// Sorts the list in ascending cost order, so that the back element has the highest cost.
void AStar::insertIndexIntoOpenList(int index)
{
    // Quick exit if necessary
    if (mOpenList.size() == 0)
    {
        mOpenList.push_back(index);
        return;
    }

    int cost = mFCosts[index];

    // Re-insert the node in the correct position
    for (int i = 0; i < mOpenList.size(); i++)
    {
        // We want the list to be sorted by cost ascending
        if (cost > mFCosts[mOpenList[i]])
        {
            continue;
        }
        // cost <= cost of this index, so insert before this element
        else
        {
            mOpenList.insert(mOpenList.begin() + i, index);
            return;
        }
    }
    // The end of the list was reached, and no elements had a higher cost.
    mOpenList.push_back(index);
    return;
}

// Output the path to PathOutput.txt
void AStar::outputPathToFile()
{
    std::string fileName = "PathOutput.txt";
    std::ofstream file;
    file.open(fileName);
    file << "--- A* SEARCH " << "[" << mFileName << "]" << std::endl;

    for (int i = 0; i < mPath.size(); i++)
    {
        file << "(" << mPath[i] % mCols << ", " << mPath[i] / mCols << ")" << std::endl;
    }
    file.close();
}

void AStar::outputMazeToFile()
{
    std::string fileName = "MazeOutput.txt";
    std::ofstream file;
    file.open(fileName);

    // Iterate over every character in the maze array
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            int index = i * mCols + j;

            // Default is the original maze value
            char c = mMaze[index];
            if (c == EMPTY)
            {
                if (mClosedList.at(index) != -1)
                {
                    c = VISITED;
                }

                if (std::find(mPath.begin(), mPath.end(), index) != mPath.end())
                {
                    c = PATH;
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