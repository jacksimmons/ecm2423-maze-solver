// Commented fully
#include <algorithm>
#include <ctime>
#include <queue>

#include <math.h>

#include "AStar.h"
#include "Constants.h"

// Commented
void runAStar(char mazeType, bool outputMaze)
{
    // Initialise the maze
    char* maze;

    // Initialise the vectors used to control the search
    Vector2 *start;
    Vector2 *goal;

    // Read the vectors from the read maze
    std::tuple<char *, Vector2 *, Vector2 *> mazeInfo = readMaze(mazeType);
    maze = std::get<0>(mazeInfo);
    start = std::get<1>(mazeInfo);
    goal = std::get<2>(mazeInfo);

    // Output the start and end of the maze
    std::cout << "Start: " << std::endl;
    Vector2::print(*start);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*goal);

    // Complete the search
    std::tuple<Path, int> pathData = astar(mazeType, start, goal, maze);
    Path finalPath = std::get<0>(pathData);
    int numNodes = std::get<1>(pathData);

    // Output the path and maze to files
    outputPathToFile("--- A* SEARCH " + getName(mazeType) + " [" + getFilename(mazeType) + "] ---", finalPath);
    if (outputMaze)
        outputMazeToFile(mazeType, maze, finalPath);

    // Execution statistics
    std::cout << "Number of nodes visited: " << numNodes << std::endl;
    std::cout << "Number of steps in final path: " << finalPath.size() << std::endl;

    // Garbage collection
    delete[] maze;
    delete goal;

    while (!finalPath.empty())
    {
        Vector2 *last = finalPath.back();
        finalPath.pop_back();
        delete last;
    }
}


std::tuple<Path, int> astar(char mazeType, Vector2 *start, Vector2 *goal, char* maze)
{
    // Counter for how many nodes are explored
    int numNodes = 0;

    // Pointer to the current node's position
    Vector2 *pos;

    // Initialise the path
    Path path;

    // Initialise the deque of potential nodes
    std::deque<std::tuple<Node *, int>> potential_list;
    
    // Initialise the queue of used nodes for garbage collection
    std::queue<Node *> hierarchy_queue;

    // Initialise the vector of Vector2 positions for explored, inactive nodes
    Path explored_list;

    // Initial setup for the potential list
    // And creating the node pointer
    Node *node = new Node();
    node->setPos(start);
    
    potential_list.push_front(std::make_tuple(node, 0));

    // Loop the algorithm until the list is empty (invalid maze), or the algorithm terminates
    while (!potential_list.empty())
    {
        // Increment the numNodes counter
        // Since every loop is an atomic action - an exploration of a node.
        numNodes++;

        // Get current node
        node = std::get<0>(potential_list.front());

        // Points to the current node's position for convenience
        pos = node->getPos();

        // Check if the position is the goal early to save one pass
        // If this is the case, the goal has been reached and a path found
        // Terminate the loop
        if (*pos == *goal)
        {
            break;
        }

        // Create position vectors for all cardinal directions
        Vector2 *posUp = *pos + *UP;
        Vector2 *posLeft = *pos + *LEFT;
        Vector2 *posRight = *pos + *RIGHT;
        Vector2 *posDown = *pos + *DOWN;

        // Calculate whether or not each cardinal direction should be traversed
        // Uses node as a test case by setting its position to said cardinal direction
        node->setPos(posUp);
        bool canGoUp = false;
        if (!(pos->y <= 0 || maze[calculatePosIndex(mazeType, posUp)] == WALL))
            canGoUp = true;

        node->setPos(posLeft);
        bool canGoLeft = false;
        if (!(pos->x <= 0 || maze[calculatePosIndex(mazeType, posLeft)] == WALL))
            canGoLeft = true;

        node->setPos(posRight);
        bool canGoRight = false;
        if (!(pos->x >= getCols(mazeType) - 1 || maze[calculatePosIndex(mazeType, posRight)] == WALL))
            canGoRight = true;

        node->setPos(posDown);
        bool canGoDown = false;
        if (!(pos->y >= getRows(mazeType) - 1 || maze[calculatePosIndex(mazeType, posDown)] == WALL))
            canGoDown = true;
        
        // Set the position back
        node->setPos(pos);

        // Booleans to control which directions are going to be traversed
        bool goingUp = false;
        bool goingLeft = false;
        bool goingRight = false;
        bool goingDown = false;

        // Calculate which directions need to be added to the potential_list
        // Ensures there are no loops in the path, and 
        if (canGoLeft)
        {
            if (!hasNodeExplored(node, posLeft) && !isPosInVector(posLeft, explored_list))
                goingLeft = true;
        }
        if (canGoRight)
        {
            if (!hasNodeExplored(node, posRight) && !isPosInVector(posRight, explored_list))
                goingRight = true;
        }
        if (canGoUp)
        {
            if (!hasNodeExplored(node, posUp) && !isPosInVector(posUp, explored_list))
                goingUp = true;
        }
        if (canGoDown)
        {
            if (!hasNodeExplored(node, posDown) && !isPosInVector(posDown, explored_list))
                goingDown = true;
        }

        // Remove node at the front and put its position in the explored list
        // Placed after goal checking, so that node doesn't get deleted on the final step
        potential_list.pop_front();
        explored_list.push_back(node->getPos());

        // Handle each direction to be added, delete the rest
        // Also carry out an insertion sort by cost after adding each one
        // This ensures the cheapest node is always explored first
        if (goingUp)
        {
            Node *next = new Node(node, posUp);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            potential_list = insertionSortByCost(potential_list, goal);
            hierarchy_queue.push(next);
        }
        else
            delete posUp;
        
        if (goingLeft)
        {
            Node *next = new Node(node, posLeft);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            potential_list = insertionSortByCost(potential_list, goal);
            hierarchy_queue.push(next);
        }
        else
            delete posLeft;
        
        if (goingRight)
        {
            Node *next = new Node(node, posRight);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            potential_list = insertionSortByCost(potential_list, goal);
            hierarchy_queue.push(next);
        }
        else
            delete posRight;

        if (goingDown)
        {
            Node *next = new Node(node, posDown);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            potential_list = insertionSortByCost(potential_list, goal);
            hierarchy_queue.push(next);
        }
        else
            delete posDown;
    }

    // Load all positions from the finished node into the path
    Node *node_ptr = node;
    while (node_ptr != 0)
    {
        Vector2 *pos = node_ptr->getPos();
        Vector2 *vec = new Vector2(pos->x, pos->y);
        path.push_back(vec);
        node_ptr = node_ptr->getPrev();
    }

    // Garbage collection (Node)
    while (!hierarchy_queue.empty())
    {
        Node *node_ptr = hierarchy_queue.front();
        hierarchy_queue.pop();
        if (!isPosInVector(node_ptr->getPos(), explored_list))
            delete node_ptr->getPos();
        delete node_ptr;
    }
    
    // Garbage collection (Vector2)
    while (!explored_list.empty())
    {   
        Vector2 *pos = explored_list.back();
        explored_list.pop_back();
        delete pos;
    }
    
    potential_list.clear();

    // Termination of the algorithm and return to runAStar
    return std::make_tuple(path, numNodes);
}


std::deque<std::tuple<Node *, int>> insertionSortByCost(std::deque<std::tuple<Node *, int>> &list, Vector2 *goal)
{
    // Quick exit if necessary
    if (list.size() <= 1)
        return list;

    // Get first node, cost pair in the list, then remove it from the list
    std::tuple<Node *, int> pair = list.front();
    Node *new_node = std::get<0>(pair);
    int cost = std::get<1>(pair);
    list.pop_front();

    // Re-insert the node in the correct position
    for (int i = 0; i < list.size() - 1; i++)
    {
        // We want the list to be sorted by cost ascending
        if (cost > std::get<1>(list[i]))
        {
            continue;
        }
        // cost <= cost of this index, so insert before this element
        else
        {
            list.insert(list.begin() + i, pair);
            return list;
        }
    }
    // The end of the list was reached, so highest cost in the list
    list.push_back(pair);
    return list;
}


int calculateCost(Node *node, Vector2 *goal)
{
    // Size of path thus far + Manhattan distance to the goal
    return node->getSize() + node->getPos()->distTo(*goal);
}


bool isNodeParentOf(Node *potential_parent, Node *potential_child)
{
    // Iterate through every node in node_ptr->getPrev()->...->0
    // Check if node_ptr points to the child
    // If not, continue iterating until the address 0x0 is reached
    // If 0x0 is reached, potential_parent is not a parent of potential_child.
    Node *node_ptr = potential_parent;
    while (node_ptr != 0)
    {
        if (node_ptr == potential_child)
            return true;
        node_ptr = node_ptr->getPrev();
    }
    return false;
}

// Commented
bool isAnyNodeParentOf(std::deque<Node *> &nodes, Node *node)
{
    // Iterates through every node in a deque, to see if any are parents of node.
    for (Node *n : nodes)
    {
        if (isNodeParentOf(n, node))
            return true;
    }
    return false;
}

// Commented
bool hasNodeExplored(Node *node, Vector2 *pos)
{
    // Iterate through every node in node_ptr->getPrev()->...->0
    // Check if *node_ptr->getPos() == *pos
    // If not, continue iterating until the address 0x0 is reached
    // If 0x0 is reached, the position has not been explored by this node
    Node *node_ptr = node;
    while (node_ptr != 0)
    {
        if (*node_ptr->getPos() == *pos)
            return true;
        node_ptr = node_ptr->getPrev();
    }
    return false;
}

// Commented
bool isPosInVector(Vector2 *pos, Path &vecs)
{
    // Iterate through every Vector2 in the vector, checking if
    // it has the same value as the provided position
    for (Vector2 *vec : vecs)
    {
        if (*pos == *vec)
            return true;
    }
    return false;
}