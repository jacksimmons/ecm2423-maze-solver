#include <string>


enum class Algorithm {
    DFS,
    BFS,
    AStar,
    MazeGen,
};


enum class CommandLineError {
    None,
    NoArgValue,
};


void runSolver(std::string, Algorithm, int, bool, bool, bool);

std::string getMazeFileName(std::string input);
Algorithm getAlgorithm(std::string input);