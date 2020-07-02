#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return (getPalavra() < ps1.getPalavra());
}

//a alterar
void Dicionario::lerDicionario(ifstream &fich){
    string buf1, buf2;
    while(getline(fich, buf1)) {
        getline(fich, buf2);
        palavras.insert(PalavraSignificado(buf1, buf2));
    }
}

//a alterar
string Dicionario::consulta(string palavra) const{
    const PalavraSignificado &p = palavras.find(PalavraSignificado(palavra, ""));
    if(p.getPalavra() != palavra){
        BSTItrIn<PalavraSignificado> it(palavras);
        PalavraSignificado p1("","");
        while(!it.isAtEnd() && it.retrieve().getPalavra() < palavra){
            p1 = it.retrieve();
            it.advance();
        }
        PalavraSignificado p2("","");
        if(!it.isAtEnd()){
            p2 = it.retrieve();
        }
        throw PalavraNaoExiste(p1, p2);
    }else return p.getSignificado();
}

//a alterar
bool Dicionario::corrige(string palavra, string significado){
    if(palavras.find(PalavraSignificado(palavra, "")).getPalavra() == palavra){
        palavras.remove(PalavraSignificado(palavra, ""));
        palavras.insert(PalavraSignificado(palavra, significado));
        return true;
    }else {
        palavras.insert(PalavraSignificado(palavra, significado));
        return false;
    }
}

//a alterar
void Dicionario::imprime() const{
    BSTItrIn<PalavraSignificado> it(palavras);
    const PalavraSignificado &q = it.retrieve();
    while(!it.isAtEnd()){
        const PalavraSignificado &p = it.retrieve();
        cout << p.getPalavra() << endl;
        cout << p.getSignificado() << endl;
        it.advance();
    }
}
