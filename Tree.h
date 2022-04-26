#ifndef TREE_H
#define TREE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
class Node;
class treeNode: public QGraphicsObject
{
public:
    QPoint coords;
    int value;
    QGraphicsLineItem* line_left;
    QGraphicsLineItem* line_right;
    treeNode(int x, int y, int value);
    virtual~treeNode();
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void animate();

};
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
