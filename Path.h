#ifndef NODE_H
#define NODE_H

#include "Main.h"

class Path {
    private:
        Vector2 position;
        Path *previous;
    public:
        Path(Vector2 pos);
        Vector2 getPosition();
        void setPosition(Vector2 pos);
        Path *getPrevious();
        void setPrevious(Path *path);
};

#endif