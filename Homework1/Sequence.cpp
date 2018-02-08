//
//  Sequence.cpp
//  Homework1
//
//  Created by Akshara Sundararajan on 1/18/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

#include "Sequence.h"
#include<iostream>
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
    if(m_size>=DEFAULT_MAX_ITEMS||pos<0||pos>m_size)
        return false;
    for(int i=size(); i>pos; i--)
    {
        m_arr[i] = m_arr[i-1];
    }
    m_arr[pos] = value;
    m_size++;
    return true;
}


// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
int Sequence::insert(const ItemType& value)
{
    int p=-1;
    bool foundPos=false;
    for(int i=0; i<m_size; i++)
    {
        if(value<=m_arr[i])
        {
            p=i;
            foundPos=true;
            break;
        }
    }
    if(foundPos==false)
        p=size();
    if(insert(p,value))
        return p;
    else
        return -1;
}


// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos)
{
    if(0<=pos&& pos<size())
    {
        for(int i=pos; i<size()-1; i++)
        {
            m_arr[i] = m_arr[i+1];
        }
        m_size--;
        return true;
    }
    return false;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value)
{
    int numRemoved = 0;
    for(int i=0; i<size(); i++)
    {
        if(m_arr[i] == value)
        {
            numRemoved++;
            erase(i);
            i--;
        }
    }
    return numRemoved;
}

// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value)const
{
    if(0<= pos && pos< size())
    {
        value = m_arr[pos];
        return true;
    }
    return false;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value)
{
    if(0<= pos && pos< size())
    {
        m_arr[pos] = value;
        return true;
    }
    return false;
    
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const
{
    int p = -1;
    for(int i = 0; i < m_size; i++)
    {
        if(value == m_arr[i])
        {
            p = i;
            break;
        }
    }
    return p;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other)
{/*
  ItemType x;
  int i=0;
  
  
  int max1 = (m_size<= other.m_size)? m_size:other.m_size;
  //switch until size of both
  for(i = 0; i< max1; i++)
  {
  x = m_arr[i];
  m_arr[i] = other.m_arr[i];
  other.m_arr[i] = x;
  }
  int left = other.m_size - m_size;
  if(left < 0) left-=left;
  for(i=0;i<left;i++)
  {
  if(m_size<= other.m_size)
  {
  //x = m_arr[max1+i];
  m_arr[max1+i]= other.m_arr[max1+i];
  //other.m_arr[max1+i] = x;
  }
  else
  {
  other.m_arr[max1+i] = m_arr[max1+i];
  }
  }
  i = m_size;
  m_size = other.m_size;
  other.m_size = i;
  */
    Sequence temp = other;
    other = *this;
    *this = temp;
    
}

