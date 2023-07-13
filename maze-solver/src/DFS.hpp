#include <vector>
#include <tuple>

#include "Vector2.hpp"
#include "Maze.hpp"

// Function templates
void runDFS(char, bool);
Path dfs(char, Vector2*, Vector2*, char*, bool*);