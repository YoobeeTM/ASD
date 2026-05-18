#include <iostream>

using namespace std;

int sommaPrimiNNumeri(n)
{
    if(n==0) return;
    return n + sommaPrimiNNumeri(n-1);
}