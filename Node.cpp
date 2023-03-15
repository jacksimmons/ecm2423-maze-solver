#include "Node.h"

// Node implementation
Node::Node()
{
    previous_node = nullptr;
    position = new Vector2();
}

Node::Node(Node *prev_node, Vector2 *pos)
{
    previous_node = prev_node;
    position = pos;
}

void Node::set(Node *prev_node, Vector2 *pos)
{
    previous_node = prev_node;
    position = pos;
}