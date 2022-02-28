#include <iostream>

using namespace std;

struct Nodo{
    int dato;
    Nodo *sig=NULL;
    Nodo *ant=NULL;
};

//int nodos = 0;

void mostrar(Nodo ** nod){
    Nodo *aux = (*nod);
    if((*nod)!=NULL){
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

void inserta(Nodo** nod, Nodo** top, int n){
    int aux;
    if((*nod)==NULL){
        (*nod) = new Nodo();
        (*nod)->dato = n;
        (*top) = (*nod);
    }
    else{
        (*top)->sig = new Nodo();
        (*top)->sig->ant = (*top);
        (*top) = (*top)->sig;
        (*top)->dato = n;
    }
}

void SortedMerge(Nodo *vec[], int longVec){
    int i, j;
    Nodo *nueva = NULL;
    Nodo *tope = NULL;
    Nodo *tope2;
    int nodos=0;
    cout<<"\nFusion: ";
    for(i=0;i<longVec;i++){
        while(vec[i]!=NULL){
            if(nueva==NULL){
                nueva = new Nodo();
                nueva->dato = vec[i]->dato;
                tope = nueva;
            }
            else{
                tope->sig = new Nodo();
                tope->sig->ant = tope;
                tope = tope->sig;
                tope->dato = vec[i]->dato;
            }
            nodos++;
            vec[i]= vec[i]->sig;
        }
    }

    int auxiliar;
    for(i=0;i<nodos;i++){
        tope2=tope;
        for(j=0;j<nodos-1;j++){

            if(tope2->dato < tope2->ant->dato){
                auxiliar = tope2->dato;
                tope2->dato = tope2->ant->dato;
                tope2->ant->dato = auxiliar;

            }
            //cout<<"aqui"<<endl;
            tope2 = tope2->ant;
        }
    }
    tope2 = nueva;
    while(tope2!=NULL){
        cout<<"["<<tope2->dato<<"]";
        tope2 = tope2->sig;
    }
}

int main()
{
    Nodo *lista1 = NULL, *lista2 = NULL, *lista3 = NULL;
    Nodo *tope1 = NULL, *tope2 = NULL, *tope3 = NULL;
    Nodo *aux1, *aux2, *aux3;

    inserta(&lista1,&tope1,3);
    inserta(&lista1,&tope1,7);
    mostrar(&lista1);
    inserta(&lista2,&tope2,8);
    inserta(&lista2,&tope2,4);
    mostrar(&lista2);
    inserta(&lista3,&tope3,9);
    inserta(&lista3,&tope3,1);
    mostrar(&lista3);

    aux1 = lista1;
    aux2 = lista2;
    aux3 = lista3;

    Nodo *vec[] ={aux1, aux2, aux3};
    SortedMerge(vec, 3);
}
