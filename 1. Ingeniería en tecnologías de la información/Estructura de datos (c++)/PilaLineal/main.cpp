#include <iostream>
#include "Pila.cpp"
#include "Pila.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	Pila pila = Pila();
	
	//se apilan 4 elementos
	pila.apilar(5);
	pila.apilar(4);
	pila.apilar(8);
	pila.apilar(9);
	pila.vista();

	//se desapila un elemento
	pila.desapilar();
	pila.vista();

	//se apilan 3 elementos mas
	pila.apilar(1);
	pila.apilar(3);
	pila.apilar(7);
	pila.vista();

	//se desapilan 2 elemento
	pila.desapilar();
	pila.desapilar();
	pila.vista();

	
    return 0;
}