//
// Created by chris on 4/1/2023.
//

#ifndef P2_NEW__PARSER_H
#define P2_NEW__PARSER_H

#include "scanner.h"
#include "token.h"
#include "node.h"
#include "scanner.cpp"
#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

extern int lineNum;
node_t* parser(fstream &file);
node_t* getNode(string label);

void error();

#endif //P2_NEW__PARSER_H
