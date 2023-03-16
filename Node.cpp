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

Node::~Node()
{
    Node *node_ptr = this;
    if (node_ptr != 0)
    {
        node_ptr->getPrev()->~Node();
    }
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