#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class ListaCircular{
	private:
		ListaCircular *nodo_sig;
		ListaCircular *nodo_ant;
		float x, y;
		double distLocal, distTotal;
		int noCliente;

	public:
		ListaCircular(){
			nodo_sig = NULL;
			nodo_ant = NULL;
			x = 0;
			y = 0;
			distLocal = 0;
			distTotal = 0;
			noCliente = 0;
		}
		void setX(float x){this->x = x;}
		float getX(){return x;}
		
		void setY(float y){this->y = y;}
		float getY(){return y;}

		void setNoCliente(int n){noCliente = n;}
		int getNoCliente(){return noCliente;}

		void setDistLocal(double d){distLocal = d;}
		double getDistLocal(){return distLocal;}

		void setDistTotal(double d){distTotal = d;}
		double getDistTotal(){return distTotal;}

		void setSiguiente(ListaCircular *sig){nodo_sig = sig;}
		ListaCircular *getSiguiente(){return nodo_sig;}

		void setAnterior(ListaCircular *ant){nodo_ant= ant;}
		ListaCircular *getAnterior(){return nodo_ant;}
};
