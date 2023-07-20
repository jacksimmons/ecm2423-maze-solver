#ifndef DFS_HPP
#define DFS_HPP

#include <string>

#include "SearchAlgorithm.hpp"

class DFS : public SearchAlgorithm
{
private:
    std::shared_ptr<bool[]> mVisited;
public:
    DFS(std::string, bool, bool, bool);
    void run() override;

    bool isVisited(int index) override;
};
#endif