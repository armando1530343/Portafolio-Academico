#include <iostream>
#include "Lista.h"
using namespace std;

int main()
{
    Lista<int> lista;
    Lista<int> lista2;
    int total;

    lista.push(1);
    lista.push(2);
    lista.push(3);
    cout<<endl;
    lista2.push(4);
    lista2.push(5);
    lista2.push(6);
    lista2.push(9);

    total = lista.totalNodos()+lista2.totalNodos();
    cout<<total<<endl;

    lista.ShuffleMerge(lista2.getLista(), total);

}
