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


void handleRunSolver(std::string maze, Algorithm alg, int iters, bool c_out, bool p_out, bool m_out, bool s_out);
void runSolver(std::string, Algorithm, int, bool, bool, bool);
void outputStats(double timeTaken, std::string algName, int iters, std::string mazeName);
std::string getMazeFileName(std::string input);
Algorithm strToAlgorithm(std::string input);
std::string algorithmToStr(Algorithm alg);