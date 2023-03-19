// Commented fully
#include <vector>
#include <deque>
#include <tuple>

#include "Vector2.h"
#include "Node.h"
#include "Maze.h"

// Function templates

// Sets up and starts the A* search algorithm.
void runAStar();
// Runs the A* search algorithm.
std::tuple<Path, int> astar(Vector2 *start, Vector2 *goal, char* maze);
// Carries out one pass of an insertion sort, to get a priority queue structure for potential_list.
std::deque<std::tuple<Node *, int>> insertionSortByCost(std::deque<std::tuple<Node *, int>> &list, Vector2 *goal);
// Calculates the cost of using this node in the path.
int calculateCost(Node *node, Vector2 *goal);
// Returns true if the first argument is higher up in the parent hierarchy.
// Meaning if the first argument is a parent, grandparent, etc. of the second.
bool isNodeParentOf(Node *potential_parent, Node *potential_child);
// Carries out isNodeParentOf for an entire deque.
bool isAnyNodeParentOf(std::deque<Node *> &nodes, Node *node);
// Returns true if the node, or any of its children, have traversed the provided Vector2 (*getPos() == *vec).
bool hasNodeExplored(Node *node, Vector2 *vec);
// Returns true if the Vector2* is present in the vector<Vector2*>.
bool isPosInVector(Vector2 *pos, Path &vecs);