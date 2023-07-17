#include <vector>
#include <stack>
#include <tuple>
#include <string>

#include "SearchAlg.hpp"
#include "Vector2.hpp"
#include "Maze.hpp"

class DFS : public SearchAlg
{
private:
    std::vector<bool> mVisited;
    DFSPath mPath;
public:
    DFS(std::string, bool);
    void run() override;
    void dfs();
    void outputPathToFile() override;
    void outputMazeToFile() override;
};