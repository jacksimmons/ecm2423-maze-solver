#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <tuple>

#include "Vector2.h"

#define E_COLS 20
#define E_ROWS 10
#define E_FILENAME "mazes/maze-Easy.txt"

#define M_COLS 200
#define M_ROWS 100
#define M_FILENAME "mazes/maze-Medium.txt"

#define L_COLS 300
#define L_ROWS 600
#define L_FILENAME "mazes/maze-Large.txt"

#define VL_COLS 2000
#define VL_ROWS 1000
#define VL_FILENAME "mazes/maze-VLarge.txt"

#define JOIN(a, b) a ## b
#define MAZE(suffix) JOIN(E_, suffix)

#define EMPTY '-'
#define WALL '#'

Vector2 *calculatePos(std::vector<Vector2 *> &path, int index);
int calculatePosIndex(Vector2 *pos);
void printMaze(char* maze, std::vector<Vector2 *> path, bool* visited);
std::tuple<char *, Vector2 *, Vector2 *> readMaze();
Vector2 *calculatePos(std::vector<Vector2 *> &path, int index);
int calculatePosIndex(Vector2 *pos);
#endif