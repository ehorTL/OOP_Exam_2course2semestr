#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer;
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();
    setSystemDate();
}

MainWindow::~MainWindow()
{
    timer->stop();
    if(timer) delete timer;
    delete ui;
}

void MainWindow::updateTime()
{
    ui->labelTime->setText(QTime::currentTime().toString());

    if(QTime::currentTime().minute() == 0 && QTime::currentTime().second() == 0)
    {
        setSystemDate();
    }
}

void MainWindow::setSystemDate()
{
    QString placeHolder = (QDate::currentDate().month() < 10) ? "0" : "";
    ui->labelData->setText(QString::number(QDate::currentDate().day())+"."+
                           placeHolder +
                           QString::number(QDate::currentDate().month())+"."+
                           QString::number(QDate::currentDate().year()));
}
