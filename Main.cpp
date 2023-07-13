#include <chrono>
#include <stdexcept>
#include <string>

#include "Main.hpp"
#include "AStar.hpp"
#include "DFS.hpp"
#include "Constants.hpp"

// Assign to the externs in Constants.h
Vector2 *LEFT = new Vector2(-1, 0);
Vector2 *UP = new Vector2(0, -1);
Vector2 *RIGHT = new Vector2(1, 0);
Vector2 *DOWN = new Vector2(0, 1);
Vector2 *ZERO = new Vector2(0, 0);

int main(int argc, char **argv)
{
	char maze = 'E';
	bool dfs = true;
	int iterations = 1;
	bool outputMaze = true;
	try
	{
		if (argc > 1)
		{
			char *argMaze = argv[1];
			switch (argMaze[0])
			{
			case 'E':
			case 'M':
			case 'L':
			case 'V':
				maze = argMaze[0];
				break;
			default:
				throw 1;
			}
		}
		if (argc > 2)
		{
			std::string argAlg = argv[2];
			if (argAlg == "dfs")
				dfs = true;
			else if (argAlg == "astar")
				dfs = false;
			else
				throw 2;
		}
		if (argc > 3)
		{
			int iters = std::stoi(argv[3]);
			if (iters > 0)
				iterations = iters;
			else
				throw 3;
		}
		if (argc > 4)
		{
			std::string argOutputMaze = argv[4];
			if (argOutputMaze == "true")
				outputMaze = true;
			else if (argOutputMaze == "false")
				outputMaze = false;
			else
				throw 4;
		}
	}
	catch (int argI)
	{
		switch (argI)
		{
		case 1:
			std::cout << "Invalid [MAZE] argument." << std::endl;
			break;
		case 2:
			std::cout << "Invalid [ALG] argument." << std::endl;
			break;
		case 3:
			std::cout << "Invalid [ITER] argument." << std::endl;
			break;
		case 4:
			std::cout << "Invalid [OUTPUT_MAZE] argument." << std::endl;
			break;
		}
		std::cout << "Please refer to README.txt for details." << std::endl;
		return 1;
	}

	using namespace std::chrono;

	// Create a clock to measure runtime speed
	high_resolution_clock::time_point before = high_resolution_clock::now();

    // Run the search algorithms
	runSolver(maze, dfs, iterations, outputMaze);

    // Final garbage collection
    delete UP;
    delete DOWN;
    delete LEFT;
    delete RIGHT;

	high_resolution_clock::time_point after = high_resolution_clock::now();
	duration<double> timeTaken = duration_cast<duration<double>>(after - before);
	std::cout << "Average time taken for one to execute: " << timeTaken.count() / iterations << "s" << std::endl;
}

void runSolver(char mazeType, bool dfs, int N, bool outputMaze)
{
	if (dfs)
	{
		for (int i = 0; i < N; i++)
			runDFS(mazeType, outputMaze);
	}
	else
	{
		for (int i = 0; i < N; i++)
			runAStar(mazeType, outputMaze);
	}
}