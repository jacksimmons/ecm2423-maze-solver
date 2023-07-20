#include <stack>
#include <vector>
#include <memory>

#include "../SearchSpace.hpp"


class GeneratorAlgorithm : public SearchSpace
{
private:
    std::stack<int> mStack;
    std::shared_ptr<bool[]> mVisited;
    std::shared_ptr<char[]> mMaze;
public:
    GeneratorAlgorithm(int rows, int cols, int start, int goal);
    void initialiseDataStructures();
    void tunnelOutMazeArray();
    bool posInInnerBox(int pos);
    bool tryExcludeNeighbour(int neighbour, int arcDirX, int arcDirY);
    void outputMazeArray();
};