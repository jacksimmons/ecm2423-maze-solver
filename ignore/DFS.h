#include <vector>
#include <tuple>
#include "Vector2.h"

std::tuple<std::vector<Vector2 *>, int> dfs(Vector2 *start, Vector2 *goal, char* maze, bool* visited);