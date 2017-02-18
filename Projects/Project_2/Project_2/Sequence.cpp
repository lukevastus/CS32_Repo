//
//  Sequence.cpp
//  Project_2
//
//  Created by Runjia Li on 1/25/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include "Sequence.h"
using namespace std;

Sequence::Sequence(): m_size(0)
{
    head = new Node;
    head->prev = head;
    head->next = head;
}

Sequence::Sequence(const Sequence& other)
{
    head = new Node;
    head->prev = head;
    head->next = head;
    m_size = 0;
    
    for (int i = 0; i < other.m_size; i++)
    {
        ItemType temp;
        other.get(i, temp);
        insert(i, temp);
    }
}

Sequence& Sequence::operator=(const Sequence &other)
{
    if (this == &other)
        return *this;
    
    Sequence temp(other);
    swap(temp);
    return *this;
}

Sequence::~Sequence()
{
    Node* curNode = head->next;
    while (curNode != head)
    {
        Node* temp = curNode->next;
        delete curNode;
        curNode = temp;
    }
    delete head;
}

bool Sequence::empty() const
{
    return (m_size == 0);
}

int Sequence::size() const
{
    return m_size;
}

bool Sequence::insert(int pos, const ItemType &value)
{
    if (pos < 0 || pos > m_size)
        return false;
    
    Node* nextNode = head->next;
    
    if (pos >= m_size / 2)
    {
        nextNode = head;
        for (int i = 0; i < (m_size - pos); i++)
            nextNode = nextNode->prev;
    }
    
    else
    {
        for (int i = 0; i < pos; i++)
            nextNode = nextNode->next;
    }
    
    Node* newNode = new Node;
    newNode->value = value;
    
    Node* prevNode = nextNode->prev;
    prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = nextNode;
    nextNode->prev = newNode;
    
    m_size++;
    return true;
}

int Sequence::insert(const ItemType &value)
{
    int pos = 0;
    Node* nextNode = head->next;
    
    while (nextNode != head && nextNode->value < value)
    {
        nextNode = nextNode->next;
        pos++;
    }
    
    insert(pos, value);
    return pos;
}

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    Node* curNode = head->next;
    
    if (pos >= m_size / 2)
    {
        curNode = head->prev;
        for (int i = 0; i < (m_size - pos - 1); i++)
            curNode = curNode->prev;
    }
    
    else
    {
        for (int i = 0; i < pos; i++)
            curNode = curNode->next;
    }
    
    Node* prevNode = curNode->prev;
    Node* nextNode = curNode->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete curNode;
    
    m_size--;
    return true;
}

int Sequence::remove(const ItemType &value)
{
    int counter = 0;
    int pos = 0;
    Node* curNode = head->next;
    
    while (curNode != head)
    {
        Node* nextNode = curNode->next;
        
        if (curNode->value == value)
        {
            erase(pos);
            counter++;
            pos--;
        }
        
        curNode = nextNode;
        pos++;
    }
    
    return counter;
}

bool Sequence::get(int pos, ItemType &value) const
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    Node* curNode = head->next;
    
    if (pos >= m_size / 2)
    {
        curNode = head->prev;
        for (int i = 0; i < (m_size - pos - 1); i++)
            curNode = curNode->prev;
    }
    
    else
    {
        for (int i = 0; i < pos; i++)
            curNode = curNode->next;
    }
    
    value = curNode->value;
    return true;
}

bool Sequence::set(int pos, const ItemType &value)
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    Node* curNode = head->next;
    
    if (pos >= m_size / 2)
    {
        curNode = head->prev;
        for (int i = 0; i < (m_size - pos - 1); i++)
            curNode = curNode->prev;
    }
    
    else
    {
        for (int i = 0; i < pos; i++)
            curNode = curNode->next;
    }
    
    curNode->value = value;
    return true;
}

int Sequence::find(const ItemType &value) const
{
    int p = -1;
    int counter = 0;
    Node* curNode = head->next;
    
    while (curNode != head)
    {
        if (curNode->value == value)
        {
            p = counter;
            break;
        }
        curNode = curNode->next;
        counter++;
    }
    
    return p;
}

void Sequence::swap(Sequence &other)
{
    
    Node* otherHead = other.head;
    other.head = head;
    head = otherHead;
    
    int otherSize = other.size();
    other.m_size = m_size;
    m_size = otherSize;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq2.size() > seq1.size() || seq2.empty())
    {
        return -1;
    }
    
    ItemType first;
    seq2.get(0, first);
    
    for (int i = seq2.find(first); i <= seq1.size() - seq2.size(); i++)
    {
        bool found = true;
        for (int j = 0; j < seq2.size(); j++)
        {
            ItemType item1, item2;
            seq1.get(i + j, item1);
            seq2.get(j, item2);
            if (item1 != item2)
            {
                found = false;
                break;
            }
        }
        
        if (found)
            return i;
    }
    
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence newSeq = seq1;
    
    for (int i = 0; i < seq2.size(); i++)
    {
        ItemType temp;
        seq2.get(i, temp);
        
        if ((2 * i + 1) >= newSeq.size())
        {
            newSeq.insert(newSeq.size(), temp);
        }
        
        else
            newSeq.insert(2 * i + 1, temp);
    }
    
    result = newSeq;
}







