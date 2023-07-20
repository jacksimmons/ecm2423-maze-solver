#ifndef BFS_HPP
#define BFS_HPP

#include <string>

#include "SearchAlgorithm.hpp"

class BFS : public SearchAlgorithm
{
private:
    std::vector<int> mParentList;
public:
    BFS(std::string, bool, bool, bool);
    void run() override;
};
#endif