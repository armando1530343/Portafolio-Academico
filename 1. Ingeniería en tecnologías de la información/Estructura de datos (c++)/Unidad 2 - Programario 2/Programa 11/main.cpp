#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{
    Lista<int> lista;
    lista.push(3);
    lista.push(4);
    lista.push(1);
    lista.push(7);
    lista.push(3);
    lista.push(7);
    lista.RemoveDuplicates();
}
