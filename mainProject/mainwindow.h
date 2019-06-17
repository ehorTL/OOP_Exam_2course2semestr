#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>

#include "list.h"
#include "dateandtime.h"

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
    //bool chosenList = false;

private slots:
    void pushValue();
    void showStructure();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
