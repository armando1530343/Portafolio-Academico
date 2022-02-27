#include <iostream>
#include <stdlib.h>
#include "Lista.h"

using namespace std;

int main()
{
    Lista_enlazada<int> lista;
    lista.insertar(5);
    lista.insertar(4);
    lista.insertar(3);
    lista.insertar(6);
    lista.insertar(8);
    lista.insertar(1);
    lista.mostrar();
    lista.getNth(lista.getLista(),5);
    lista.borrar();
    lista.borrar();
    lista.mostrar();
    lista.getNth(lista.getLista(),5);
}
