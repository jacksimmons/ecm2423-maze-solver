#include "Node.h"

Node::Node()
{
    previous_node = 0;
    position = new Vector2();
}

Node::Node(Node *prev_node, Vector2 *pos)
{
    previous_node = prev_node;
    position = pos;
}

Node *Node::getPrev() const
{
    return previous_node;
}

void Node::setPrev(Node *prev)
{
    previous_node = prev;
}

Vector2 *Node::getPos() const
{
    return position;
}

void Node::setPos(Vector2 *pos)
{
    position = pos;
}

int Node::getSize()
{
    if (getPrev() == 0)
        return 1;
    return getPrev()->getSize() + 1;
}