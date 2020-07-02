#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { significado=sig; }
       bool operator < (const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};

// a alterar
class PalavraNaoExiste{
private:
    PalavraSignificado p1, p2;
public:
    PalavraNaoExiste(PalavraSignificado p1, PalavraSignificado p2):p1(p1),p2(p2){}
	string getPalavraAntes() const { return p1.getPalavra(); }
	string getSignificadoAntes() const { return p1.getSignificado(); }
	string getPalavraApos() const { return p2.getPalavra(); }
	string getSignificadoApos() const { return p2.getSignificado(); }
};


#endif
