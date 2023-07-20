#include <iostream>
#include <chrono>
#include <stdexcept>
#include <memory>

#include "MainSolver.hpp"
#include "DFS.hpp"
#include "BFS.hpp"
#include "AStar.hpp"


int main(int argc, char **argv)
{
	std::string mazeFileName = "maze-Easy.txt";
	Algorithm algorithm = Algorithm::DFS;
	int iterations = 1;
	bool mazeOutput = true;
	bool pathOutput = true;
	bool consoleOutput = true;

	CommandLineError commandLineError = CommandLineError::None;

	std::string arg;
	int argIndex;

	for (int argIndex = 1; argIndex < argc; argIndex++)
	{
		arg = argv[argIndex];

		if (arg == "-maze" || arg == "-m")
		{
			if (argIndex == argc - 1)
			{
				commandLineError = CommandLineError::NoArgValue;
				break;
			}
			mazeFileName = getMazeFileName(argv[argIndex+1]);
		}
		else if (arg == "-algorithm" || arg == "-alg" || arg == "-a")
		{
			if (argIndex == argc - 1)
			{
				commandLineError = CommandLineError::NoArgValue;
				break;
			}
			algorithm = getAlgorithm(argv[argIndex+1]);
		}
		else if (arg == "-iterations" || arg == "-iter" || arg == "-i")
		{
			if (argIndex == argc - 1)
			{
				commandLineError = CommandLineError::NoArgValue;
				break;
			}
			iterations = std::atoi(argv[argIndex+1]);
			if (iterations > 0)
				continue;
		}
		else if (arg == "-no-console-output" || arg == "-no-console")
		{
			consoleOutput = false;
			continue;
		}
		else if (arg == "-no-path-output" || arg == "-no-path")
		{
			pathOutput = false;
			continue;
		}
		else if (arg == "-no-maze-output" || arg == "-no-maze")
		{
			mazeOutput = false;
			continue;
		}
	}

	switch (commandLineError)
	{
		case CommandLineError::NoArgValue:
			std::cout << "No argument was provided for argument " << argIndex << ": " << arg << "." << std::endl;
			return 1;
		default:
			break;
	}

	using namespace std::chrono;

	// Create a clock to measure runtime speed
	high_resolution_clock::time_point before = high_resolution_clock::now();

    // Run the search algorithms
	runSolver(mazeFileName, algorithm, iterations, consoleOutput, pathOutput, mazeOutput);

	high_resolution_clock::time_point after = high_resolution_clock::now();
	duration<double> timeTaken = duration_cast<duration<double>>(after - before);
	std::cout << "Average time taken for one to execute: " << timeTaken.count() / iterations << "s" << std::endl;
}


void runSolver(std::string mazeFileName, Algorithm alg, int N, bool consoleOutput, bool pathOutput, bool mazeOutput)
{
	if (alg == Algorithm::DFS)
	{
		for (int i = 0; i < N; i++)
		{
			std::unique_ptr<DFS> dfs = std::make_unique<DFS>(mazeFileName, consoleOutput, pathOutput, mazeOutput);
			dfs->run();
		}
	}
	else if (alg == Algorithm::BFS)
	{
		for (int i = 0; i < N; i++)
		{
			std::unique_ptr<BFS> bfs = std::make_unique<BFS>(mazeFileName, consoleOutput, pathOutput, mazeOutput);
			bfs->run();
		}
	}
	else if (alg == Algorithm::AStar)
	{
		for (int i = 0; i < N; i++)
		{
			std::unique_ptr<AStar> astar = std::make_unique<AStar>(mazeFileName, consoleOutput, pathOutput, mazeOutput);
			astar->run();
		}
	}
}


std::string getMazeFileName(std::string input)
{
	std::string mazeFileName = input;
	if (mazeFileName == "E")
		return "maze-Easy.txt";
	if (mazeFileName == "M")
		return "maze-Medium.txt";
	if (mazeFileName == "L")
		return "maze-Large.txt";
	if (mazeFileName == "VL")
		return "maze-VLarge.txt";
	return mazeFileName;
}


Algorithm getAlgorithm(std::string input)
{
	if (input == "bfs")
		return Algorithm::BFS;
	if (input == "astar")
		return Algorithm::AStar;
	return Algorithm::DFS;
}