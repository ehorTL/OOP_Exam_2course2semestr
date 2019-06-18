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

    void merge(QVector<T> &arr, int l, int m, int r, bool (*firstGreaterThan)(T, T));
    void mergeSort(QVector<T> &arr, int l, int r, bool (*firstGreaterThan)(T, T));

    void sortInsert(bool (*firstGreaterThan)(T, T));
    void sortMerge(bool (*firstGreaterThan)(T, T));
    //void sortHeap(std::priority_queue<T> &pq);
    void sortCount(long long(*DataKey)(T));
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


template<class T> void List<T>::merge(QVector<T> &arr, int l, int m, int r, bool (*firstGreaterThan)(T, T))
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    QVector<T> L(n1), R(n2);
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (firstGreaterThan(R[j], L[i])) //(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template<class T> void List<T>:: mergeSort(QVector<T> &arr, int l, int r, bool (*firstGreaterThan)(T, T))
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m, firstGreaterThan);
        mergeSort(arr, m+1, r, firstGreaterThan);
        merge(arr, l, m, r, firstGreaterThan);
    }
}

template <class T> void List<T>::sortMerge(bool (*firstGreaterThan)(T, T))
{
    if (size==0 || size==1) return;
    //else
    Node<T> *p = head;
    QVector<T> v;
    for (int i=0; i<size; i++)
    {
        v.push_back(p->Data);
        p = p->next;
    }

    mergeSort(v, 0, size - 1, firstGreaterThan);

    p = head;
    for (int i=0; i<size; i++)
    {
        p->Data = v[i];
        p = p->next;
    }
}


template <class T> void List<T>::sortCount(long long (*DataKey)(T))
{
    if (size==0 || size==1) return;
    //else
    const int MAX_VECTOR_SIZE = 2000;
    long long range = 1;
    Node<T> *p = head;
    int min = DataKey(head->Data);
    int max = 1;
    for (int i=0; i<size; i++)
    {
        if (DataKey(p->Data) > max)
        {
             max = DataKey(p->Data);
        }
        if ((DataKey(p->Data) < min))
        {
            min = DataKey(p->Data);
        }
        p = p->next;
    }
    range = max - min + 1;
    if (range > MAX_VECTOR_SIZE || range==0) return; // count sort is no effective and can cause to errors or keys are equal

    QVector<QVector<T>> stableSortVector;
    stableSortVector.resize(range);

    Node<T>* ptr = head;
    for (int i=0; i<size; i++)
    {
        stableSortVector[DataKey(ptr->Data) - min].push_back(ptr->Data);
        ptr = ptr->next;
    }

    Node<T> *pt = head;
    for (int i=0; i<stableSortVector.size(); i++) //size == range
    {
        for (int j=0; j<stableSortVector[i].size(); j++)
        {
            pt->Data = stableSortVector[i][j];
            qDebug()<< DataKey(pt->Data);
            pt = pt->next;
        }
    }
}

#endif // LIST_H
