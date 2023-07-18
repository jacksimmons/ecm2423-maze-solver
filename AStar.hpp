#include <vector>
#include <list>
#include <deque>
#include <tuple>
#include <memory>
#include <unordered_map>

#include "SearchAlg.hpp"
#include "Maze.hpp"


class AStar : public SearchAlg {
private:    
    std::deque<int> mOpenList;

    std::vector<int> mGCosts;
    std::vector<int> mFCosts;
public:

    AStar(std::string, bool);
    void run() override;
    void astar();

    // Carries out one pass of an insertion sort, so that the open list acts a priority queue.
    void insertIndexIntoOpenList(int index);

    void outputCostsToFile();
};