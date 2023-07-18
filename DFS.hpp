#include <vector>
#include <stack>
#include <tuple>
#include <string>

#include "SearchAlg.hpp"
#include "Maze.hpp"

class DFS : public SearchAlg
{
public:
    DFS(std::string, bool);
    void run() override;
    void dfs();
};