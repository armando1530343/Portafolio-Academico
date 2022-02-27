#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{
    Lista<int> lista;
    lista.push(3);
    lista.push(6);
    lista.push(4);
    lista.push(3);
    lista.push(8);
    lista.push(8);
    lista.push(8);
    lista.ccount(8);
    lista.ccount(3);
}
