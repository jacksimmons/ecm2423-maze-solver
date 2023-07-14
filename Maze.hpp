#ifndef MAZE_H
#define MAZE_H 1

#include <vector>
#include <tuple>
#include <string>

#include "Vector2.hpp"
#include "Typedef.hpp"

// Define the maze macros
#define E_COLS 20
#define E_ROWS 10
#define E_FILENAME "mazes/maze-Easy.txt"
#define E_NAME "EASY"

#define M_COLS 200
#define M_ROWS 100
#define M_FILENAME "mazes/maze-Medium.txt"
#define M_NAME "MEDIUM"

#define L_COLS 300
#define L_ROWS 600
#define L_FILENAME "mazes/maze-Large.txt"
#define L_NAME "LARGE"

#define V_COLS 2000
#define V_ROWS 1000
#define V_FILENAME "mazes/maze-VLarge.txt"
#define V_NAME "VLARGE"

// Define node macros
#define EMPTY '-'
#define WALL '#'

// Function templates
std::tuple<std::vector<char>, std::shared_ptr<Vector2>, std::shared_ptr<Vector2>> readMaze(char);
std::unique_ptr<Vector2> calculatePos(VectorPath&, int);
int calculatePosIndex(char, Vector2&);
void outputPathToFile(std::string header, VectorPath&);
void outputMazeToFile(char, std::vector<char>, VectorPath&, std::vector<bool>);
void outputMazeToFile(char, std::vector<char>, VectorPath&);

int getCols(char);
int getRows(char);
std::string getFilename(char);
std::string getName(char);
#endif