//
//  Sequence.hpp
//  Project2
//
//  Created by Akshara Sundararajan on 1/27/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h
//#include<string>
//#include "IntWrapper.h"      // TODO: remove this line after testing
//typedef IntWrapper ItemType; // TODO: replace this line after testing
typedef unsigned long ItemType;

//typedef std::string ItemType;

class Sequence
{
public:
    Sequence();
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
    ~Sequence();
    Sequence(const Sequence &s);
    Sequence& operator=(const Sequence& s);
    void dump() const;
private:
    struct Node{
        ItemType value;
        Node *next, *prev;
    };
    Node *head;
    Node *tail;
    int m_size;
};
int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
#endif /* Sequence_h */
