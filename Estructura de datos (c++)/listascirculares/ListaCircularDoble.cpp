#include "ListaCircularDoble.h"
#include <iostream>

using namespace std;

ListaCircularDoble::ListaCircularDoble(){
	numero_nodos = 0;
	lista = NULL;
	nodo_final = NULL;
}
ListaCircularDoble::~ListaCircularDoble(){}

void ListaCircularDoble::Visualizar(){
	NodoCircularDoble *lista_aux = lista;
	for(int i = 0; i < numero_nodos; i++){
		cout << "|" << lista_aux->getDato() << "|";
		lista_aux = lista_aux->getSig();
	}
	cout << endl;
}

void ListaCircularDoble::InsertarAlInicio(int dato){
	if(numero_nodos == 0){
		lista = new NodoCircularDoble();
		lista->setDato(dato);
		nodo_final = lista;

	}
	else{
		NodoCircularDoble *nuevo = new NodoCircularDoble();
		nuevo->setDato(dato);
		nuevo->setSig(lista);
		nuevo->getSig()->setAnt(nuevo);
		lista = nuevo;
	}
	numero_nodos = numero_nodos + 1;
	nodo_final->setSig(lista);
}
void ListaCircularDoble::InsertarAlFinal(int dato){

	if(numero_nodos == 0){
		lista = new NodoCircularDoble();
		lista->setDato(dato);
		nodo_final = lista;
	}
	else{
		nodo_final->setSig(new NodoCircularDoble());
		nodo_final->getSig()->setAnt(nodo_final);
		nodo_final = nodo_final->getSig();
		nodo_final->setDato(dato);
	}
	numero_nodos = numero_nodos + 1;
	nodo_final->setSig(lista);

}

void ListaCircularDoble::InsertarInLista(int dato){
	if(numero_nodos == 0){
		lista = new NodoCircularDoble();
		lista->setDato(dato);
		nodo_final = lista;
	}
	else{
		NodoCircularDoble *lista_aux = lista;
		for(int i = 0; i < (numero_nodos/2); i++){
			if(i == (numero_nodos/2)-1)
				break;
			lista_aux = lista_aux->getSig();
		}

		NodoCircularDoble *aux = lista_aux->getSig();
		lista_aux->setSig(new NodoCircularDoble());
		lista_aux->getSig()->setAnt(lista_aux);
		lista_aux->getSig()->setDato(dato);
		lista_aux->getSig()->setSig(aux);
	}


	numero_nodos = numero_nodos + 1;
	nodo_final->setSig(lista);
}

void ListaCircularDoble::CrearListaOrdenada(){
	NodoCircularDoble *lista_aux1 = lista;
	NodoCircularDoble *lista_aux2;
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

void ListaCircularDoble::Eliminar(int posicion){
	if(posicion == 0){
		lista = lista->getSig();
		nodo_final->setSig(lista);
		numero_nodos --;
	}
	else if(posicion < numero_nodos){
		NodoCircularDoble *buscar = ListaCircularDoble::Buscar(posicion);
		buscar->setSig(buscar->getSig()->getSig());
		buscar->getSig()->setAnt(buscar);
		numero_nodos --;
	}
}

NodoCircularDoble* ListaCircularDoble::Buscar(int posicion){
	NodoCircularDoble *busca = NULL;
	if(posicion > 0 && posicion < numero_nodos){
		posicion--;
		busca = lista;
		for(int i = 0; i < posicion; i++)			
			busca = busca->getSig();

	}
	return busca;
}