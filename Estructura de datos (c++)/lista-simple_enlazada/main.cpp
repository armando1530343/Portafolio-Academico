#include <iostream>
#include "Lista.h"
#include "ListaDoble.h"

using namespace std;


int main(int argc, char const *argv[]) {
	
    Lista simple = Lista();
    Lista ordenada = Lista();
    ListaDoble doble = ListaDoble();

    cout << "\n\t>>LISTA SIMPLE" << endl;
    simple.crearLista();
    simple.visualizar();
    cout << "Inserta inicio: valor 9" << endl;
    simple.insertarInicioLista(9);
    simple.visualizar();
    cout << "Inserta final: valor 7" << endl;
    simple.insertarFinalLista(7);
    simple.visualizar();
    cout << "Eliminar: valor 7" << endl;
    simple.eliminar(7);
    simple.visualizar();

    cout << "\n\t>>LISTA ORDENADA" << endl;

    ordenada.crearListaordenada();
    ordenada.visualizar();
    cout << "Inserta inicio: valor 3" << endl;
    ordenada.insertarInicioLista(3);
    ordenada.visualizar();
    cout << "Inserta final: valor 2" << endl;
    ordenada.insertarFinalLista(2);
    ordenada.visualizar();
    cout << "Eliminar: valor 3" << endl;
    ordenada.eliminar(3);
    ordenada.visualizar();

    cout << "\n\t>>LISTA DOBLE ENLAZADA" << endl;

    doble.crearLista();
    doble.visualizar();
    cout << "Inserta inicio: valor 23" << endl;
    doble.insertarInicioLista(23);
    doble.visualizar();
    cout << "Eliminar: valor 23" << endl;
    doble.eliminar(23);
    doble.visualizar();

}