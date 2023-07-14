#include <vector>
#include <stack>
#include <tuple>

#include <vector>

#include "SearchAlg.hpp"
#include "Vector2.hpp"
#include "Maze.hpp"

class DFS : public SearchAlg
{
private:
    StackPath mPath;
    std::vector<bool> mVisited;
public:
    DFS(char, bool);
    void run() override;
    void dfs();
};