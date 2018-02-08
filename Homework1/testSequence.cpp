//
//  testSequence.cpp
//  Homework1
//
//  Created by Akshara Sundararajan on 1/18/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>
void testInsert(Sequence &s)
{
    s.insert(34);
    s.insert(22);
    s.insert(3,45);
    s.insert(22);
    assert(s.size()==5);
}
void testErase(Sequence &s)
{
    if(s.erase(0))
    {
        assert(s.size()==4);
        ItemType tester;
        assert(s.get(3, tester) && tester == 45);
    }
}
void testSwap()
{
    Sequence r,s;
    s.insert(2);
    r.insert(3);
    testInsert(r);
    testInsert(s);
    s.insert(33);
    s.insert(88);
    s.swap(r);
    assert(r.find(88)==6 && s.find(3)==0);
}
using namespace std;
int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    s.insert(42);
    cerr<<s.find(42);
    assert(s.size() == 1  &&  s.find(42) == 0);
    testInsert(s);
    testErase(s);
    testSwap();
    cout << "Passed all tests" << endl;
}
/*
 #include "Sequence.h"
 #include <iostream>
 #include <cassert>
 using namespace std;
 
 int main()
 {
 Sequence s;
 s.insert(0, "a");
 s.insert(1, "b");
 s.insert(2, "c");
 s.insert(3, "b");
 s.insert(4, "e");
 assert(s.remove("b") == 2);
 assert(s.size() == 3);
 string x;
 assert(s.get(0, x)  &&  x == "a");
 assert(s.get(1, x)  &&  x == "c");
 assert(s.get(2, x)  &&  x == "e");
 Sequence s1;
 s1.insert(0, "paratha");
 s1.insert(0, "focaccia");
 Sequence s2;
 s2.insert(0, "roti");
 s1.swap(s2);
 assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
 s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
 Sequence s3;
 s3.insert(0, "dosa");
 s3.insert(1, "pita");
 s3.insert(2, "");
 s3.insert(3, "matzo");
 assert(s3.find("") == 2);
 s3.remove("dosa");
 assert(s3.size() == 3  &&  s3.find("pita") == 0  &&  s3.find("") == 1  &&
 s3.find("matzo") == 2);
 cout<<"All good"<<endl;
 }*/

/*
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "c");
    s.insert(3, "b");
    s.insert(4, "e");
    assert(s.remove("b") == 2);
    assert(s.size() == 3);
    string x;
    assert(s.get(0, x)  &&  x == "a");
    assert(s.get(1, x)  &&  x == "c");
    assert(s.get(2, x)  &&  x == "e");
    Sequence s1;
    s1.insert(0, "paratha");
    s1.insert(0, "focaccia");
    Sequence s2;
    s2.insert(0, "roti");
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
           s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
    Sequence s3;
    s3.insert(0, "dosa");
    s3.insert(1, "pita");
    s3.insert(2, "");
    s3.insert(3, "matzo");
    assert(s3.find("") == 2);
    s3.remove("dosa");
    assert(s3.size() == 3  &&  s3.find("pita") == 0  &&  s3.find("") == 1  &&
           s3.find("matzo") == 2);
    cout<<"All good"<<endl;
}*/
