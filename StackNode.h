//
// Created by nscc on 2/15/18.
//

#ifndef ASS2_MAZESOLVER_STACKNODE_H
#define ASS2_MAZESOLVER_STACKNODE_H

#include <array>
#include "Position.h"

using namespace std;

class StackNode
{
private:
    Position* _data;
    StackNode* _next;

public:
    StackNode();
    StackNode(Position* data, StackNode* next);
    virtual ~StackNode();

    Position* getData();
    void setData(Position* data);

    StackNode* getNext();
    void setNext(StackNode* next);
};


#endif //ASS2_MAZESOLVER_STACKNODE_H
