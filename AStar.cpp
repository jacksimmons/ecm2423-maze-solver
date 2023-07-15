#include <algorithm>
#include <queue>
#include <fstream>

#include <math.h>

#include "AStar.hpp"
#include "Constants.hpp"


AStar::AStar(char mazeType, bool bOutputMazeToFile) : SearchAlg(mazeType, bOutputMazeToFile)
{
    mNumNodes = 0;
}

void AStar::run()
{
    // Output the start and end of the maze
    std::cout << "Start: " << std::endl;
    Vector2::print(*mStart);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*mGoal);

    // Complete the search
    this->astar();

    // Output the path and maze to files
    outputPathToFile();
    if (mOutputMazeToFile)
        outputMazeToFile();

    // Execution statistics
    std::cout << "Number of nodes visited: " << mNumNodes << std::endl;
    std::cout << "Number of steps in final path: " << mPath.size() << std::endl;
}

void AStar::astar()
{
    // Initialise the vector of Vector2 positions for explored, inactive nodes
    AStarPath explored_list;

    // Initial setup for the potential list
    std::deque<std::shared_ptr<Node>> potentialList;
    potentialList.push_front(std::make_shared<Node>(nullptr, mStart, *mGoal));

    std::shared_ptr<Node> node;
    std::shared_ptr<Vector2> pos;

    // Loop the algorithm until the list is empty (invalid maze), or the algorithm terminates
    while (!potentialList.empty())
    {
        // Increment the numNodes counter
        // Since every loop is an atomic action - an exploration of a node.
        mNumNodes++;

        // Get current node
        node = potentialList.front();
        pos = node->getPos();

        // Check if the position is the goal early to save one pass
        // If this is the case, the goal has been reached and a path found
        // Terminate the loop
        if (*pos == *mGoal)
        {
            break;
        }

        // Create position vectors for all cardinal directions
        Vector2 posUp;
        posUp += *pos;
        posUp += *g_UP;

        Vector2 posDown;
        posDown += *pos;
        posDown += *g_DOWN;

        Vector2 posLeft;
        posLeft += *pos;
        posLeft += *g_LEFT;

        Vector2 posRight;
        posRight += *pos;
        posRight += *g_RIGHT;

        // Calculate whether or not each cardinal direction should be traversed
        // Uses node as a test case by setting its position to said cardinal direction
        bool canGoUp = false;
		if (!(posUp.y < 0 || mMaze[calculatePosIndex(mMazeType, posUp)] == WALL))
			canGoUp = true;

        bool canGoLeft = false;
        if (!(posLeft.x < 0 || mMaze[calculatePosIndex(mMazeType, posLeft)] == WALL))
            canGoLeft = true;

        bool canGoRight = false;
        if (!(posRight.x >= getCols(mMazeType) || mMaze[calculatePosIndex(mMazeType, posRight)] == WALL))
            canGoRight = true;

        bool canGoDown = false;
        if (!(posDown.y >= getRows(mMazeType) || mMaze[calculatePosIndex(mMazeType, posDown)] == WALL))
            canGoDown = true;

		std::vector<Vector2> nextPositions;

        // Calculate which directions need to be added to the potential_list
        // Ensures there are no loops in the path
		if (canGoLeft)
        {
			if (!hasNodeExplored(node, posLeft) && !isPosInVector(posLeft, explored_list))
				nextPositions.push_back(posLeft);
        }
        if (canGoRight)
        {
			if (!hasNodeExplored(node, posRight) && !isPosInVector(posRight, explored_list))
				nextPositions.push_back(posRight);
        }
        if (canGoUp)
        {
			if (!hasNodeExplored(node, posUp) && !isPosInVector(posUp, explored_list))
				nextPositions.push_back(posUp);
        }
        if (canGoDown)
        {
			if (!hasNodeExplored(node, posDown) && !isPosInVector(posDown, explored_list))
				nextPositions.push_back(posDown);
        }

        // Remove node at the front and put its position in the explored list
        // Placed after goal checking, so that node doesn't get deleted on the final step
        potentialList.pop_front();
        explored_list.push_back(node->getPos());

        // Handle each direction to be added, delete the rest
        // Also carry out an insertion sort by cost after adding each one
        // This ensures the cheapest node is always explored first
		for (int i = 0; i < nextPositions.size(); i++)
		{
            Vector2 nextPos = nextPositions.at(i);
            potentialList.push_front(std::make_shared<Node>(node, std::make_shared<Vector2>(nextPos.x, nextPos.y), *mGoal));
            insertionSortByCost(potentialList);
		}
    }

    // Load all positions from the finished node into the path
    std::shared_ptr<Node> node_ptr = std::move(node);

    while (node_ptr != nullptr)
    {
        mPath.push_back(node_ptr->getPos());
        node_ptr = std::move(node_ptr->getPrev());
    }
    
    potentialList.clear();
}

// Output the path to PathOutput.txt
void AStar::outputPathToFile()
{
    std::string fileName = "PathOutput.txt";
    std::ofstream file;
    file.open(fileName);
    file << "--- A* SEARCH " << getName(mMazeType) << "[" << getFilename(mMazeType) << "]" << std::endl;
    // Print each position in (x,y) format
    for (int i = mPath.size() - 1; i >= 0; i--)
    {
        file << "(" << mPath[i]->x << ", " << mPath[i]->y << ")" << std::endl;
    }
    file.close();
}

void AStar::outputMazeToFile()
{
    std::string fileName = "MazeOutput.txt";
    std::ofstream file;
    file.open(fileName);

    // Iterate over every character in the maze array
    for (int i = 0; i < getRows(mMazeType); i++)
    {
        for (int j = 0; j < getCols(mMazeType); j++)
        {
            // Empty by default
            char c = '-';
            Vector2 pos(j, i);
            if (mMaze[i * getCols(mMazeType) + j] == WALL)
                c = '#';
            else
            {
                c = '-';

                // Overwrite the above if on the path with *
                for (int i = 0; i < mPath.size(); i++)
                {
                    if (pos == *mPath[i])
                    {
                        c = '*';
                    }
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


// (Inplace) Performs one pass of insertion sort to place the front element into its
// correct position in the list.
// Sorts the list in ascending cost order, so that the back element has the highest cost.
void insertionSortByCost(std::deque<std::shared_ptr<Node>> &list)
{
    // Quick exit if necessary
    if (list.size() <= 1)
        return;

    // Get last node in the list (newest added) and now temp points to it.
    std::shared_ptr<Node> temp = std::move(list.front());
    list.pop_front();
    int cost = temp->getCost();

    // Re-insert the node in the correct position
    int size = list.size();
    for (int i = 0; i < size; i++)
    {
        // We want the list to be sorted by cost ascending
        if (cost > list[i]->getCost())
        {
            continue;
        }
        // cost <= cost of this index, so insert before this element
        else
        {
            list.insert(list.begin() + i, std::move(temp));
            return;
        }
    }
    // The end of the list was reached, and no elements had a higher cost.
    list.push_back(std::move(temp));
    return;
}


bool isNodeParentOf(std::shared_ptr<Node> potential_parent, std::shared_ptr<Node> potential_child)
{
    // Iterate through every node in node_ptr->getPrev()->...->0
    // Check if node_ptr points to the child
    // If not, continue iterating until the address 0x0 is reached
    // If 0x0 is reached, potential_parent is not a parent of potential_child.
    while (potential_parent != nullptr)
    {
        if (potential_parent == potential_child)
            return true;
        potential_parent = potential_parent->getPrev();
    }
    return false;
}

bool hasNodeExplored(std::shared_ptr<Node> node, Vector2& pos)
{
    // Iterate through every node in node_ptr->getPrev()->...->nullptr
    // Check if *node_ptr->getPos() == *pos
    // If not, continue iterating until the address 0x0 is reached
    // If 0x0 is reached, the position has not been explored by this node
    // Casting is necessary as getPrev is an inherited method from Node, returning Node*.
    while (node != nullptr)
    {
        if (*node->getPos() == pos)
            return true;
        node = node->getPrev();
    }
    return false;
}

bool isPosInVector(Vector2& pos, AStarPath& vecs)
{
    // Iterate through every Vector2 in the vector, checking if
    // it has the same value as the provided position
    for (int i = 0; i < vecs.size(); i++)
    {
        if (pos == *vecs[i])
            return true;
    }
    return false;
}