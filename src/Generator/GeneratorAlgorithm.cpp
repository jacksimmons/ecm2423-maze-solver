#include <memory>
#include <iostream>
#include <fstream>

#include "GeneratorAlgorithm.hpp"
#include "../Maze.hpp"


GeneratorAlgorithm::GeneratorAlgorithm(int rows, int cols, int start, int goal)
: SearchSpace(rows, cols, start, goal)
{
    mMaze = std::shared_ptr<char[]>(new char[rows * cols]);
    mVisited = std::shared_ptr<bool[]>(new bool[rows * cols]);

    initialiseDataStructures();
    tunnelOutMazeArray();
    mMaze[start] = 's';
    mMaze[goal] = 'g';
    outputMazeArray();
}


void GeneratorAlgorithm::initialiseDataStructures()
{
    for (int i = 0; i < mRows * mCols; i++)
    {
        mMaze[i] = '#';
        mVisited[i] = false;
    }
}


void GeneratorAlgorithm::tunnelOutMazeArray()
{
    int currentPos = mStart;
    mVisited[mStart] = true;
    mStack.push(mStart);
    while (!mStack.empty())
    {
        currentPos = mStack.top();

        int left = getPosPlusDir(currentPos, -1, 0);
        int right = getPosPlusDir(currentPos, 1, 0);
        int up = getPosPlusDir(currentPos, 0, -1);
        int down = getPosPlusDir(currentPos, 0, 1);

        std::vector<int> neighbours;

        if (posInInnerBox(left) && !mVisited[left] && !tryExcludeNeighbour(left, -1, 0))
            neighbours.push_back(left);
        if (posInInnerBox(right) && !mVisited[right] && !tryExcludeNeighbour(right, 1, 0))
            neighbours.push_back(right);
        if (up > mCols && !mVisited[up] && !tryExcludeNeighbour(up, 0, -1))
            neighbours.push_back(up);
        if (down < mRows * (mCols - 1) && !mVisited[down] && !tryExcludeNeighbour(down, 0, 1))
            neighbours.push_back(down);

        int numNeighbours = neighbours.size();
        if (numNeighbours == 0)
        {
            mStack.pop();
            continue;
        }

        int randomNeighbourIndex = std::rand() % numNeighbours;
        int neighbour = neighbours.at(randomNeighbourIndex);
        if (mMaze[neighbour] == WALL)
            mMaze[neighbour] = EMPTY;
        mVisited[neighbour] = true;
        mStack.push(neighbour);
    }
}


// The maze is surrounded by a 1-thick box of wall/start/goal nodes.
// Anything inside this box is the "inner box", which can have empty nodes.
bool GeneratorAlgorithm::posInInnerBox(int pos)
{
    int posX = getPosX(pos);
    int posY = getPosY(pos);

    if ((posX > 0 && posX < mCols - 1) && (posY > 0 && posY < mRows - 1))
        return true;
    return false;
}


// Adds the neighbour to mVisited and returns false, if adding the neighbour would form a 2x2 empty
// space (i.e. the beginning of a non-single-file path)
bool GeneratorAlgorithm::tryExcludeNeighbour(int neighbour, int arcDirX, int arcDirY)
{
    int checkParallel;
    int checkNegPerp;
    int checkPosPerp;
    if (arcDirX != 0)
    {
        checkParallel = getPosPlusDir(neighbour, arcDirX, 0);
        checkNegPerp = getPosPlusDir(neighbour, 0, -arcDirX);
        checkPosPerp = getPosPlusDir(neighbour, 0, arcDirX);
    }
    else
    {
        checkParallel = getPosPlusDir(neighbour, 0, arcDirY);
        checkNegPerp = getPosPlusDir(neighbour, -arcDirY, 0);
        checkPosPerp = getPosPlusDir(neighbour, arcDirY, 0);
    }

    if (mMaze[checkParallel] == WALL && mMaze[checkNegPerp] == WALL && mMaze[checkPosPerp] == WALL)
        return false;
    mVisited[neighbour] = true;
    return true;
}


void GeneratorAlgorithm::outputMazeArray()
{
    std::string fileName = "mazes/GeneratorOutput.txt";
    std::ofstream file(fileName);
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            file << mMaze[i * mCols + j];
        }
        file << std::endl;
    }
    file.close();
}