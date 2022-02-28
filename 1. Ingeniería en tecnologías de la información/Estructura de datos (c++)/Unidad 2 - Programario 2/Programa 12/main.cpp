#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{
    Lista<int> lista;
    Lista<int> lista2;

    lista.push(4);
    lista.push(3);
    lista.push(7);
    lista.push(8);

    lista2.push(12);
    lista2.push(1);
    lista2.push(9);
    lista2.push(2);

    lista.mostrar();
    lista2.mostrar();

    lista.MoveNode(lista2.getLista());
    lista.mostrar();
    lista2.mostrar();
}
