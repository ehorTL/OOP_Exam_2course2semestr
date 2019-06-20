#ifndef MAIN_H
#define MAIN_H
#include <gtest/gtest.h>
#include <iostream>
#include <QApplication>

#include "bplustree.h" 
#include "dateandtime.h"
#include "hashtable.h"
//#include "rbtree.h"
#include "list.h"

TEST(TestList, testConstructor)
{
    List<int> *l = new List<int>;
    EXPECT_EQ(l->size, 0);
    EXPECT_TRUE(l->head == nullptr);
    EXPECT_TRUE(l->tail == nullptr);
    delete l;
}


TEST(TestList, testPush)
{
    List<int> *l = new List<int>;
    l->pushBack(1);
    EXPECT_EQ(l->size, 1);
    l->pushBack(2);
    EXPECT_EQ(l->size, 2);
    l->pushBack(3);
    EXPECT_EQ(l->size, 3);
    delete l;
}

TEST(TestList, testClear)
{
    List<int> *l = new List<int>;
    l->pushBack(1);
    l->pushBack(2);
    l->pushBack(3);
    l->clear();

    EXPECT_EQ(l->size, 0);
    EXPECT_TRUE(l->head == nullptr);
    EXPECT_TRUE(l->tail == nullptr);
    delete l;
}


long long keyInt(int a) {return a;}
TEST(TestList, testFind)
{
    List<int> *l = new List<int>;
    l->pushBack(1);
    l->pushBack(2);
    l->pushBack(3);

    EXPECT_EQ((l->find(1, keyInt))->Data, 1);
    EXPECT_EQ((l->find(2, keyInt))->Data, 2);
    EXPECT_EQ((l->find(3, keyInt))->Data, 3);
    l->clear();
    delete l;
}
/*
TEST(TestList, testDelete)
{
    List<int> *l = new List<int>;
    l->pushBack(1);
    l->pushBack(2);
    l->pushBack(3);
    l->deleteNode(l->find(1, keyInt));
    EXPECT_TRUE(l->find(1, keyInt) == nullptr);
    l->deleteNode(l->find(2, keyInt));
    EXPECT_TRUE(l->find(2, keyInt) == nullptr);
    l->deleteNode(l->find(3, keyInt));
    EXPECT_TRUE(l->find(3, keyInt) == nullptr);

    l->clear();
    delete l;
}
*/


bool greaterThanInt(int a, int b) {return a>b;}
TEST(TestList, testSorting)
{
    List<int> *l = new List<int>;
    l->pushBack(3);
    l->pushBack(1);
    l->pushBack(2);
    l->pushBack(5);
    l->pushBack(4);
    l->sortInsert(greaterThanInt);
    Node<int> *p = l->head;
    EXPECT_EQ(p->Data, 1);
    p = p->next;
    EXPECT_EQ(p->Data, 2);
    p = p->next;
    EXPECT_EQ(p->Data, 3);
    p = p->next;
    EXPECT_EQ(p->Data, 4);
    p = p->next;
    EXPECT_EQ(p->Data, 5);
    l->clear();

    l->pushBack(3);
    l->pushBack(1);
    l->pushBack(2);
    l->pushBack(5);
    l->pushBack(4);
    l->sortCount(keyInt);
    p = l->head;
    EXPECT_EQ(p->Data, 1);
    p = p->next;
    EXPECT_EQ(p->Data, 2);
    p = p->next;
    EXPECT_EQ(p->Data, 3);
    p = p->next;
    EXPECT_EQ(p->Data, 4);
    p = p->next;
    EXPECT_EQ(p->Data, 5);
    l->clear();

    l->pushBack(3);
    l->pushBack(1);
    l->pushBack(2);
    l->pushBack(5);
    l->pushBack(4);
    l->sortMerge(greaterThanInt);
    p = l->head;
    EXPECT_EQ(p->Data, 1);
    p = p->next;
    EXPECT_EQ(p->Data, 2);
    p = p->next;
    EXPECT_EQ(p->Data, 3);
    p = p->next;
    EXPECT_EQ(p->Data, 4);
    p = p->next;
    EXPECT_EQ(p->Data, 5);
    l->clear();

    delete l;
}


/**
* HashTable tests with additional functions needed.
*/

TEST(TestHashTable, constructor)
{
    const int TABLE_SIZE = 7;
    HashTable<int> *hashTable = new HashTable<int>(TABLE_SIZE);
    EXPECT_EQ(hashTable->sizeTable, 7);
    delete hashTable;
}

long long keyData(int a) {return a;}
TEST(TestHashTable, hashFuncitonANDaddItem)
{
    const int TABLE_SIZE = 7;
    HashTable<int> *hashTable = new HashTable<int>(TABLE_SIZE);

    hashTable->addItem(1, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 1)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(1))][0], 1);
    }
    hashTable->addItem(1, keyData);
    hashTable->addItem(2, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 2)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(2))][0], 2);
    }
    hashTable->addItem(3, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 3)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(3))][0], 3);
    }
    hashTable->addItem(4, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 4)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(4))][0], 4);
    }
    hashTable->addItem(5, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 5)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(5))][0], 5);
    }
    hashTable->addItem(6, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 6)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(6))][0], 6);
    }
    hashTable->addItem(7, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 7)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(7))][0], 7);
    }
    hashTable->addItem(8, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 8)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(8))][0], 8);
    }
    hashTable->addItem(9, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 9)
    {
        EXPECT_EQ(hashTable->hashTable[(hashTable->hashFunction(9))][0], 9);
    }

    delete hashTable;
}

TEST(TestHashTable, findByKey)
{
    const int TABLE_SIZE = 7;
    HashTable<int> *hashTable = new HashTable<int>(TABLE_SIZE);

    hashTable->addItem(1, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 1)
    {
        EXPECT_EQ((hashTable->findByKey(1, keyData))[0], 1);
    }
    hashTable->addItem(1, keyData);
    hashTable->addItem(2, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 2)
    {
        EXPECT_EQ((hashTable->findByKey(2, keyData))[0], 2);
    }
    hashTable->addItem(3, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 3)
    {
        EXPECT_EQ((hashTable->findByKey(3, keyData))[0], 3);
    }
    hashTable->addItem(4, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 4)
    {
        EXPECT_EQ((hashTable->findByKey(4, keyData))[0], 4);
    }
    hashTable->addItem(5, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 5)
    {
        EXPECT_EQ((hashTable->findByKey(5, keyData))[0], 5);
    }
    hashTable->addItem(6, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 6)
    {
        EXPECT_EQ((hashTable->findByKey(6, keyData))[0], 6);
    }
    hashTable->addItem(7, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 7)
    {
        EXPECT_EQ((hashTable->findByKey(7, keyData))[0], 7);
    }
    hashTable->addItem(8, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 8)
    {
        EXPECT_EQ((hashTable->findByKey(8, keyData))[0], 8);
    }
    hashTable->addItem(9, keyData);
    if (hashTable->hashTable[(hashTable->hashFunction(1))].size() == 9)
    {
        EXPECT_EQ((hashTable->findByKey(9, keyData))[0], 9);
    }

    delete hashTable;
}

TEST(TestHashTable, deleteByKey)
{
    const int TABLE_SIZE = 7;
    HashTable<int> *hashTable = new HashTable<int>(TABLE_SIZE);
    hashTable->addItem(1, keyData);
    hashTable->addItem(1, keyData);
    hashTable->addItem(2, keyData);
    hashTable->addItem(3, keyData);
    hashTable->addItem(4, keyData);
    hashTable->addItem(5, keyData);
    hashTable->addItem(6, keyData);
    hashTable->addItem(7, keyData);
    hashTable->addItem(8, keyData);
    hashTable->addItem(9, keyData);

    for (int i=1; i<=TABLE_SIZE; i++)
    {
        hashTable->deleteByKey(i, keyData);
        EXPECT_EQ(hashTable->findByKey(i, keyData).size(), 0);
    }

    delete hashTable;
}

TEST(TestHashTable, clear)
{
    const int TABLE_SIZE = 7;
    HashTable<int> *hashTable = new HashTable<int>(TABLE_SIZE);
    hashTable->clear();
    EXPECT_EQ(hashTable->sizeTable, 0);
    delete hashTable;
}

#endif // MAIN_H
