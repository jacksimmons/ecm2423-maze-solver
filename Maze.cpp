#include <tuple>
#include <vector>
#include <fstream>
#include <cmath>

#include "Maze.hpp"
#include "Vector2.hpp"


// Convert the maze file into a char array
// Also provides start and goal vectors
std::tuple<std::vector<char>, std::shared_ptr<Vector2>, std::shared_ptr<Vector2>> readMaze(char mazeType)
{
    std::vector<char> maze;
    std::shared_ptr<Vector2> start = std::make_shared<Vector2>();
    std::shared_ptr<Vector2> goal = std::make_shared<Vector2>();

    // Create input file stream
    std::ifstream fin;
    fin.open(getFilename(mazeType));

    // Iterate over the entire file, putting it into an array
    for (int i = 0; i < getRows(mazeType); i++)
    {
        for (int j = 0; j < getCols(mazeType); j++)
        {
            char c;
            fin >> c;
            maze.push_back(c);

            // If we're on the first row, and there is an empty node
            // Then this must be the start node
            if (i == 0 && c == EMPTY)
            {
                start->x = j;
                start->y = i;
            }

            // If we're on the final row, and there is an empty node
            // Then this must be the goal node
            else if (i == getRows(mazeType) - 1 && c == EMPTY)
            {
                goal->x = j;
                goal->y = i;
            }
        }
    }

    // Close the file
    fin.close();

    return std::make_tuple(maze, start, goal);
}


// Get the ith element of the path, and return its vector form
std::unique_ptr<Vector2> calculatePos(DFSPath& path, int index)
{
    std::unique_ptr<Vector2> pos = std::make_unique<Vector2>();
    for (int i = 0; i <= index; i++)
        *pos += *path.at(i);
    return pos;
}


// Convert vector to index of maze array
int posToIndex(char mazeType, Vector2& pos)
{
    return (pos.y) * getCols(mazeType) + pos.x;
}


float getIndexDistance(int i1, int i2, int cols)
{
    int dx = (i1 - i2) % cols;
    int dy = (i1 - i2) / cols;
    return abs(dx) + abs(dy);
}


int getRows(char type)
{
	if (type == 'E')
		return E_ROWS;
	if (type == 'M')
		return M_ROWS;
	if (type == 'L')
		return L_ROWS;
	if (type == 'V')
		return V_ROWS;
	return -1;
}


int getCols(char type)
{
	if (type == 'E')
		return E_COLS;
	if (type == 'M')
		return M_COLS;
	if (type == 'L')
		return L_COLS;
	if (type == 'V')
		return V_COLS;
	return -1;
}


std::string getFilename(char type)
{
	if (type == 'E')
		return E_FILENAME;
	if (type == 'M')
		return M_FILENAME;
	if (type == 'L')
		return L_FILENAME;
	if (type == 'V')
		return V_FILENAME;
	return "";
}


std::string getName(char type)
{
	if (type == 'E')
		return E_NAME;
	if (type == 'M')
		return M_NAME;
	if (type == 'L')
		return L_NAME;
	if (type == 'V')
		return V_NAME;
	return "";
}