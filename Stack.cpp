#include "Stack.h"

Stack::Stack() : _top(nullptr)
{
}

Stack::~Stack()
{
    //Pop all data off of the stack before deconstructing.
    while (_top != nullptr)
    {
        Pop();
    }
}

Position *Stack::Peek()
{
    return _top->getData();
}

myerror_code Stack::Push(Position *data)
{
    _top = new StackNode(data, _top);
    return (success);
}

myerror_code Stack::Pop()
{
    if (_top != nullptr)
    {
        StackNode* node = _top;
        _top = _top->getNext();
        delete node;
        return (success);
    }
    else
    {
        return (underflow);
    }
}

ostream &operator<<(ostream &output, Stack &stack)
{
    StackNode* node = stack._top;

    while(node != nullptr)
    {
        cout << "(" << node->getData()->row << ","
             << node->getData()->col << ")" << endl;
        node = node->getNext();
    }

    return output;
}

