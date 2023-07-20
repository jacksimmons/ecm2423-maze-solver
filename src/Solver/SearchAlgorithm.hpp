#ifndef SEARCHALG_HPP
#define SEARCHALG_HPP

#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <deque>

#include "../SearchSpace.hpp"


constexpr std::string_view PATH_OUTPUT_FILENAME = "out/PathOutput.txt";
constexpr std::string_view MAZE_OUTPUT_FILENAME = "out/MazeOutput.txt";


class SearchAlgorithm : public SearchSpace {
protected:
    std::string mFileName;
    std::string mSearchName;

    // Stores the maze file in vector form.
    std::vector<char> mMaze;
    // Stores the final path through the maze.
    std::deque<int> mPath;

    // Whether the algorithm outputs to various media.
    bool mOutputConsole;
    bool mOutputPath;
    bool mOutputMaze;
public:
    SearchAlgorithm(std::string filename, bool console, bool path, bool maze);
    void setup();
    virtual void run() = 0;

    void loadMaze();

    void outputPathToFile();
    void outputMazeToFile();
    virtual bool isVisited(int index) = 0;

    int calculateNumNodesVisited();
};


class InformedSearchAlgorithm : public SearchAlgorithm {
public:
    InformedSearchAlgorithm(std::string, bool, bool, bool);
    int getPosDist(int pos1, int pos2);
private:
    virtual bool isVisited(int index) = 0;
};


#endif