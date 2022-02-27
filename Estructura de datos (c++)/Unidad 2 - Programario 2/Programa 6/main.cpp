#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{
    Lista<int> lista;
    lista.SortInsert(7);
    lista.SortInsert(5);
    lista.SortInsert(6);
    lista.SortInsert(4);
    lista.SortInsert(3);
    lista.SortInsert(2);
    lista.SortInsert(10);
}
