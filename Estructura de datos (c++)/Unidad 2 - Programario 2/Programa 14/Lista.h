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
    }*lis=NULL, *tope=NULL;
    int nodos;
public:
    Lista(){nodos=0;}
    void push(Tipo);
    void ShuffleMerge(Nodo **, int);
    Nodo** getLista(){
        return &lis;
    }
    int totalNodos(){
        return nodos;
    }
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
        tope = tope->sig;
        tope->dato = n;
    }
    nodos++;
    mostrar();
}
template<class Tipo>
void Lista<Tipo>::ShuffleMerge(Nodo **nod, int total){
    Nodo *nueva=NULL;
    Nodo *top=NULL;
    Nodo *aux;
    Nodo *aux1=lis;
    Nodo *aux2=(*nod);
    bool cambio=false;
    bool termina=false;
    int i;
    if((*nod)!=NULL){
        for(i=0;i<total;i++){
            if(nueva==NULL){
                nueva=new Nodo();
                top = nueva;
            }
            else{
                top->sig=new Nodo();
                top = top->sig;
            }
            //top->dato=0;cout<<top->dato<<endl;system("pause");
        }
        aux=nueva;
        cout<<"\nFusion: ";
        while(aux!=NULL){
            if(cambio==false){
                if(aux1!=NULL){
                    aux->dato = aux1->dato;
                    aux1 = aux1->sig;
                    //cambio=true;
                }
                if(aux2!=NULL)
                    cambio=true;
                //cout<<"["<<aux->dato<<"]";system("pause");

            }
            else if(cambio==true){
                if(aux2!=NULL){
                    aux->dato = aux2->dato;
                    aux2 = aux2->sig;
                    //cambio=false;
                }
                if(aux1!=NULL)
                    cambio=false;
                //cout<<"["<<aux->dato<<"]";system("pause");

            }
            cout<<"["<<aux->dato<<"]";
            aux=aux->sig;
        }
        cout<<endl;

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
