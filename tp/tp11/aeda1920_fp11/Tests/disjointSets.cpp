#include "disjointSets.h"

DisjointSets::DisjointSets()
{}

// create n disjoint sets (one for each item)
DisjointSets::DisjointSets(int n)
{
   for (int i=0 ; i<n; i++)
        set.push_back(i);
}

// Find the root of the set in which element v belongs
int DisjointSets::find(int v) const
{
    if (set[v] == v)
        return v;
    return find(set[v]);
}

// Perform Union of two subsets
void DisjointSets::unionSets(int root1, int root2)
{
    set[root2] = root1;
}

//a implementar

int DisjointSets::getNumberOfSets() const{
    int ret = set.size();
    for(int i = 0; i < set.size(); ++i){
        if(set[i] != i) --ret;
    }
    return ret;
}

