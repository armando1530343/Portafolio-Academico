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
    }
    //mostrar();
    nodos++;
}

void AlternatingSplit(){
    Nodo *aux = lista;
    //Nodo *aux2 = sub1;
    //int cont = 1+nodos/2;
    int i=0;
    int num;

    if(lista!=NULL){
    while(aux!=NULL){
        if(i==0){
            num = aux->dato;
            sub1 = new Nodo();
            sub1->dato = num;
            t1 = sub1;
        }
        else{
            if(aux->dato == num){
                t1->sig = new Nodo();
                t1 = t1->sig;
                t1->dato = aux->dato;
            }
            else{
                if(sub2==NULL){
                    sub2 = new Nodo();
                    sub2->dato = aux->dato;
                    t2 = sub2;
                }
                else{
                    t2->sig = new Nodo();
                    t2 = t2->sig;
                    t2->dato = aux->dato;
                }
            }
        }
        i++;
        aux = aux->sig;
    }
    cout<<"Sublista 1: ";
    while(sub1!=NULL){
        cout<<"["<<sub1->dato<<"]";
        sub1 = sub1->sig;
    }
    cout<<"\nSublista 2: ";
    while(sub2!=NULL){
        cout<<"["<<sub2->dato<<"]";
        sub2 = sub2->sig;
    }
    cout<<endl;
    }
    cout<<endl;
}
int main()
{
    inserta(1);
    inserta(2);
    inserta(1);
    inserta(2);
    inserta(2);
    inserta(1);
    inserta(2);
    mostrar();
    AlternatingSplit();
}
