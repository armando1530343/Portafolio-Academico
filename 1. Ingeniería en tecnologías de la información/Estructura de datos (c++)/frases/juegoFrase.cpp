#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "ListaCircular.h"

using namespace std;

struct Frase{
	char palabra[20];
	char frase_actual[500];
	Frase *siguiente = NULL;
	Frase *anterior = NULL;
};


 
int main(int argc, char const *argv[])
{
	int n;
	int num_palabras = 0;
	int respuesta;
	int posicion_nombre = 0;
	int i;
	string *nombres;

	cout << "Numero nombres: ";
	cin >> n;

	nombres = new string[n];
	

	for(i = 0; i < n; i++){
		cout << "Nombre Jugador: ";
		cin >> nombres[i];
	}

	

	ListaCircular *frase = NULL;
	ListaCircular *ultima_palabra = NULL;

	do{
		system("cls");
		cout << "<< JUEGO DE FRASE >>" << endl;
		cout << "posicion_nombre de " << nombres[posicion_nombre] << endl;

		if(num_palabras == 0){	
			cout << "\tIngresa Palabra: ";		
			frase = new ListaCircular();
			char *palabra = new char[15];
			scanf(" %[^\n]", palabra);
			frase->setPalabra(palabra);
			strcat(frase->frase_actual, frase->getPalabra());
			ultima_palabra = frase;
		}
		else{
			char frase_jugador[500];
			cout << "\tIngresa la frase actual: "; 
			scanf(" %[^\n]", frase_jugador);

			if(strcmp(frase_jugador, ultima_palabra->frase_actual) == 0){
				cout << "\tIngresa Palabra: ";
				//se crea un nuevo nodo
				ultima_palabra->siguiente = new ListaCircular();
				//se apunta al nodo anterior del nuevo nodo
				ultima_palabra->siguiente->anterior = ultima_palabra;
				ultima_palabra = ultima_palabra->siguiente;
				scanf(" %[^\n]", ultima_palabra->getPalabra());
				strcpy(ultima_palabra->frase_actual, ultima_palabra->anterior->frase_actual);
				strcat(ultima_palabra->frase_actual, " ");
				strcat(ultima_palabra->frase_actual, ultima_palabra->getPalabra());
			}
			else{
				cout << "\n" << nombres[posicion_nombre] << " a perdido" << endl;

				for(i = posicion_nombre; i < n-1; i++){
					nombres[i] = nombres[i+1];
				}

				n--;
				posicion_nombre--;
			}
		}

		posicion_nombre++;

		if(posicion_nombre >= n)
			posicion_nombre = 0;

		num_palabras++;

		if(n > 1){
			cout << "\nTerminar juego? (1.SI 2.NO):";
			cin >> respuesta;
		}
		else
			cout << "\n" << nombres[posicion_nombre] << " es el GANADOR !!!" << endl;
	}
	while(respuesta == 2 && n > 1);
	return 0;
}

/*
Integrantes:
Silvino Moya García 1430554
Brian Alejandro Mireles Ortiz 1630273
Rigoberto Beas Carrizales 1610005
*/