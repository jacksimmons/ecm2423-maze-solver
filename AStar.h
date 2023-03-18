#include <vector>
#include <deque>
#include <tuple>
#include <memory>

#include "Vector2.h"
#include "Node.h"
#include "Maze.h"

void runAStar();
std::tuple<Path, int, int> astar(Vector2 *start, Vector2 *goal, char* maze);
std::deque<Node *> insertionSortByCost(std::deque<Node *> &list, Vector2 *goal);
float calculateCost(Node *node, Vector2 *goal);
bool isNodeParentOf(Node *potential_parent, Node *potential_child);
bool isAnyNodeParentOf(std::deque<Node *> &nodes, Node *node);
bool hasNodeExplored(Node *node, Vector2 *vec);
bool haveAnyNodesExplored(std::deque<Node *> &nodes, Vector2 *vec);
bool isPosInVector(Vector2 *pos, std::vector<Vector2 *> &vecs);