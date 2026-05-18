#include <iostream>

using namespace std;

int prodottoPrimiNNumeri(n)
{
    if(n==1) return;
    return n * prodottoPrimiNNumeri(n-1);
}