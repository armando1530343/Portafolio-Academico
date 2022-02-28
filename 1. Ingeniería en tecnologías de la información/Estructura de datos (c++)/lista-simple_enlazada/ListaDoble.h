#ifndef NODOENLAZADO_LISTADOBLE_H
#define NODOENLAZADO_LISTADOBLE_H
typedef int Dato;
#include <iostream>
#include "NodoDoble.h"
class IteradorLista;
class ListaDoble{
protected:
    NodoDoble* primero;
public:
    ListaDoble(){
        primero=NULL;
    }
    void crearLista();
    void visualizar();
    void insertarInicioLista(int d);
    void eliminar(Dato x);
    void insertarOrden(Dato x);
    void crearListaordenada();
    NodoDoble* Ultimo();
    NodoDoble* buscarLista(int d);
};
void ListaDoble::crearLista(){
    Dato x;
    cout <<"Temina con -1";
    do{
        cin >> x;
        if(x!=-1){
            insertarInicioLista(x);
        }
    }while(x!=-1);
}
void ListaDoble::visualizar()
{
    NodoDoble* n;
    int k = 0;
    n = primero;
    while (n != NULL)
    {
        char c;
        k++; c = (k % 15 != 0 ? ' ' : '\n');
        cout << n -> datoNodo() << c;
        n = n -> izquierdaNodo();
    }
}

void ListaDoble::insertarInicioLista(Dato x)
{
    NodoDoble* nuevo;
    nuevo = new NodoDoble(x);
    nuevo -> ponerIzquierda(primero);
    if (primero != NULL )
        primero -> ponerDerecha(nuevo);
    primero = nuevo;
}


NodoDoble* ListaDoble::buscarLista(int x) {

    NodoDoble* n = primero;

    while(n != NULL){
        if (n -> datoNodo() == x) {
            return n;
        } else {
            n = n -> izquierdaNodo();
        }
    }
}

void ListaDoble::eliminar(Dato x){

    NodoDoble* actual;
    bool encontrado = false;
    actual = primero;

    while ((actual != NULL) && (!encontrado))
    {
        encontrado = (actual -> datoNodo() == x);
        if (!encontrado)
            actual = actual -> izquierdaNodo();
    }
    if (actual != NULL)
    {
        if (actual == primero)
        {
            primero = actual -> izquierdaNodo();
            if (actual -> izquierdaNodo() != NULL)
                actual -> izquierdaNodo() -> ponerDerecha(NULL);
        }
        else if (actual -> izquierdaNodo() != NULL) {
            actual -> derechaNodo() -> ponerIzquierda(actual -> izquierdaNodo());
            actual -> izquierdaNodo() -> ponerDerecha(actual -> derechaNodo());
        }
        else
            actual -> derechaNodo() -> ponerIzquierda(NULL);
    }
}

NodoDoble* ListaDoble::Ultimo(){

    NodoDoble* n = primero;

    bool encontrado = false;

    while(!encontrado){
        if( n-> derechaNodo() == NULL){
            encontrado = true;
        } else {
            n = n -> derechaNodo();
        }
    }
    return n;
}

#endif //NODOENLAZADO_LISTADOBLE_H
