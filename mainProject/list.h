#ifndef LIST_H
#define LIST_H

#include <QVector>
#include <QString>
#include <QFile>
#include<QDebug>
#include<algorithm>
#include<queue>
#include<vector>

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
    //Node<T> *head, *tail;
    //int size;
public:
    const QString pathToOutput = "C:\\QTProjectsMy\\list.txt";

    Node<T> *head, *tail; //made public in order not to create get- methods
    int size; //made public

    List()
    {
        head = tail = nullptr;
        size = 0;
    }

    Node<T>* find(T Data, long long(*keyIdentityFunction)(T));
    QVector<Node<T>*> findAll(T Data, long long(*keyIdentityFunction)(T)); //only for reading
    bool deleteNode(Node<T> *NodePtr);
    void pushBack(T Data);
    void printListInFile(QString (*DataToString)(T));
    void clear();

    void sortInsert(bool (*firstGreaterThan)(T, T));
    void sortMerge(bool (*firstGreaterThan)(T, T));
    //void sortHeap(std::priority_queue<T> &pq);
    void sortCount(bool (*firstGreaterThan)(T, T));
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
        if (NodePtr == head)
        {
            head = head->next;
        }
        else if (NodePtr == tail)
        {
            tail = tail->prev;
        }
        delete NodePtr;
        size--;
    }

    return true;
}

template <class T> Node<T>* List<T>::find(T keyData, long long(*keyIdentityFunction)(T))
{
    Node<T> *tmpPtr = head;
    for (int i=0; i<size; i++)
    {
        if (keyIdentityFunction(tmpPtr->Data) == keyIdentityFunction(keyData))
        {
            return tmpPtr;
        }
        tmpPtr=tmpPtr->next;
    }

    return nullptr; //nothing found
}


template <class T> QVector<Node<T>*> List<T>::findAll(T keyData, long long(*keyIdentityFunction)(T))
{
    QVector<Node<T>*> resultVector;
    Node<T> *tmpPtr = head;
    for (int i=0; i<size; i++)
    {
        if (keyIdentityFunction(tmpPtr->Data) == keyIdentityFunction(keyData))
        {
            resultVector.push_back(tmpPtr);
        }
        tmpPtr=tmpPtr->next;
    }

    for (int i=0; i<resultVector.size(); i++)
    {
        qDebug()<< QString::number(i) << " ";
    }
    return resultVector;
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
        printedList += DataToString(tmpPtr->Data) + "\n";
        tmpPtr = tmpPtr->next;
    }
    file.write(printedList.toStdString().c_str());
    file.close();
}


template <class T> void List<T>::clear()
{
    Node<T> *ndPtr = head;
    Node<T> *ndPtrNext = head->next;
    for (int i=0; i<size; i++)
    {
        ndPtrNext = ndPtr->next;
        delete ndPtr;
        ndPtr = ndPtrNext;
    }
    size = 0;
    head = tail = nullptr;
}

template <class T> void List<T>::sortInsert(bool (*firstGreaterThan)(T, T))
{
    if (size==0 || size==1) return; //already sorted
    //else
    Node<T> *curLastPos = head->next;
    Node<T> *cur = head->next;
    Node<T> *prev = head;
    for (int i=1; i<size; i++)
    {
        cur = curLastPos;
        prev = cur->prev;
        for (int j=i; j>0 && firstGreaterThan(prev->Data, cur->Data); j--)
        {
            std::swap(prev->Data, cur->Data);
            cur = prev;
            prev = prev->prev;
        }
        curLastPos = curLastPos->next;
    }

}

//template <class T> void List<T>:: sortHeap(bool (*firstGreaterThan)(T, T))
/*template <class T> void List<T>:: sortHeap(std::priority_queue<T> &pq)
{
    if (size==0 || size==1) return;
    if (pq.size() != size) return;
    //else
    Node<T> *p = head;
    for (int i=0; i<size; i++)
    {
        p->Data = pq.top();
        pq.pop();
        p = p->next;
    }
}
*/

template <class T> void List<T>::sortMerge(bool (*firstGreaterThan)(T, T))
{
    if (size==0 || size==1) return;
}



template <class T> void List<T>::sortCount(bool (*firstGreaterThan)(T, T))
{
    if (size==0 || size==1) return;
}

#endif // LIST_H
