#include <iostream>

#include "BFS.hpp"
#include "../Maze.hpp"


BFS::BFS(std::string filename, bool c_out, bool p_out, bool m_out) 
: SearchAlgorithm(filename, c_out, p_out, m_out)
{
    // Logging
    mSearchName = "BFS";

    mParentList = std::shared_ptr<int[]>(new int[mRows * mCols]);
    mVisited = std::shared_ptr<bool[]>(new bool[mRows * mCols]);

    for (int i = 0; i < mRows * mCols; i++)
    {
        mVisited[i] = false;
        mParentList[i] = -1;
    }

    // Mark starting node as visited as we start here (visited is != -1, see InformedSearchAlgorithm.cpp)
    mVisited[mStart] = true;
    mPath.push_back(mStart);

    setup();
}


void BFS::run()
{
    while (!mPath.empty())
    {
        int current = mPath.front();
        mPath.pop_front();

        if (current == mGoal)
        {
            break;
        }

        int up = getPosPlusDir(current, 0, -1);
        int down = getPosPlusDir(current, 0, 1);
        int left = getPosPlusDir(current, -1, 0);
        int right = getPosPlusDir(current, 1, 0);

        std::vector<int> adjacencies;

        if ((up > 0) && (mMaze[up] != WALL))
            adjacencies.push_back(up);
        if ((down < mRows * mCols) && (mMaze[down] != WALL))
            adjacencies.push_back(down);
        if ((left % mCols != 0) && left > 0 && (mMaze[left] != WALL))
            adjacencies.push_back(left);
        if ((right % mCols) != (mCols - 1) && right < mRows * mCols && (mMaze[right] != WALL))
            adjacencies.push_back(right);

        // For all adjacent nodes
        for (int i = 0; i < adjacencies.size(); i++)
        {
            int adj = adjacencies[i];
            // If adjacency hasn't been explored
            if (!mVisited[adj])
            {
                mVisited[adj] = true;
                mParentList[adj] = current;
                mPath.push_back(adj);
            }
        }
    }

    mPath.clear();

    int pos = mGoal;
    while (true)
    {
        mPath.push_front(pos);

        if (pos == -1)
            mPath.clear();
        if (pos == mStart || pos == -1)
            break;

        pos = mParentList[pos];
    }
}


bool BFS::isVisited(int index)
{
    return mVisited[index];
}