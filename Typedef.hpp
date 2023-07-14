#include <vector>
#include <stack>
#include <memory>

#include "Vector2.hpp"

typedef std::vector<std::shared_ptr<Vector2>> VectorPath;
typedef std::stack<std::unique_ptr<Vector2>> StackPath;