#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::gatherAnims(QParallelAnimationGroup *group, Node* current, Node* newNode, bool where){
    if(current){
        gatherAnims(group, current->left, newNode, where);
        gatherAnims(group, current->right, newNode, where);

        if(where){
            if(current != newNode && current != tree.root && current->node->coords.x() > newNode->node->coords.x()){
                QPropertyAnimation* anim = new QPropertyAnimation(current->node, "pos");
                anim->setDuration(1500);
                anim->setStartValue(QPoint(current->node->coords.x(), current->node->coords.y()));
                anim->setEndValue(QPoint(current->node->coords.x() + 30, current->node->coords.y()));
                current->node->coords = QPoint(current->node->coords.x() + 30, current->node->coords.y());
                 group->addAnimation(anim);
            }
            else if(current != newNode && current != tree.root && current->node->coords.x() == newNode->node->coords.x() && current->value > newNode->value){
                QPropertyAnimation* anim = new QPropertyAnimation(current->node, "pos");
                anim->setDuration(1500);
                anim->setStartValue(QPoint(current->node->coords.x(), current->node->coords.y()));
                anim->setEndValue(QPoint(current->node->coords.x() + 30, current->node->coords.y()));
                current->node->coords = QPoint(current->node->coords.x() + 30, current->node->coords.y());
                group->addAnimation(anim);
            }
        }
        else{
            if(current != newNode && current != tree.root && current->node->coords.x() < newNode->node->coords.x()){
                QPropertyAnimation* anim = new QPropertyAnimation(current->node, "pos");
                anim->setDuration(1500);
                anim->setStartValue(QPoint(current->node->coords.x(), current->node->coords.y()));
                anim->setEndValue(QPoint(current->node->coords.x() - 30, current->node->coords.y()));
                current->node->coords = QPoint(current->node->coords.x() - 30, current->node->coords.y());
                 group->addAnimation(anim);
            }
            else if(current != newNode && current != tree.root && current->node->coords.x() == newNode->node->coords.x() && current->value < newNode->value){
                QPropertyAnimation* anim = new QPropertyAnimation(current->node, "pos");
                anim->setDuration(1500);
                anim->setStartValue(QPoint(current->node->coords.x(), current->node->coords.y()));
                anim->setEndValue(QPoint(current->node->coords.x() - 30, current->node->coords.y()));
                current->node->coords = QPoint(current->node->coords.x() - 30, current->node->coords.y());
                group->addAnimation(anim);
            }
        }
    }
}
void MainWindow::checkSubTreeOf(Node* marker, bool where){ //false - left, true - right
    QParallelAnimationGroup* anim_group = new QParallelAnimationGroup;
    gatherAnims(anim_group, tree.root,marker, where);
    if(marker != tree.root){
        checkDistance(anim_group, tree.root, marker, nullptr);
    }
    anim_group->start(QAbstractAnimation::DeleteWhenStopped);

}

void MainWindow::insertNode(int value){
    if(!tree.root){
        tree.root = new Node(value);
        tree.root->node = new treeNode((int)(ui->graphicsView->width()/2) - 15, 0, tree.root->value);
        scene->addItem(tree.root->node);
        delay(2000);
        tree.root->node->animate();
    }
    else{
        Node* newNode = new Node(value);
        Node* current = tree.root;
        Node* prev;
        while (true) {
            prev = current;
            if (value < current->value) {
                current = current->left;
                if (current == nullptr) {
                    newNode->node = new treeNode(prev->node->coords.x() - 30,prev->node->coords.y() + 40, newNode->value);
                    scene->addItem(newNode->node);
                    prev->left = newNode;
                    delay(2000);
                    newNode->node->animate();
                    delay(2000);
                    if(value < tree.root->value){
                        checkNode(tree.root,newNode, false);
                    }
                    else{
                        checkNode(tree.root,newNode, true);
                    }
                    checkNode(tree.root,newNode, false); //холостой прогон для обновления линий, лучше варианта пока не нашёл

                    break;
                }
            }
            else if (value > current->value) {
                current = current->right;
                if (current == nullptr) {
                    newNode->node = new treeNode(prev->node->coords.x() + 30,prev->node->coords.y() + 40, newNode->value);
                    scene->addItem(newNode->node);
                    prev->right = newNode;
                    delay(2000);
                    newNode->node->animate();
                    delay(2000);
                    if(value < tree.root->value){
                        checkNode(tree.root,newNode, false);
                    }
                    else{
                        checkNode(tree.root,newNode, true);
                    }
                    checkNode(tree.root,newNode, false);

                    break;
                }
            }
            else {
                delete newNode;
                break;
            }
        }
    }
}

void MainWindow::checkNode(Node *current, Node* newNode, bool where){
    if(current){
        checkNode(current->left, newNode, where);
        checkNode(current->right, newNode, where);
        if(current != newNode && current->node->coords.x() == newNode->node->coords.x()){
            checkSubTreeOf(newNode, where);
            return;
        }
        findParentWithAddLine(scene,tree.root, current, nullptr);
    }
}

bool MainWindow::findNode(int value){
    Node* current = tree.root;
    while (current != nullptr) {
        if (value == current->value) {
            return true;
        }
        else if (value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

void MainWindow::on_insertButton_clicked()
{
    insertNode(ui->spinBox->value());
}


void MainWindow::on_findButton_clicked()
{

}

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void findParentWithAddLine(QGraphicsScene* scene,Node *node, Node *child, Node *parent)
{
    if(node == nullptr){
        return;
    }
    if(node->value == child->value && parent != nullptr){
        if(child->value < parent->value){
            if(parent->node->line_left != nullptr){
                scene->removeItem(parent->node->line_left);
                delete parent->node->line_left;
            }
            parent->node->line_left = new QGraphicsLineItem(parent->node->coords.x() + 15 - 8, parent->node->coords.y() + 15 + 13, child->node->coords.x() + 15 + 8, child->node->coords.y() + 15 - 13); //15 - это корректировка, чтобы отсчитывали от центра, 8 и 13 для нахождения точки сбоку кружка
            scene->addItem(parent->node->line_left);
        }
        else{
            if(parent->node->line_right != nullptr){
                scene->removeItem(parent->node->line_right);
                delete parent->node->line_right;
            }
            parent->node->line_right = new QGraphicsLineItem(parent->node->coords.x() + 15 + 8, parent->node->coords.y() + 15 + 13, child->node->coords.x() + 15 - 8, child->node->coords.y() + 15 - 13);
            scene->addItem(parent->node->line_right);
        }
        return;
    }
    else{
        findParentWithAddLine(scene,node->left, child, node);
        findParentWithAddLine(scene,node->right, child, node);
    }
}



void checkDistance(QParallelAnimationGroup* anim_group,Node *current, Node *child, Node *parent)
{
    if(current == nullptr){
        return;
    }
    if(current->value == child->value && parent != nullptr){
        if(parent->node->coords.x() - child->node->coords.x() > 30){
            QPropertyAnimation* anim = new QPropertyAnimation(current->node, "pos");
            anim->setDuration(1500);
            anim->setStartValue(QPoint(current->node->coords.x(), current->node->coords.y()));
            anim->setEndValue(QPoint(current->node->coords.x() + 30, current->node->coords.y()));
            current->node->coords = QPoint(current->node->coords.x() + 30, current->node->coords.y());
            anim_group->addAnimation(anim);
            return;
        }
        else if(parent->node->coords.x() - child->node->coords.x() < -30){
            QPropertyAnimation* anim = new QPropertyAnimation(current->node, "pos");
            anim->setDuration(1500);
            anim->setStartValue(QPoint(current->node->coords.x(), current->node->coords.y()));
            anim->setEndValue(QPoint(current->node->coords.x() - 30, current->node->coords.y()));
            current->node->coords = QPoint(current->node->coords.x() - 30, current->node->coords.y());
            anim_group->addAnimation(anim);
            return;
        }

        else{
            return;
        }
    }
    else{
        checkDistance(anim_group,current->left, child, current);
        checkDistance(anim_group,current->right, child, current);
    }
}
