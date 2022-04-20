#ifndef TREENODE_H
#define TREENODE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPropertyAnimation>
class treeNode: public QGraphicsObject
{
public:
    QPoint coords;
    int value;
    treeNode(int x, int y, int value);
    virtual~treeNode();
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void animate();

};
#endif // TREENODE_H
