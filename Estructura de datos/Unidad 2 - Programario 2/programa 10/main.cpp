#include <iostream>

using namespace std;

struct Nodo{
    int dato;
    Nodo *sig=NULL;
    Nodo *ant=NULL;
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
    int aux;
    if(lista==NULL){
        lista = new Nodo();
        lista->dato = n;
        tope = lista;

    }
    else{
        tope->sig = new Nodo();
        tope->sig->ant = tope;
        tope = tope->sig;
        tope->dato = n;
        //tope2 = tope;
        /*while(tope2->ant!=NULL){
            if(tope2->dato < tope2->ant->dato){
                aux = tope2->dato;
                tope2->dato = tope2->ant->dato;
                tope2->ant->dato = aux;
            }
            tope2 = tope2->ant;
        }*/

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
void ordenar(){
    int i, j, aux;
    Nodo *tope2;
    for(i=0;i<nodos;i++){
        tope2=tope;
        for(j=0;j<nodos-1;j++){
            if(tope2->dato < tope2->ant->dato){
                aux = tope2->dato;
                tope2->dato = tope2->ant->dato;
                tope2->ant->dato = aux;
            }
            tope2 = tope2->ant;
        }
    }
}

int main()
{
    inserta(3);
    inserta(8);
    inserta(2);
    inserta(7);
    inserta(1);
    ordenar();
    subListas();
}
