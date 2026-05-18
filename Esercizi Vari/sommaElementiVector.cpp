#include <vector>
#include <iostream>

using namespace std;

int sommaElementiVectorRicorsiva(vector <int> v, unsigned int i)
{
    if(i>=v.size()) return;
    return v.at(i)+ sommaElementiVectorRicorsiva(v,i+1);
}