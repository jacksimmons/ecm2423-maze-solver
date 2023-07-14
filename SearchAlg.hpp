#ifndef SEARCHALG_H
#define SEARCHALG_H 1

#include <vector>
#include "Vector2.hpp"

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
};
#endif