#include "jogo.h"
#include <sstream>


//a alterar
ostream &operator << (ostream &os, Circulo &c1){
	return os;
}


//a alterar
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados){
    jogo = iniciarJogo(niv, 0, pontos, estados);
}

BinaryTree<Circulo> Jogo::iniciarJogo(int niv, int pos, const vector<int> &pontos, const vector<bool> &estados){
    if(niv < 0) return BinaryTree<Circulo>();
    Circulo c(pontos[pos], estados[pos]);
    BinaryTree<Circulo> l = iniciarJogo(niv-1, 2*pos+1, pontos, estados);
    BinaryTree<Circulo> r = iniciarJogo(niv-1, 2*pos+2, pontos, estados);
    return BinaryTree<Circulo>(c, l, r);
}

//a alterar
string Jogo::escreveJogo(){
    stringstream ss;
    BTItrLevel<Circulo> it(jogo);
    while(!it.isAtEnd()){
        const Circulo &c = it.retrieve();
        ss << c.getPontuacao() << "-";
        if(c.getEstado()) ss << "true"; else ss << "false";
        ss << "-" << c.getNVisitas() << "\n";
        it.advance();
    }
	return ss.str();
}

//a alterar
int Jogo::jogada(){
    BTItrLevel<Circulo> it(jogo);
    int current = 0;
    int next = 0;
    int ret = 0;
    while(!it.isAtEnd()){
        if(current == next) {
            next = 2*current + (it.retrieve().getEstado() ? 2 : 1);
            it.retrieve().mudaEstado();
            it.retrieve().incNVisitas();
            ret = it.retrieve().getPontuacao();
        }
        current++;
        it.advance();
    }
    return ret;
}


//a alterar
int Jogo::maisVisitado(){
    BTItrLevel<Circulo> it(jogo);
    it.advance();
    int ret = 0;
    while(!it.isAtEnd()){
        ret = max(ret, it.retrieve().getNVisitas());
        it.advance();
    }
	return ret;
}

