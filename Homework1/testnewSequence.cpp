//
//  testnewSequence.cpp
//  Homework1
//
//  Created by Akshara Sundararajan on 1/19/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

#include "newSequence.h"
#include <iostream>
#include <cassert>

//
//  testnewSequence.cpp
//  Homework1
//
//  Created by Akshara Sundararajan on 1/19/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

int main()
{
    Sequence a(32);
    a.insert(3, 43);
    a.insert(2);
    a.insert(4);
    Sequence b(a);
    assert(b.find(2)== 0);
    b.insert(55);
    Sequence c;
    c = b;
    c.remove(4);
    assert(c.find(4) == -1);
    b.swap(c);
    assert(b.find(4) == -1);
    
    
}
/*
int main()
{
 Sequence a(1000);   // a can hold at most 1000 items
 Sequence b(5);      // b can hold at most 5 items
 Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
 ItemType v = 6666;
 
 // No failures inserting 5 items into b
 for (int k = 0; k < 5; k++)
 assert(b.insert(k, v));
 
 // Failure if we try to insert a sixth item into b
 assert(!b.insert(5, v));
 
 // When two Sequences' contents are swapped, their capacities are
 // swapped as well:
 a.swap(b);
 assert(!a.insert(5, v));
 for (int k = 0; k < 1000; k++)
 assert(b.insert(k, v));
 }*/
/*
#include "newSequence.h"
 #include <iostream>
 #include <cassert>
 using namespace std;
 
 int main()
 {
 Sequence s;
 assert(s.empty());
 assert(s.find("laobing") == -1);
 s.insert("laobing");
 assert(s.size() == 1  &&  s.find("laobing") == 0);
 cout << "Passed all tests" << endl;
 }
*/
