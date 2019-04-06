#include "StackNode.h"

StackNode::StackNode() : _data(nullptr), _next(nullptr)
{
}

StackNode::StackNode(Position* data, StackNode* next) : _data(data), _next(next)
{
}

StackNode::~StackNode()
{
}

Position *StackNode::getData()
{
    return _data;
}

void StackNode::setData(Position *data)
{
    _data = data;
}

StackNode *StackNode::getNext()
{
    return _next;
}

void StackNode::setNext(StackNode *next)
{
    _next = next;
}
