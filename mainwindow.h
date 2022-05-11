#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTime>
#include "Tree.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void insertNode(int value);
    void checkSubTreeOf(Node* begin, bool where);
    void checkNode(Node*current, Node* newNode, bool where);
    void findNode(int value);
private slots:
    void on_insertButton_clicked();

    void on_findButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    void gatherAnims(QParallelAnimationGroup* group, Node* begin, Node* newNode, bool where);
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    BinaryTree tree;
    double multiplicator = 1;
};
void findParentWithAddLine(QGraphicsScene* scene,Node* node, Node* child, Node*parent);
void checkDistance(QParallelAnimationGroup* anim_group, Node* current, Node*child, Node*parent, double multi);
void delay( int millisecondsToWait );
#endif // MAINWINDOW_H
