#include "treeNode.h"
QRectF treeNode::boundingRect()const{
    return QRectF(0, 0, 30, 30);
}
treeNode::treeNode(int x, int y, int val): coords(x, y), value(val){}
treeNode::~treeNode(){}
void treeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::green);
    painter->setPen(pen);

    QString W(QString::number(value));

    painter->drawEllipse(0, 0, 30,30);
    painter->drawText(boundingRect(), Qt::AlignCenter, W);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
void treeNode::animate(){
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(1500);
    anim->setStartValue(QPoint(0, 0));
    anim->setEndValue(coords);
    anim->start();
}
