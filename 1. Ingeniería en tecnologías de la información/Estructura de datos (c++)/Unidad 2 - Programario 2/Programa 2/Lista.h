#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>

using namespace std;

template <class Tipo>
class Lista_enlazada{
private:
    struct Lista{
        Tipo dato;
        Lista *sig=NULL;
    }*lis,*tope;

public:
    Lista_enlazada();
    void insertar(Tipo);
    void borrar();
    void getNth(Lista*,int);
    void mostrar();
    Lista* getLista(){
        return lis;
    }
};
template <class Tipo>
Lista_enlazada<Tipo>::Lista_enlazada(){
    lis = NULL;
    tope = NULL;
}

template <class Tipo>
void Lista_enlazada<Tipo>::insertar(Tipo n){
    if(lis==NULL){
        lis = new Lista();
        lis->dato = n;
        tope = lis;
    }
    else{
        tope->sig = new Lista();
        tope = tope->sig;
        tope->dato = n;
    }
}
template <class Tipo>
void Lista_enlazada<Tipo>::getNth(Lista *l, int pos){
    int i;
    int existe=1;
    if(l!=NULL){
        for(i=0;i<pos;i++){
            if(i==pos-1)
                cout<<"Posicion "<<pos<<": "<<l->dato<<endl;
            l = l->sig;
            if(l==NULL){
                existe=0;
                break;
            }
        }
        if(existe==0)
            cout<<"La posicion "<<pos<<" no existe"<<endl;
    }
    else
        cout<<"La lista esta vacia"<<endl;
}
template <class Tipo>
void  Lista_enlazada<Tipo>::borrar(){
    Lista **aux=&lis;
    if(lis!=NULL){
        while(true){
            if((*aux)->sig==NULL){
                (*aux)=NULL;
                tope=NULL;
                break;
            }
            else if((*aux)->sig->sig==NULL){
                (*aux)->sig=NULL;
                tope=(*aux);
                break;
            }
            aux=&((*aux)->sig);
        }
    }
    else
        cout<<"No hay datos"<<endl;
}

template <class Tipo>
void  Lista_enlazada<Tipo>::mostrar(){
    Lista *aux=lis;
    while(aux!=NULL){
        cout<<"["<<aux->dato<<"]";
        aux = aux->sig;
    }
    cout<<endl;
    /*cout<<"\nTope = "<<tope->dato<<endl;
    tope--;
    cout<<"\nTope-1 = "<<tope->dato<<endl;*/
}


#endif // LISTA_H_INCLUDED
