#include "veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a): marca(mc), mes(m), ano(a) {}

string Veiculo::getMarca() const {
    return marca;
}

int Veiculo::getAno() const {
    return ano;
}

int Veiculo::info() const {
    cout << "Marca: " << marca << "\n";
    cout << "Mes: " << mes << "\n";
    cout << "Ano: " << ano << "\n";
    return 3;
}

bool Veiculo::operator<(const Veiculo &v) const {
    if(ano != v.ano) return (ano < v.ano);
    else             return (mes < v.mes);
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc, m, a), combustivel(c), cilindrada(cil){}

string Motorizado::getCombustivel() const {
    return combustivel;
}

int Motorizado::info() const{
    int ret = Veiculo::info();
    cout << "Combustivel: " << combustivel << "\n";
    cout << "Cilindrada: " << cilindrada << "\n";
    return ret+2;
}

float Motorizado::calcImposto() const{
    int categoria;
    if(combustivel == "gasolina"){
        if     (cilindrada <= 1000) categoria = 0;
        else if(cilindrada <= 1300) categoria = 1;
        else if(cilindrada <= 1750) categoria = 2;
        else if(cilindrada <= 2600) categoria = 3;
        else if(cilindrada <= 3500) categoria = 4;
        else                        categoria = 5;
    }else{
        if     (cilindrada <= 1500) categoria = 0;
        else if(cilindrada <= 2000) categoria = 1;
        else if(cilindrada <= 3000) categoria = 2;
        else                        categoria = 3;
    }
    float imposto[2][6] = {{14.56, 29.06, 45.15, 113.98, 181.17, 320.89},
                           { 8.10, 14.56, 22.65,  54.89,  87.13, 148.37}};
    return imposto[getAno() > 1995 ? 0 : 1][categoria];
}

Automovel::Automovel(string mc, int m, int a, string c, int cil):Motorizado(mc, m, a, c, cil){}

int Automovel::info() const{
    return Motorizado::info();
}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm):Motorizado(mc,m,a,c,cil), carga_maxima(cm){}

int Camiao::info() const{
    int ret = Motorizado::info();
    cout << "Carga_maxima: " << carga_maxima << "\n";
    return ret+1;
}

Bicicleta::Bicicleta(string mc, int m, int a, string t):Veiculo(mc, m, a), tipo(t){}

int Bicicleta::info() const {
    int ret = Veiculo::info();
    cout << "Tipo: " << tipo << "\n";
    return ret+1;
}

float Bicicleta::calcImposto() const {
    return 0;
}