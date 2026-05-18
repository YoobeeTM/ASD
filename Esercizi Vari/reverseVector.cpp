#include <vector>
#include <iostream>

using namespace std;

vector reverseVector(vector<int> v, unsigned int i)
{
    vector <int> vr;
    if(i>=v.size()) return vr;

    vr.push_back(v[i]);
    return reverseVector(v, i+1);
}