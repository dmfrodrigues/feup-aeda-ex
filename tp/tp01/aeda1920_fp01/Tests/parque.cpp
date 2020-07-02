#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):lotacao(lot), numMaximoClientes(nMaxCli) {
    vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for(int i = 0; i < clientes.size(); ++i)
        if(nome == clientes[i].nome)
            return i;
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if(clientes.size() >= numMaximoClientes) return false;
    InfoCartao c; c.nome = nome; c.presente = false;
    clientes.push_back(c);
    return true;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    int i = posicaoCliente(nome);
    if(i == -1) return false;
    if(clientes[i].presente) return false;
    if(vagas <= 0) return false;
    --vagas;
    clientes[i].presente = true;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    int i = posicaoCliente(nome); if(i == -1) return false;
    if(clientes[i].presente) return false;
    clientes.erase(clientes.begin()+i);
    return true;
}

bool ParqueEstacionamento::sair(const string &nome) {
    int i = posicaoCliente(nome); if(i == -1) return false;
    if(!clientes[i].presente) return false;
    clientes[i].presente = false;
    --vagas;
    return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}