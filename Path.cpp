#include "Path.h"
#include <stdlib.h>

Path::Path(Vector2 pos)
{
    position = pos;
    
}

Vector2 Path::getPosition()
{
    return position;
}

void Path::setPosition(Vector2 pos)
{
    position = pos;
}

Path *Path::getPrevious()
{
    return previous;
}

void Path::setPrevious(Path *prev)
{
    previous = prev;
}