#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<chrono>
#include<ctime>
#include "list.h"
#include "dateandtime.h"
#include"rbtree.h"
#include"hashtable.h"
#include"bplustree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    List<DateAndTime> *list = nullptr;
    HashTable<DateAndTime> *HashTableChained = nullptr;
    ms::BTree<long long, DateAndTime> *bTree = nullptr;

private slots:
    void pushValue();
    void showStructure();
    void sort();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_createNewButton_clicked();
    void on_deleteButton_clicked();
    void on_findButton_clicked();
    void on_sortButton_clicked();
    void on_structure3_toggled(bool checked);
};

#endif // MAINWINDOW_H
