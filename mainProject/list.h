#ifndef LIST_H
#define LIST_H

#include<QVector>

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
public:
    List()
    {
        head = tail = nullptr;
    }

    QVector<Node<T>*> find(T Data, long (*keyIdentityFunction)(T));
    bool deleteNode(Node<T> *NodePtr);
    void pushBack(T Data);
};

#endif // LIST_H
