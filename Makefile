.PHONY: maze_solver, maze_generator

maze_solver:
	g++ src/Solver/MainSolver.cpp \
		src/Solver/AStar.cpp \
		src/Solver/BFS.cpp \
		src/Solver/DFS.cpp \
		src/Solver/SearchAlgorithm.cpp \
		src/SearchSpace.cpp \
		-g -o maze_solver

maze_generator:
	g++ src/Generator/MainGenerator.cpp \
		src/Generator/GeneratorAlgorithm.cpp \
		src/SearchSpace.cpp \
		-g -o maze_generator