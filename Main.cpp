#include <iostream>
#include <chrono>
#include <stdexcept>
#include <memory>

#include "Main.hpp"
#include "DFS.hpp"
#include "BFS.hpp"
#include "AStar.hpp"


int main(int argc, char **argv)
{
	std::string mazeFileName = "maze-Easy.txt";
	SearchType searchType = SEARCHTYPE_DFS;
	int iterations = 1;
	bool mazeOutput = true;
	bool pathOutput = true;
	bool consoleOutput = true;
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
				searchType = SEARCHTYPE_DFS;
			else if (argAlg == "bfs")
				searchType = SEARCHTYPE_BFS;
			else if (argAlg == "astar")
				searchType = SEARCHTYPE_ASTAR;
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
			std::string argMazeOutput = argv[4];
			if (argMazeOutput == "true")
				mazeOutput = true;
			else if (argMazeOutput == "false")
				mazeOutput = false;
			else
				throw 4;
		}
		if (argc > 5)
		{
			std::string argPathOutput = argv[5];
			if (argPathOutput == "true")
				pathOutput = true;
			else if (argPathOutput == "false")
				pathOutput = false;
			else
				throw 5;
		}
		if (argc > 6)
		{
			std::string argConsoleOutput = argv[6];
			if (argConsoleOutput == "true")
				consoleOutput = true;
			else if (argConsoleOutput == "false")
				consoleOutput = false;
			else
				throw 5;
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
		case 5:
			std::cout << "Invalid [OUTPUT_PATH] argument." << std::endl;
			break;
		case 6:
			std::cout << "Invalid [OUTPUT_CONSOLE] argument." << std::endl;
			break;
		}
		std::cout << "Please refer to README.txt for details." << std::endl;
		return 1;
	}

	using namespace std::chrono;

	// Create a clock to measure runtime speed
	high_resolution_clock::time_point before = high_resolution_clock::now();

    // Run the search algorithms
	runSolver(mazeFileName, searchType, iterations, consoleOutput, pathOutput, mazeOutput);

	high_resolution_clock::time_point after = high_resolution_clock::now();
	duration<double> timeTaken = duration_cast<duration<double>>(after - before);
	std::cout << "Average time taken for one to execute: " << timeTaken.count() / iterations << "s" << std::endl;
}

void runSolver(std::string mazeFileName, SearchType searchType, int N, bool consoleOutput, bool pathOutput, bool mazeOutput)
{
	if (searchType == SEARCHTYPE_DFS)
	{
		for (int i = 0; i < N; i++)
		{
			std::unique_ptr<DFS> dfs = std::make_unique<DFS>(mazeFileName, consoleOutput, pathOutput, mazeOutput);
			dfs->run();
		}
	}
	else if (searchType == SEARCHTYPE_BFS)
	{
		for (int i = 0; i < N; i++)
		{
			std::unique_ptr<BFS> bfs = std::make_unique<BFS>(mazeFileName, consoleOutput, pathOutput, mazeOutput);
			bfs->run();
		}
	}
	else if (searchType == SEARCHTYPE_ASTAR)
	{
		for (int i = 0; i < N; i++)
		{
			std::unique_ptr<AStar> astar = std::make_unique<AStar>(mazeFileName, consoleOutput, pathOutput, mazeOutput);
			astar->run();
		}
	}
}