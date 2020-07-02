#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
    N info;
    NoRepetido(N inf) { info=inf; }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no){
    out << "No repetido: " << no.info;
    return out;
}

// excecao NoInexistente
template <class N>
class NoInexistente {
public:
    N info;
    NoInexistente(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni){
    out << "No inexistente: " << ni.info;
    return out;
}

template<class N>
class ArestaRepetida {
public:
    N info1, info2;
    ArestaRepetida(N inf1, N inf2):info1(inf1), info2(inf2){}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &aresta){
    out << "Aresta repetida: " << aresta.info1 << " , " << aresta.info2;
    return out;
}

template<class N>
class ArestaInexistente{
public:
    N info1, info2;
    ArestaInexistente(N inf1, N inf2):info1(inf1), info2(inf2){}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &aresta){
    out << "Aresta inexistente: " << aresta.info1 << " , " << aresta.info2;
    return out;
}

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public:
    /**
     * Constructor
     */
    Grafo(){
    }
    /**
     * Destructor
     */
    ~Grafo(){
        for(auto p:nos){
            delete p;
        }
    }
    /**
     * Insert node in graph.
     * Throws exception of class NoRepetido<N> if node to be created already exists.
     * @param   dados   data to create node
     * @return          reference to this graph
     */
    Grafo & inserirNo(const N &dados){
        bool found = false;
        for(const auto &p:nos){
            if(p->info == dados){
                found = true;
                break;
            }
        }
        if(found) throw NoRepetido<N>(dados);
        No<N,A> *ptr = new No<N,A>(dados);
        nos.push_back(ptr);
        return *this;
    }
    /**
     * Inserts edge from 'inicio' to 'fim' with value 'val'.
     * Throws exception of class NoInexistente<N> when either nodes do not exist.
     * Throws exception of class ArestaRepetida<N> when edge already exists.
     * @param   inicio  beginning of edge
     * @param   fim     end of edge
     * @param   val     value of edge
     * @return          reference to this graph
     */
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val){
        int i_inicio = -1;
        for(int i = 0; i < nos.size(); ++i) if(nos[i]->info == inicio ){ i_inicio = i; break; }
        if(i_inicio == -1) throw NoInexistente<N>(inicio);
        int i_fim = -1;
        for(int i = 0; i < nos.size(); ++i) if(nos[i]->info == fim    ){ i_fim    = i; break; }
        if(i_fim    == -1) throw NoInexistente<N>(fim   );
        for(const Aresta<N,A> &a:nos[i_inicio]->arestas) {
            if (a.destino->info == fim)
                throw ArestaRepetida<N>(inicio, fim);
        }
        nos[i_inicio]->arestas.push_back(Aresta<N,A>(nos[i_fim], val));
        return *this;
    }
    /**
     * Deletes edge from graph.
     * Throws exception of class NoInexistente<N> if either of the nodes do not exist.
     * Throws exception of class ArestaInexistente<N> if the edge to remove does not exist.
     * @param   inicio  beginning of edge to delete
     * @param   fim     end of edge to delete
     * @return          reference to this graph
     */
    Grafo & eliminarAresta(const N &inicio, const N &fim){
        int i_inicio = -1;
        for(int i = 0; i < nos.size(); ++i) if(nos[i]->info == inicio ){ i_inicio = i; break; }
        if(i_inicio == -1) throw NoInexistente<N>(inicio);
        int i_fim = -1;
        for(int i = 0; i < nos.size(); ++i) if(nos[i]->info == fim    ){ i_fim    = i; break; }
        if(i_fim    == -1) throw NoInexistente<N>(fim   );
        int i_aresta = -1;
        for(int i = 0; i < nos[i_inicio]->arestas.size(); ++i){
            if(nos[i_inicio]->arestas[i].destino->info == fim)
                i_aresta = i;
        }
        if(i_aresta == -1) throw ArestaInexistente<N>(inicio, fim);
        nos[i_inicio]->arestas.erase(nos[i_inicio]->arestas.begin() + i_aresta);
        return *this;
    }
    /**
     * Gets value of edge.
     * @param   inicio  beginning of edge
     * @param   fim     end of edge
     * @return          reference to value of edge
     */
    A & valorAresta(const N &inicio, const N &fim){
        int i_inicio = -1;
        for(int i = 0; i < nos.size(); ++i) if(nos[i]->info == inicio ){ i_inicio = i; break; }
        if(i_inicio == -1) throw NoInexistente<N>(inicio);
        int i_fim = -1;
        for(int i = 0; i < nos.size(); ++i) if(nos[i]->info == fim    ){ i_fim    = i; break; }
        if(i_fim    == -1) throw NoInexistente<N>(fim   );
        for(Aresta<N,A> &a:nos[i_inicio]->arestas){
            if(a.destino->info == fim)
                return a.valor;
        }
        throw ArestaInexistente<N>(inicio, fim);
    }
    /**
     * Get number of edges.
     * @return  number of edges
     */
    int numArestas(void) const{
        int ret = 0;
        for(const auto &p:nos){
            ret += p->arestas.size();
        }
        return ret;
    }
    /**
     * Get number of nodes.
     * @return  number of nodes
     */
    int numNos(void) const{
        return nos.size();
    }
    /**
     * Print graph nodes and edges.
     * @param os    output stream to print information
     */
    void imprimir(std::ostream &os) const{
        for(const auto &p:nos){
            os << "( " << p->info;
            for(const Aresta<N,A> &q:p->arestas){
                os << "[ " << q.destino->info << " " << q.valor << "] ";
            }
            os << ") ";
        }
    }
};

/**
 * Overload of operator<< for objects of class Grafo<N,A>.
 * @tparam  N   node id type
 * @tparam  A   edge value type
 * @param   out output stream to write to
 * @param   g   graph
 * @return      output stream provided as `out`
 */
template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g){
    g.imprimir(out);
    return out;
}
