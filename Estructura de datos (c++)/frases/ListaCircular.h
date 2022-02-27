#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class ListaCircular{
	private:

		ListaCircular *nodo_sig;
		ListaCircular *nodo_ant;
		char *palabra;
		char *frase_completa;

	public:
		ListaCircular(){
			nodo_sig = NULL;
			nodo_ant = NULL;
			palabra = new char[15];
			frase_completa = new char[100];
		}
		void setPalabra(char *palabra){strcpy(this->palabra, palabra);}
		char* getPalabra(){return palabra;}

		void setFrase(char *frase_completa){strcat(frase_completa, palabra);}
		char* getFrase(){return frase_completa;}

		void setSiguiente(ListaCircular *sig){nodo_sig = sig;}
		ListaCircular *getSiguiente(){return nodo_sig;}

		void setAnterior(ListaCircular *ant){nodo_ant= ant;}
		ListaCircular *getAnterior(){return nodo_ant;}
};