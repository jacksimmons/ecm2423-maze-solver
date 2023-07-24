#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <stdexcept>
#include <memory>

#include <ctime>

#include "MainSolver.hpp"
#include "DFS.hpp"
#include "BFS.hpp"
#include "AStar.hpp"

using namespace std::chrono;


int main(int argc, char **argv)
{
	std::string mazeFileName = "maze-Easy.txt";
	Algorithm algorithm = Algorithm::DFS;
	int iterations = 1;
	bool mazeOutput = true;
	bool pathOutput = true;
	bool consoleOutput = true;
	bool statsOutput = false;

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
			algorithm = strToAlgorithm(argv[argIndex+1]);
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
		else if (arg == "-output-stats" || arg == "-stats")
		{
			statsOutput = true;
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

	if (statsOutput)
	{
		std::string mazes[4] = { "maze-Easy.txt", "maze-Medium.txt", "maze-Large.txt", "maze-VLarge.txt" };

		std::string fileName = "stats/" + algorithmToStr(algorithm) + "_stats.txt";
		std::ofstream file;
		file.open(fileName, std::ios_base::app);
		time_t time = system_clock::to_time_t(system_clock::now());
		file << std::endl << std::put_time(std::localtime(&time), "%d/%m/%y") << std::endl;

		for (int i = 0; i < 4; i++)
		{
			handleRunSolver(mazes[i], algorithm, iterations, consoleOutput, pathOutput, mazeOutput, true);
		}
	}
	else
	{
		handleRunSolver(mazeFileName, algorithm, iterations, consoleOutput, pathOutput, mazeOutput, false);
	}

	return 0;
}


void handleRunSolver(std::string maze, Algorithm alg, int iters, bool c_out, bool p_out, bool m_out, bool s_out)
{
	high_resolution_clock::time_point before = high_resolution_clock::now();
	
	runSolver(maze, alg, iters, c_out, p_out, m_out);

	high_resolution_clock::time_point after = high_resolution_clock::now();
	duration<double> timeTaken = duration_cast<duration<double>>(after - before);

	if (s_out)
	{
		outputStats(timeTaken.count(), algorithmToStr(alg), iters, maze);
	}
	else
	{
		std::cout << "Average time to complete " << iters << " iterations: " << timeTaken.count() / iters << "s." << std::endl;
	}
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


void outputStats(double timeTaken, std::string algName, int iters, std::string mazeName)
{
	std::string fileName = "stats/" + algName + "_stats.txt";
	std::ofstream file;
	file.open(fileName, std::ios_base::app);

	file << mazeName << ": " << timeTaken / iters << "s (Average over " << iters << " iterations)" << std::endl;
	file.close();
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


Algorithm strToAlgorithm(std::string input)
{
	if (input == "bfs")
		return Algorithm::BFS;
	if (input == "astar")
		return Algorithm::AStar;
	return Algorithm::DFS;
}


std::string algorithmToStr(Algorithm alg)
{
	if (alg == Algorithm::BFS)
		return "bfs";
	if (alg == Algorithm::AStar)
		return "astar";
	return "dfs";
}