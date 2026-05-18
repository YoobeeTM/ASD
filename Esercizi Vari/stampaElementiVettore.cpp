#include <vector>
#include <iostream>

using namespace std;

void stampaElementiVettore(vector<int> v, unsigned int i)
{
    if(i>=v.size()) return;
    cout<< v[i]<<stampaElementiVector(v, i+1);
}