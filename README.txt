Prerequisites:
GNU C++ compiler (g++), downloadable from:
https://gcc.gnu.org/

(Alternatively, run with Visual Studio Code or an IDE with a built-in C++ compiler)


To run:
To change which maze to solve, go into "Maze.h", and edit the MAZE preprocessor definition:
#define MAZE(suffix) JOIN({maze size}_, suffix)

Change the above line (Maze.h:6) to any of the following:

#define MAZE(suffix) JOIN(E_, suffix) // Easy
#define MAZE(suffix) JOIN(M_, suffix) // Medium
#define MAZE(suffix) JOIN(L_, suffix) // Large
#define MAZE(suffix) JOIN(VL_, suffix) // VLarge

Now in Main.cpp:
To run both algorithms, change nothing (note that as A* happens after, only the A* output will be written
to PathOutput.txt)
To run only DFS, comment out just the "runAStar" line (runAStar(); -> //runAStar();)
To run only A*, comment out just the "runDFS" line (runDFS(); -> //runDFS();)
This is explained further under Depth First Search: and A* Search:

Now run the following commands:
1. g++ *.cpp -O3 -flto -o a.exe
2. ./a.exe
(The command line arguments -O3 and -flto are optional optimisation flags which lead to faster execution)
(These are only necessary for the VLarge maze)


Depth-First Search:

In Main.cpp, to just run DFS, call the procedure runDFS() {void runDFS()} after including "DFS.h"
This DFS operates by storing only pointers to the cardinal directions; the LEFT, RIGHT, UP and DOWN vectors
This is a much more efficient approach than storing new Vector2s for every node, especially on the larger mazes.


A* Search:

In Main.cpp, to just run A*, call the procedure runAStar() {void runAStar()} after including "AStar.h"
This A* operates by storing new Node objects which link back to the previous nodes.
This less efficient approach was neccessary as A* compares paths by cost, while DFS just looks by depth.


Performance:

To improve performance, you can disable outputMaze in "Constants.h".
However, this change will only have a major impact on the Very Large maze. (4.749s -> 51.577s)