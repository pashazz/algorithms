//
// Created by Pasha on 12/12/2019.
//

#ifndef BINARYTREE_LINKEDBINARYTREE_H
#define BINARYTREE_LINKEDBINARYTREE_H


#include "node.h"
#include "bintree.h"


class LinkedBinaryTree : BinaryTree {
public:
    void add(int what) override final ;

protected:
    Node * makeNode(int, Node* = nullptr);
    void insertNewNode(Node*);
    void restore();
    Node * root = nullptr;
};


#endif //BINARYTREE_LINKEDBINARYTREE_H
