//
// Created by chris on 4/1/2023.
//

#ifndef P2_NEW__SCANNER_H
#define P2_NEW__SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "token.h"
#include "parser.h"
using namespace std;


Token scanner(fstream &file, int&);
int** buildFSATable();
int characterLookup(int);
Token checkTokens(int, string);

#endif //P2_NEW__SCANNER_H
