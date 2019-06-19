#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <utility>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <string>
#include<fstream>

#include<QString>
#include<QFile>

namespace ms {

#define MINIMAL_VALUE_OF_M 3
#define M_PARAMETER_SHOULD_BE_GREATER "Parameter that defines maximum number of children should be greater"

    template <typename Key, class Value/*,std::uint16_t M*/>
    class BTree {
    protected:
        struct Node;
        typedef std::vector<std::pair<BTree::Node*, std::pair<Key, Value>>> NodeContentType;
        //friend class BTreeTest;
    public:
        const QString pathToOutput = "C:\\QTProjectsMy\\BPlusTree.txt";
        int M = 3;
        BTree(int m);
        ~BTree();
        BTree(BTree && tree) = delete;
        BTree(const BTree & tree) = delete;
        BTree & operator = (BTree && tree) = delete;
        BTree & operator = (const BTree & tree) = delete;

        bool insert(const Key & key, const Value & value);
        std::pair<bool, Value> findFirst(const Key & key) const;
        std::pair<bool, Value> find_first(const Key & key) const {
            return findFirst(key);
        }
        std::vector<Value> find(const Key & key) const;
        bool erase(const Key & key);
        void print(QString (*dataToString)(Value)) const;
        void clear() {if (rootNode) delete this->rootNode; rootNode = nullptr;}
    protected:
        Node* rootNode;
        void find_from(const Node * node, const Key & key, std::vector<Value> & insertTo, typename NodeContentType::iterator from) const;
        std::pair<bool, Value> find_first_from(const Node * node, const Key & key) const;
        bool insert_from(Node * node, Node * parent, typename NodeContentType::iterator parentIt, const Key & key, const Value & value);
        auto split(Node * nodeToSplit, Node * parentNode, typename NodeContentType::iterator median, typename NodeContentType::iterator parent);
        void print_from(Node const * node, std::ofstream &fout,QString (*dataToString)(Value)) const;
    };



    //mark Tree implementation

    template <typename Key, class Value>
    std::vector<Value> BTree<Key, Value>::find(const Key & key) const {
        auto vec = std::vector<Value>();
        if (rootNode != nullptr) {
            find_from(rootNode, key, vec, rootNode->content.begin());
        }
        return vec;
    }

    template <typename Key, class Value>
    void BTree<Key, Value>::find_from(const Node * node, const Key & key, std::vector<Value> & insertTo, typename NodeContentType::iterator from) const {
        auto res = std::find_if(node->content.begin() + (from - node->content.begin()), node->content.end(), [key](auto pair) { return pair.second.first >= key; });
        if (res == node->content.end() && node->rightSubtree != nullptr) {
            this->find_from(node->rightSubtree, key, insertTo, node->rightSubtree->content.begin());
        }
        else if (res != node->content.end()) {
            if (res->second.first == key) {
                insertTo.insert(insertTo.begin(), res->second.second);
                find_from(node, key, insertTo, from + 1);
            }
            if (res->first != nullptr) {
                find_from(res->first, key, insertTo, res->first->content.begin());
            }
            if ((res + 1) != node->content.end()) {
                if ((res + 1)->first != nullptr) {
                    find_from((res + 1)->first, key, insertTo, (res + 1)->first->content.begin());
                }
            }
            else if (node->rightSubtree != nullptr) {
                find_from(node->rightSubtree, key, insertTo, node->rightSubtree->content.begin());
            }
        }
        return;
    }

    template <typename Key, class Value>
    BTree<Key, Value>::BTree(int m) {
        M = m;
        //static_assert(M >= MINIMAL_VALUE_OF_M, M_PARAMETER_SHOULD_BE_GREATER);
        this->rootNode = nullptr;
    }

    template <typename Key, class Value>
    void BTree<Key, Value>::print(QString (*dataToString)(Value)) const
    {
        std::string filename = pathToOutput.toStdString();
        std::ofstream fout(filename); //openfile

        if (this->rootNode != nullptr) {
            print_from(this->rootNode, fout, dataToString);
        }
        fout.close(); //close file
    }

    template <typename Key, class Value>
    void BTree<Key, Value>::print_from(Node const * node, std::ofstream &fout, QString(* dataToString)(Value)) const {
        for (auto pair : node->content) {
            if (pair.first != nullptr) {
                print_from(pair.first, fout, dataToString);
            }
            fout << "|key: " << std::to_string(pair.second.first) << " -> value: " << (dataToString(pair.second.second)).toStdString() << "|\n";
        }
        if (node->rightSubtree != nullptr) {
            print_from(node->rightSubtree, fout,dataToString);
        }
    }

    template <typename Key, class Value>
    bool  BTree<Key, Value>::insert(const Key &key, const Value &value) {
        if (this->rootNode == nullptr) {
            this->rootNode = new Node(std::pair<Key, Value>(key, value), M);
            return true;
        }
        else {
            return insert_from(this->rootNode, nullptr, this->rootNode->content.end(), key, value);
        }
    }

    template <typename Key, class Value>
    bool BTree<Key, Value>::insert_from(Node * node, Node * parent, typename NodeContentType::iterator parentIt, const Key & key, const Value & value) {
        auto pairToInsert = std::pair<Node *, std::pair<Key, Value>>(nullptr, std::make_pair(key, value));
        if (node->isLeaf) {
            auto hasSpaceBeforeInsert = node->has_empty_space();
            auto placeToInsert = std::upper_bound(node->content.begin(), node->content.end(), pairToInsert, [](const auto & first, const auto & second) { return first.second.first < second.second.first; });
            node->content.insert(placeToInsert, pairToInsert);
            if (!node->has_empty_space() && !hasSpaceBeforeInsert) {
                std::uint16_t medianIndex = node->content.size() / 2;
                this->split(node, parent, node->content.begin() + medianIndex, parentIt);
            }
            return true;
        }
        else {
            if (!node->has_empty_space()) {
                std::uint16_t medianIndex = node->content.size() / 2;
                bool isBigger = key > node->content[medianIndex].second.first;
                auto subtrees = this->split(node, parent, node->content.begin() + medianIndex, parentIt);
                if (isBigger) {
                    return insert_from(subtrees.second, parent, parentIt + 1, key, value);
                }
                else {
                    return insert_from(subtrees.first, parent, parentIt - 1, key, value);
                }
            }
            auto placeToInsert = std::upper_bound(node->content.begin(), node->content.end(), pairToInsert, [](const auto & first, const auto & second) { return first.second.first < second.second.first; });
            if (placeToInsert == node->content.end()) {
                return insert_from(node->rightSubtree, node, node->content.end() - 1, key, value);
            }
            else {
                return insert_from(placeToInsert->first, node, placeToInsert, key, value);
            }
        }
    }

    template <typename Key, class Value>
    std::pair<bool, Value>  BTree<Key, Value>::findFirst(const Key &key) const {
        return find_first_from(this->rootNode, key);
    }

    template <typename Key, class Value>
    std::pair<bool, Value> BTree<Key, Value>::find_first_from(const Node * node, const Key & key) const {
        if (node != nullptr && node->content.size() > 0) {
            auto element = std::find_if(node->content.begin(), node->content.end(), [key](auto el) { return el.second.first >= key; });
            if (element != node->content.end()) {
                if (element->second.first == key) {
                    return std::pair<bool, Value>(true, element->second.second);
                }
                else {
                    return find_first_from(element->first, key);
                }
            }
            else {
                return find_first_from(node->rightSubtree, key);
            }
        }
        return std::pair<bool, Value>(false, Value());
    }

    template <typename Key, class Value>
    BTree<Key, Value>::~BTree() {
        delete this->rootNode;
    }

    template <typename Key, class Value>
    auto BTree<Key, Value>::split(Node * nodeToSplit, Node * parentNode, typename NodeContentType::iterator median, typename NodeContentType::iterator parent) {
        if (parentNode != nullptr) {
            if (median->second.first >= parent->second.first) {
                auto pairToReturn = std::pair<Node*, Node*>();
                if (median != nodeToSplit->content.begin()) {
                    auto medianLeftSubtree = new Node(M);
                    medianLeftSubtree->content.insert(medianLeftSubtree->content.begin(), nodeToSplit->content.begin(), median);
                    medianLeftSubtree->rightSubtree = median->first;
                    median->first = medianLeftSubtree;
                    pairToReturn.first = medianLeftSubtree;
                }
                else {
                    median->first = nullptr;
                }
                pairToReturn.second = nodeToSplit;
                parentNode->content.insert(parent + 1, median, median + 1);
                nodeToSplit->content.erase(nodeToSplit->content.begin(), median + 1);
                return pairToReturn;
            }
            else {
                auto pairToReturn = std::pair<Node*, Node*>();
                if (median + 1 != nodeToSplit->content.end()) {
                    auto newLeftNodeOfParent = new Node(M);
                    newLeftNodeOfParent->content.insert(newLeftNodeOfParent->content.begin(), median + 1, nodeToSplit->content.end());
                    newLeftNodeOfParent->rightSubtree = nodeToSplit->rightSubtree;
                    nodeToSplit->rightSubtree = nullptr;
                    parent->first = newLeftNodeOfParent;
                    pairToReturn.second = newLeftNodeOfParent;
                }
                else if (nodeToSplit->rightSubtree != nullptr) {
                    parent->first = nodeToSplit->rightSubtree;
                    nodeToSplit->rightSubtree = nullptr;
                    pairToReturn.second = parent->first;
                }
                else {
                    parent->first = nullptr;
                    pairToReturn.second = nullptr;
                    nodeToSplit->rightSubtree = nullptr;
                }
                parentNode->content.insert(parent, std::make_pair(static_cast<Node*>(nodeToSplit), median->second));
                nodeToSplit->rightSubtree = median->first;
                nodeToSplit->content.erase(median, nodeToSplit->content.end());
                pairToReturn.first = nodeToSplit;
                return pairToReturn;
            }
        }
        else {
            auto newRootNode = new Node(std::pair<Key, Value>(median->second), M);
            if (median + 1 != nodeToSplit->content.end()) {
                auto newRightSubtree = new Node(M);
                newRightSubtree->content.insert(newRightSubtree->content.begin(), median + 1, nodeToSplit->content.end());
                newRightSubtree->rightSubtree = nodeToSplit->rightSubtree;
                newRootNode->rightSubtree = newRightSubtree;
            }
            else {
                newRootNode->rightSubtree = nodeToSplit->rightSubtree;
            }
            newRootNode->isLeaf = false;
            newRootNode->content.begin()->first = this->rootNode;
            this->rootNode->rightSubtree = median->first;
            this->rootNode = newRootNode;
            nodeToSplit->content.erase(median, nodeToSplit->content.end());
            return std::pair<Node*, Node*>(newRootNode->content[0].first, newRootNode->rightSubtree);
        }
    }

    //mark Node implementation
    template <typename Key, class Value>
    struct BTree<Key, Value>::Node {
    public:
        int M = 3;
        Node(int m);
        Node(const std::pair<Key, Value> & initialPair, int m);
        Node(std::pair<Key, Value> && initialPair, int m);
        ~Node();

        Node(const Node & node) = delete;
        Node(Node && node) = delete;

        Node & operator = (const Node & node) = delete;
        Node & operator = (Node && node) = delete;

        bool has_empty_space() const;

        std::vector <std::pair<Node *, std::pair<Key, Value>>> content;
        Node * rightSubtree;
        bool isLeaf;
    };

    template <typename Key, class Value>
    BTree<Key, Value>::Node::Node(int m) {
        M = m;
        rightSubtree = nullptr;
        isLeaf = true;
    }

    template <typename Key, class Value>
    BTree<Key, Value>::Node::Node(const std::pair<Key, Value> & initialPair, int m) : Node(std::pair<Key, Value>(initialPair)) {M = m;}

    template <typename Key, class Value>
    BTree<Key, Value>::Node::Node(std::pair<Key, Value> && initialPair, int m) : Node(m) {
        content.push_back(std::pair<Node *, std::pair<Key, Value>>(nullptr, std::move(initialPair)));
    }

    template <typename Key, class Value>
    BTree<Key, Value>::Node::~Node() {
        delete rightSubtree;
        for (auto & keyChild : content) {
            delete keyChild.first;
        }
    }

    template <typename Key, class Value>
    bool BTree<Key, Value>::Node::has_empty_space() const {
        return content.size() < (M - 1);
    }
}


#endif // BPLUSTREE_H
