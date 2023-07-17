#include "SearchAlg.hpp"
#include "Maze.hpp"

SearchAlg::SearchAlg(std::string filename, bool bOutputMazeToFile)
{
    mFileName = filename;
    mOutputMazeToFile = bOutputMazeToFile;
    std::tuple<std::vector<char>, std::shared_ptr<Vector2>, std::shared_ptr<Vector2>, int, int> mazeInfo = readMaze(mFileName);
    mMaze = std::get<0>(mazeInfo);
    mStart = std::get<1>(mazeInfo);
    mGoal = std::get<2>(mazeInfo);
    mRows = std::get<3>(mazeInfo);
    mCols = std::get<4>(mazeInfo);
}

// Convert vector to index of maze array
int SearchAlg::posToIndex(Vector2& pos)
{
    return (pos.y) * mCols + pos.x;
}