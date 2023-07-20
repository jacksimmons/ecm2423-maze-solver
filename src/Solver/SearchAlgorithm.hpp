#ifndef SEARCHALG_HPP
#define SEARCHALG_HPP

#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <deque>

#include "../SearchSpace.hpp"


class SearchAlgorithm : public SearchSpace {
protected:
    std::string mFileName;
    std::string mSearchName;

    // Stores the maze file in vector form.
    std::vector<char> mMaze;
    // Stores the final path through the maze.
    std::deque<int> mPath;
    // Data structure of equal size to mMaze.
    // In A*, this is used as the closed list (each index stores the node it came from).
    // In DFS/BFS, this is used to just store which nodes have been visited.
    // Either way, if a value is -1 at index i, then i has not been visited, otherwise it has.
    std::vector<int> mVisited;

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

    int calculateNumNodesVisited();
};


class InformedSearchAlgorithm : public SearchAlgorithm {
public:
    InformedSearchAlgorithm(std::string, bool, bool, bool);
    int getPosDist(int pos1, int pos2);
};


#endif