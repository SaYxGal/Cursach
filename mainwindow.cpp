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
                    newNode->node = new treeNode(prev->node->coords.x() - 30,prev->node->coords.y() + 30, newNode->value);
                    scene->addItem(newNode->node);
                    prev->left = newNode;
                    delay(2000);
                    newNode->node->animate();
                    break;
                }
            }
            else if (value > current->value) {
                current = current->right;
                if (current == nullptr) {
                    newNode->node = new treeNode(prev->node->coords.x() + 30,prev->node->coords.y() + 30, newNode->value);
                    scene->addItem(newNode->node);
                    prev->right = newNode;
                    delay(2000);
                    newNode->node->animate();
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

