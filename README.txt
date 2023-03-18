Prerequisites:
GNU C++ compiler (g++), downloadable from:
https://gcc.gnu.org/

(Alternatively, run with Visual Studio Code or an IDE with a built-in C++ compiler)


To run:
To change which maze to solve, go into "Maze.h", and edit the MAZE preprocessor definition:
#define MAZE(suffix) JOIN({maze size}_, suffix)

#define MAZE(suffix) JOIN(E_, suffix) // Easy
#define MAZE(suffix) JOIN(M_, suffix) // Medium
#define MAZE(suffix) JOIN(L_, suffix) // Large
#define MAZE(suffix) JOIN(VL_, suffix) // VLarge

In Main.cpp:
To run both algorithms, change nothing.
To run only DFS, comment out the "runAStar" line (runAStar(); -> //runAStar();)
To run only A*, comment out the "runDFS" line (runDFS(); -> //runDFS();)
This is explained further under Depth First Search: and A* Search:

Then run the following commands:
1. g++ *.cpp -O3 -o a.out
2. ./a.out
(The command line argument -O3 is an optional optimisation flag which leads to faster execution)


Settings:
At the top of the DFS and A* algorithm source files (DFS.cpp, AStar.cpp), there are const bool values which act as settings.
The most important of which to change are:
`pauseForInput`, `outputEveryCycle`, `suppressFinalDiagram`
Note that outputEveryCycle should only be true on the Easy/Medium mazes, as the printMaze procedure is computationally expensive, especially
to use every cycle.
Note that suppressFinalDiagram shouldn't be false on the Very Large maze, as it won't fit in the terminal and is computationally expensive.
pauseForInput is also not advised for bigger mazes, as there can be millions of cycles in these algorithms.


Depth-First Search:

In Main.cpp, to just run DFS, call the procedure runDFS() {void runDFS()} after including "DFS.h"
This DFS operates by storing only pointers to the cardinal directions; the LEFT, RIGHT, UP and DOWN vectors
This is a much more efficient approach than storing new Vector2s for every node, especially on the larger mazes.


A* Search:

In Main.cpp, to just run A*, call the procedure runAStar() {void runAStar()} after including "AStar.h"
This A* operates by storing new Node objects which link back to the previous nodes.
This less efficient approach was neccessary as A* compares paths, while DFS just attempts to find one by depth.