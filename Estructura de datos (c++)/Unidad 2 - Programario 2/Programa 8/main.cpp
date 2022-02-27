#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{
    Lista<int> lista1;
    Lista<int> lista2;

    lista1.push(1);
    lista1.push(2);
    lista1.push(3);
    lista1.mostrar();

    lista2.push(4);
    lista2.push(5);
    lista2.push(6);
    lista2.mostrar();

    lista1.Append(lista2.getLista());
    lista2.Append(lista1.getLista());
}
