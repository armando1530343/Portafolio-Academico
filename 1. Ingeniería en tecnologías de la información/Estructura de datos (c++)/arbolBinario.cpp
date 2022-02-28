#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

template <class Tipoelemento>

class Nodo{
	
	protected:
		Tipoelemento dato;
		Nodo *izdo;
		Nodo *dcho;
	
	public:
		Nodo(Tipoelemento valor){
			dato = valor;
			izdo = dcho = NULL;
		}
		Nodo(Nodo* ramaIzdo, Tipoelemento valor, Nodo* ramaDcho){
			dato = valor;
			izdo = ramaIzdo;
			dcho = ramaDcho;
		}
		Tipoelemento valorNodo(){ return dato; }
		Nodo* subArbolIzdo(){ return izdo; }
		Nodo* subArbolDcho(){ return dcho; }
		void nuevoValor(Tipoelemento d){ dato = d; }
		void ramaIzdo(Nodo* n){ izdo = n; }
		void ramaDcho(Nodo* n){ dcho = n; }
};

template <class Tipoelemento>

class ArbolBinario{
	
	protected:
		Nodo<Tipoelemento> *raiz;

	public:
		ArbolBinario(){
			raiz = NULL;
		}

		ArbolBinario(Nodo<Tipoelemento> *r){ raiz = r;}

		Nodo<Tipoelemento> raizArbol(){
			if(raiz)
				return *raiz;
			else
				throw " arbol vacio";
		}

		bool esVacio(){	return raiz == NULL;}

		Nodo<Tipoelemento> * hijoIzdo(){
			if(raiz)
				return raiz->subArbolIzdo();
			else
				throw " arbol vacio";
		}

		Nodo<Tipoelemento> * hijoDcho(){
			if(raiz)
				return raiz->subArbolDcho();
			else
				throw " arbol vacio";
		}

		void Praiz( Nodo<Tipoelemento> *r){ raiz = r;}

		Nodo<Tipoelemento> * Oraiz(){	return raiz;}

		Nodo<Tipoelemento>* nuevoArbol(Nodo<Tipoelemento>* ramaIzqda, Tipoelemento dato, Nodo<Tipoelemento>* ramaDrcha){
			return new Nodo<Tipoelemento>(ramaIzqda, dato, ramaDrcha);
		}
};

int main(int argc, char const *argv[])
{
	/* code */
	ArbolBinario<string> a1,a2,a3, a4,a;
    Nodo<string> * n1,*n2,*n3, *n4;
    n1 = a1.nuevoArbol(NULL,"Rigoberto",NULL);
    n2 = a2.nuevoArbol(NULL,"Emmanuel",NULL);
    n3 = a3.nuevoArbol(n1,"Eduardo",n2);
    n1 = a1.nuevoArbol(NULL,"Sofia",NULL);
    n2 = a2.nuevoArbol(NULL,"Esaú",NULL);
    n4 = a4.nuevoArbol(n1,"Alejandra",n2);
    n1 = a1.nuevoArbol(n3,"Max",n4);
    a.Praiz(n1);

    //se imprime el arbol desde la raiz 'a'
    cout << "Raiz del arbol: " << a.Oraiz()->valorNodo() << endl;
    cout << endl;
    
    //subarbol izquierdo
    cout << "\tRaiz subarbol izquierdo: " << a.Oraiz()->subArbolIzdo()->valorNodo() << endl;
    cout << endl;
    //hijo izquierdo
    cout << "\t\tHijo izquierdo: " << a.Oraiz()->subArbolIzdo()->subArbolIzdo()->valorNodo() << endl;
    //hijo derecho
    cout << "\t\tHijo derecho: " << a.Oraiz()->subArbolIzdo()->subArbolDcho()->valorNodo() << endl;
    cout << endl;
    
    //subarbol derecho
    cout << "\tRaiz subarbol izquierdo: " << a.Oraiz()->subArbolDcho()->valorNodo() << endl;
    cout << endl;
    //hijo izquierdo
    cout << "\t\tHijo izquierdo: " << a.Oraiz()->subArbolDcho()->subArbolIzdo()->valorNodo() << endl;
    //hijo derecho
    cout << "\t\tHijo derecho: " << a.Oraiz()->subArbolDcho()->subArbolDcho()->valorNodo() << endl;
    

	return 0;
}