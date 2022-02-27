#include "ListaCircular.h"
#include "ListaCircular.cpp"
#include "ListaCircularDoble.h"
#include "ListaCircularDoble.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	ListaCircular l1 = ListaCircular();
	l1.InsertarAlInicio(3);
	l1.InsertarAlInicio(19);
	l1.InsertarAlFinal(78);
	l1.Visualizar();
	l1.CrearListaOrdenada();
	l1.Visualizar();

	cout << endl;

	ListaCircularDoble l2 = ListaCircularDoble();
	l2.InsertarAlInicio(5);
	l2.InsertarAlFinal(87);
	l2.InsertarAlInicio(90);
	l2.InsertarInLista(41);
	l2.Visualizar();
	l2.CrearListaOrdenada();
	l2.Visualizar();

	
    return 0;
}