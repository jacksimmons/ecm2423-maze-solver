#include "SearchAlg.hpp"
#include "Maze.hpp"

SearchAlg::SearchAlg(char mazeType, bool bOutputMazeToFile)
{
    mMazeType = mazeType;
    mOutputMazeToFile = bOutputMazeToFile;
    std::tuple<std::vector<char>, std::shared_ptr<Vector2>, std::shared_ptr<Vector2>> mazeInfo = readMaze(mazeType);
    mMaze = std::get<0>(mazeInfo);
    mStart = std::get<1>(mazeInfo);
    mGoal = std::get<2>(mazeInfo);
}