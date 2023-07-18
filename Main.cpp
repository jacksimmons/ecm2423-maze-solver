#include <iostream>
#include <chrono>
#include <stdexcept>
#include <string>

#include "Main.hpp"
#include "AStar.hpp"
#include "DFS.hpp"


int main(int argc, char **argv)
{
	std::string mazeFileName = "maze-Easy.txt";
	bool dfs = true;
	int iterations = 1;
	bool outputMaze = true;
	try
	{
		if (argc > 1)
		{
			mazeFileName = argv[1];
			if (mazeFileName == "E")
				mazeFileName = "maze-Easy.txt";
			else if (mazeFileName == "M")
				mazeFileName = "maze-Medium.txt";
			else if (mazeFileName == "L")
				mazeFileName = "maze-Large.txt";
			else if (mazeFileName == "VL")
				mazeFileName = "maze-VLarge.txt";
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
	runSolver(mazeFileName, dfs, iterations, outputMaze);

	high_resolution_clock::time_point after = high_resolution_clock::now();
	duration<double> timeTaken = duration_cast<duration<double>>(after - before);
	std::cout << "Average time taken for one to execute: " << timeTaken.count() / iterations << "s" << std::endl;
}

void runSolver(std::string mazeFileName, bool dfs, int N, bool outputMaze)
{
	if (dfs)
	{
		for (int i = 0; i < N; i++)
		{
			DFS *dfs = new DFS(mazeFileName, outputMaze);
			dfs->run();
			delete dfs;
		}
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			AStar *astar = new AStar(mazeFileName, outputMaze);
			astar->run();
			delete astar;
		}
	}
}