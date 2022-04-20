#include "Tree.h"
BinaryTree::~BinaryTree() {
    clearTree();
}
Node::Node(int val) : value(val), left(nullptr), right(nullptr), node(nullptr) {}
BinaryTree::BinaryTree() : root(nullptr) {} // -1 знак пустоты
void clearNode(Node* curr) {
    if (curr) {
        clearNode(curr->left);
        clearNode(curr->right);
        delete curr->node;
        delete curr;
    }
}
void BinaryTree::clearTree() {
    clearNode(root);
}

