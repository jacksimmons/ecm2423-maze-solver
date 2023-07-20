#include <iostream>
#include <fstream>
#include <stdexcept>

#include "SearchAlgorithm.hpp"
#include "../Maze.hpp"


SearchAlgorithm::SearchAlgorithm(std::string filename, bool consoleOutput, bool pathOutput, bool mazeOutput)
 : SearchSpace()
{
    mStart = -1;
    mGoal = -1;
    mFileName = filename;
    mOutputConsole = consoleOutput;
    mOutputPath = pathOutput;
    mOutputMaze = mazeOutput;
    loadMaze();

    if (mStart == -1)
        throw std::runtime_error((std::string)"No start node [" + START + "] was found.");
    else if (mGoal == -1)
        throw std::runtime_error((std::string)"No goal node [" + GOAL + "] was found.");

    // Output start and goal positions
    if (mOutputConsole)
    {
        std::cout << "Start: " << posToStr(mStart) << std::endl;
        std::cout << "Goal: " << posToStr(mGoal) << std::endl;
    }
}


void SearchAlgorithm::setup()
{
    // Complete the search
    run();

    // Failure
    if (mPath.size() == 0)
    {
        std::cout << "Failed to find a solution." << std::endl;
        return;
    }

    // File output
    if (mOutputPath)
	    outputPathToFile();
    if (mOutputMaze)
        outputMazeToFile();
    
    // Execution statistics
    if (mOutputConsole)
    {
        std::cout << "Number of nodes visited: " << calculateNumNodesVisited() << std::endl;
        std::cout << "Number of steps in final path: " << mPath.size() << std::endl;
    }
}


// Extracts data from the maze file into corresponding data structures.
void SearchAlgorithm::loadMaze()
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


// Output the path to PathOutput.txt.
void SearchAlgorithm::outputPathToFile()
{
    std::string fileName = "out/PathOutput.txt";
    std::ofstream file;
    file.open(fileName);
    file << mSearchName << " SEARCH " << "[" << mFileName << "]" << std::endl;

    for (int i = 0; i < mPath.size(); i++)
    {
        file << posToStr(mPath[i]) << std::endl;
    }
    file.close();
}


// Output the maze with the found path and visited nodes on it to MazeOutput.txt.
void SearchAlgorithm::outputMazeToFile()
{
    std::string fileName = "out/MazeOutput.txt";
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
int SearchAlgorithm::calculateNumNodesVisited()
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


InformedSearchAlgorithm::InformedSearchAlgorithm(std::string fileName, bool c_out, bool p_out, bool m_out)
 : SearchAlgorithm(fileName, c_out, p_out, m_out) {}


// Get the distance between two positions.
int InformedSearchAlgorithm::getPosDist(int i1, int i2)
{
    return abs(getPosX(i1) - getPosX(i2)) + abs(getPosY(i1) - getPosY(i2));
}