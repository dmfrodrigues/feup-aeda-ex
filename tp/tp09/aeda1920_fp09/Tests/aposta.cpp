#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const{
    return (numeros.find(num) != numeros.end());
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n){
    for(const unsigned u:valores) {
        if(numeros.size() >= n) return;
        numeros.insert(u);
    }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const{
    unsigned ret = 0;
    for(const auto &i:sorteio) if(contem(i)) ++ret;
    return ret;
}





