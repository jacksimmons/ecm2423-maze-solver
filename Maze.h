#ifndef MAZE_H
#define MAZE_H

#define JOIN(a, b) a ## b
// E_ = Easy, M_ = Medium, L_ = Large, VL_ = VLarge
#define MAZE(suffix) JOIN(M_, suffix)

#include <vector>
#include <tuple>

#include "Vector2.h"

#define E_COLS 20
#define E_ROWS 10
#define E_FILENAME "mazes/maze-Easy.txt"
#define E_SIZE "EASY"

#define M_COLS 200
#define M_ROWS 100
#define M_FILENAME "mazes/maze-Medium.txt"
#define M_SIZE "MEDIUM"

#define L_COLS 300
#define L_ROWS 600
#define L_FILENAME "mazes/maze-Large.txt"
#define L_SIZE "LARGE"

#define VL_COLS 2000
#define VL_ROWS 1000
#define VL_FILENAME "mazes/maze-VLarge.txt"
#define VL_SIZE "VLARGE"

#define EMPTY '-'
#define WALL '#'

typedef std::vector<Vector2 *> Path;

Vector2 *calculatePos(Path &path, int index);
int calculatePosIndex(Vector2 *pos);
void printMaze(char* maze, Path &path, bool* visited);
void printMaze(char* maze, Path &path);
std::tuple<char *, Vector2 *, Vector2 *> readMaze();
Vector2 *calculatePos(Path &path, int index);
int calculatePosIndex(Vector2 *pos);
#endif