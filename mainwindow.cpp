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
            if(current != newNode && current->node->coords.x() > newNode->node->coords.x()){
                QPropertyAnimation* anim = new QPropertyAnimation(current->node, "pos");
                anim->setDuration(1500);
                anim->setStartValue(QPoint(current->node->coords.x(), current->node->coords.y()));
                anim->setEndValue(QPoint(current->node->coords.x() + 30, current->node->coords.y()));
                current->node->coords = QPoint(current->node->coords.x() + 30, current->node->coords.y());
                 group->addAnimation(anim);
            }
        }
        else{
            if(current != newNode && current->node->coords.x() < newNode->node->coords.x()){
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
        QPropertyAnimation* an = new QPropertyAnimation(marker->node, "pos");
        an->setDuration(1500);
        if(where){
            an->setStartValue(QPoint(marker->node->coords.x(), marker->node->coords.y()));
            an->setEndValue(QPoint(marker->node->coords.x() + 30, marker->node->coords.y()));
            marker->node->coords = QPoint(marker->node->coords.x() + 30, marker->node->coords.y());
        }
        else{
            an->setStartValue(QPoint(marker->node->coords.x(), marker->node->coords.y()));
            an->setEndValue(QPoint(marker->node->coords.x() - 30, marker->node->coords.y()));
            marker->node->coords = QPoint(marker->node->coords.x() - 30, marker->node->coords.y());
        }
        anim_group->addAnimation(an);
    }
    anim_group->start(QAbstractAnimation::DeleteWhenStopped);

}

void MainWindow::insertNode(int value){
    if(!tree.root){
        tree.root = new Node(value);
        tree.root->node = new treeNode(270, 0, tree.root->value);
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
        findParent(tree.root, current, nullptr);
        if(current->node->line_left != nullptr){
            scene->addItem(current->node->line_left);
        }
        if(current->node->line_right != nullptr){
            scene->addItem(current->node->line_right);
        }
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

void findParent(Node *node, Node *child, Node *parent)
{
    if(node == nullptr){
        return;
    }
    if(node->value == child->value && parent != nullptr){
        if(child->value < parent->value){
            parent->node->line_left = new QGraphicsLineItem(parent->node->coords.x() + 15 - 8, parent->node->coords.y() + 15 + 13, child->node->coords.x() + 15 + 8, child->node->coords.y() + 15 - 13); //15 - это корректировка, чтобы отсчитывали от центра, 8 и 13 для нахождения точки сбоку кружка
        }
        else{
            parent->node->line_right = new QGraphicsLineItem(parent->node->coords.x() + 15 + 8, parent->node->coords.y() + 15 + 13, child->node->coords.x() + 15 - 8, child->node->coords.y() + 15 - 13);
        }
        return;
    }
    else{
        findParent(node->left, child, node);
        findParent(node->right, child, node);
    }
}

