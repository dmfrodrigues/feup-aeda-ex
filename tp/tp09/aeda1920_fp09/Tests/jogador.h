#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "aposta.h"
#include <string>

using namespace std;

//a alterar
struct apostaHash
{
	int operator() (const Aposta & ap) const{
	    int ret = 0;
	    for(const auto &i:ap.getNumeros()){
	        ret = std::hash<unsigned>{}(ret+i);
	    }
		return ret;
	}
	
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
	    return true;
	}
};



typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;

class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
