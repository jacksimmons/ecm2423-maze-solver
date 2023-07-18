#include <iostream>
#include <fstream>
#include <stdexcept>

#include "SearchAlg.hpp"
#include "Maze.hpp"


SearchAlg::SearchAlg(std::string filename, bool bOutputMazeToFile)
{
    mStart = -1;
    mGoal = -1;
    mFileName = filename;
    mOutputMazeToFile = bOutputMazeToFile;
    loadMaze();

    if (mStart == -1)
        throw std::runtime_error((std::string)"No start node [" + START + "] was found.");
    else if (mGoal == -1)
        throw std::runtime_error((std::string)"No goal node [" + GOAL + "] was found.");

    // Output start and goal positions
    std::cout << "Start: " << posToStr(mStart) << std::endl;
    std::cout << "Goal: " << posToStr(mGoal) << std::endl;
}


// Extracts data from the maze file into corresponding data structures.
void SearchAlg::loadMaze()
{
    // Create input file stream
    std::ifstream fin;
    fin.open("mazes/" + mFileName);
    std::string line;

    int col = -1;
    int row = -1;

    int startX = -1;
    int startY = -1;

    int goalX = -1;
    int goalY = -1;

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
                startX = col; startY = row;
            }
            else if (ch == GOAL)
            {
                goalX = col; goalY = row;
            }
            else if (ch != EMPTY && ch != WALL)
            {
                // Skip pushing this character - it is invalid.
                col--;
                continue;
            }
            mMaze.push_back(ch);
        }
    }

    // Close the file
    fin.close();

    // Assume the user has given rectangular input
    mRows = row + 1;
    mCols = col + 1;

    // Now that mRows and mCols are defined, we can use cartesianToPos
    mStart = cartesianToPos(startX, startY);
    mGoal = cartesianToPos(goalX, goalY);
}


// Get the col component of a position.
int SearchAlg::getPosX(int pos)
{
    return pos % mCols;
}


// Get the row component of a position.
int SearchAlg::getPosY(int pos)
{
    return pos / mCols;
}


// Get the distance between two positions.
int SearchAlg::getPosDist(int i1, int i2)
{
    return abs(getPosX(i1 - i2)) + abs(getPosY(i1 - i2));
}


// Convert two coordinates to a position in the maze list.
int SearchAlg::cartesianToPos(int posx, int posy)
{
    return (posy) * mCols + posx;
}


// Convert a position in the maze list to a string coordinate.
std::string SearchAlg::posToStr(int pos)
{
    std::string x, y;
    x = std::to_string(getPosX(pos));
    y = std::to_string(getPosY(pos));
    std::string str = (std::string)"(" + x + ", " + y + ")";
    return str;
}


// Returns the position moved in a given direction (dirX and dirY should be -1, 0 or 1).
int SearchAlg::getPosPlusDir(int pos, int dirX, int dirY)
{
    return pos + dirX + (mCols * dirY);
}


// Output the path to PathOutput.txt.
void SearchAlg::outputPathToFile()
{
    std::string fileName = "PathOutput.txt";
    std::ofstream file;
    file.open(fileName);
    file << "--- " << mSearchName << " SEARCH " << "[" << mFileName << "]" << std::endl;

    for (int i = 0; i < mPath.size(); i++)
    {
        file << posToStr(mPath[i]) << std::endl;
    }
    file.close();
}


// Output the maze with the found path and visited nodes on it to MazeOutput.txt.
void SearchAlg::outputMazeToFile()
{
    std::string fileName = "MazeOutput.txt";
    std::ofstream file;
    file.open(fileName);

    // Iterate over every character in the maze array
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            int index = i * mCols + j;

            // Default is the original maze value
            char c = mMaze[index];
            if (c == EMPTY)
            {
                if (mVisited.at(index) != -1)
                {
                    c = VISITED;
                }

                if (std::find(mPath.begin(), mPath.end(), index) != mPath.end())
                {
                    c = PATH;
                }
            }
            // Output the character c to file
            file << c;
        }
        // Newline for next row
        file << std::endl;
    }

    file.close();
}


// Calculate the number of visited nodes
int SearchAlg::calculateNumNodesVisited()
{
	int numNodes = 0;
	for (int i = 0; i < mRows * mCols; i++)
	{
		if (mVisited[i] != -1)
		{
			numNodes++;
		}
	}
    return numNodes;
}