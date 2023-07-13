#ifndef NODE_H
#define NODE_H
#include "Vector2.h"

// Node class template
class Node
{
private:
    // Members
    Node *previous_node;
    Vector2 *position;
public:
    // Constructors
    Node();
    Node(Node *prev_node, Vector2 *pos);

    // Methods
    Node *getPrev() const;
    void setPrev(Node *prev);
    Vector2 *getPos() const;
    void setPos(Vector2 *pos);
    int getSize();
};
#endif