#include <tuple>
#include <vector>
#include <fstream>
#include <cmath>

#include "Maze.hpp"
#include "Vector2.hpp"


// Convert the maze file into a char vector
// Also provides start and goal vectors, and number of rows and cols
std::tuple<std::vector<char>, std::shared_ptr<Vector2>, std::shared_ptr<Vector2>, int, int> readMaze(std::string fileName)
{
    std::vector<char> maze;
    std::shared_ptr<Vector2> start = std::make_shared<Vector2>();
    std::shared_ptr<Vector2> goal = std::make_shared<Vector2>();

    // Create input file stream
    std::ifstream fin;
    fin.open("mazes/" + fileName);
    std::string line;

    int col = -1;
    int row = -1;

    // Iterate over every line
    while (std::getline(fin, line))
    {
        col = -1;
        row++;
        for (int i = 0; i < line.size(); i++)
        {
            char ch = line.at(i);
            col++;
            if (ch == START)
            {
                start->x = col;
                start->y = row;
            }
            else if (ch == GOAL)
            {
                goal->x = col;
                goal->y = row;
            }
            else if (ch != EMPTY && ch != WALL)
            {
                // Skip pushing this character - it is invalid.
                col--;
                continue;
            }
            maze.push_back(ch);
        }
    }

    // Close the file
    fin.close();

    // Assume the user has given rectangular input
    int rows = row + 1;
    int cols = col + 1;
    return std::make_tuple(maze, start, goal, rows, cols);
}


// Get the ith element of the path, and return its vector form
std::unique_ptr<Vector2> calculatePos(DFSPath& path, int index)
{
    std::unique_ptr<Vector2> pos = std::make_unique<Vector2>();
    for (int i = 0; i <= index; i++)
        *pos += *path.at(i);
    return pos;
}


float getIndexDistance(int i1, int i2, int cols)
{
    int dx = (i1 - i2) % cols;
    int dy = (i1 - i2) / cols;
    return abs(dx) + abs(dy);
}