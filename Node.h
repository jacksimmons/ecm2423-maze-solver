#include "Vector2.h"

class Node
{
private:
    Node *previous_node;
    Vector2 *position;
public:
    Node();
    Node(Node *prev_node, Vector2 *pos);
    ~Node();
    Node *getPrev() const;
    void setPrev(Node *prev);
    Vector2 *getPos() const;
    void setPos(Vector2 *pos);
};