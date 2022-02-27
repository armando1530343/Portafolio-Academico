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
    Lista(){nodos = 0;}
    void SortInsert(Tipo);
    void mostrar();
};
template<class Tipo>
void Lista<Tipo>::SortInsert(Tipo n){
    Nodo *tope2;
    int i, j;
    Tipo auxiliar;
    if(lis==NULL){
        lis=new Nodo();
        lis->dato = n;
        tope = lis;
        tope2 = tope;
    }
    else{
        tope->sig = new Nodo();
        tope->sig->ant = tope;
        tope = tope->sig;
        tope2 = tope;
        tope->dato = n;

        while(tope2->ant!=NULL){
            if(tope2->dato < tope2->ant->dato){
                auxiliar = tope2->dato;
                tope2->dato = tope2->ant->dato;
                tope2->ant->dato = auxiliar;
            }
            tope2 = tope2->ant;
        }
    }
    mostrar();
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
