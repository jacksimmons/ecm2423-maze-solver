#include "CostNode.hpp"

CostNode::CostNode(Vector2* goal)
	: Node()
{
	cost = CostNode::calculateCost(this, goal);
}

CostNode::CostNode(CostNode* prev_node, Vector2* pos, Vector2* goal)
	: Node(prev_node, pos)
{
	cost = CostNode::calculateCost(this, goal);
}

int CostNode::getCost()
{
	return cost;
}