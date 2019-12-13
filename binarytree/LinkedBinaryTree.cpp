//
// Created by Pasha on 12/12/2019.
//

#include "LinkedBinaryTree.h"

void LinkedBinaryTree::add(int what) {
    Node *node = makeNode(what);
    insertNewNode(node);
    restore();
}

Node *LinkedBinaryTree::makeNode(int value, Node *parent) {
    return new Node(value, parent);
}

void LinkedBinaryTree::insertNewNode(Node *node) {
    if (!root) {
        root = node;
        return;
    }
    // This tree is complete binary tree. Find the position at the deepest level or create a new level if possible

    Node *current = root;
    //1. Going to the bottom
    while (current->leftChild) {
        current = current->leftChild;
    }
    //2. Going to the right


}

void LinkedBinaryTree::restore() {

}

