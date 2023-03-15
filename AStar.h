#include <vector>
#include <tuple>
#include "Vector2.h"
#include "Node.h"

std::tuple<std::vector<Vector2 *>, int> astar(Vector2 *start, Vector2 *goal, char* maze);

float calculateCost(Node *node);