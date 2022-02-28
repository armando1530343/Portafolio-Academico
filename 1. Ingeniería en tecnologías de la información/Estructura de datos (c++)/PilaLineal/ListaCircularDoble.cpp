#include "ListaCircularDoble.h"
#include <iostream>

using namespace std;

ListaCircularDoble::ListaCircularDoble(){
	lista = NULL;
	nodo_final = NULL;
	numero_nodos = 0;
}
ListaCircularDoble::~ListaCircularDoble(){}

void ListaCircularDoble::CrearListaOrdenada(){
	ListaDoble *lista_aux1 = lista;

	for(int i = 0; i < numero_nodos; i++){

		ListaDoble *lista_aux2 = lista;

		for(int j = 0; j < numero_nodos; j++){
			
			if(lista_aux1->dato < lista_aux2->dato){
				int aux = lista_aux1->dato;
				lista_aux1->dato = lista_aux2->dato;
				lista_aux2->dato = aux;
			}
			lista_aux2 = lista_aux2->nodo_sig;
		}
		lista_aux1 = lista_aux1->nodo_sig;
	}
}

void ListaCircularDoble::InsertarAlInicio(int dato){
	if(numero_nodos == 0){
		lista = new ListaDoble();
		lista->dato = dato;
		nodo_final = lista;
	}
	else{

		ListaDoble *nuevo = new ListaDoble();
		nuevo->dato = dato;
		nuevo->nodo_sig = lista;
		nuevo->nodo_sig->nodo_ant = nuevo;
		lista = nuevo;
	}
	nodo_final->nodo_sig = lista;
	lista->nodo_ant = nodo_final;
	numero_nodos++;
}
void ListaCircularDoble::InsertarAlFinal(int dato){

	if(numero_nodos == 0){
		lista = new ListaDoble();
		lista->dato = dato;
		nodo_final = lista;
	}
	else{
		nodo_final->nodo_sig = new ListaDoble();
		nodo_final->nodo_sig->nodo_ant = nodo_final;
		nodo_final = nodo_final->nodo_sig;
		nodo_final->dato = dato;
	}

	nodo_final->nodo_sig = lista;
	lista->nodo_ant = nodo_final;

	numero_nodos++;

}

void ListaCircularDoble::InsertarInLista(int dato){
	if(numero_nodos == 0){
		lista = new ListaDoble();
		lista->dato = dato;
		nodo_final = lista;
	}
	else{
		ListaDoble *lista_aux = lista;
		for(int i = 0; i < (numero_nodos/2); i++){
			if(i == (numero_nodos/2)-1)
				break;
			lista_aux = lista_aux->nodo_sig;
		}
		ListaDoble *aux = lista_aux->nodo_sig;
		lista_aux->nodo_sig = new ListaDoble();
		lista_aux->nodo_sig->nodo_ant = lista_aux;
		lista_aux->nodo_sig->dato = dato;
		lista_aux->nodo_sig->nodo_sig = aux;
	}

	nodo_final->nodo_sig = lista;
	lista->nodo_ant = nodo_final;

	numero_nodos++;
}

ListaDoble* ListaCircularDoble::Buscar(int indice){
	ListaDoble *busca = NULL;
	if(indice > 0 && indice < numero_nodos){
		indice--;
		busca = lista;
		for(int i = 0; i < indice; i++)			
			busca = busca->nodo_sig;

	}
	return busca;
}

void ListaCircularDoble::Eliminar(int indice){
	ListaDoble *e;
	if(indice == 0){
		e = lista;
		lista = lista->nodo_sig;
		numero_nodos --;
	}
	else if(indice < numero_nodos){
		ListaDoble *buscar = this->Buscar(indice);
		e = buscar->nodo_sig;
		buscar->nodo_sig = buscar->nodo_sig->nodo_sig;
		buscar->nodo_sig->nodo_ant = buscar;
		numero_nodos --;
	}

	delete e;
	
}


void ListaCircularDoble::Visualizar(){
	ListaDoble *lista_aux = lista;
	for(int i = 0; i < numero_nodos; i++){
		cout << "|" << lista_aux->dato << "|";
		lista_aux = lista_aux->nodo_sig;
	}
	cout << endl;
}