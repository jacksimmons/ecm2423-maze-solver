#include <vector>
#include <tuple>

#include "SearchAlg.hpp"
#include "Vector2.hpp"
#include "Maze.hpp"

class DFS : public SearchAlg
{
private:
    bool *mVisited;
public:
    DFS(char, bool);
    ~DFS();
    void run() override;
    void dfs();
};