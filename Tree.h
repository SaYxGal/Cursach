#ifndef TREE_H
#define TREE_H
#include "treeNode.h"
class Node {
public:
    Node(int value);
    int value;
    Node* left;
    Node* right;
    treeNode* node;
};
void clearNode(Node* curr);
class BinaryTree {
public:
    BinaryTree();
    void clearTree();
    ~BinaryTree();
    Node* root;
};
#endif // TREE_H
