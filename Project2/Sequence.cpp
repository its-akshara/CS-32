//
//  Sequence.cpp
//  Project2
//
//  Created by Akshara Sundararajan on 1/27/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

#include "Sequence.h"

#include<iostream>

//Constructor
Sequence:: Sequence()
{
    head = nullptr;
    tail = nullptr;
    
    m_size = 0;
}


//Destructor, deletes all nodes in Sequence
Sequence:: ~Sequence()
{
    Node *temp = head;
    //dump();
    while(temp!=nullptr)
    {
      //  dump();
        Node *p= temp;
        temp=temp->next;
        delete p;
        //std::cerr<<"Destroy\n";
    }
    //int pos = 0;
    //for(int i=0; i<size()-1; i++)
    //{
      //  if(erase(0))
        //    continue;
            //i--;
    //}
}


//returns true if the function is empty
bool Sequence::empty() const
{
    return m_size == 0;
}


//returns number of nodes in Sequence
int Sequence::size() const
{
    return m_size;
}

// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// (e.g., because it's implemented using a fixed-size array) and is
// full.)  Otherwise, leave the sequence unchanged and return false.
// Notice that if pos is equal to size(), the value is inserted at the
// end.
bool Sequence::insert(int pos, const ItemType& value)
{
    Node *p=new Node;
    p->value = value;
   //std::cerr<<"Create\n";
    if(head!=nullptr && pos>0 && pos<size() ) //insert in the middle
       {
           Node *temp;
           temp = head;
           for(int i = 0; i<pos; i++)
           {
               temp= temp->next;
               
           }
           p->next = temp;   //do pointer manipulation to insert node
           p->prev = temp->prev;
           temp->prev->next = p;
           temp->prev = p;
           m_size++;
           return true;
       }
    else if ((head == nullptr || size() == 0) && pos == 0) //if Sequence is empty
    {
        p->prev = nullptr;
        head = p;
        p->next = nullptr;
        tail = p;
        m_size++;
        return true;
            }
    else if(head != nullptr && pos == 0)//insert in beginning
    {
        //p->next = head->next;
        //head->next->prev = p;
        
        p->next = head;
        head->prev = p;
        //p->prev = head;
        p->prev = nullptr;
        head = p;
        
        m_size++;
        return true;
    }
    else if(pos == size() && head != nullptr)  //add to end
    {
        p->prev = tail;
        p->next = nullptr;
        tail->next = p;
        tail = p;
        m_size++;
        return true;
    }
    delete p;
    //std::cerr<<"Destroy\n";
    return false;
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
int Sequence::insert(const ItemType& value)
{
    
    int index = 0;
    
    Node *temp;
    temp = head;
    if((head == nullptr || value < head->value ))  //if Sequence is empty
    {
        // m_size ++;
        if(insert(0, value))
            return 0;
    }
    
    else                //insert in middle
    {
        
        while(temp!=nullptr)
        {
            if(value <= temp->value)
            {
               if(insert(index, value))
                   return index;
            }
            temp = temp->next;
            index++;
            
        }
        //m_size++;
    }
    if(temp == nullptr && head != nullptr) //enter at the end
    {
        if(insert(size(), value))
           {
               return size()-1;
           }
    }
    
    return -1;
}

//Prints all the elements in the doubly linked list
void Sequence::dump() const
{
    Node *temp = head;
    //ItemType x = 0;
    //assert(this->insert(x) == 0);
    std::cerr<<"m_size:"<<m_size<<std::endl<<std::endl;
    int i = 0;
    if(head != nullptr)
        while(i<size())
        {   i++;
            std::cerr<<temp->value<<std::endl;
            temp = temp->next;
        }
}


// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos)
{
    if(head==nullptr || pos>=size() || pos<0 || m_size == 0) //underflow
        return false;
    Node *temp = head;
    if(pos == 0 && head==tail && size() == 1) //only one element
    {
        head = nullptr;
        tail = nullptr;
        delete temp;
        //std::cerr<<"Destroy\n";
        
        m_size--;
        return true;
    }
    else if(pos == 0 && head != tail) //remove first element
    {
        head = head->next;
        head->prev = nullptr;
        m_size--;
        delete temp;
        //std::cerr<<"Destroy\n";
        return true;
    }
    else if(pos>0 && pos<(size()-1)){ //in the middle
        for(int i = 0; i<pos; i++)
        {
            temp= temp->next;
            
        }
        //now at node that needs to be deleted
        temp->prev->next = temp -> next;
        temp->next->prev = temp->prev;
        m_size--;
        delete temp;
        //std::cerr<<"Destroy\n";
        return true;
    }
    else if(pos == (size()-1)) //deleting tail
    {
        temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        //std::cerr<<"Destroy\n";
        m_size--;
        return true;
    }
    return false;
}


// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value)
{
    int countRemoved = 0;
    Node *temp = head;
    int pos = 0;
    while(temp != nullptr &&  m_size != 0)
    {
        if(temp->value == value)
        {
            temp=temp->next;
            if(erase(pos))
            {
                countRemoved++;
                
                //pos--;
                continue;
            }
        }
        pos++;
        temp=temp->next;
    }
    
    return countRemoved;
}

// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const
{
    if(pos<0 || pos>=size() || head == nullptr)
    {
        return false;
    }
    Node *temp = head;
    for(int i = 0; i < pos; i++)
    {
        temp= temp->next;
    }
    value = temp->value;
    return true;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value)
{
    if(pos<0 || pos>=size() || head == nullptr)
        return false;
    else{
        Node *temp = head;
        for(int i = 0; i < pos; i++)
        {
            temp= temp->next;
        }
        temp->value = value;
        return true;
    }
    
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const
{
    int p = -1;
    Node *temp = head;
    while(temp!=nullptr)
    {   p++;
        if(value == temp->value)  //check if value same
        {
            return p;
        }
        temp = temp->next;
    }
    return -1;
}


 // Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other)
{
    Node *temp = head;
    head = other.head;
    other.head = temp;
    
    temp = other.tail;
    other.tail = tail;
    tail = temp;
    
    int i;
    i = m_size;
    m_size = other.m_size;
    other.m_size = i;
    
    
}


//copy constructor of Sequence
Sequence::Sequence(const Sequence &s)
{
    //int tsize = s.m_size/2-1;
    //int i = 0;
    
    
    m_size = 0;
    //head = s.head;
    //tail = s.tail;
    if(s.head == nullptr)
    {
        head = nullptr;
        tail = nullptr;
    }
    //head = nullptr;
    Node *temp;
    temp = s.head;
    int pos=0;
    //head = nullptr;
    while(pos<s.size() && temp != nullptr && insert(pos, temp->value))
    {
        //i++;
        pos++;
        //m_size--;
        temp = temp ->next;
    }
     m_size = s.m_size;
}



//overloading assignment operator
Sequence& Sequence::operator=(const Sequence& s)
{
    if(this!=&s)
    {Sequence t = s;
        swap(t);
    }
    return *this;
}



//if seq2 is a consecutive subsequence of seq1, the function returns the earliest place in seq1 where that subsequence starts.) If no such k exists or if seq2 is empty, the function returns -1.
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq2.empty() || seq2.size()>seq1.size() || seq1.empty())
        return -1;
    
    //bool found = false;
    ItemType s1,s2;
    seq2.get(0, s2);
    int ctr1,ctr2;
    for(int i = 0; i<seq1.size(); i++)
    {
        seq1.get(i,s1);
        //seq2.get(i, s2);
        //So s1 and s2 are our means of checking equality/comparing
        if(s1==s2) //first ItemType matches
        {
            for(ctr1=i,ctr2=0;ctr1<seq1.size() && ctr2<seq2.size(); ctr1++, ctr2++)
            {
                seq1.get(ctr1,s1);
                seq2.get(ctr2, s2);
                if(s1 != s2)   //so not a subsequence break
                {
                    break;
                }
            }
            if(ctr2 == seq2.size())
                return i;
        }
        
    }
    return -1;
}


//This function produces as a result a sequence that consists of the first item in seq1, then the first in seq2, then the second in seq1, then the second in seq2, etc.
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    if(seq2.empty() && seq1.empty())  //check if empty
        result = seq2;
    else if(seq2.empty())
    {result = seq1;
    }
    else if (seq1.empty())
        result = seq2;
    else{
        
        Sequence temp;
        int pos = 0;
        ItemType s1, s2;
        int ctr = 0;
        while(ctr<seq1.size() && ctr<seq2.size())   //go through until one sequence ends
        {
                        //int ctr1 = 0, ctr2 = 0;
            
            if(seq1.get(ctr, s1) && seq2.get(ctr,s2 ))
            {  if(ctr<seq1.size() && temp.insert(pos, s1) ) //increment after inserting
            {   //temp.dump();
                    pos++;
                
                
                    }
           // else break;
                if(ctr<seq2.size() && temp.insert(pos, s2)) //increment after inserting
                {
                    
                    pos++;
                }
                else
                    break;
                ctr++;
            }
            
        }
        //temp.dump();
        if(seq1.size()>seq2.size() && ctr<seq1.size()) //seq1 has items left
        {
            while(ctr<seq1.size() && seq1.get(ctr, s1) )
            {
                if(temp.insert(pos, s1))
                { pos++;
                ctr++;}
            }
        }
        else{
            while(ctr<seq2.size() && seq2.get(ctr, s2) ) //seq2 has items left
            {
                if(temp.insert(pos, s2))
                {
                    ctr++;
                    ++pos;
                }
                if(ctr>=seq2.size())
                {
                    
                    break;
                }
            }
        }
        //int eraser = 0;
        for(int i =0; i<result.size(); i++)
        {
            result.erase(0);
        }
        //temp.dump();
        //std::cerr<<std::endl<<std::endl;
        result = temp;
    }
}
