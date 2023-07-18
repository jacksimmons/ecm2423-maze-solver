#include <string>

#include "SearchAlgorithm.hpp"

class DFS : public Search
{
public:
    DFS(std::string, bool, bool, bool);
    void run() override;
};