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
QRectF treeNode::boundingRect()const{
    return QRectF(0, 0, 30, 30);
}
treeNode::treeNode(int x, int y, int val): coords(x, y), value(val), line_left(nullptr), line_right(nullptr){}
treeNode::~treeNode(){
    delete line_right;
    delete line_left;
}
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
    anim->setDuration(2000);
    anim->setStartValue(QPoint(0, 0));
    anim->setEndValue(coords);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}





FinderNode::~FinderNode(){}

QRectF FinderNode::boundingRect() const
{
    return QRectF(0, 0, 30, 30);
}

void FinderNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::red, 3);
    painter->setPen(pen);
    painter->drawEllipse(0, 0, 30, 30);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

