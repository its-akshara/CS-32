//
//  testScoreList.cpp
//  Homework1
//
//  Created by Akshara Sundararajan on 1/19/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

#include "ScoreList.h"
#include <cassert>
int main()
{
    ScoreList s;
    s.add(10);
    s.add(11);
    s.add(12);
    s.add(13);
    assert(s.maximum()==13&&s.minimum()==10);
    assert(s.remove(13)&&s.maximum()==12);
}
