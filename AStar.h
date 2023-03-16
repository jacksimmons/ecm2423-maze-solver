#include <vector>
#include <tuple>
#include "Vector2.h"
#include "Node.h"

std::tuple<std::vector<Vector2 *>, int> astar(Vector2 *start, Vector2 *goal, char* maze, bool* visited);

float calculateCost(Node *node, Vector2 *goal);
bool hasNodeExplored(Node *node, Vector2 *vec);
bool haveAnyNodesExplored(std::vector<Node *> nodes, Vector2 *vec);
