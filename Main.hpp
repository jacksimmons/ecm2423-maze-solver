#include <string>


enum SearchType {
    SEARCHTYPE_DFS,
    SEARCHTYPE_BFS,
    SEARCHTYPE_ASTAR
};


void runSolver(std::string, SearchType, int, bool, bool, bool);