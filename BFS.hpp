#include <string>

#include "SearchAlgorithm.hpp"

class BFS : public Search
{
private:
    std::vector<int> mParentList;
public:
    BFS(std::string, bool, bool, bool);
    void run() override;
};