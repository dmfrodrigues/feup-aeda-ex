/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar
Jogo::Jogo(){}

// a implementar
Jogo::Jogo(list<Crianca>& lc2):criancas(lc2){}

// a implementar
void Jogo::insereCrianca(const Crianca &c1){
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const{
    return criancas;
}

// a implementar
string Jogo::escreve() const{
    string ret = "";
    for(const Crianca &c:criancas){
        ret += c.escreve() + "\n";
    }
    return ret;
}

// a implementar
Crianca& Jogo::perdeJogo(string frase){
    unsigned int n = numPalavras(frase);
    list<Crianca> c = criancas;
    auto it = c.begin();
    while(c.size() > 1){
        for(int i = 1; i < n; ++i) {
            ++it;
            if (it == c.end()) it = c.begin();
        }
        it = c.erase(it);
        if (it == c.end()) it = c.begin();
    }
    return *c.begin();
}

// a implementar
list<Crianca>& Jogo::inverte(){
    reverse(criancas.begin(), criancas.end());
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id){
    list<Crianca> ret;
    auto it = criancas.begin();
    while(it != criancas.end()){
        if(it->getIdade() > id) {
            ret.push_back(*it);
            it = criancas.erase(it);
        }else{
            ++it;
        }
    }
    return ret;
}

// a implementar
void Jogo::setCriancasJogo(const list<Crianca>& l1){
    criancas = l1;
}

// a implementar
bool Jogo::operator==(Jogo& j2){
    return (criancas == j2.criancas);
}

// a implementar
list<Crianca> Jogo::baralha() const{
    vector<Crianca> v(criancas.begin(), criancas.end());
    random_shuffle(v.begin(), v.end());
    list<Crianca> ret(v.begin(), v.end());
    return ret;
}
