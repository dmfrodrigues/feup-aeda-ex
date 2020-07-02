#include "jogador.h"

//a alterar
void Jogador::adicionaAposta(const Aposta & ap){
    apostas.insert(ap);
}

//a alterar
unsigned Jogador::apostasNoNumero(unsigned num) const{
	unsigned ret = 0;
    for(const Aposta &a:apostas){
	    if(a.contem(num)) ret++;
	}
    return ret;
}

//a alterar
tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const{
	tabHAposta ret;
    for(const Aposta &a:apostas){
	    if(a.calculaCertos(sorteio) > 3) ret.insert(a);
	}
	return ret;
}
