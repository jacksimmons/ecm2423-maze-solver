#ifndef COSTNODE_H
#define COSTNODE_H 1

#include "Node.hpp"

class CostNode : public Node
{
private:
	int cost;
public:
	CostNode(Vector2* goal);
	CostNode(CostNode* prev_node, Vector2* pos, Vector2* goal);
	
	// Static methods
	static int calculateCost(Node* node, Vector2* goal)
	{
		return node->getSize() + node->getPos()->distTo(goal);
	}
	int getCost();
};
#endif