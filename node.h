//
// Created by chris on 4/1/2023.
//

#ifndef P2_NEW__NODE_H
#define P2_NEW__NODE_H

#include "scanner.h"
#include <vector>

struct node_t
{
    string label;
    vector<Token> tokens;

    node_t* child1  = nullptr;
    node_t* child2 = nullptr;
    node_t* child3 = nullptr;
    node_t* child4 = nullptr;
    node_t* child5 = nullptr;
};

#endif //P2_NEW__NODE_H
