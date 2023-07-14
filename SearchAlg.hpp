#ifndef SEARCHALG_H
#define SEARCHALG_H 1

#include <vector>
#include "Vector2.hpp"

class SearchAlg {
protected:
    char mMazeType;
    char *mMaze;
    Vector2 *mStart;
    Vector2 *mGoal;
    std::vector<Vector2 *> mPath;
    bool mOutputMazeToFile;
public:
    SearchAlg(char, bool);
    ~SearchAlg();
    virtual void run() = 0;
};
#endif