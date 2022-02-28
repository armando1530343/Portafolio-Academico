#ifndef PILA_H
#define PILA_H
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Pila
{
	private:
		struct _Pila{
			int valor;
			_Pila *sig = NULL;
			_Pila *ant = NULL;
		};

		_Pila *pila;
		_Pila *tope;
		int elementos;

    public:
        Pila();
        virtual ~Pila();

        void apilar(int);
        void desapilar();
        void vista();
};

#endif // PILA_H
