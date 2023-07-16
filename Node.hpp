#ifndef NODE_H
#define NODE_H 1

#include <memory>
#include "Vector2.hpp"

// Node class template
class Node
{
private:
    // Members
    std::shared_ptr<Node> previous_node;
    std::shared_ptr<Vector2> position;
    int gCost; // Start to this node
    int hCost; // This node to the goal
public:
	Node(Vector2&);
	Node(std::shared_ptr<Node>, std::shared_ptr<Vector2>, Vector2&);

    // Methods
    std::shared_ptr<Node> getPrev() const;
    void setPrev(std::shared_ptr<Node>);
    std::shared_ptr<Vector2> getPos() const;
    void setPos(std::shared_ptr<Vector2>);
    int getSize();
    void calculateCost(Vector2& goal);
	int getGCost();
    int getHCost();
    int getCost();
    void setGCost(int);
    void setHCost(int);
};
#endif