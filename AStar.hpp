#include <vector>
#include <deque>
#include <tuple>

#include "Vector2.hpp"
#include "CostNode.hpp"
#include "SearchAlg.hpp"
#include "Maze.hpp"

class AStar : public SearchAlg {
private:
    int mNumNodes;
public:
    AStar(char, bool);
    void run() override;
    void astar();
};

// Carries out one pass of an insertion sort, to get a priority queue structure for potential_list.
std::deque<std::unique_ptr<CostNode>> insertionSortByCost(std::deque<std::unique_ptr<CostNode>>&);

// Returns true if the first argument is higher up in the parent hierarchy.
// Meaning if the first argument is a parent, grandparent, etc. of the second.
bool isNodeParentOf(std::unique_ptr<CostNode>, std::unique_ptr<CostNode>);

// Carries out isNodeParentOf for an entire deque.
bool isAnyNodeParentOf(std::deque<std::unique_ptr<CostNode>>&, std::unique_ptr<CostNode>);

// Returns true if the node, or any of its children, have traversed the provided Vector2 (*getPos() == *vec).
bool hasNodeExplored(std::unique_ptr<CostNode>, std::unique_ptr<Vector2>);

// Returns true if the std::unique_ptr<Vector2> is present in the vector<std::unique_ptr<Vector2>>.
bool isPosInVector(std::unique_ptr<Vector2>, Path&);