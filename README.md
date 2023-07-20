
# Overview

## Prerequisites
- A C++ compiler (e.g. g++, msvc) and C++ compatible processor.

## Mazes
A maze (maze file) must follow these rules for the program to run as expected:
1. It must have a rectangular shape (see the example below).
2. It must have one start node and one goal node.
3. It must be encased in an outer 'shell' of walls.
4. It must only contain valid characters
5. It must have no leading/trailing newlines, except for the standard newline at the end of CRLF files.
Mazes are defined by certain characters, which are defined as macros in Maze.hpp:
	WALL: '#' 
	EMPTY: '-'
	START: 's'
	GOAL: 'g'
In maze output, a few other characters are also used:
	VISITED: '.'
	PATH: 'x'
Mazes must be placed in the "mazes" folder, and referred to by their local filename (e.g. maze-Easy.txt).

With the above descriptions, here is an example (dimensions 10x5):
(This may look strange if you are using a font where -, #, s and g are different widths)

##s#######  
##-#######  
##-------#  
########-#  
########g#  

# Compiling

## With make
	 make
	./maze_solver
	Use "make -B" if it is not updating correctly (e.g. it says maze_solver is up
	to date when it is not).

## Without make
Copy and paste the command from the Makefile into your terminal.

## Command-Line Arguments
Arguments are processed in any order, and if not provided the program will run
with the following default arguments:

	./maze_solver -maze maze-Easy.txt -alg DFS -iter 1
	> maze = maze-Easy.txt
	> algorithm = DFS
	> iterations = 1
	> console output = true
	> path output = true
	> maze output = true

Below are all supported arguments, followed by the number of values they require
in brackets.

[-maze(1)]

	Usage:
	-maze/-m [filename]
	-maze maze-Easy.txt
	-m E

	Description:
	Provide the name of any maze file under the mazes folder, that you want solved.
	Additionally, the following phrases can be used as shortcuts for the 4 default mazes:
	"E" - maze-Easy.txt
	"M" - maze-Medium.txt
	"L" - maze-Large.txt
	"VL" - maze-VLarge.txt

[-algorithm/-alg/-a(1)]

	Usage:
	-algorithm/-alg/-a [dfs/bfs/astar]
	-algorithm dfs
	-alg astar

	Description:
	Provide the search algorithm to use, as one lowercase word.

[-iterations/-iter/-i(1)] default: "1"

	Usage:
	-iterations/-iter/-i [int > 0]
	-iterations 10
	-iter 1

	Description:
	Provide the number of executions to carry out (use more than 1 to get a better
	estimate for average speed). Output is unaffected by this parameter.

[-no-console-output/-no-console(0)]

	Usage:
	-no-console-output

	Description:
	Disables algorithm console output.

[-no-path-output/-no-path(0)]

	Usage:
	-no-path-output

	Description:
	Disables algorithm path output.

[-no-maze-output/-no-maze(0)]

	Usage:
	-no-maze-output

	Description:
	Disables output of the solved maze to MazeOutput.txt

[-stats-output/-stats(0)]

	Usage:
	-stats-output

	Description:
	Enables output of statistics to stats/{alg name}_stats.txt.
	Will ignore -alg argument and instead run each of Easy, Medium, Large and VLarge
	`iterations` times.

# Output

## Console
The program provides some information about the performance of the search to console.

## out Folder
The program also outputs to the out folder, in out/PathOutput.txt and out/MazeOutput.txt.

### PathOutput.txt
In PathOutput.txt, the Cartesian Coordinate path from start to goal is stored.
Note that the Cartesian Coordinates I used follow these rules:
- Origin (0,0) is in the top left, and all coordinates have positive x and y for that reason.
- Right is +x, Left is -x
- Up is -y, Down is +y

### MazeOutput.txt
MazeOutput.txt stores the path traversed, as well as visited nodes, overlayed on top of the
input maze.
It is quite slow on larger mazes, taking a couple of seconds on the VLarge (2000 x 1000) maze.

# Algorithms

## Depth-First Search (DFS)
A quick and simple algorithm which isn't optimal.

## Breadth-First Search (BFS)
A quick and simple algorithm which is optimal, but has a high space complexity.

## A-Star Search (A*)
An optimal algorithm which minimises the path by distance. (i.e. it finds the shortest path)
This is equivalent to finding the path with the fewest nodes in this search space.

# Performance
To improve performance, insert -flto (standard link-time optimiser) or -O1, -O2 or -O3 (increasingly aggressive optimisation) compiler optimisation flags before the -o flag in your compiler execution:

	Original:
	... -o ./maze_solver
	New:
	... -O3 -flto -o ./maze_solver

Or just run "make maze_solver_opt".
Since smaller mazes are already very quick, this will only have a major impact on the larger mazes.
