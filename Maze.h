// Commented fully
#ifndef MAZE_H
#define MAZE_H 1

#include <vector>
#include <tuple>
#include <string>

#include "Vector2.h"

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

typedef std::vector<Vector2 *> Path;

// Function templates
std::tuple<char *, Vector2 *, Vector2 *> readMaze(char);
Vector2 *calculatePos(Path &path, int index);
int calculatePosIndex(char, Vector2 *pos);
void outputPathToFile(std::string header, Path path);
void outputMazeToFile(char, char *, Path &, bool *);
void outputMazeToFile(char, char *, Path &);

int getCols(char);
int getRows(char);
std::string getFilename(char);
std::string getName(char);
#endif