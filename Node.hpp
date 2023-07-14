#ifndef NODE_H
#define NODE_H 1

#include <memory>
#include "Vector2.hpp"

// Node class template
class Node
{
private:
    // Members
    std::unique_ptr<Node> previous_node;
    std::unique_ptr<Vector2> position;
public:
    // Constructors
	Node();
    Node(std::unique_ptr<Node>, std::unique_ptr<Vector2>);

    // Methods
    std::unique_ptr<Node> getPrev() const;
    void setPrev(std::unique_ptr<Node>);
    std::unique_ptr<Vector2> getPos() const;
    void setPos(std::unique_ptr<Vector2>);
    int getSize();
};
#endif