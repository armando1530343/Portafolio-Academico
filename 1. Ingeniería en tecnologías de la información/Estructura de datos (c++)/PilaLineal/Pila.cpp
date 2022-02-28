#include "Pila.h"
#include <string.h>

using namespace std;

Pila::Pila(){
	pila = NULL;
	tope = NULL;
	elementos = 0;
}
Pila::~Pila(){}

void Pila::apilar(int valor){

	if(elementos == 0){
		//si no hay elementos se inicializa el apuntador de la pila
		pila = new _Pila();
		pila->valor = valor;
		//se asigna el valor del tope inicial
		tope = pila;
	}
	else{
		//mientras hay elementos en la pila, se hace instancia a partir del 'tope' de la pila
		//sin afectar la raiz que es 'pila'
		tope->sig = new _Pila();
		//se hace referencia al valor anterior del nodo de la pila actual
		tope->sig->ant = tope;
		//el tope apunta al ultimo nodo de la pila
		tope = tope->sig;
		//se asigna el valor
		tope->valor = valor;
	}

	//se incrementa el numero de elementos al apilar
	elementos ++;
}

void Pila::desapilar(){
	//el tope de la pila se recorre al valor anterior
	tope = tope->ant;
	//el nodo siguiente del tope se elimina
	tope->sig = NULL;
}

void Pila::vista(){
	_Pila *ver = pila;
	cout << "Pila: ";
	while(ver != NULL){
		cout << "|" << ver->valor << "|";
		ver = ver->sig;
	}
	cout << endl;
}
