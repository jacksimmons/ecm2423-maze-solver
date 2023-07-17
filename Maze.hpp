#ifndef MAZE_H
#define MAZE_H 1

#include <memory>
#include <vector>
#include <tuple>
#include <string>

#include "Vector2.hpp"
#include "SearchAlg.hpp"

// Define node macros
#define EMPTY '-'
#define WALL '#'
#define START 's'
#define GOAL 'g'
#define VISITED '.'
#define PATH 'x'

// Function templates
std::tuple<std::vector<char>, std::shared_ptr<Vector2>, std::shared_ptr<Vector2>, int, int> readMaze(std::string filename);
std::unique_ptr<Vector2> calculatePos(DFSPath&, int);
int posToIndex(char, Vector2&);
float getIndexDistance(int i1, int i2, int rows, int cols);

int getCols(char);
int getRows(char);
std::string getFilename(char);
std::string getName(char);
#endif