#ifndef ASS2_MAZESOLVER_STACK_H
#define ASS2_MAZESOLVER_STACK_H

#include "iostream"
#include "StackNode.h"

using namespace std;
enum myerror_code { success, underflow, overflow};

class Stack
{
private:
    StackNode *_top;

public:
    Stack();
    virtual ~Stack();

    Position* Peek();
    myerror_code Push(Position* data);
    myerror_code Pop();

    friend ostream& operator<<( ostream& output, Stack& stack);
};


#endif //ASS2_MAZESOLVER_STACK_H
