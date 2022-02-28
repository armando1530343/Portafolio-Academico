//
// Created by broyi on 26/02/2019.
//

#ifndef NODOENLAZADO_NODO_H
#define NODOENLAZADO_NODO_H

typedef int Dato;
#include <iostream>

class Nodo
{
protected:
    Dato dato;
    Nodo* enlace;
public:
    Nodo(Dato t){
        dato = t;
        enlace = 0;//0 es el puntero NULL en C++
    }
    Nodo(Dato p, Nodo* n){
        dato = p;
        enlace = n;
    }
    Dato datoNodo()const{
        return dato;
    }
    Nodo* enlaceNodo()const{
        return enlace;
    }
    void ponerEnlace(Nodo* sgte){
        enlace = sgte;
    }
};

#endif //NODOENLAZADO_NODO_H
