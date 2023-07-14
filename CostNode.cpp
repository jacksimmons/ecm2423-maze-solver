#include "CostNode.hpp"

CostNode::CostNode(std::unique_ptr<Vector2> goal)
	: Node()
{
	cost = calculateCost(goal);
}

CostNode::CostNode(std::unique_ptr<CostNode> prev_node, std::unique_ptr<Vector2> pos, std::unique_ptr<Vector2> goal)
	: Node(prev_node, pos)
{
	cost = calculateCost(goal);
}

int CostNode::getCost()
{
	return cost;
}