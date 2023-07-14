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
	int cost;
public:
	Node(Vector2&);
	Node(std::shared_ptr<Node>, std::shared_ptr<Vector2>, Vector2&);
	
	// Static methods
	int calculateCost(Vector2 goal)
	{
		return getSize() + getPos()->distTo(goal);
	}
	int getCost();

    // Methods
    std::shared_ptr<Node> getPrev() const;
    void setPrev(std::shared_ptr<Node>);
    std::shared_ptr<Vector2> getPos() const;
    void setPos(std::shared_ptr<Vector2>);
    int getSize();
};
#endif