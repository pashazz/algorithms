//
// Created by Pasha on 12/12/2019.
//

#ifndef BINARYTREE_NODE_H
#define BINARYTREE_NODE_H

class Node {
public:
    Node (int value, Node* parent) {
        this->value = value;
        this->parent = parent;
    }
    int value;
    Node * parent = nullptr;
    Node * leftChild = nullptr;
    Node * rightChild = nullptr;

    Node * getSibiling();

    Node * getRightSibiling();
};


#endif //BINARYTREE_NODE_H
