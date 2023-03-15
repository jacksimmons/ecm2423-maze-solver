#include <fstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>

#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Maze.h"
#include "AStar.h"
#include "Vector2.h"

// Parameters changing the output and function of the program - the comments show what happens when each is true
const bool pauseForInput = false; // Pauses at the start of each iteration
const bool outputEveryCycle = true; // Prints the maze with colour coding after every iteration
const bool suppressFinalDiagram = false; // Suppresses printing of the fully explored maze at the end
const bool suppressFinalPath = true; // Suppresses printing of the ordered nodes on the path at the end
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
    std::tuple<std::vector<Vector2 *>, int> pathData = astar(start, goal, maze);
    std::vector<Vector2 *> finalPath = std::get<0>(pathData);
    int loop_count = std::get<1>(pathData);

    // Final path output
    if (!suppressFinalPath)
    {
        cout << "Final path: " << std::endl;
        for (int i = 0; i < finalPath.size(); i++)
        {
            // Calculate the position of the ith element in the path
            Vector2 *calcPos = calculatePos(finalPath, i);
            Vector2::print(*calcPos);
            delete calcPos;
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
    
    delete maze;

    return 0;
}

std::tuple<std::vector<Vector2 *>, int> astar(Vector2 *start, Vector2 *goal, char* maze)
{
    int loop_count = 0;

    Vector2 *pos = new Vector2();

    // Direction vectors
    Vector2 *LEFT = new Vector2(-1, 0);
    Vector2 *UP = new Vector2(0, -1);
    Vector2 *RIGHT = new Vector2(1, 0);
    Vector2 *DOWN = new Vector2(0, 1);
    Vector2 *ZERO = new Vector2(0, 0);

    // Initialise the path
    std::vector<Vector2 *> path;
    std::queue<Node *> astar_queue;

    // Initialise the queue
    Node *start_node = new Node(nullptr, start);
    astar_queue.push(start_node);

    Node *node = new Node();
    Node *nodeUp = new Node();
    Node *nodeRight = new Node();
    Node *nodeLeft = new Node();
    Node *nodeDown = new Node();

    while (!astar_queue.empty())
    {
        std::cout << "loop" << std::endl;

        if (pauseForInput)
            cin.get();

        // Points to the current node's position for convenience
        pos = node->position;

        // Iterate over every item in the queue
        Node *front = astar_queue.front();
        astar_queue.pop();
        node->previous_node = front;

        Vector2 *posUp = *(node->position) + *UP;
        Vector2 *posLeft = *(node->position) + *LEFT;
        Vector2 *posRight = *(node->position) + *RIGHT;
        Vector2 *posDown = *(node->position) + *DOWN;

        nodeUp->set(node, posUp);
        nodeLeft->set(node, posLeft);
        nodeRight->set(node, posRight);
        nodeDown->set(node, posDown);

        // The distances are F = G + H
        // e.g. float distUp = dist_start + heuristic
        float cost = calculateCost(node);
        float distUp = cost + posUp->distTo(*goal);
        if (pos->y <= 0 || maze[calculatePosIndex(posUp)] == WALL)
            distUp = INFINITY;
        float distLeft = cost + posLeft->distTo(*goal);
        if (pos->x <= 0 || maze[calculatePosIndex(posLeft)] == WALL)
            distLeft = INFINITY;
        float distRight = cost + posRight->distTo(*goal);
        if (pos->x >= MAZE(COLS) - 1 || maze[calculatePosIndex(posRight)] == WALL)
            distRight = INFINITY;
        float distDown = cost + posDown->distTo(*goal);
        if (pos->y >= MAZE(ROWS) - 1 || maze[calculatePosIndex(posDown)] == WALL)
            distDown = INFINITY;

        std::vector<float> distances;
        distances.push_back(distUp);
        distances.push_back(distLeft);
        distances.push_back(distRight);
        distances.push_back(distDown);

        float min = *std::min_element(distances.begin(), distances.end());
        
        if (distLeft == min && distLeft != INFINITY)
            astar_queue.push(nodeLeft);
        
        if (distRight == min && distRight != INFINITY)
            astar_queue.push(nodeRight);

        if (distUp == min && distDown != INFINITY)
            astar_queue.push(nodeUp);

        if (distDown == min && distDown != INFINITY)
            astar_queue.push(nodeDown);

        if (outputEveryCycle)
        {
            Vector2::print(*pos);
            bool* visited = new bool[MAZE(ROWS) * MAZE(COLS)];
            printMaze(maze, path, visited);
            delete []visited;
        }

        if (*pos == *goal)
        {
            std::cout << "win" << std::endl;
        }

        delete posUp;
        delete posLeft;
        delete posRight;
        delete posDown;
    }

    delete node;
    delete nodeUp;
    delete nodeLeft;
    delete nodeRight;
    delete nodeDown;
    delete pos;
    delete UP;
    delete DOWN;
    delete LEFT;
    delete RIGHT;
    delete ZERO;

    std::cout << "end" << std::endl;

    return std::make_tuple(path, loop_count);
}

float calculateCost(Node *node)
{
    Node *node_ptr = node->previous_node;
    float cost = 0;
    while (node_ptr != nullptr)
    {
        cost++;
        node_ptr = (Node*)node_ptr->previous_node;
        Vector2::print(*(node_ptr->position));
    }
    return cost;
}