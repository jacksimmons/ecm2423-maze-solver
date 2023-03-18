#include "Vector2.h"

// Parameters changing the output and function of the program - the comments show what happens when each is true
// These are mainly for testing purposes and may produce unexpected and extremely slow results so it isn't
// recommended to change them.

const bool pauseForInput = false; // Pauses at the start of each iteration
const bool outputEveryCycle = false; // Prints the maze with colour coding after every iteration
const bool suppressFinalDiagram = true; // Suppresses printing of the fully explored maze at the end
const bool suppressOutput = true; // Suppresses debug output, giving information on what the algorithm is doing

// These are the cardinal directions (and zero vector), used in both search algorithms for convenience.
// They are `extern` meaning they are defined elsewhere, and that is in Main.cpp.
extern Vector2 *LEFT;
extern Vector2 *UP;
extern Vector2 *RIGHT;
extern Vector2 *DOWN;
extern Vector2 *ZERO;