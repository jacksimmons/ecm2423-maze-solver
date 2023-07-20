#include "SearchSpace.hpp"


SearchSpace::SearchSpace() {}


SearchSpace::SearchSpace(int rows, int cols, int start, int goal)
{
    mRows = rows;
    mCols = cols;
    mStart = start;
    mGoal = goal;
}


int SearchSpace::getRows()
{
    return mRows;
}


int SearchSpace::getCols()
{
    return mCols;
}


int SearchSpace::getStart()
{
    return mStart;
}


int SearchSpace::getGoal()
{
    return mGoal;
}


// Get the col component of a position.
int SearchSpace::getPosX(int pos)
{
    return pos % mCols;
}


// Get the row component of a position.
int SearchSpace::getPosY(int pos)
{
    return pos / mCols;
}


// Convert two coordinates to a position in the maze list.
int SearchSpace::cartesianToPos(int posX, int posY)
{
    return (posY) * mCols + posX;
}


// Convert a position in the maze list to a string coordinate.
std::string SearchSpace::posToStr(int pos)
{
    std::string x, y;
    x = std::to_string(getPosX(pos));
    y = std::to_string(getPosY(pos));
    std::string str = (std::string)"(" + x + ", " + y + ")";
    return str;
}


// Returns the position moved in a given direction (dirX and dirY should be -1, 0 or 1).
int SearchSpace::getPosPlusDir(int pos, int dirX, int dirY)
{
    return pos + dirX + (mCols * dirY);
}