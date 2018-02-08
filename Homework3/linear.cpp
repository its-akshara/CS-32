
/*#include <iostream>
#include<cassert>
using namespace std;
bool somePredicate(double x)
{
    return x>0;
}
*/
// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    if(n<=0)
        return false;
    
    if(n == 1)
        return somePredicate(a[0]);
    
    return  somePredicate(a[n-1]) && allTrue(a, n-1);
    

}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    if(n<=0)
        return -1;
    
    if(n == 1
       && !somePredicate(a[0]))
        return 1;
    else if(n == 1
            && somePredicate(a[0]))
        return 0;
    
    if(somePredicate(a[n-1]))
        return countFalse(a,n-1);
    else
        return 1+countFalse(a,n-1);
    

}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
    if(n <= 0 )
        return -1;
    
    
    if(n==1)
    {
        if(somePredicate(a[0]) || n<0)
            return -1;
        else
            return 0;
    }
    if(firstFalse(a, n-1) != -1)
        return firstFalse(a, n-1);
    else
        if(!somePredicate(a[n-1]))
            return n-1;
    
    
    return -1;  // This is incorrect.
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    if(n<=0)
        return -1;
    /*if(n==1)
        return a[0];
    int t = indexOfMin(a, n-1);
    if(a[n-1]<a[t])
        return n-1;
    else
        return t;*/
    if(n==1)
        return 0;
    int t =indexOfMin(a+1,n-1);
    if(a[0]<=a[t+1])
        return 0;
    else
        return 1+t;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if(n1<n2)
        return false;
    if(n2 == 0)
        return true;
    
    if(a2[0] == a1[0])
        return includes(a1+1,n1-1,a2+1,n2-1);
    else
        return includes(a1+1,n1-1,a2,n2);
    
    
    
    return false;
}
/*
int main()
{
    double a[]={1,1,-33,1,-33};
    assert(!allTrue(a, 5));
    assert(indexOfMin(a, 5)==2);
    assert(countFalse(a, 5) == 2);
    assert(firstFalse(a, 5) == 2);
    double a1[]={10,50,40,20,50,40,30};
    double a2[]={10,20,20};
    assert(!includes(a1, 7, a2, 3));
    assert(indexOfMin(a1, 7) == 0);
    assert(indexOfMin(a2, 3) == 0);
    cout<<"Success!"<<endl;
}

*/
