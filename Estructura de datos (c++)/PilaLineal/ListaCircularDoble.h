#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct ListaDoble{
	int dato;
	ListaDoble *nodo_sig = NULL;
	ListaDoble *nodo_ant = NULL;
};

class ListaCircularDoble
{
	public:
        ListaCircularDoble();
        virtual ~ListaCircularDoble();
        void CrearListaOrdenada();
        void InsertarAlInicio(int);
        void InsertarAlFinal(int);
        void InsertarInLista(int);
        ListaDoble* Buscar(int);
        void Eliminar(int);
        void Visualizar();

    private:		
		int numero_nodos;
		ListaDoble *lista;
		ListaDoble *nodo_final;
};

#endif // LISTA_CIRCULAR_DOBLE_H
