#include <iostream>
#include "Lista.h"
using namespace std;

int main()
{
    Lista<int> lista;
    lista.push(3);
    lista.push(8);
    lista.push(2);
    lista.push(9);
    lista.push(1);
    lista.mostrar();
    lista.InsertSort(lista.getLista());
}
