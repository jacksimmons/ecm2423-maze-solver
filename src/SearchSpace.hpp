#ifndef SEARCHSPACE_HPP
#define SEARCHSPACE_HPP

#include <string>


class SearchSpace {
protected:
    int mRows;
    int mCols;

    // Index of the start and goal nodes in mMaze.
    int mStart;
    int mGoal;
public:
    SearchSpace();
    SearchSpace(int rows, int cols, int start, int goal);

    int getRows();
    int getCols();
    int getStart();
    int getGoal();

    int cartesianToPos(int posx, int posy);

    int getPosX(int pos);
    int getPosY(int pos);

    int getPosPlusDir(int pos, int dirX, int dirY);

    std::string posToStr(int pos);
};

#endif