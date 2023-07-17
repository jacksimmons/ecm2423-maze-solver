#include <vector>
#include <list>
#include <deque>
#include <tuple>
#include <memory>
#include <unordered_map>

#include "Vector2.hpp"
#include "Node.hpp"
#include "SearchAlg.hpp"
#include "Maze.hpp"

class AStar : public SearchAlg {
private:
    int mNumNodes;
    
    std::deque<int> mOpenList;
    std::vector<int> mClosedList;
    std::deque<int> mPath;

    std::vector<float> mGCosts;
    std::vector<float> mFCosts;

public:

    AStar(std::string, bool);
    void run() override;
    void astar();

    // Carries out one pass of an insertion sort, so that the open list acts a priority queue.
    void insertIndexIntoOpenList(int index);

    void outputPathToFile() override;
    void outputMazeToFile() override;
};