#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdlib.h>

using namespace std;
template<class Tipo>
class Lista{
private:
    struct Nodo{
        Tipo dato;
        Nodo *sig = NULL;
        Nodo *ant = NULL;
    }*lis=NULL, *tope=NULL;
    int nodos;
public:
    Lista(){nodos=0;}
    void push(Tipo);
    void inversa();
    void mostrar();
};
template<class Tipo>
void Lista<Tipo>::push(Tipo n){
    if(lis==NULL){
        lis=new Nodo();
        lis->dato = n;
        tope = lis;
    }
    else{
        tope->sig = new Nodo();
        tope->sig->ant = tope;
        tope = tope->sig;
        tope->dato = n;
    }
    nodos++;
    //mostrar();
}
template<class Tipo>
void Lista<Tipo>::inversa(){
    Nodo *tope2 = tope;
    Tipo aux;
    int i;
    if(lis!=NULL){
        for(i=0;i<nodos-1;i++){
            aux = tope2->dato;
            tope2->dato = tope2->ant->dato;
            tope2->ant->dato = aux;
            tope2=tope2->ant;
        }
        nodos--;
        if(nodos>0)
            inversa();
        else
            mostrar();
    }
    else{
        cout<<"Lista Vacia"<<endl;
    }
}
template<class Tipo>
void Lista<Tipo>::mostrar(){
    Nodo *aux = lis;
    if(lis!=NULL){
        cout<<"Lista: ";
        while(aux!=NULL){
            cout<<"["<<aux->dato<<"]";
            aux = aux->sig;
        }
        cout<<endl;
    }
    else
        cout<<"No hay datos"<<endl;
}
#endif // LISTA_H_INCLUDED
