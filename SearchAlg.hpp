#ifndef SEARCHALG_H
#define SEARCHALG_H 1

#include <memory>
#include <vector>
#include <deque>

#include "Vector2.hpp"

typedef std::deque<std::shared_ptr<Vector2>> DFSPath;
typedef std::vector<std::shared_ptr<Vector2>> AStarPath;

class SearchAlg {
protected:
    char mMazeType;
    std::vector<char> mMaze;
    std::shared_ptr<Vector2> mStart;
    std::shared_ptr<Vector2> mGoal;
    bool mOutputMazeToFile;
public:
    SearchAlg(char, bool);
    virtual void run() = 0;
    virtual void outputPathToFile() = 0;
    virtual void outputMazeToFile() = 0;
};
#endif