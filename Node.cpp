#include "Node.hpp"

Node::Node(Vector2 &goal)
{
	previous_node = nullptr;
	position = std::make_unique<Vector2>();
    calculateCost(goal);
}

Node::Node(std::shared_ptr<Node> prev_node, std::shared_ptr<Vector2> pos, Vector2& goal)
{
    previous_node = prev_node;
    position = pos;
	calculateCost(goal);
}

std::shared_ptr<Node> Node::getPrev() const
{
    return previous_node;
}

void Node::setPrev(std::shared_ptr<Node> prev)
{
    previous_node = prev;
}

std::shared_ptr<Vector2> Node::getPos() const
{
    return position;
}

void Node::setPos(std::shared_ptr<Vector2> pos)
{
    position = pos;
}

int Node::getSize()
{
    if (getPrev() == nullptr)
        return 1;
    return getPrev()->getSize() + 1;
}

void Node::calculateCost(Vector2 &goal)
{
    gCost = getSize()-1;
    hCost = getPos()->distTo(goal);
}

int Node::getGCost()
{
	return gCost;
}

int Node::getHCost()
{
    return hCost;
}

int Node::getCost()
{
    return gCost + hCost;
}

void Node::setGCost(int gCost)
{
    this->gCost = gCost;
}

void Node::setHCost(int hCost)
{
    this->hCost = hCost;
}