#include <vector>
#include <stack>
#include <memory>

#include "Vector2.hpp"

typedef std::vector<std::shared_ptr<Vector2>> SharedPath;
typedef std::vector<std::unique_ptr<Vector2>> UniquePath;
