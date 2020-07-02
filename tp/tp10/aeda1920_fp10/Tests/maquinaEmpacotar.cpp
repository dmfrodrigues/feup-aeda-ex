#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


// a alterar
unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	unsigned ret = 0;
	vector<Objeto> objs_;
    for(const Objeto &o:objs){
	    if(o.getPeso() <= capacidadeCaixas){ objetos.push(o); ++ret; }
	    else                                 objs_.push_back(o);
	}
    objs=objs_;
    return ret;
}

// a alterar
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
    queue<Caixa> q;
    Caixa cx(capacidadeCaixas);
    while(!caixas.empty() && caixas.top().getCargaLivre() < obj.getPeso()){
        q.push(caixas.top()); caixas.pop();
    }
    if(!caixas.empty()){
        cx = caixas.top(); caixas.pop();
    }
    while(!q.empty()){
        caixas.push(q.front()); q.pop();
    }
	return cx;
}

// a alterar
unsigned MaquinaEmpacotar::empacotaObjetos() {
    while(!objetos.empty()){
        Objeto obj = objetos.top(); objetos.pop();
        Caixa cx = procuraCaixa(obj);
        cx.addObjeto(obj);
        addCaixa(cx);
    }
	return caixas.size();
}

// a alterar
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    stringstream ss;
    HEAP_OBJS h = objetos;
    while(!h.empty()){
        ss << h.top() << "\n"; h.pop();
    }
    string ret = ss.str();
    if(ret == "") ret = "Nao ha objetos!\n";
	return ret;
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
    if(caixas.empty()) throw MaquinaSemCaixas();
    HEAP_CAIXAS h = caixas;
	Caixa cx = h.top();
	while(!h.empty()) {
        if (h.top().getSize() > cx.getSize()) cx = h.top();
        h.pop();
    }
	return cx;
}



