#include "SearchAlg.hpp"
#include "Maze.hpp"

SearchAlg::SearchAlg(char mazeType, bool bOutputMazeToFile)
{
    mMazeType = mazeType;
    mOutputMazeToFile = bOutputMazeToFile;
    std::tuple<char *, Vector2 *, Vector2 *> mazeInfo = readMaze(mazeType);
    mMaze = std::get<0>(mazeInfo);
    mStart = std::get<1>(mazeInfo);
    mGoal = std::get<2>(mazeInfo);
}

SearchAlg::~SearchAlg()
{
    // Garbage collection
    delete[] mMaze;
    delete mGoal;
}