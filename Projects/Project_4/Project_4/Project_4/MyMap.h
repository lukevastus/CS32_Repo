//
//  MyMap.h
//  Project_4
//
//  Created by Runjia Li on 3/8/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//
//  Skeleton for the MyMap class template.  You must implement the first six
//  member functions.

#ifndef MyMap_h
#define MyMap_h
#include <iostream>

template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap();
    ~MyMap();
    void clear(); // Deletes all of the tree's nodes
    int size() const; // Returns the number of nodes
    void associate(const KeyType& key, const ValueType& value);
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    struct Node
    {
        KeyType n_key;
        ValueType n_value;
        Node* left;
        Node* right;
    };
    
    Node* m_root;
    int m_size;
    
    void deleteSubtree(Node* root); // Delete the subtree spanned from root
    Node* newNode(const KeyType& key, const ValueType& value); // Add a new node
};

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::MyMap():m_root(nullptr), m_size(0)
{
    
}

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::~MyMap()
{
    clear();
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear()
{
    deleteSubtree(m_root);
    m_root = nullptr;
}

template<typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::size() const
{
    return m_size;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    if (m_root == nullptr)
        m_root = newNode(key, value);
    
    else
    {
        Node* curNode = m_root;
        while (true)
        {
            if (key == curNode->n_key)
            {
                curNode->n_value = value;
                return;
            }
            
            if (key < curNode->n_key)
            {
                if (curNode->left != nullptr)
                    curNode = curNode->left;
                else
                {
                    curNode->left = newNode(key, value);
                    return;
                }
            }
            
            else
            {
                if (curNode->right != nullptr)
                    curNode = curNode->right;
                else
                {
                    curNode->right = newNode(key, value);
                    return;
                }
            }
        }
    }
}

template<typename KeyType, typename ValueType>
const ValueType* MyMap<KeyType, ValueType>::find(const KeyType& key) const
{
    if (m_root == nullptr)
        return nullptr;
    
    Node* curNode = m_root;
    while (curNode->n_key != key)
    {
        if (key < curNode->n_key)
            curNode = curNode->left;
            
        else if (key > curNode->n_key)
            curNode = curNode->right;
        
        if (curNode == nullptr)
            return nullptr;
    }
    
    ValueType* valuePtr = &(curNode->n_value);
    return valuePtr;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::deleteSubtree(Node* root)
{
    if (root == nullptr)
        return;
    deleteSubtree(root->left);
    deleteSubtree(root->right);
    KeyType key = root->n_key;
    delete root;
    m_size--;
}

template<typename KeyType, typename ValueType>
typename MyMap<KeyType, ValueType>::Node* MyMap<KeyType, ValueType>::newNode(const KeyType& key, const ValueType& value)
{
    Node* newNode = new Node;
    newNode->n_key = key;
    newNode->n_value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    m_size++;
    return newNode;
}

#endif /* MyMap_h */