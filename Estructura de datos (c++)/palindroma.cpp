#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

struct Pila{
	char c;
	Pila *sig = NULL;
	Pila *ant = NULL;
};

int main(int argc, char const *argv[])
{

	//se declara la variable que almacena la palabra
	string palabra;

	//se ingresa la palabra
	cout << "Ingresa palabra: ";
	
	//se lee la palabra a la variable
	cin >> palabra;
	
	//tamaño de la palabra
	int tam = palabra.size();
	
	//se crea una pila con el tamaño de la palabra ingresada
	//char *pila = new char[tam];

	//se crea un puntero de Pila
	Pila *pila = NULL;
	Pila *fin = NULL;


	//se recorre la variable string y se almacenan los caracteres en la pila
	for(int i = 0; i < tam; i++){
		if(i == 0){
			pila = new Pila();
			pila->c = palabra[i];
			fin = pila;
		}
		else{
			fin->sig = new Pila();
			fin->sig->ant = fin;
			fin = fin->sig;
			fin->c = palabra[i];
		}

	}

	//verificacion de palabra palindroma
	bool palindroma = true;

	//se extraen los caracteres de la pila
	for(int i = 0; i < tam/2; i++){

		//se comparan el primer caracter con el ultimo de la pila
		if(pila->c != fin->c)
			//si los caracteres son diferentes palindroma = FLASE, sino permanece en TRUE
			palindroma = false;

		//se modifica el inicio de la pila
		pila = pila->sig;
		//se modifica el final de la pila
		fin = fin->ant;
	}

	//se verifica que la pila quede vacia
	if(pila != NULL)
		pila = NULL;

	//se comenta el resultado
	if(palindroma)
		cout << "Es palindroma" << endl;
	else
		cout << "No es palindroma" << endl;

	cout << endl;
	
	return 0;
}