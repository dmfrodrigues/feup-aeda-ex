#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

ClienteNaoExistente::ClienteNaoExistente(const string &nome):nome(nome){}

const string& ClienteNaoExistente::getNome()const{
    return nome;
}

PosicaoNaoExistente::PosicaoNaoExistente(const size_t &p):p(p){}

const size_t& PosicaoNaoExistente::getValor()const{
    return p;
}

bool InfoCartao::operator==(const InfoCartao &s)const{
    return (nome == s.nome);
}

bool InfoCartao::operator<(const InfoCartao &i)const{
    if(frequencia != i.frequencia) return (frequencia > i.frequencia);
    else                           return (nome       < i.nome      );
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a imnplementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    InfoCartao cmp; cmp.nome = nome;
    return sequentialSearch(clientes, cmp);
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    InfoCartao cmp; cmp.nome = nome;
    int pos = sequentialSearch(clientes, cmp);
    if(pos == -1){
        ClienteNaoExistente e(nome);
        throw e;
    }
    return clientes[pos].frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    for(int i = 0; i < clientes.size(); ++i) {
        for (int j = 0; j < clientes.size() - 1; ++j) {
            if (!(clientes[j].nome < clientes[j + 1].nome)) {
                swap(clientes[j], clientes[j + 1]);
            }
        }
    }
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<InfoCartao> info;
    for(const InfoCartao &i:clientes)
        if(n1 <= i.frequencia && i.frequencia <= n2)
            info.push_back(i);

    insertionSort(info);

    vector<string> nomes;
    for(const InfoCartao &i:info)
        nomes.push_back(i.nome);

    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    for(const InfoCartao &i:pe.clientes) {
        cout << "Nome: " << i.nome << endl;
        cout << "Presente: " << i.presente << endl;
        cout << "Frequencia: " << i.frequencia << endl;
    }
    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    if(p >= clientes.size()){
        PosicaoNaoExistente e(p);
        throw e;
    }
    return clientes[p];
}
