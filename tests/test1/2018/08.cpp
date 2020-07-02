#include <iostream>
using namespace std;

template <class T> class Auto{};
template <class T> class AutoOne: public Auto<T>{};

int main(){
    Auto<string> a= AutoOne<string>();
    //AutoOne<string> b = Auto<string>();
    return 0;
}
