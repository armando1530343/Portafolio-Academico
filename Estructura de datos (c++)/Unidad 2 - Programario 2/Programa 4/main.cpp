#include <iostream>
#include "Lista.h"
using namespace std;

int main()
{
    Lista<int> lista("PILA");
    lista.push(3);
    lista.push(7);
    lista.push(4);
    lista.push(8);
    lista.pop();
    lista.pop();
    lista.push(9);
    lista=Lista<int>("COLA");
    lista.push(3);
    lista.push(7);
    lista.push(4);
    lista.push(8);
    lista.pop();
    lista.pop();
    lista.push(9);
}
