#include "Vector2.hpp"

// These are the cardinal directions (and zero vector), used in both search algorithms for convenience.
// They are `extern` meaning they are defined elsewhere, and that is in Main.cpp.
extern std::unique_ptr<Vector2> g_LEFT;
extern std::unique_ptr<Vector2> g_UP;
extern std::unique_ptr<Vector2> g_RIGHT;
extern std::unique_ptr<Vector2> g_DOWN;
extern std::unique_ptr<Vector2> g_ZERO;