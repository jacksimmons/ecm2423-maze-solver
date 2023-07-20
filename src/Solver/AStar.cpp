#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <climits>
#include <cmath>

#include "AStar.hpp"
#include "../Maze.hpp"



AStar::AStar(std::string filename, bool c_out, bool p_out, bool m_out)
: InformedSearchAlgorithm(filename, c_out, p_out, m_out)
{
    // Logging
    mSearchName = "A*";

    // Initial setup
    for (int i = 0; i < mRows * mCols; i++)
    {
        mGCosts.push_back(INT_MAX);
        mFCosts.push_back(INT_MAX);
        mClosedList.push_back(-1);
    }

    mOpenList.push_front(mStart);
    mGCosts[mStart] = 1;

    setup();
}


void AStar::run()
{
    // Loop the algorithm until the list is empty (invalid maze), or the algorithm terminates
    while (!mOpenList.empty())
    {
        // Get current node
        int current = mOpenList.front();

        // Check if the position is the goal early to save one pass
        // If this is the case, the goal has been reached and a path found
        // Terminate the loop
        if (current == mGoal)
        {
            break;
        }

        // Create position vectors for all cardinal directions
        int up = getPosPlusDir(current, 0, -1);
        int down = getPosPlusDir(current, 0, 1);
        int left = getPosPlusDir(current, -1, 0);
        int right = getPosPlusDir(current, 1, 0);

        // Calculate whether or not each cardinal direction should be traversed
        // Uses node as a test case by setting its position to said cardinal direction

		std::vector<int> validNeighbours;

        if ((up > 0) && (mMaze[up] != WALL))
            validNeighbours.push_back(up);
        if ((down < mRows * mCols) && (mMaze[down] != WALL))
            validNeighbours.push_back(down);
        if ((left % mCols != 0) && left > 0 && (mMaze[left] != WALL))
            validNeighbours.push_back(left);
        if ((right % mCols) != (mCols - 1) && right < mRows * mCols && (mMaze[right] != WALL))
            validNeighbours.push_back(right);

        // Remove node at the front and put its position in the explored list
        // Placed after goal checking, so that node doesn't get deleted on the final step
        mOpenList.pop_front();

        // Handle each direction to be added, delete the rest
        // Also carry out an insertion sort by cost after adding each one
        // This ensures the cheapest node is always explored first

		for (int i = 0; i < validNeighbours.size(); i++)
		{
            int neighbour = validNeighbours.at(i);
            
            // Distance from start to neighbour via current
            int tentativeGCost = mGCosts[current] + getPosDist(current, neighbour);

            if (tentativeGCost < mGCosts[neighbour])
            {
                mClosedList[neighbour] = current;

                mGCosts[neighbour] = tentativeGCost;
                mFCosts[neighbour] = tentativeGCost + getPosDist(neighbour, mGoal);

                if (std::count(mOpenList.begin(), mOpenList.end(), neighbour) == 0)
                {
                    insertIndexIntoOpenList(neighbour);
                }
            }
		}
    }
    
    mOpenList.clear();

    // Need to reverse the list for printing
    int pos = mGoal;

    // Termination condition is executed after the step counter and output, so that mStart is included.
    // mStart points to a non -1 node, as mPath simply stores the shortest path to it.
    while (true)
    {
        mPath.push_front(pos);

        if (pos == -1)
            mPath.clear();
        if (pos == mStart || pos == -1)
            break;

        pos = mClosedList.at(pos);
    }
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


bool AStar::isVisited(int index)
{
    if (mClosedList[index] != -1)
        return true;
    return false;
}


// void AStar::outputCostsToFile()
// {
//     std::string fileName = "CostOutput.txt";
//     std::ofstream file;
//     file.open(fileName);

//     int size = mRows * mCols;
//     int digits = 0;
//     while (size != 0)
//     {
//         size /= 10;
//         digits++;
//     }
    
//     std::cout << "[ ";
//     for (int i = 0; i < mRows * mCols; i++)
//     {
//         int cost = mGCosts[i];
//         if (cost == INT_MAX)
//             cost = -1;
//         std::cout << std::setw(digits) << std::to_string(cost) << " ";
//         if (i % mCols == mCols - 1)
//             std::cout << "]" << std::endl << "[ ";
//     }
//     std::cout << "]" << std::endl;
//     file.close();
// }