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
    }*lis=NULL;
    Nodo *tope=NULL;
    int nodos;
public:
    Lista(){nodos = 0;}
    void push(Tipo);
    void RemoveDuplicates();
    void mostrar();
};
template<class Tipo>
void Lista<Tipo>::push(Tipo n){
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
    nodos++;
    mostrar();
}
template<class Tipo>
void Lista<Tipo>::RemoveDuplicates(){
    int vec[nodos];
    Nodo *aux = lis;
    int cont=0, existe;
    int i, j;
    if(lis!=NULL){
        cout<<"\nSin duplicados"<<endl;
        while(aux!=NULL){
            if(cont==0){
                vec[cont]=aux->dato;
            }
            else{
                existe=0;
                for(i=0;i<cont;i++){
                    if(aux->dato == vec[i]){
                        existe=1;
                        break;
                    }
                }
                if(existe==0){
                    vec[cont]=aux->dato;
                }
                else{
                    aux->ant->sig = aux->sig;
                }
            }
            cont++;
            aux = aux->sig;
        }

        mostrar();
    }
    else
        cout<<"Lista Vacia"<<endl;
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
