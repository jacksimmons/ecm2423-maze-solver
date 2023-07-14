#ifndef COSTNODE_H
#define COSTNODE_H 1

#include "Node.hpp"

class CostNode : public Node
{
private:
	int cost;
public:
	CostNode(std::unique_ptr<Vector2>);
	CostNode(std::unique_ptr<CostNode> prev_node, std::unique_ptr<Vector2> pos, std::unique_ptr<Vector2> goal);
	
	// Static methods
	int calculateCost(Vector2 goal)
	{
		return getSize() + getPos()->distTo(goal);
	}
	int getCost();
};
#endif