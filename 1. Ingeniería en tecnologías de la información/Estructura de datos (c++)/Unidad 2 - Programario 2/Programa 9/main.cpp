#include <iostream>
#include <math.h>

using namespace std;

struct Nodo{
    int dato;
    Nodo *sig=NULL;
};
Nodo *lista = NULL;
Nodo *tope = NULL;
Nodo *sub1=NULL, *t1 = NULL;
Nodo *sub2=NULL, *t2 = NULL;
int nodos = 0;

void mostrar(){
    Nodo *aux = lista;
    if(lista!=NULL){
        cout<<"Lista: ";
        while(aux!=NULL){
            cout<<"["<<aux->dato<<"]";
            aux = aux->sig;
        }
        cout<<endl;
    }
    else
        cout<<"La lista esta vacia"<<endl;
}

void inserta(int n){
    if(lista==NULL){
        lista = new Nodo();
        lista->dato = n;
        tope = lista;
    }
    else{
        tope->sig = new Nodo();
        tope = tope->sig;
        tope->dato = n;
    }
    mostrar();
    nodos++;
}

void subListas(){
    Nodo *aux = lista;
    //Nodo *aux2 = sub1;
    int cont = 1+nodos/2;
    int i;

    cout<<"\nSublista 1: ";
    for(i=0;i<cont;i++){
        if(i==0){
            sub1 = new Nodo();
            sub1->dato = aux->dato;
            t1 = sub1;
        }
        else{
            t1->sig = new Nodo();
            t1 = t1->sig;
            t1->dato = aux->dato;
        }
        aux = aux->sig;
        cout<<"["<<t1->dato<<"]";
    }
    cout<<"\nSublista 2: ";
    for(i=cont;i<nodos;i++){
        if(i==cont){
            sub2 = new Nodo();
            sub2->dato = aux->dato;
            t2 = sub2;
        }
        else{
            t2->sig = new Nodo();
            t2 = t2->sig;
            t2->dato = aux->dato;
        }
        aux = aux->sig;
        cout<<"["<<t2->dato<<"]";
    }
    cout<<endl;
}

int main()
{
    inserta(3);
    inserta(4);
    inserta(6);
    inserta(7);
    inserta(1);
    //inserta(6);
    subListas();
    mostrar();
}
