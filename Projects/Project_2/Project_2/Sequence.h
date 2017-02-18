//
//  Sequence.h
//  Project_2
//
//  Created by Runjia Li on 1/25/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>

typedef std::string ItemType;

class Sequence
{
public:
    Sequence();
    Sequence(const Sequence& other);
    ~Sequence();
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
    Sequence& operator=(const Sequence& other);

private:
    struct Node
    {
        ItemType value;
        Node* next;
        Node* prev;
    };
    
    Node* head;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_h */
