#include <fstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <stack>

#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Maze.h"
#include "AStar.h"
#include "Vector2.h"

// Parameters changing the output and function of the program - the comments show what happens when each is true
const bool pauseForInput = true; // Pauses at the start of each iteration
const bool outputEveryCycle = false; // Prints the maze with colour coding after every iteration
const bool suppressFinalDiagram = false; // Suppresses printing of the fully explored maze at the end
const bool suppressFinalPath = false; // Suppresses printing of the ordered nodes on the path at the end
const bool suppressOutput = true; // Suppresses debug output, giving information on what the algorithm is doing

// Every element in path is stored as either a pointer to start, or to the following vectors (so don't garbage collect them!)
// Global variables so they can be garbage collected at the end of the program

// Stores how many times the algorithm has been entered
int loop_count = 0;

// Create a clock to measure runtime speed
int main()
{
    const clock_t startTime = clock();

    // Initialise the maze
    char* maze;
    bool* visited = new bool[MAZE(ROWS) * MAZE(COLS)];

    // Make the visited array full of "false"
    for (int i = 0; i < MAZE(ROWS); i++)
    {
        for (int j = 0; j < MAZE(COLS); j++)
        {
            visited[i * MAZE(COLS) + j] = false;
        }
    }

    // Initialise the vectors used to control the search
    Vector2 *start = new Vector2();
    Vector2 *goal = new Vector2();

    // Read the vectors from the read maze
    tuple<char *, Vector2 *, Vector2 *> mazeInfo = readMaze();
    maze = std::get<0>(mazeInfo);
    start = std::get<1>(mazeInfo);
    goal = std::get<2>(mazeInfo);

    std::cout << "Start: " << std::endl;
    Vector2::print(*start);
    std::cout << "Goal: " << std::endl;
    Vector2::print(*goal);

    // Complete the search
    std::tuple<std::vector<Vector2 *>, int> pathData = astar(start, goal, maze, visited);
    std::vector<Vector2 *> finalPath = std::get<0>(pathData);
    int loop_count = std::get<1>(pathData);

    // Final diagram output
    if (!suppressFinalDiagram)
    {
        printMaze(maze, finalPath, visited);
    }

    // Final path output
    if (!suppressFinalPath)
    {
        cout << "Final path: " << std::endl;
        for (int i = finalPath.size() - 1; i >= 0; i--)
        {
            Vector2::print(*finalPath.at(i));
        }
    }
    
    // Calculate the number of visited nodes
    int numNodes = 0;

    // Execution statistics
    std::cout << "Number of nodes visited: " << numNodes << endl;
    std::cout << "Number of steps in final path: " << finalPath.size() << endl;
    std::cout << "Execution time: " <<  float(clock() - startTime) / CLOCKS_PER_SEC << "s" << endl;
    std::cout << "Loop count: " << loop_count;

    // Garbage collection
    delete start;
    delete goal;
    
    delete[] maze;
    delete[] visited;

    cin.get();

    return 0;
}

std::tuple<std::vector<Vector2 *>, int> astar(Vector2 *start, Vector2 *goal, char* maze, bool* excluded)
{
    int loop_count = 0;

    Vector2 *pos = new Vector2();

    // Cardinal direction vectors
    Vector2 *LEFT = new Vector2(-1, 0);
    Vector2 *UP = new Vector2(0, -1);
    Vector2 *RIGHT = new Vector2(1, 0);
    Vector2 *DOWN = new Vector2(0, 1);
    Vector2 *ZERO = new Vector2(0, 0);

    Vector2 *posUp = new Vector2();
    Vector2 *posLeft = new Vector2();
    Vector2 *posRight = new Vector2();
    Vector2 *posDown = new Vector2();

    // Initialise adjacency nodes
    Node *nodeUp = new Node();
    Node *nodeRight = new Node();
    Node *nodeLeft = new Node();
    Node *nodeDown = new Node();

    // Initialise the path
    std::vector<Vector2 *> path;

    // Initialise the queue
    Node *start_node = new Node(0, start);
    Node *node = new Node();

    std::vector<Node *> potential_list;
    potential_list.push_back(start_node);

    while (!potential_list.empty())
    {
        if (pauseForInput)
            cin.get();

        // Iterate over every node in the list
        float minCost = INFINITY;
        std::cout << "potential_list" << std::endl;
        int index = 0;
        for (Node *n : potential_list)
        {
            float cost = calculateCost(n, goal);
            std::cout << cost << std::endl;
            Vector2::print(*n->getPos());
            if (cost < minCost)
            {
                node = new Node(n->getPrev(), n->getPos());
                minCost = cost;
                break;
            }
            index++;
        }

        if (!suppressOutput)
        {
            Vector2::print(*node->getPos());
        }

        // Points to the current node's position for convenience
        pos = node->getPos();

        posUp = *(node->getPos()) + *UP;
        posLeft = *(node->getPos()) + *LEFT;
        posRight = *(node->getPos()) + *RIGHT;
        posDown = *(node->getPos()) + *DOWN;

        nodeUp->setPrev(node);
        nodeUp->setPos(posUp);
        nodeLeft->setPrev(node);
        nodeLeft->setPos(posLeft);
        nodeRight->setPrev(node);
        nodeRight->setPos(posRight);
        nodeDown->setPrev(node);
        nodeDown->setPos(posDown);
        
        // The distances are F = G + H
        // e.g. float distUp = dist_start + heuristic
        float distUp = minCost + posUp->distTo(*goal);
        if (pos->y <= 0 || maze[calculatePosIndex(posUp)] == WALL)
            distUp = INFINITY;
        float distLeft = minCost + posLeft->distTo(*goal);
        if (pos->x <= 0 || maze[calculatePosIndex(posLeft)] == WALL)
            distLeft = INFINITY;
        float distRight = minCost + posRight->distTo(*goal);
        if (pos->x >= MAZE(COLS) - 1 || maze[calculatePosIndex(posRight)] == WALL)
            distRight = INFINITY;
        float distDown = minCost + posDown->distTo(*goal);
        if (pos->y >= MAZE(ROWS) - 1 || maze[calculatePosIndex(posDown)] == WALL)
            distDown = INFINITY;

        // A boolean to store when all sides of this node are in potential nodes
        // Hence we need to remove this node
        bool fullyExplored = true;
        if (distLeft != INFINITY)
        {
            if (!haveAnyNodesExplored(potential_list, posLeft))
            {
                potential_list.push_back(nodeLeft);
                fullyExplored = false;
            }
        }
        if (distRight != INFINITY)
        {
            if (!haveAnyNodesExplored(potential_list, posRight))
            {
                potential_list.push_back(nodeRight);
                fullyExplored = false;
            }
        }
        if (distUp != INFINITY)
        {
            if (!haveAnyNodesExplored(potential_list, posUp))
            {
                potential_list.push_back(nodeUp);
                fullyExplored = false;
            }
        }
        if (distDown != INFINITY)
        {
            if (!haveAnyNodesExplored(potential_list, posDown))
            {
                potential_list.push_back(nodeDown);
                fullyExplored = false;
            }
        }

        if (fullyExplored)
        {
            // Remove node at index
            potential_list.erase(potential_list.begin() + index);
            delete node;
        }

        if (outputEveryCycle)
        {
            path.clear();
            Node *node_ptr = node;
            while (node_ptr != 0)
            {
                path.push_back(node_ptr->getPos());
                node_ptr = node_ptr->getPrev();
            }
            printMaze(maze, path, excluded);
        }

        if (*pos == *goal)
        {
            std::cout << "win" << std::endl;
            break;
        }
    }

    std::cout << "end" << std::endl;

    path.clear();
    Node *node_ptr = node;
    while (node_ptr != 0)
    {
        path.push_back(node_ptr->getPos());
        node_ptr = node_ptr->getPrev();
    }
    node_ptr->~Node();

    // Garbage collection
    delete UP;
    delete DOWN;
    delete LEFT;
    delete RIGHT;
    delete ZERO;

    delete nodeUp;
    delete nodeDown;
    delete nodeLeft;
    delete nodeRight;

    delete posUp;
    delete posDown;
    delete posLeft;
    delete posRight;

    return std::make_tuple(path, loop_count);
}

float calculateCost(Node *node, Vector2 *goal)
{
    Node *node_ptr = node->getPrev();
    float cost = 0;
    while (node_ptr != 0)
    {
        cost++;
        node_ptr = node_ptr->getPrev();
        //std::cout << "Cost" << cost << std::endl;
    }
    cost += node->getPos()->distTo(*goal);
    return cost;
}

bool hasNodeExplored(Node *node, Vector2 *vec)
{
    Node *node_ptr = node;
    while (node_ptr != 0)
    {
        if (*node_ptr->getPos() == *vec)
            return true;
        node_ptr = node_ptr->getPrev();
    }
    return false;
}

bool haveAnyNodesExplored(std::vector<Node *> nodes, Vector2 *vec)
{
    for (Node *node : nodes)
    {
        if (hasNodeExplored(node, vec))
            return true;
    }
    return false;
}