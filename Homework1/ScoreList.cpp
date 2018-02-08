//
//  ScoreList.cpp
//  Homework1
//
//  Created by Akshara Sundararajan on 1/18/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//

#include "ScoreList.h"
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
bool ScoreList::add(unsigned long score)
{
    return (score<=100 && m_scores.insert(score));
}


// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
bool ScoreList::remove(unsigned long score)
{
    return (m_scores.erase(m_scores.find(score)));
    
}

// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::minimum() const
{
    
    ItemType min,check;
    
    if(m_scores.empty())
        return NO_SCORE;
    else
    {
        if(m_scores.get(0, min))
            for(int i=1; i<m_scores.size(); i++)
            {
                if(m_scores.get(i, check) && check<min)
                {
                    min = check;
                }
            }
    }
    return min;
}

// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::maximum() const
{
    ItemType max,check;
    
    if(m_scores.empty())
        return NO_SCORE;
    else
    {
        if(m_scores.get(0, max))
            for(int i=1; i<m_scores.size(); i++)
            {
                if(m_scores.get(i, check) && check>max)
                {
                    max = check;
                }
            }
    }
    return max;
}
