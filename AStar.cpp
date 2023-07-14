#include <algorithm>
#include <queue>

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
    outputPathToFile("--- A* SEARCH " + getName(mMazeType) + " [" + getFilename(mMazeType) + "] ---", mPath);
    if (mOutputMazeToFile)
        outputMazeToFile(mMazeType, mMaze, mPath);

    // Execution statistics
    std::cout << "Number of nodes visited: " << mNumNodes << std::endl;
    std::cout << "Number of steps in final path: " << mPath.size() << std::endl;
}

void AStar::astar()
{
    // Initialise the deque of potential nodes
    std::deque<std::unique_ptr<CostNode>> potential_list;

    // Initialise the vector of Vector2 positions for explored, inactive nodes
    Path explored_list;

    // Initial setup for the potential list
    // And creating the node pointer
    std::unique_ptr<CostNode> node = std::make_unique<CostNode>(mGoal);
    node->setPos(std::make_unique<Vector2>(mStart->x, mStart->y));

    // Pointer to the current node's position
    std::unique_ptr<Vector2> pos;
    
    potential_list.push_front(node);

    // Loop the algorithm until the list is empty (invalid maze), or the algorithm terminates
    while (!potential_list.empty())
    {
        // Increment the numNodes counter
        // Since every loop is an atomic action - an exploration of a node.
        mNumNodes++;

        // Get current node
        node = std::make_unique<CostNode>(potential_list.front());

        // Points to the current node's position for convenience
        pos = node->getPos();

        // Check if the position is the goal early to save one pass
        // If this is the case, the goal has been reached and a path found
        // Terminate the loop
        if (*pos == *mGoal)
        {
            break;
        }

        // Create position vectors for all cardinal directions
        std::unique_ptr<Vector2> posUp = *pos + *g_UP;
        std::unique_ptr<Vector2> posDown = *pos + *g_DOWN;
        std::unique_ptr<Vector2> posLeft = *pos + *g_LEFT;
        std::unique_ptr<Vector2> posRight = *pos + *g_RIGHT;

        // Calculate whether or not each cardinal direction should be traversed
        // Uses node as a test case by setting its position to said cardinal direction
        bool canGoUp = false;
		if (!(posUp->y < 0 || mMaze[calculatePosIndex(mMazeType, *posUp)] == WALL))
			canGoUp = true;

        bool canGoLeft = false;
        if (!(posLeft->x < 0 || mMaze[calculatePosIndex(mMazeType, *posLeft)] == WALL))
            canGoLeft = true;

        bool canGoRight = false;
        if (!(posRight->x >= getCols(mMazeType) || mMaze[calculatePosIndex(mMazeType, *posRight)] == WALL))
            canGoRight = true;

        bool canGoDown = false;
        if (!(posDown->y >= getRows(mMazeType) || mMaze[calculatePosIndex(mMazeType, *posDown)] == WALL))
            canGoDown = true;

		std::vector<std::unique_ptr<Vector2>> nextPositions;

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
        potential_list.pop_front();
        explored_list.push_back(node->getPos());

        // Handle each direction to be added, delete the rest
        // Also carry out an insertion sort by cost after adding each one
        // This ensures the cheapest node is always explored first
		for (int i = 0; i < nextPositions.size(); i++)
		{
			std::unique_ptr<CostNode> next = std::make_unique<CostNode>(node, nextPositions.at(i), mGoal);
			potential_list.push_front(next);
			potential_list = insertionSortByCost(potential_list);
		}
    }

    // Load all positions from the finished node into the path
    std::unique_ptr<CostNode> node_ptr = node;
    while (node_ptr != nullptr)
    {
        std::unique_ptr<Vector2> pos = node_ptr->getPos();
        std::unique_ptr<Vector2> vec = std::make_unique<Vector2>(pos->x, pos->y);
        mPath.push_back(vec);
        node_ptr = std::static_pointer_cast<CostNode>(node_ptr->getPrev());
    }
    
    potential_list.clear();
}


// Performs one pass of insertion sort to place the front element into its
// correct position in the list.
std::deque<std::unique_ptr<CostNode>> insertionSortByCost(std::deque<std::unique_ptr<CostNode>> &list)
{
    // Quick exit if necessary
    if (list.size() <= 1)
        return list;

    // Get first node, cost pair in the list, then remove it from the list
    std::unique_ptr<CostNode> newNode = list.front();
    int cost = newNode->getCost();
    list.pop_front();

    // Re-insert the node in the correct position
    for (int i = 0; i < list.size() - 1; i++)
    {
        // We want the list to be sorted by cost ascending
        if (cost > list[i]->getCost())
        {
            continue;
        }
        // cost <= cost of this index, so insert before this element
        else
        {
            list.insert(list.begin() + i, newNode);
            return list;
        }
    }
    // The end of the list was reached, so highest cost in the list
    list.push_back(newNode);
    return list;
}


bool isNodeParentOf(std::unique_ptr<CostNode> potential_parent, std::unique_ptr<CostNode> potential_child)
{
    // Iterate through every node in node_ptr->getPrev()->...->0
    // Check if node_ptr points to the child
    // If not, continue iterating until the address 0x0 is reached
    // If 0x0 is reached, potential_parent is not a parent of potential_child.
    auto node_ptr = potential_parent;
    while (node_ptr != 0)
    {
        if (node_ptr == potential_child)
            return true;
        node_ptr = std::static_pointer_cast<CostNode>(node_ptr->getPrev());
    }
    return false;
}

// Commented
bool isAnyNodeParentOf(std::deque<std::shared_ptr<CostNode>> &nodes, std::unique_ptr<CostNode> node)
{
    // Iterates through every node in a deque, to see if any are parents of node.
    for (std::shared_ptr<CostNode> n : nodes)
    {
        if (isNodeParentOf(n, node))
            return true;
    }
    return false;
}

// Commented
bool hasNodeExplored(CostNode &node, Vector2 &pos)
{
    // Iterate through every node in node_ptr->getPrev()->...->nullptr
    // Check if *node_ptr->getPos() == *pos
    // If not, continue iterating until the address 0x0 is reached
    // If 0x0 is reached, the position has not been explored by this node
    // Casting is necessary as getPrev is an inherited method from Node, returning Node*.
    auto node_ptr = &node;
    while (node_ptr != nullptr)
    {
        if (*node_ptr->getPos() == pos)
            return true;
        node_ptr = (CostNode *)node_ptr->getPrev().get();
    }
    return false;
}

bool isPosInVector(std::unique_ptr<Vector2> pos, Path &vecs)
{
    // Iterate through every Vector2 in the vector, checking if
    // it has the same value as the provided position
    for (std::shared_ptr<Vector2> vec : vecs)
    {
        if (*pos == *vec)
            return true;
    }
    return false;
}