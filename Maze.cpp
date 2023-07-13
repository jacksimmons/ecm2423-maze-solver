// Commented fully
#include <fstream>
#include <tuple>

#include "Maze.h"
#include "Vector2.h"


// Convert the maze file into a char array
// Also provides start and goal vectors
std::tuple<char *, Vector2 *, Vector2 *> readMaze(char mazeType)
{
	char* maze = new char[getRows(mazeType) * getCols(mazeType)];
    Vector2 *start = new Vector2();
    Vector2 *goal = new Vector2();

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
            maze[i * getCols(mazeType) + j] = c;

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
Vector2 *calculatePos(Path &path, int index)
{
    Vector2 *pos = new Vector2();
    Vector2 *dir;
    for (int i = 0; i <= index; i++)
    {
        dir = path.at(i);
        pos->set(pos->x + dir->x, pos->y + dir->y);
    }
    return pos;
}


// Convert vector to index of maze array
int calculatePosIndex(char mazeType, Vector2 *pos)
{
    return (pos->y) * getCols(mazeType) + pos->x;
}


// Output the path to PathOutput.txt
void outputPathToFile(std::string header, Path path)
{
    std::string fileName = "PathOutput.txt";
    std::ofstream file;
    file.open(fileName);
    file << header << std::endl;
    // Print each position in (x,y) format
    for (int i = path.size() - 1; i >= 0; i--)
    {
        file << "(" << path[i]->x << ", " << path[i]->y << ")" << std::endl;
    }
    file.close();
}


void outputMazeToFile(char mazeType, char *maze, Path &path, bool *visited)
{
    std::string fileName = "MazeOutput.txt";
    std::ofstream file;
    file.open(fileName);

    // Iterate over every character in the maze array
    for (int i = 0; i < getRows(mazeType); i++)
    {
        for (int j = 0; j < getCols(mazeType); j++)
        {
            // Empty by default
            char c = '-';
            Vector2 *pos = new Vector2(j, i);
            if (maze[i * getCols(mazeType) + j] == WALL)
                c = '#';
            else
            {
                // Visited nodes marked v
                if (visited[i * getCols(mazeType) + j])
                    c = 'v';
                else
                    c = '-';

                // Overwrite the above if on the path with *
                for (int i = 0; i < path.size(); i++)
                {
                    if (*pos == *path[i])
                    {
                        c = '*';
                    }
                }
            }
            delete pos;
            // Output the character c to file
            file << c;
        }
        // Newline for next row
        file << std::endl;
    }
}


// Output maze when a visited array is not present
void outputMazeToFile(char mazeType, char *maze, Path &path)
{
    // Make new visited array and fill it with false
    bool *visited = new bool[getCols(mazeType) * getRows(mazeType)];
    for (int i = 0; i < getCols(mazeType) * getRows(mazeType); i++)
        visited[i] = false;
    outputMazeToFile(mazeType, maze, path, visited);
    delete[] visited;
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