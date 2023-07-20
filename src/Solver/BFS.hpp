#ifndef BFS_HPP
#define BFS_HPP

#include <string>

#include "SearchAlgorithm.hpp"

class BFS : public SearchAlgorithm
{
private:
    std::shared_ptr<int[]> mParentList;
    std::shared_ptr<bool[]> mVisited;
public:
    BFS(std::string, bool, bool, bool);
    void run() override;

    bool isVisited(int index) override;
};
#endif