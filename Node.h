#include "Vector2.h"

struct Node
{
    Node();
    Node(Node *prev_node, Vector2 *pos);
    Node *previous_node;
    Vector2 *position;
    void set(Node *prev_node, Vector2 *pos);
};