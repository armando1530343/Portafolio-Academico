//
// Created by broyi on 26/02/2019.
//

#ifndef NODOENLAZADO_NODODOBLE_H
#define NODOENLAZADO_NODODOBLE_H
#include <iostream>
typedef int Dato;
class NodoDoble{
protected:
    Dato dato;
    NodoDoble* izquierda;
    NodoDoble* derecha;
public:
    NodoDoble(Dato t){
        dato = t;
        izquierda = derecha = NULL;
    }
    NodoDoble(Dato t,NodoDoble* izquierda,NodoDoble* derecha){
        dato = t;
        izquierda = izquierda;
        derecha = derecha;
    }
    Dato datoNodo() const{
        return dato;
    }

    NodoDoble* izquierdaNodo() const{
        return izquierda;
    }
    NodoDoble* derechaNodo()const{
        return derecha;
    }

    void ponerIzquierda(NodoDoble* a){
        izquierda = a;
    }
    void ponerDerecha(NodoDoble* a){
        derecha = a;
    }
};
#endif //NODOENLAZADO_NODODOBLE_H
