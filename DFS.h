#include <vector>
#include <tuple>

#include "Vector2.h"
#include "Maze.h"

// Function templates
void runDFS(char, bool);
Path dfs(char, Vector2*, Vector2*, char*, bool*);