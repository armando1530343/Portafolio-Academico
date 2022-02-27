#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>

using namespace std;

template <class Tipo>
class Lista{
private:
    struct Nodo{
        Tipo dato;
        Nodo *sig;
    }*lis=NULL, *tope=NULL;
    char *tipo;
public:
    Lista(char t[5]){
        tipo=new char;
        tipo = t;
        cout<<"\n"<<tipo<<endl;
    }
    void push(Tipo);
    void pop();
    void mostrar();
};

template <class Tipo>
void Lista<Tipo>::push(Tipo n){
    Nodo *aux=NULL;
    if(lis==NULL){
        lis = new Nodo();
        lis->dato = n;
        tope = lis;
    }
    else{
        tope->sig = new Nodo();
        tope = tope->sig;
        tope->dato = n;
    }
    mostrar();
}
template <class Tipo>
void Lista<Tipo>::mostrar(){
    Nodo *aux=lis;
    if(lis!=NULL){
        while(aux!=NULL){
            cout<<"["<<aux->dato<<"]";
            aux = aux->sig;
        }
        cout<<endl;
    }
    else
        cout<<"No hay datos"<<endl;
}
template <class Tipo>
void Lista<Tipo>::pop(){
    Nodo **aux=&lis;
    if(lis!=NULL){
        if(tipo=="PILA"){
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
                aux = &((*aux)->sig);
            }
        }
        else{
            lis=lis->sig;
        }
    }
    else
        cout<<"No hay datos"<<endl;
    mostrar();
}












#endif // LISTA_H_INCLUDED
