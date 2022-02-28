#include "ListaCircular.h"
#include <iostream>

using namespace std;

ListaCircular::ListaCircular(){
	numero_nodos = 0;
	lista = NULL;
	nodo_final = NULL;
}
ListaCircular::~ListaCircular(){}

void ListaCircular::Visualizar(){
	NodoCircular *lista_aux = lista;
	for(int i = 0; i < numero_nodos; i++){
		cout << "|" << lista_aux->getDato() << "|";
		lista_aux = lista_aux->getSig();
	}
	cout << endl;
}

void ListaCircular::InsertarAlInicio(int dato){
	if(numero_nodos == 0){
		lista = new NodoCircular();
		lista->setDato(dato);
		nodo_final = lista;

	}
	else{
		NodoCircular *nuevo = new NodoCircular();
		nuevo->setDato(dato);
		nuevo->setSig(lista);
		lista = nuevo;
	}
	numero_nodos = numero_nodos + 1;
	nodo_final->setSig(lista);
}
void ListaCircular::InsertarAlFinal(int dato){

	if(numero_nodos == 0){
		lista = new NodoCircular();
		lista->setDato(dato);
		nodo_final = lista;
	}
	else{
		nodo_final->setSig(new NodoCircular());
		nodo_final = nodo_final->getSig();
		nodo_final->setDato(dato);
	}
	numero_nodos = numero_nodos + 1;
	nodo_final->setSig(lista);

}

void ListaCircular::InsertarInLista(int dato){
	if(numero_nodos == 0){
		lista = new NodoCircular();
		lista->setDato(dato);
		nodo_final = lista;
	}
	else{
		NodoCircular *lista_aux = lista;
		for(int i = 0; i < (numero_nodos/2); i++){
			if(i == (numero_nodos/2)-1)
				break;
			lista_aux = lista_aux->getSig();
		}

		NodoCircular *aux = lista_aux->getSig();
		lista_aux->setSig(new NodoCircular());
		lista_aux->getSig()->setDato(dato);
		lista_aux->getSig()->setSig(aux);
	}


	numero_nodos = numero_nodos + 1;
	nodo_final->setSig(lista);
}

void ListaCircular::CrearListaOrdenada(){
	NodoCircular *lista_aux1 = lista;
	NodoCircular *lista_aux2;
	for(int i = 0; i < numero_nodos; i++){		
		lista_aux2 = lista;
		for(int j = 0; j < numero_nodos; j++){			
			if(lista_aux1->getDato() < lista_aux2->getDato()){
				int aux = lista_aux1->getDato();
				lista_aux1->setDato(lista_aux2->getDato());
				lista_aux2->setDato(aux);
			}
			lista_aux2 = lista_aux2->getSig();
		}
		lista_aux1 = lista_aux1->getSig();
	}
}

void ListaCircular::Eliminar(int posicion){
	if(posicion == 0){
		lista = lista->getSig();
		nodo_final->setSig(lista);
		numero_nodos --;
	}
	else if(posicion < numero_nodos){
		NodoCircular *buscar = ListaCircular::Buscar(posicion);
		buscar->setSig(buscar->getSig()->getSig());
		numero_nodos --;
	}
	
}

NodoCircular* ListaCircular::Buscar(int posicion){
	NodoCircular *busca = NULL;
	if(posicion > 0 && posicion < numero_nodos){
		posicion--;
		busca = lista;
		for(int i = 0; i < posicion; i++)			
			busca = busca->getSig();

	}
	return busca;
}