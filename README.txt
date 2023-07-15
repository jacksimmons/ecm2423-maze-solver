Prerequisites:
C++ compiler (e.g. g++, MSVC)
https://gcc.gnu.org

Now run the following commands:
1. g++ *.cpp -O3 -flto -o a.exe
(The command line arguments -O3 and -flto are optional optimisation flags which lead to faster execution)
(These are only necessary for the VLarge maze)

2. ./a.exe [MAZE] [ALG] [ITERS] [OUTPUT_MAZE]

No arguments leads to the default process (Easy, DFS, 1 iteration).

[MAZE] default: "E"
    should be replaced by one character to represent the file name of the maze to solve:

    maze-Easy.txt = E
    maze-Medium.txt = M
    maze-Large.txt = L
    maze-VLarge.txt = V

[ALG] default: "dfs"
    should be replaced by "astar" or "dfs".

[ITERS] default: "1"
    must be an integer greater than 0. The number of executions to carry out (for
    calculating average speed).

[OUTPUT_MAZE] default: "true"
    whether to output the maze calculated by the algorithm


Performance:

To improve performance, you can disable OUTPUT_MAZE.
However, this change will only have a major impact on the Very Large maze, as the writing implementation is very slow, due to
it only writing one character at a time, and the Very Large maze having 2,000,000 characters.


Coordinate System:

I used a 2D cartesian coordinate system to represent the position of each node. (0, 0) represents the 0th row and 0th column.
(0, 1) would represent the 1st row and 0th column.
The x-coordinate represents the column, and the y-coordinate represents the row.


Maze Output:

There are 2 forms of output: PathOutput.txt and MazeOutput.txt
PathOutput.txt is an ordered list of positions making up the path from the start to the goal (cartesian coordinates)
MazeOutput.txt is the explored maze outputted in visual form, with the following key:
    v = Visited node (DFS only) which isn't on the path
    * = Node on the path
    - = Unvisited node
    # = Wall