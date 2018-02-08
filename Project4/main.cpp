//
//  main.cpp
//  Project 4
//
//  Created by Akshara Sundararajan on 3/9/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//
#include "MyMap.h"
#include "provided.h"
#include <iostream>
#include <cassert>

using namespace std;
void example(const MapLoader& ml)
{
    AttractionMapper am;
    am.init(ml); // let our object build its internal data structures
    // by iterating thru all segments from the MapLoader object
    GeoCoord fillMe;
    string attraction = "Native Foods Café";
    bool found = am.getGeoCoord(attraction, fillMe);
    if ( ! found)
    {
        cout << "No geolocation found for " << attraction << endl;
        return;
    }
    cout << "The location of " << attraction << " is " <<fillMe.latitude << ", " << fillMe.longitude << endl;
    
}
void foo()
{
    MyMap<string,double> nameToGPA; // maps student name to GPA
    // add new items to the binary search tree-based map
    nameToGPA.associate("Carey", 3.5); // Carey has a 3.5 GPA
    nameToGPA.associate("David", 3.99); // David beat Carey
    nameToGPA.associate("Abe", 3.2); // Abe has a 3.2 GPA
    
    double* davidsGPA = nameToGPA.find("David");
    if (davidsGPA != nullptr)
        *davidsGPA = 1.5; // after a re-grade of David’s exam
    
  
    nameToGPA.associate("Carey", 4.0); // Carey deserves a 4.0
    // replaces old 3.5 GPA
    double* lindasGPA = nameToGPA.find("Linda");
    if (lindasGPA == nullptr)
        cout << "Linda is not in the roster!" << endl;
    else
        cout << "Linda’s GPA is: " << *lindasGPA << endl;
    
   // MyMap<Attraction,GeoCoord> m_attractionToGeoCoord;
    
    
}
void testsegmap()
{
    MapLoader m;
   bool x =m.load("/Users/akshara/UCLA/CS 32/Project 4/Project 4/mapdata.txt");
    if(x)
        cout<<"hmm"<<endl;
    assert(m.getNumSegments()==12);
    StreetSegment tes;
    assert(!m.getSegment(-1, tes));
    assert(!m.getSegment(22, tes));
    assert(m.getSegment(4, tes));
    assert(tes.streetName=="13th Helena Drive");
    example(m);
}

int main() {
    foo();
    testsegmap();
    return 0;
}
