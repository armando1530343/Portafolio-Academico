#ifndef NODOENLAZADO_LISTA_H
#define NODOENLAZADO_LISTA_H
typedef int Dato;
#include <iostream>
#include "Nodo.h"

using namespace std;

class Lista
{
    protected:
        Nodo* primero;
    public:
        Lista(){
            primero=NULL;
        }
        void crearLista();
        void visualizar();
        void insertarInicioLista(int d);
        void insertarFinalLista(int d);
        void insertarMedioLista(Dato anterior, Dato entrada);
        void eliminar(Dato x);
        void insertarOrden(Dato x);
        void crearListaordenada();
        Nodo* buscarLista(int d);
};

void Lista::eliminar(Dato x){
    
    Nodo* n;
    Nodo* Buscando;
    bool band= false;
    
    Buscando = buscarLista(x);
    n=primero;
    
    if(primero==Buscando){
        primero=primero->enlaceNodo();
        Buscando=NULL;
    }
    else if(Buscando!=NULL){
        
        while(n!=NULL && !band){
            
            if(n->enlaceNodo()==Buscando){
                band=true;
            }
            else{
                n=n->enlaceNodo();
            }

        }
        n->ponerEnlace(Buscando ->enlaceNodo());
        Buscando=NULL;
    }
}
void Lista::crearListaordenada(){
     int x;
     bool band;
    primero = 0;
    cout<<"Termina con -1"<<endl;
    do{
        cin>>x;
        if (x != -1){
            if(band == false){
                primero = new Nodo(x,primero);
                band=true;
            }else{
                insertarOrden(x);
            }
        }
    }while(x != -1);
}
void Lista::crearLista(){
    int x;
    primero = 0;
    cout<<"Termina con -1"<<endl;
    do{
        cin>>x;
        if (x != -1)
        {
            primero = new Nodo(x,primero);
        }
    }while(x != -1);
}
void Lista::insertarInicioLista(int d){
    primero = new Nodo(d,primero);
}

void Lista::insertarFinalLista(Dato entrada){
    Nodo* nuevo;
    Nodo* n;

    nuevo = new Nodo(entrada);
    n = primero;
    while(n -> enlaceNodo() != NULL){
        n = n -> enlaceNodo();
    }
    n -> ponerEnlace(nuevo);
}

void Lista::insertarMedioLista(Dato anterior, Dato entrada){

    Nodo* nuevo;
    Nodo* ant;

    ant = buscarLista(anterior);

    if(ant != NULL){
        nuevo = new Nodo(entrada);
        nuevo -> ponerEnlace(ant->enlaceNodo());
        ant ->ponerEnlace(nuevo);
    }
}

void Lista::visualizar(){
    Nodo* n;
    n = primero;
    while(n != NULL){
        cout<<n->datoNodo() << ",";
        n = n->enlaceNodo();
    }
    cout<<endl;

}
void Lista::insertarOrden(Dato x) {

    Nodo* n;

    n = new Nodo(x);

    if(primero == NULL){
        primero = n;
    } else if (x < primero -> datoNodo()){
        n -> ponerEnlace(primero);
        primero = n;
    } else {
        Nodo *anterior, *p;
        anterior = p = primero;
        while ((p -> enlaceNodo() != NULL) && (x > p -> datoNodo())){
            anterior = p;
            p = p -> enlaceNodo();
        }
        if(x > p -> datoNodo()){
            anterior = p;
            p = p->enlaceNodo();
        }
        n -> ponerEnlace(anterior -> enlaceNodo());
        anterior -> ponerEnlace(n);

    }
}

Nodo* Lista::buscarLista(int d){

    Nodo* n = primero;

    while(n != NULL){
        if (n -> datoNodo() == d) {
            return n;
        } else {
            n = n -> enlaceNodo();
        }
    }
}


#endif //NODOENLAZADO_LISTA_H
