#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "NodoCircular.h"
using namespace std;

/*struct ListaSimple{
	int dato;
	ListaSimple *nodo_sig = NULL;
};*/

class ListaCircular
{
    public:
        ListaCircular();
        virtual ~ListaCircular();
        void CrearListaOrdenada();
        void InsertarAlInicio(int);
        void InsertarAlFinal(int);
        void InsertarInLista(int);
        NodoCircular* Buscar(int);
        void Eliminar(int);
        void Visualizar();
	
	private:		

		int numero_nodos;
		NodoCircular *lista;
		NodoCircular *nodo_final;        
};

#endif // LISTACIRCULAR_H
