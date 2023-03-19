// Commented fully
#include "Vector2.h"

// Outputs to MazeOutput.txt the explored path, with notation explained in README.txt.
// Setting this to false disables this output.
const bool outputMaze = true;

// These are the cardinal directions (and zero vector), used in both search algorithms for convenience.
// They are `extern` meaning they are defined elsewhere, and that is in Main.cpp.
extern Vector2 *LEFT;
extern Vector2 *UP;
extern Vector2 *RIGHT;
extern Vector2 *DOWN;
extern Vector2 *ZERO;