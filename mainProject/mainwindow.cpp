#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Date And Time");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------------------------------------------------------------

//function to convert structure fields in visible form
QString DateAndTimeToString(DateAndTime dt)
{
    QString result;
    result += QString::number(dt.dateTime.date().day()) + "." +
            QString::number(dt.dateTime.date().month()) + "." +
            QString::number(dt.dateTime.date().year()) + " " +
            QString::number(dt.dateTime.time().hour()) + ":" +
            QString::number(dt.dateTime.time().minute()) + ":" +
            QString::number(dt.seconds);
    return result;
}

long long keyDateAndTime_byDate(DateAndTime dt)
{
    long long result;
    QString strResult;
    strResult+= QString::number(dt.dateTime.date().year()) +
            QString::number(dt.dateTime.date().month()) +
            QString::number(dt.dateTime.date().day());
    result = strResult.toLongLong();
    return result;
}

long long keyDateAndTime_byTime(DateAndTime dt)
{
    long long result;
    QString strResult;
    strResult+= QString::number(dt.dateTime.time().hour()) +
            QString::number(dt.dateTime.time().minute()) +
            QString::number(dt.seconds);
    result = strResult.toLongLong();
    return result;
}

long long keyDateAndTime_byDateTime(DateAndTime dt)
{
    long long result;
    QString strResult;
    strResult+= QString::number(dt.dateTime.date().year()) +
            QString::number(dt.dateTime.date().month()) +
            QString::number(dt.dateTime.date().day()) +
            QString::number(dt.dateTime.time().hour()) +
            QString::number(dt.dateTime.time().minute()) +
            QString::number(dt.seconds);
    result = strResult.toLongLong();
    return result;
}

long long keyDateAndTime_byYear(DateAndTime dt)
{
    return (long long) dt.dateTime.date().year();
}

long long keyDateAndTime_byMonth(DateAndTime dt)
{
    return (long long) dt.dateTime.date().month();
}

long long keyDateAndTime_byDay(DateAndTime dt)
{
    return (long long) dt.dateTime.date().day();
}

long long keyDateAndTime_byHour(DateAndTime dt)
{
    return (long long)dt.dateTime.time().hour();
}

long long keyDateAndTime_byMinute(DateAndTime dt)
{
    return (long long)dt.dateTime.time().minute();
}

long long keyDateAndTime_bySecond(DateAndTime dt)
{
    return (long long)(dt.seconds);
}
//----------------------------------------------------------


void MainWindow::pushValue()
{
    DateAndTime dt;
    dt.dateTime = ui->dateTimeSpin->dateTime();
    dt.seconds = ui->secondsSpin->value();


    if (ui->structure1->isChecked()) //if DL chosen
    {
        if (list==nullptr)
        {
            list = new List<DateAndTime>();
        }
        list->pushBack(dt);
        //qDebug() << DateAndTimeToString(dt); //works correctly
    }
}

void MainWindow::showStructure()
{
    QString path;
    if (ui->structure1->isChecked())
    {
        if (list==nullptr) return;
        list->printListInFile(DateAndTimeToString);
        path = list->pathToOutput;
    }

    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QString result = "";
    while(!file.atEnd())
    {
        result += file.readLine();
    }
    ui->outputAlgo->setText(result);
    file.close();
}


void MainWindow::on_pushButton_clicked()
{
    pushValue();
    showStructure();
}

void MainWindow::on_pushButton_2_clicked()
{
    showStructure();
}

void MainWindow::on_createNewButton_clicked()
{
    if (ui->structure1->isChecked())
    {
        list->clear();
        showStructure();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    DateAndTime key;
    key.dateTime = ui->dateTimeSpin->dateTime();
    key.seconds = ui->secondsSpin->value();

    if (ui->structure1->isChecked()) //if checked list structure
    {
        Node<DateAndTime> *delNode = nullptr;

        if (ui->keyBox->currentIndex() == 0)
        {
            delNode = list->find(key, keyDateAndTime_byDate);
        }
        else if(ui->keyBox->currentIndex() == 1)
        {
            delNode = list->find(key, keyDateAndTime_byTime);
        }
        else if(ui->keyBox->currentIndex() == 2)
        {
            delNode = list->find(key, keyDateAndTime_byHour);
        }
        else if(ui->keyBox->currentIndex() == 3)
        {
            delNode = list->find(key, keyDateAndTime_byMinute);
        }
        else if(ui->keyBox->currentIndex() == 4)
        {
            delNode = list->find(key, keyDateAndTime_bySecond);
        }
        else if(ui->keyBox->currentIndex() == 5)
        {
            delNode = list->find(key, keyDateAndTime_byYear);
        }
        else if(ui->keyBox->currentIndex() == 6)
        {
            delNode = list->find(key, keyDateAndTime_byMonth);
        }
        else if(ui->keyBox->currentIndex() == 7)
        {
            delNode = list->find(key, keyDateAndTime_byDay);
        }
        else if(ui->keyBox->currentIndex() == 7)
        {
            delNode = list->find(key, keyDateAndTime_byDateTime);
        }

        list->deleteNode(delNode);
    }

    showStructure();
}
