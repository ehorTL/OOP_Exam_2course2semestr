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
    }
    else if (ui->structure3->isChecked())
    {
        if (HashTableChained==nullptr)
        {
            HashTableChained = new HashTable<DateAndTime>(ui->spinHashTableSize->value());
            ui->keyBox->setEnabled(false);
            ui->spinHashTableSize->setEnabled(false);
        }
        //adding
        if (ui->keyBox->currentIndex() == 0)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byDate);
            ui->key3->setText("date");
        }
        else if (ui->keyBox->currentIndex() == 1)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byTime);
            ui->key3->setText("time");
        }
        else if (ui->keyBox->currentIndex() == 2)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byHour);
            ui->key3->setText("hour");
        }
        else if (ui->keyBox->currentIndex() == 3)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byMinute);
            ui->key3->setText("minutes");
        }
        else if (ui->keyBox->currentIndex() == 4)
        {
            HashTableChained->addItem(dt, keyDateAndTime_bySecond);
            ui->key3->setText("seconds");
        }
        else if (ui->keyBox->currentIndex() == 5)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byYear);
            ui->key3->setText("year");
        }
        else if (ui->keyBox->currentIndex() == 6)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byMonth);
            ui->key3->setText("month");
        }
        else if (ui->keyBox->currentIndex() == 7)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byDay);
            ui->key3->setText("day");
        }
        else if (ui->keyBox->currentIndex() == 8)
        {
            HashTableChained->addItem(dt, keyDateAndTime_byDateTime);
            ui->key3->setText("dateTime");
        }
    }
    else if (ui->structure4->isChecked()) //tree chosen
    {
        if (bTree==nullptr)
        {
            bTree= new ms::BTree<long long, DateAndTime>(ui->spinBtreeSize->value());
            ui->keyBox->setEnabled(false);
            ui->spinBtreeSize->setEnabled(false);
        }
        //adding
        if (ui->keyBox->currentIndex() == 0)
        {
            bTree->insert(keyDateAndTime_byDate(dt), dt);
            ui->key4->setText("date");
        }
        else if (ui->keyBox->currentIndex() == 1)
        {
            bTree->insert(keyDateAndTime_byTime(dt), dt);
            ui->key4->setText("time");
        }
        else if (ui->keyBox->currentIndex() == 2)
        {
            bTree->insert(keyDateAndTime_byHour(dt), dt);
            ui->key4->setText("hour");
        }
        else if (ui->keyBox->currentIndex() == 3)
        {
            bTree->insert(keyDateAndTime_byMinute(dt), dt);
            ui->key4->setText("minutes");
        }
        else if (ui->keyBox->currentIndex() == 4)
        {
            bTree->insert(keyDateAndTime_bySecond(dt), dt);
            ui->key4->setText("seconds");
        }
        else if (ui->keyBox->currentIndex() == 5)
        {
            bTree->insert(keyDateAndTime_byYear(dt), dt);
            ui->key4->setText("year");
        }
        else if (ui->keyBox->currentIndex() == 6)
        {
            bTree->insert(keyDateAndTime_byMonth(dt), dt);
            ui->key4->setText("month");
        }
        else if (ui->keyBox->currentIndex() == 7)
        {
            bTree->insert(keyDateAndTime_byDay(dt), dt);
            ui->key4->setText("day");
        }
        else if (ui->keyBox->currentIndex() == 8)
        {
            bTree->insert(keyDateAndTime_byDateTime(dt), dt);
            ui->key4->setText("dateTime");
        }
    }

    ui->createNewButton->setEnabled(true);
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
    else if (ui->structure3->isChecked())
    {
        if (HashTableChained==nullptr)
        {
            ui->outputAlgo->setText("");
            ui->createNewButton->setEnabled(false);
            return;
        }
        else
        {
            HashTableChained->printHashTableInFile(DateAndTimeToString);
            qDebug()<<"print item in file";
        }
        path = HashTableChained->pathToOutput;
    }
    else if (ui->structure4->isChecked())
    {
        if (bTree==nullptr)
        {
            qDebug() << "nullptr equal";
            ui->outputAlgo->setText("");
            ui->createNewButton->setEnabled(false); //clear button
            return;
        }
        else
        {
            bTree->print(DateAndTimeToString);
            qDebug()<<"print item tree in file";
        }
        path = bTree->pathToOutput;
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
    else if (ui->structure3->isChecked())
    {
        if (HashTableChained==nullptr) return;
        HashTableChained->clear();
        if (HashTableChained) delete HashTableChained;
        HashTableChained = nullptr;
        ui->keyBox->setEnabled(true);
        ui->spinHashTableSize->setEnabled(true);
    }
    else if (ui->structure4->isChecked())
    {
        if (bTree==nullptr) return;
        bTree->clear();
        if (bTree) delete bTree;
        bTree = nullptr;
        if (bTree == nullptr) qDebug() << "btree null equal";
        ui->keyBox->setEnabled(true);
        ui->spinBtreeSize->setEnabled(true);
    }

    showStructure();
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
        else if(ui->keyBox->currentIndex() == 8)
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
        if(HashTableChained==nullptr) return;
        int cellToDelete;

        if (ui->keyBox->currentIndex() == 0)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byDate(key));
        }
        else if(ui->keyBox->currentIndex() == 1)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byTime(key));
        }
        else if(ui->keyBox->currentIndex() == 2)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byHour(key));
        }
        else if(ui->keyBox->currentIndex() == 3)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byMinute(key));
        }
        else if(ui->keyBox->currentIndex() == 4)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_bySecond(key));
        }
        else if(ui->keyBox->currentIndex() == 5)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byYear(key));
        }
        else if(ui->keyBox->currentIndex() == 6)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byMonth(key));
        }
        else if(ui->keyBox->currentIndex() == 7)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byDay(key));
        }
        else if(ui->keyBox->currentIndex() == 8)
        {
            cellToDelete = HashTableChained->hashFunction(keyDateAndTime_byDateTime(key));
        }

        HashTableChained->hashTable[cellToDelete].clear();

    }
    else if (ui->structure4->isChecked())
    {
        //do nothing still
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
        else if(ui->keyBox->currentIndex() == 8)
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
        if(HashTableChained==nullptr) return;

        QVector<DateAndTime> foundValues;

        if (ui->keyBox->currentIndex() == 0)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byDate);
        }
        else if(ui->keyBox->currentIndex() == 1)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byTime);
        }
        else if(ui->keyBox->currentIndex() == 2)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byHour);
        }
        else if(ui->keyBox->currentIndex() == 3)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byMinute);
        }
        else if(ui->keyBox->currentIndex() == 4)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_bySecond);
        }
        else if(ui->keyBox->currentIndex() == 5)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byYear);
        }
        else if(ui->keyBox->currentIndex() == 6)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byMonth);
        }
        else if(ui->keyBox->currentIndex() == 7)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byDay);
        }
        else if(ui->keyBox->currentIndex() == 8)
        {
            foundValues = HashTableChained->findByKey(key, keyDateAndTime_byDateTime);
        }

        QFile file (HashTableChained->pathToOutput);
        if(!file.open(QIODevice::WriteOnly)) //open file
        {
            return;
        }
        QString printedList;
        for (int i=0; i<foundValues.size(); i++)
        {
            printedList += DateAndTimeToString(foundValues[i]) + "\n";
        }
        file.write(printedList.toStdString().c_str());
        file.close();
        //---

        ui->outputAlgo->setText(printedList); //setting visible result

    }
    else if (ui->structure4->isChecked())
    {
        if(bTree==nullptr) return;

        std::vector<DateAndTime> foundValues;

        if (ui->keyBox->currentIndex() == 0)
        {
            foundValues = bTree->find(keyDateAndTime_byDate(key));
        }
        else if(ui->keyBox->currentIndex() == 1)
        {
            foundValues = bTree->find(keyDateAndTime_byTime(key));
        }
        else if(ui->keyBox->currentIndex() == 2)
        {
            foundValues = bTree->find(keyDateAndTime_byHour(key));
        }
        else if(ui->keyBox->currentIndex() == 3)
        {
            foundValues = bTree->find(keyDateAndTime_byMinute(key));
        }
        else if(ui->keyBox->currentIndex() == 4)
        {
            foundValues = bTree->find(keyDateAndTime_bySecond(key));
        }
        else if(ui->keyBox->currentIndex() == 5)
        {
            foundValues = bTree->find(keyDateAndTime_byYear(key));
        }
        else if(ui->keyBox->currentIndex() == 6)
        {
            foundValues = bTree->find(keyDateAndTime_byMonth(key));
        }
        else if(ui->keyBox->currentIndex() == 7)
        {
            foundValues = bTree->find(keyDateAndTime_byDay(key));
        }
        else if(ui->keyBox->currentIndex() == 8)
        {
            foundValues = bTree->find(keyDateAndTime_byDateTime(key));
        }

        QFile file (bTree->pathToOutput);
        if(!file.open(QIODevice::WriteOnly)) //open file
        {
            return;
        }
        QString printedList;
        for (int i=0; i<foundValues.size(); i++)
        {
            printedList += DateAndTimeToString(foundValues[i]) + "\n";
        }
        file.write(printedList.toStdString().c_str());
        file.close();
        //---

        ui->outputAlgo->setText(printedList); //setting visible result

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

class CompBigger_byTime
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (keyDateAndTime_byTime(a) > keyDateAndTime_byTime(b));
    }
};
class CompBigger_byDate
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (keyDateAndTime_byDate(a) > keyDateAndTime_byDate(b));
    }
};
class CompBigger_byDateTime
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (keyDateAndTime_byDateTime(a) > keyDateAndTime_byDateTime(b));
    }
};
class CompBigger_byYear
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (a.dateTime.date().year() > b.dateTime.date().year());
    }
};
class CompBigger_byMonth
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (a.dateTime.date().month() > b.dateTime.date().month());
    }
};
class CompBigger_byDay
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (a.dateTime.date().day() > b.dateTime.date().day());
    }
};
class CompBigger_byHour
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (a.dateTime.time().hour() > b.dateTime.time().hour());
    }
};
class CompBigger_byMinute
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return (a.dateTime.time().minute() > b.dateTime.time().minute());
    }
};
class CompBigger_bySecond
{
public:
    bool operator() (DateAndTime a, DateAndTime b)
    {
        return  (a.seconds > b.seconds);
    }
};
///------------------------------------------------------

void MainWindow::sort()
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
    else if (ui->sortBox->currentIndex() == 1) //start heap sorting, not uses explicit sort functions call
    {
        std::vector<DateAndTime> v;
        Node<DateAndTime> *p = list->head;
        for (int i=0; i<list->size; i++)
        {
            v.push_back(p->Data);
            p = p->next;
        }

        if (ui->keyBox->currentIndex()==0)
        {
           std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byDate> pq;
           for (int i=0; i<v.size(); i++)
           {
               pq.push(v[i]);
           }
           p = list->head;
           for (int i=0; i<list->size; i++)
           {
               p->Data = pq.top();
               pq.pop();
               p = p->next;
           }
        }
        else if (ui->keyBox->currentIndex()==1)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byTime> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

        }
        else if (ui->keyBox->currentIndex()==2)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byHour> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

        }
        else if (ui->keyBox->currentIndex()==3)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byMinute> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

        }
        else if (ui->keyBox->currentIndex()==4)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_bySecond> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

        }
        else if (ui->keyBox->currentIndex()==5)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byYear> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

        }
        else if (ui->keyBox->currentIndex()==6)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byMonth> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

        }
        else if (ui->keyBox->currentIndex()==7)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byDay> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

        }
        else if (ui->keyBox->currentIndex()==8)
        {
            std::priority_queue<DateAndTime, std::vector<DateAndTime>, CompBigger_byDateTime> pq;
            for (int i=0; i<v.size(); i++)
            {
                pq.push(v[i]);
            }
            p = list->head;
            for (int i=0; i<list->size; i++)
            {
                p->Data = pq.top();
                pq.pop();
                p = p->next;
            }

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
            list->sortCount(keyDateAndTime_byDate);
        }
        else if (ui->keyBox->currentIndex()==1)
        {
            list->sortCount(keyDateAndTime_byTime);
        }
        else if (ui->keyBox->currentIndex()==2)
        {
            list->sortCount(keyDateAndTime_byHour);
        }
        else if (ui->keyBox->currentIndex()==3)
        {
            list->sortCount(keyDateAndTime_byMinute);
        }
        else if (ui->keyBox->currentIndex()==4)
        {
            list->sortCount(keyDateAndTime_bySecond);
        }
        else if (ui->keyBox->currentIndex()==5)
        {
            list->sortCount(keyDateAndTime_byYear);
        }
        else if (ui->keyBox->currentIndex()==6)
        {
            list->sortCount(keyDateAndTime_byMonth);
        }
        else if (ui->keyBox->currentIndex()==7)
        {
            list->sortCount(keyDateAndTime_byDay);
        }
        else if (ui->keyBox->currentIndex()==8)
        {
            list->sortCount(keyDateAndTime_byDateTime);
        }
    }
    showStructure();
}

void MainWindow::on_sortButton_clicked()
{
    auto startTime = std::chrono::steady_clock::now();
    sort();
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = endTime - startTime;
    ui->timeExecuteChangable->setText(QString::number(diff.count()));
}


void MainWindow::on_structure3_toggled(bool checked)
{
    if (checked && HashTableChained!=nullptr)
    {
        ui->keyBox->setEnabled(false);
        ui->spinHashTableSize->setEnabled(false);
    }
    else
    {
        ui->keyBox->setEnabled(true);
        ui->spinHashTableSize->setEnabled(true);
    }

    if (checked && HashTableChained==nullptr)
    {
        ui->createNewButton->setEnabled(false);
    }
    else
    {
        ui->createNewButton->setEnabled(true);
    }
}

void MainWindow::on_structure4_toggled(bool checked)
{
    if (checked)
    {
        ui->deleteButton->setEnabled(false);
    }
    else
    {
        ui->deleteButton->setEnabled(true);
    }
}
