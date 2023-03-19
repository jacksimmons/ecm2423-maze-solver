// Commented fully
#ifndef MAZE_H
#define MAZE_H 1

#include <vector>
#include <tuple>
#include <string>

#include "Vector2.h"

// Preprocessor definitions for MAZE(suffix) notation
// Example: MAZE(NAME) = JOIN({maze_type}_, NAME) = {maze_type}_NAME
#define JOIN(a, b) a ## b
// E_ = Easy, M_ = Medium, L_ = Large, VL_ = VLarge
#define MAZE(suffix) JOIN(E_, suffix)

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

#define VL_COLS 2000
#define VL_ROWS 1000
#define VL_FILENAME "mazes/maze-VLarge.txt"
#define VL_NAME "VLARGE"

// Define node macros
#define EMPTY '-'
#define WALL '#'

typedef std::vector<Vector2 *> Path;

// Function templates
Vector2 *calculatePos(Path &path, int index);
int calculatePosIndex(Vector2 *pos);
std::tuple<char *, Vector2 *, Vector2 *> readMaze();
Vector2 *calculatePos(Path &path, int index);
int calculatePosIndex(Vector2 *pos);
void outputPathToFile(std::string header, Path path);
void outputMazeToFile(char *maze, Path &path, bool *visited);
void outputMazeToFile(char *maze, Path &path);
#endif