#include "Node.hpp"

Node::Node()
{
	previous_node = nullptr;
	position = std::make_unique<Vector2>();
}

Node::Node(std::unique_ptr<Node> prev_node, std::unique_ptr<Vector2> pos)
{
    previous_node = std::move(prev_node);
    position = std::move(pos);
}

std::unique_ptr<Node> Node::getPrev() const
{
    return std::make_unique<Node>(std::move(previous_node));
}

void Node::setPrev(std::unique_ptr<Node> prev)
{
    previous_node = std::move(prev);
}

std::unique_ptr<Vector2> Node::getPos() const
{
    return std::make_unique<Vector2>(std::move(position));
}

void Node::setPos(std::unique_ptr<Vector2> pos)
{
    position = std::move(pos);
}

int Node::getSize()
{
    if (getPrev() == nullptr)
        return 1;
    return getPrev()->getSize() + 1;
}