#ifndef SEARCHALG_H
#define SEARCHALG_H 1

#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <deque>


class SearchAlg {
protected:
    std::string mFileName;
    std::string mSearchName;

    std::vector<char> mMaze;
    std::deque<int> mPath;
    std::vector<int> mVisited;

    int mStart;
    int mGoal;

    bool mOutputMazeToFile;

    int mRows;
    int mCols;
public:
    SearchAlg(std::string filename, bool outputMaze);
    virtual void run() = 0;

    void loadMaze();

    int cartesianToPos(int posx, int posy);

    int getPosX(int pos);
    int getPosY(int pos);

    int getPosDist(int pos1, int pos2);
    int getPosPlusDir(int pos, int dirX, int dirY);

    std::string posToStr(int pos);
    void outputPathToFile();
    void outputMazeToFile();

    int calculateNumNodesVisited();
};
#endif