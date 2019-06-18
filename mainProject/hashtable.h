#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<QVector>
#include<QFile>

template <class T>
class HashTable
{
    const int SIZE_DEFAULT = 20;
    int hashFunction(long long key);
public:
    const QString pathToOutput = "C:\\QTProjectsMy\\hashTable.txt";
    HashTable(int tableSize)
    {
        if (tableSize<=0)
        {
            sizeTable = SIZE_DEFAULT;
        }
        else
        {
            sizeTable = tableSize;
        }
        hashTable.resize(sizeTable);
    }

    QVector<QVector<T>> hashTable;
    int sizeTable;

    void addItem(T data, long long (*dataKey)(T));
    QVector<T> findByKey(T dataKeySample, long long (*dataKey)(T));
    void deleteByKey(T dataKeySample, long long (*dataKey)(T));
    void printHashTableInFile(QString (*DataToString)(T));
    void clear();
};

template<class T> int HashTable<T>::hashFunction(long long key)
{
    return ((key*31+7)%hashTable.size());
}

template<class T> void HashTable<T>::addItem(T data, long long (*dataKey)(T))
{
    int cell = hashFunction(dataKey(data));
    hashTable[cell%hashTable.size()].push_back(data);
}

template<class T> QVector<T> HashTable<T>::findByKey(T dataKeySample, long long (*dataKey)(T))
{
    int cell = hashFunction(dataKey(dataKeySample));
    QVector<T> result;
    for (int i=0; i<hashTable[cell].size(); i++)
    {
        result.push_back(hashTable[cell][i]);
    }

    return result;
}

template<class T> void HashTable<T>::deleteByKey(T dataKeySample, long long (*dataKey)(T))
{
    int cell = hashFunction(dataKey(dataKeySample));
    hashTable[cell].clear();
}

template<class T> void HashTable<T>::printHashTableInFile(QString (*DataToString)(T))
{
    QFile file (pathToOutput);
    if(!file.open(QIODevice::WriteOnly)) //open file
    {
        return;
    }
    QString result;
    for (int i=0; i<hashTable.size(); i++)
    {
        if (hashTable[i].size()>0)
        {
            result += QString::number(i) + ":  ";
        }
        for (int j=0; j<hashTable[i].size(); j++)
        {
            result += DataToString(hashTable[i][j]) + " --> ";
            if (j==hashTable[i].size()-1){result += "\n";} //last iteration
        }
    }
    file.write(result.toStdString().c_str());
    file.close();
}

template <class T> void HashTable<T>::clear()
{
    if (!hashTable.isEmpty())
    {
        hashTable.clear();
    }
    sizeTable = 0;
}

#endif // HASHTABLE_H
