#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <list>
#include <deque>
#include <tuple>
#include <memory>
#include <unordered_map>

#include "SearchAlgorithm.hpp"


class AStar : public InformedSearchAlgorithm {
private:    
    std::deque<int> mOpenList;

    std::vector<int> mGCosts;
    std::vector<int> mFCosts;
public:
    AStar(std::string, bool, bool, bool);
    void run() override;

    // Carries out one pass of an insertion sort, so that the open list acts a priority queue.
    void insertIndexIntoOpenList(int index);
};
#endif