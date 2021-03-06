#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include "Kart.h"

#include <algorithm>

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts(){
	vector<CKart> ret;
	for(CPista &p:pistasG)
	    ret.insert(ret.end(), p.getFrotaActual().begin(), p.getFrotaActual().end());
	sort(ret.begin(), ret.end(), [](CKart &c1, CKart &c2){ return (c1.getNumero() < c2.getNumero()); });
	return ret;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind){
    vector<CKart> v = ordenaKarts();
    int ret = 0;
    for(CKart &c:v){
        if(c.getAvariado() && c.getCilindrada() == cilind)
            ++ret;
    }
    return ret;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind){
    kartsLinhaPartida.empty();
    for(CKart &c:frotaKartsPista){
        if(c.getCilindrada() == cilind && !c.getAvariado()){
            kartsLinhaPartida.push(c);
            if(kartsLinhaPartida.size() >= numeroKarts) return true;
        }
    }
    return false;
}

//Exercicio 1 d) 
int CPista::inicioCorrida(){
    kartsEmProva.clear();
    while(!kartsLinhaPartida.empty()){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

