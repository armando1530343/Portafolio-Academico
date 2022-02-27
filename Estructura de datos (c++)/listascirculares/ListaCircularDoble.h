#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "NodoCircularDoble.h"

using namespace std;

class ListaCircularDoble
{
	public:
        ListaCircularDoble();
        virtual ~ListaCircularDoble();
        void CrearListaOrdenada();
        void InsertarAlInicio(int);
        void InsertarAlFinal(int);
        void InsertarInLista(int);
        NodoCircularDoble* Buscar(int);
        void Eliminar(int);
        void Visualizar();

    private:		
		int numero_nodos;
		NodoCircularDoble *lista;
		NodoCircularDoble *nodo_final;
};

#endif // LISTA_CIRCULAR_DOBLE_H
