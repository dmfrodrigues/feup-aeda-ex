#include <iostream>
using namespace std;

class C{
public:
    static int f1(){ return 1; }
    int f2() const{ return C::f1(); }
};

int main(){
    C c;
    cout << c.f2() << endl;
    return 0;
}
