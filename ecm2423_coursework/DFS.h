#include <vector>
#include <tuple>

#include "Vector2.h"
#include "Maze.h"

// Function templates
void runDFS();
Path dfs(Vector2 *start, Vector2 *goal, char* maze, bool* visited);