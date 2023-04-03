//
// Created by chris on 4/2/2023.
//

#include "treePrint.h"

void traversePreorder(node_t* root, int level)
{

    if (root == nullptr)
    {
        return;
    }
    else
    {
        printNodeInfo(root, level);
    }


    traversePreorder(root->child1, level+1);
    traversePreorder(root->child2, level+1);
    traversePreorder(root->child3, level+1);

}


void printNodeInfo(node_t* node, int level)
{
    cout << "here is a node";


//    if (!node->tokens.empty())
//    {
//        for ( int i = 0; i < node->tokens.size(); i++)
//        {
//            Token token = node->tokens[i];
//
//            cout << token.tokenInstance;
//        }
//    }

    cout << endl;
}


