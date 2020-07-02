#include "frota.h"
#include <string>

using namespace std;

vector<Veiculo *> Frota::operator()(int anoM) const {
    vector<Veiculo *> ret;
    for(Veiculo *p:veiculos)
        if(p->getAno() == anoM)
            ret.push_back(p);
    return ret;
}

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const {
    return veiculos.size();
}

int Frota::menorAno() const {
    if(numVeiculos() <= 0) return 0;
    else {
        int ret = veiculos[0]->getAno();
        for (int i = 1; i < veiculos.size(); ++i)
            ret = min(ret, veiculos[i]->getAno());
        return ret;
    }
}

float Frota::totalImposto() const {
    float ret = 0;
    for(const Veiculo *p:veiculos)
        ret += p->calcImposto();
    return ret;
}
