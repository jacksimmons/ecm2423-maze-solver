#ifndef SEARCHALG_H
#define SEARCHALG_H 1

#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <deque>


class Search {
protected:
    std::string mFileName;
    std::string mSearchName;

    std::vector<char> mMaze;
    std::deque<int> mPath;
    std::vector<int> mVisited;

    bool mOutputConsole; // Console output
    bool mOutputPath; // Path output
    bool mOutputMaze; // Maze output

    int mRows;
    int mCols;
    int mStart;
    int mGoal;
public:
    Search(std::string filename, bool console, bool path, bool maze);
    void setup();
    virtual void run() = 0;

    void loadMaze();

    int cartesianToPos(int posx, int posy);

    int getPosX(int pos);
    int getPosY(int pos);

    int getPosPlusDir(int pos, int dirX, int dirY);

    std::string posToStr(int pos);
    void outputPathToFile();
    void outputMazeToFile();

    int calculateNumNodesVisited();
};


class InformedSearch : public Search {
public:
    InformedSearch(std::string, bool, bool, bool);
    int getPosDist(int pos1, int pos2);
};


#endif