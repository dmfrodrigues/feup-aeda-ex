#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    numPresentes = 1+rand()%5;
}

//a alterar
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual = 0;
    prox_chegada = 1+rand()%20;
    prox_saida   = 0;
    clientes_atendidos = 0;
}

//a alterar
void Balcao:: proximoEvento(){
    if(!clientes.empty() && prox_saida <= prox_chegada){
        tempo_atual = prox_saida;
        saida();
    }else{
        chegada();
    }
}

//a alterar
void Balcao::chegada(){
    Cliente c;
    clientes.push(c);
    prox_chegada = 1+rand()%20;
    if(clientes.size() <= 1){
        prox_saida = tempo_atual+clientes.front().getNumPresentes()*tempo_embrulho;
    }
    cout << "tempo= " << tempo_atual << endl;
    cout << "chegou novo cliente com " << c.getNumPresentes() << " presentes" << endl;
}

//a alterar
void Balcao::saida(){
    try{
        Cliente c = getProxCliente();
        clientes.pop();
        ++clientes_atendidos;
        prox_saida = tempo_atual+clientes.front().getNumPresentes()*tempo_embrulho;
        cout << "tempo= " << tempo_atual << endl;
        cout << "saiu cliente com " << c.getNumPresentes() << " presentes" << endl;
    }catch(...){

    }
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1){
     out << "clientes atendidos: " << b1.clientes_atendidos << endl;
     out << "clientes em espera: " << b1.clientes.size() << endl;
     return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    if(clientes.empty()) throw FilaVazia();
    return clientes.front();
}

      
