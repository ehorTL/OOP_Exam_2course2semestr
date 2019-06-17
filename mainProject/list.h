#ifndef LIST_H
#define LIST_H

#include <QVector>
#include <QString>
#include <QFile>

template <class T>
class Node
{
public:
    Node() {prev = next = nullptr;}
    Node(T &data, int keyCalculated=-1) : Data(data), key(keyCalculated)
    {
        prev = next = nullptr;
    }

    T Data;
    int key; // not obviously used
    Node *prev, *next;
};


template <class T>
class List
{
    Node<T> *head, *tail;
    int size;
public:
    const QString pathToOutput = "C:\\QTProjectsMy\\output.txt";
    List()
    {
        head = tail = nullptr;
        size = 0;
    }

    QVector<Node<T>*> find(T Data, long (*keyIdentityFunction)(T));
    bool deleteNode(Node<T> *NodePtr);
    void pushBack(T Data);
    void printListInFile(QString (*DataToString)(T));
};


template <class T> void List<T>::pushBack(T Data)
{
    Node<T> *newNode = new Node<T>(Data);
    if (size == 0) //if list is empty
    {
        head = newNode;
        head->next = head->prev = head;
        tail = head;

    }
    else if (size == 1) //if tail == head
    {
        tail = newNode;
        head->next = head->prev = tail;
        tail->next = tail->prev = head;

    }
    else
    {
        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
        tail = newNode;
    }
    size++;
}

template <class T> bool List<T>::deleteNode(Node<T> *NodePtr)
{
    if (NodePtr==nullptr) return false;
    //else
    if (size == 1)
    {
        delete NodePtr;
        head = tail = nullptr;
        size = 0;
    }
    else
    {
        NodePtr->prev->next = NodePtr->next;
        NodePtr->next->prev = NodePtr->prev;
        delete NodePtr;
        size--;
    }

    return true;
}

template <class T> QVector<Node<T>*> List<T>::find(T keyData, long (*keyIdentityFunction)(T))
{
    QVector<Node<T>*> findResult;
    //if (size==0) return findResult; //empty vector
    //else
    Node<T> *tmpPtr = head;
    for (int i=0; i<size; i++)
    {
        if (keyIdentityFunction(tmpPtr->Data) == keyIdentityFunction(keyData))
        {
            findResult.push_back(tmpPtr);
        }
        tmpPtr=tmpPtr->next;
    }
    return findResult;
}

template<class T> void List<T>::printListInFile(QString (*DataToString)(T))
{
    QFile file (pathToOutput);
    if(!file.open(QIODevice::WriteOnly)) //open file
    {
        return;
    }
    QString printedList;
    Node<T> *tmpPtr = head;
    for (int i=0; i<size; i++)
    {
        printedList += DataToString(tmpPtr->Data) + "/n";
    }
    file.write(printedList.toStdString().c_str());
}


#endif // LIST_H
