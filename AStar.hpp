#include <vector>
#include <list>
#include <deque>
#include <tuple>

#include "Vector2.hpp"
#include "Node.hpp"
#include "SearchAlg.hpp"
#include "Maze.hpp"

class AStar : public SearchAlg {
private:
    int mNumNodes;
    AStarPath mPath;
public:
    AStar(char, bool);
    void run() override;
    void astar();
    void outputPathToFile() override;
    void outputMazeToFile() override;
};

// Carries out one pass of an insertion sort, to get a priority queue structure for potential_list.
void insertionSortByCost(std::deque<std::shared_ptr<Node>>&);

// Returns true if the first argument is higher up in the parent hierarchy.
// Meaning if the first argument is a parent, grandparent, etc. of the second.
bool isNodeParentOf(std::shared_ptr<Node>, std::shared_ptr<Node>);

// Returns true if the node, or any of its children, have traversed the provided Vector2 (*getPos() == *vec).
bool hasNodeExplored(std::shared_ptr<Node>, Vector2&);

// Returns true if the std::unique_ptr<Vector2> is present in the vector<std::unique_ptr<Vector2>>.
bool isPosInVector(Vector2&, AStarPath&);

void outputPathToFile(std::string header, std::vector<std::shared_ptr<Vector2>>&);