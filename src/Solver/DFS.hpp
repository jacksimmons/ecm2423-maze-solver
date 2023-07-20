#ifndef DFS_HPP
#define DFS_HPP

#include <string>

#include "SearchAlgorithm.hpp"

class DFS : public SearchAlgorithm
{
public:
    DFS(std::string, bool, bool, bool);
    void run() override;
};
#endif