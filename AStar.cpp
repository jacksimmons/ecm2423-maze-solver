#include <algorithm>
#include <ctime>
#include <stack>
#include <queue>

#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "AStar.h"
#include "Constants.h"

void runAStar()
{
    // Create a clock to measure runtime speed
    const clock_t startTime = clock();

    // Initialise the maze
    char* maze;

    // Initialise the vectors used to control the search
    Vector2 *start;
    Vector2 *goal;

    // Read the vectors from the read maze
    tuple<char *, Vector2 *, Vector2 *> mazeInfo = readMaze();
    maze = std::get<0>(mazeInfo);
    start = std::get<1>(mazeInfo);
    goal = std::get<2>(mazeInfo);

    // Output the start and end of the maze
    std::cout << "Start: " << std::endl;
    Vector2::print(*start);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*goal);

    // Complete the search
    std::tuple<Path, int, int> pathData = astar(start, goal, maze);
    Path finalPath = std::get<0>(pathData);
    int loop_count = std::get<1>(pathData);
    int numNodes = std::get<2>(pathData);

    // Final diagram output
    if (!suppressFinalDiagram)
    {
        printMaze(maze, finalPath);
    }

    // OUTPUT PATH TO FILE
    string fileName = "PathOutput.txt";
    std::ofstream file;
    file.open(fileName);
    file << "--- A* SEARCH " << MAZE(SIZE) << " [" << MAZE(FILENAME) << "] ---" << std::endl;
    for (int i = finalPath.size() - 1; i >= 0; i--)
    {
        file << "(" << finalPath[i]->x << ", " << finalPath[i]->y << ")" << std::endl;
    }
    file.close();

    // Execution statistics
    std::cout << "Number of nodes visited: " << numNodes << endl;
    std::cout << "Number of steps in final path: " << finalPath.size() << endl;
    std::cout << "Execution time: " <<  float(clock() - startTime) / CLOCKS_PER_SEC << "s" << endl;
    std::cout << "Loop count: " << loop_count;

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

std::tuple<Path, int, int> astar(Vector2 *start, Vector2 *goal, char* maze)
{
    int loop_count = 0;
    int numNodes = 0;

    // Pointer to the current node's position
    Vector2 *pos;

    // Initialise the path
    Path path;

    // Initialise the list of potential nodes
    std::deque<std::tuple<Node *, int>> potential_list;
    std::queue<Node *> hierarchy_queue;
    Path explored_list;

    Node *node = new Node();
    node->setPos(start);
    
    potential_list.push_front(std::make_tuple(node, 0));

    while (!potential_list.empty())
    {
        loop_count++;

        if (pauseForInput)
            cin.get();

        // Get current node
        node = std::get<0>(potential_list.front());

        // Points to the current node's position for convenience
        pos = node->getPos();

        if (!suppressOutput)
        {
            Vector2::print(*pos);
        }

        // Create position vectors for all cardinal directions
        Vector2 *posUp = *pos + *UP;
        Vector2 *posLeft = *pos + *LEFT;
        Vector2 *posRight = *pos + *RIGHT;
        Vector2 *posDown = *pos + *DOWN;

        // The distances are F = G + H
        // e.g. float distUp = dist_start + heuristic
        // Try each of the directions costs from current node
        node->setPos(posUp);
        float distUp = INFINITY;
        if (!(pos->y <= 0 || maze[calculatePosIndex(posUp)] == WALL))
            distUp = calculateCost(node, goal);
        node->setPos(posLeft);
        float distLeft = INFINITY;
        if (!(pos->x <= 0 || maze[calculatePosIndex(posLeft)] == WALL))
            distLeft = calculateCost(node, goal);
        node->setPos(posRight);
        float distRight = INFINITY;
        if (!(pos->x >= MAZE(COLS) - 1 || maze[calculatePosIndex(posRight)] == WALL))
            distRight = calculateCost(node, goal);
        node->setPos(posDown);
        float distDown = INFINITY;
        if (!(pos->y >= MAZE(ROWS) - 1 || maze[calculatePosIndex(posDown)] == WALL))
            distDown = calculateCost(node, goal);
        
        // Set the position back
        node->setPos(pos);

        bool fullyExplored = true;
        bool goingUp = false;
        bool goingLeft = false;
        bool goingRight = false;
        bool goingDown = false;

        // Calculate which directions need to be added to the potential_list (<10%)
        if (distLeft != INFINITY)
        {
            if (!hasNodeExplored(node, posLeft) && !isPosInVector(posLeft, explored_list))
                goingLeft = true;
        }
        if (distRight != INFINITY)
        {
            if (!hasNodeExplored(node, posRight) && !isPosInVector(posRight, explored_list))
                goingRight = true;
        }
        if (distUp != INFINITY)
        {
            if (!hasNodeExplored(node, posUp) && !isPosInVector(posUp, explored_list))
                goingUp = true;
        }
        if (distDown != INFINITY)
        {
            if (!hasNodeExplored(node, posDown) && !isPosInVector(posDown, explored_list))
                goingDown = true;
        }

        int sizeOfList = potential_list.size();

        if (*pos == *goal)
        {
            break;
        }

        // Placed after goal checking, so that node doesn't get deleted on the final step
        // This means the pushing into `path` can't involve getting the position of a freed
        // pointer.
        numNodes++;
        // Remove node at the front
        potential_list.pop_front();
        explored_list.push_back(node->getPos());

        // Handle each direction to be added, delete the rest
        if (goingUp)
        {
            Node *next = new Node(node, posUp);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            hierarchy_queue.push(next);
        }
        else
            delete posUp;
        
        if (goingLeft)
        {
            Node *next = new Node(node, posLeft);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            hierarchy_queue.push(next);
        }
        else
            delete posLeft;
        
        if (goingRight)
        {
            Node *next = new Node(node, posRight);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            hierarchy_queue.push(next);
        }
        else
            delete posRight;

        if (goingDown)
        {
            Node *next = new Node(node, posDown);
            potential_list.push_front(std::make_tuple(next, calculateCost(next, goal)));
            hierarchy_queue.push(next);
        }
        else
            delete posDown;

        // If a new element was added, do one iteration sort pass
        if (potential_list.size() != sizeOfList)
            potential_list = insertionSortByCost(potential_list, goal);
    }

    Node *node_ptr = node;
    while (node_ptr != 0)
    {
        Vector2 *pos = node_ptr->getPos();
        Vector2 *vec = new Vector2(pos->x, pos->y);
        path.push_back(vec);
        node_ptr = node_ptr->getPrev();
    }

    // Garbage collection
    while (!hierarchy_queue.empty())
    {
        Node *node_ptr = hierarchy_queue.front();
        hierarchy_queue.pop();
        if (!isPosInVector(node_ptr->getPos(), explored_list))
            delete node_ptr->getPos();
        delete node_ptr;
    }
    
    while (!explored_list.empty())
    {   
        Vector2 *pos = explored_list.back();
        explored_list.pop_back();
        delete pos;
    }
    potential_list.clear();

    return std::make_tuple(path, loop_count, numNodes);
}

std::deque<std::tuple<Node *, int>> insertionSortByCost(std::deque<std::tuple<Node *, int>> &list, Vector2 *goal)
{
    std::tuple<Node *, int> pair = list.front();
    Node *new_node = std::get<0>(pair);
    int cost = std::get<1>(pair);
    list.pop_front();

    int index = 0;
    for (int i = 0; i < list.size() - 1; i++)
    {
        if (cost > std::get<1>(list[i]))
        {
            continue;
        }
        else
        {
            list.insert(list.begin() + i, pair);
            return list;
        }
    }
    list.push_back(pair);
    return list;
}

int calculateCost(Node *node, Vector2 *goal)
{
    return node->getSize() + node->getPos()->distTo(*goal);
}

bool isNodeParentOf(Node *potential_parent, Node *potential_child)
{
    Node *node_ptr = potential_parent;
    while (node_ptr != 0)
    {
        if (node_ptr == potential_child)
            return true;
        node_ptr = node_ptr->getPrev();
    }
    return false;
}

bool isAnyNodeParentOf(std::deque<Node *> &nodes, Node *node)
{ 
    for (Node *n : nodes)
    {
        if (isNodeParentOf(n, node))
            return true;
    }
    return false;
}

bool hasNodeExplored(Node *node, Vector2 *pos)
{
    Node *node_ptr = node;
    while (node_ptr != 0)
    {
        if (*node_ptr->getPos() == *pos)
            return true;
        node_ptr = node_ptr->getPrev();
    }
    return false;
}

bool haveAnyNodesExplored(std::deque<Node *> &nodes, Vector2 *pos)
{
    for (Node *n : nodes)
    {
        if (hasNodeExplored(n, pos))
            return true;
    }
    return false;
}

bool isPosInVector(Vector2 *pos, std::vector<Vector2 *> &vecs)
{
    for (Vector2 *vec : vecs)
    {
        if (*pos == *vec)
            return true;
    }
    return false;
}