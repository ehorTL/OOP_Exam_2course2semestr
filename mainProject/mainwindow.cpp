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
    else if (ui->structure2->isChecked())
    {

    }
    else if (ui->structure2->isChecked())
    {

    }
    else if (ui->structure2->isChecked())
    {

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
    else if (ui->structure2->isChecked())
    {

    }
    else if (ui->structure3->isChecked())
    {

    }
    else if (ui->structure4->isChecked())
    {

    }

    showStructure();
}

void MainWindow::on_findButton_clicked()
{
    DateAndTime key;
    key.dateTime = ui->dateTimeSpin->dateTime();
    key.seconds = ui->secondsSpin->value();

    if (ui->structure1->isChecked()) //if checked list structure
    {
        QVector<Node<DateAndTime>*> foundValues;

        if (ui->keyBox->currentIndex() == 0)
        {
            foundValues = list->findAll(key, keyDateAndTime_byDate);
        }
        else if(ui->keyBox->currentIndex() == 1)
        {
            foundValues = list->findAll(key, keyDateAndTime_byTime);
        }
        else if(ui->keyBox->currentIndex() == 2)
        {
            foundValues = list->findAll(key, keyDateAndTime_byHour);
        }
        else if(ui->keyBox->currentIndex() == 3)
        {
            foundValues = list->findAll(key, keyDateAndTime_byMinute);
        }
        else if(ui->keyBox->currentIndex() == 4)
        {
            foundValues = list->findAll(key, keyDateAndTime_bySecond);
        }
        else if(ui->keyBox->currentIndex() == 5)
        {
            foundValues = list->findAll(key, keyDateAndTime_byYear);
        }
        else if(ui->keyBox->currentIndex() == 6)
        {
            foundValues = list->findAll(key, keyDateAndTime_byMonth);
        }
        else if(ui->keyBox->currentIndex() == 7)
        {
            foundValues = list->findAll(key, keyDateAndTime_byDay);
        }
        else if(ui->keyBox->currentIndex() == 7)
        {
            foundValues = list->findAll(key, keyDateAndTime_byDateTime);
        }

        //writing file just for easy output taking
        //rewrites output file
        QFile file (list->pathToOutput);
        if(!file.open(QIODevice::WriteOnly)) //open file
        {
            return;
        }
        QString printedList;
        for (int i=0; i<foundValues.size(); i++)
        {
            printedList += DateAndTimeToString(foundValues[i]->Data) + "\n";
        }
        file.write(printedList.toStdString().c_str());
        file.close();
        //---

        ui->outputAlgo->setText(printedList); //setting visible result
    }
    else if (ui->structure2->isChecked())
    {

    }
    else if (ui->structure3->isChecked())
    {

    }
    else if (ui->structure4->isChecked())
    {

    }

}

/**
* Comparator functions for different sort criteria.
*/
bool greaterThan_byTime(DateAndTime a, DateAndTime b)
{
    return (keyDateAndTime_byTime(a) > keyDateAndTime_byTime(b));
}
bool greaterThan_byDate(DateAndTime a, DateAndTime b)
{
    return (keyDateAndTime_byDate(a) > keyDateAndTime_byDate(b));
}
bool greaterThan_byDateTime(DateAndTime a, DateAndTime b)
{
    return (keyDateAndTime_byDateTime(a) > keyDateAndTime_byDateTime(b));
}
bool greaterThan_byYear(DateAndTime a, DateAndTime b)
{
    return (a.dateTime.date().year() > b.dateTime.date().year());
}
bool greaterThan_byMonth(DateAndTime a, DateAndTime b)
{
    return (a.dateTime.date().month() > b.dateTime.date().month());
}
bool greaterThan_byDay(DateAndTime a, DateAndTime b)
{
    return (a.dateTime.date().day() > b.dateTime.date().day());
}
bool greaterThan_byHour(DateAndTime a, DateAndTime b)
{
    return (a.dateTime.time().hour() > b.dateTime.time().hour());
}
bool greaterThan_byMinute(DateAndTime a, DateAndTime b)
{
    return (a.dateTime.time().minute() > b.dateTime.time().minute());
}
bool greaterThan_bySecond(DateAndTime a, DateAndTime b)
{
    return  (a.seconds > b.seconds);
}
///------------------------------------------------------

void MainWindow::on_sortButton_clicked()
{
    if (!(ui->structure1->isChecked())) //sorting is only appplied to list structure
    {
        return;
    }
    //else
    if (ui->sortBox->currentIndex() == 0) //start insert sorting
    {
        if (ui->keyBox->currentIndex()==0)
        {
            //qDebug() << "sorting started";
            list->sortInsert(greaterThan_byDate);
        }
        else if (ui->keyBox->currentIndex()==1)
        {
            list->sortInsert(greaterThan_byTime);
        }
        else if (ui->keyBox->currentIndex()==2)
        {
            list->sortInsert(greaterThan_byHour);
        }
        else if (ui->keyBox->currentIndex()==3)
        {
            list->sortInsert(greaterThan_byMinute);
        }
        else if (ui->keyBox->currentIndex()==4)
        {
            list->sortInsert(greaterThan_bySecond);
        }
        else if (ui->keyBox->currentIndex()==5)
        {
            list->sortInsert(greaterThan_byYear);
        }
        else if (ui->keyBox->currentIndex()==6)
        {
            list->sortInsert(greaterThan_byMonth);
        }
        else if (ui->keyBox->currentIndex()==7)
        {
            list->sortInsert(greaterThan_byDay);
        }
        else if (ui->keyBox->currentIndex()==8)
        {
            list->sortInsert(greaterThan_byDateTime);
        }
    }
    else if (ui->sortBox->currentIndex() == 1) //start heap sorting
    {
        if (ui->keyBox->currentIndex()==0)
        {
            list->sortHeap(greaterThan_byDate);
        }
        else if (ui->keyBox->currentIndex()==1)
        {
            list->sortHeap(greaterThan_byTime);
        }
        else if (ui->keyBox->currentIndex()==2)
        {
            list->sortHeap(greaterThan_byHour);
        }
        else if (ui->keyBox->currentIndex()==3)
        {
            list->sortHeap(greaterThan_byMinute);
        }
        else if (ui->keyBox->currentIndex()==4)
        {
            list->sortHeap(greaterThan_bySecond);
        }
        else if (ui->keyBox->currentIndex()==5)
        {
            list->sortHeap(greaterThan_byYear);
        }
        else if (ui->keyBox->currentIndex()==6)
        {
            list->sortHeap(greaterThan_byMonth);
        }
        else if (ui->keyBox->currentIndex()==7)
        {
            list->sortHeap(greaterThan_byDay);
        }
        else if (ui->keyBox->currentIndex()==8)
        {
            list->sortHeap(greaterThan_byDateTime);
        }
    }
    else if (ui->sortBox->currentIndex() == 2) //start merge sorting
    {
        if (ui->keyBox->currentIndex()==0)
        {
            list->sortMerge(greaterThan_byDate);
        }
        else if (ui->keyBox->currentIndex()==1)
        {
            list->sortMerge(greaterThan_byTime);
        }
        else if (ui->keyBox->currentIndex()==2)
        {
            list->sortMerge(greaterThan_byHour);
        }
        else if (ui->keyBox->currentIndex()==3)
        {
            list->sortMerge(greaterThan_byMinute);
        }
        else if (ui->keyBox->currentIndex()==4)
        {
            list->sortMerge(greaterThan_bySecond);
        }
        else if (ui->keyBox->currentIndex()==5)
        {
            list->sortMerge(greaterThan_byYear);
        }
        else if (ui->keyBox->currentIndex()==6)
        {
            list->sortMerge(greaterThan_byMonth);
        }
        else if (ui->keyBox->currentIndex()==7)
        {
            list->sortMerge(greaterThan_byDay);
        }
        else if (ui->keyBox->currentIndex()==8)
        {
            list->sortMerge(greaterThan_byDateTime);
        }
    }
    else if (ui->sortBox->currentIndex() == 3) //start count sorting
    {
        if (ui->keyBox->currentIndex()==0)
        {
            list->sortCount(greaterThan_byDate);
        }
        else if (ui->keyBox->currentIndex()==1)
        {
            list->sortCount(greaterThan_byTime);
        }
        else if (ui->keyBox->currentIndex()==2)
        {
            list->sortCount(greaterThan_byHour);
        }
        else if (ui->keyBox->currentIndex()==3)
        {
            list->sortCount(greaterThan_byMinute);
        }
        else if (ui->keyBox->currentIndex()==4)
        {
            list->sortCount(greaterThan_bySecond);
        }
        else if (ui->keyBox->currentIndex()==5)
        {
            list->sortCount(greaterThan_byYear);
        }
        else if (ui->keyBox->currentIndex()==6)
        {
            list->sortCount(greaterThan_byMonth);
        }
        else if (ui->keyBox->currentIndex()==7)
        {
            list->sortCount(greaterThan_byDay);
        }
        else if (ui->keyBox->currentIndex()==8)
        {
            list->sortCount(greaterThan_byDateTime);
        }
    }

    showStructure();
}
