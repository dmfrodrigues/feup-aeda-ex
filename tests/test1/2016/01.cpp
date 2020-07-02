#include <bits/stdc++.h>
using namespace std;

class Pessoa{
public:
    virtual void test_virtual() final{}
};

class Estudante: public Pessoa{
public:
    virtual void test_virtual(){}
};

int main(){
    Pessoa p;
    Estudante e;
    return 0;
}
