//
// Created by Pasha on 12/12/2019.
//


#include "node.h"
#include <cassert>

Node * Node::getSibiling() {
    if (!this->parent) {
        return nullptr;
    }
    assert(this == this->parent->rightChild || this == this->parent->leftChild);

    if (this == this->parent->rightChild) {
        return this->parent->leftChild;
    } else {
        return this->parent->rightChild;
    }
}

Node *Node::getRightSibiling() {
    if (!this->parent) {
        return nullptr;
    }
    if (this == this->parent->leftChild) {
        return this->parent->rightChild;
    }
    //If this is the right child of the parent, then go up and find left child of the right sibiling
    Node *grandparent = this->parent->parent;
    if (!grandparent) {
        return nullptr;
    }

}
