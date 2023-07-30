#include <stdexcept>
#include <memory>
#include <random>
#include <fstream>

#include "GeneratorAlgorithm.hpp"


int main(int argc, char **argv)
{
    if (argc < 3)
    {
        throw std::invalid_argument("Expected 2 command-line arguments; cols (width) and rows (height).");
    }

    int cols = std::atoi(argv[1]);
    int rows = std::atoi(argv[2]);

    if (cols <= 2)
    {
        throw std::invalid_argument("cols must be an integer greater than 2.");
    }

    if (rows <= 2)
    {
        throw std::invalid_argument("rows must be an integer greater than 2.");
    }

    int start = std::rand() % cols;
    int goal = std::rand() % cols + cols * (rows - 1);

    std::shared_ptr<GeneratorAlgorithm> generator = std::make_shared<GeneratorAlgorithm>(rows, cols, start, goal);
}