#include <iostream>

using namespace std;

//template<typename Tipo>
struct Lista{
    int dato;
    Lista *sig=NULL;
}*lis=NULL, *tope=NULL, *raiz=NULL;

void insertar(int n){
    if(lis==NULL){
        lis=new Lista();
        raiz=lis;
        lis->dato=n;
        tope = lis;
    }
    else{
        tope->sig = new Lista();
        tope = tope->sig;
        tope->dato = n;
    }
}
void mostrarLista(){
    Lista *aux=lis;
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

void deleteList(Lista **li){
    Lista **aux=li;
    if((*li)!=NULL){
        while(true){
            if((*aux)->sig==NULL){
                (*aux)=NULL;
                tope=NULL;
                break;
            }
            if((*aux)->sig->sig==NULL){
                (*aux)->sig=NULL;
                tope=(*aux);
                break;
            }
            aux = &((*aux)->sig);
        }
        deleteList(li);
    }
    else
        cout<<"Lista Borrada"<<endl;
}


int main()
{
    insertar(4);
    insertar(5);
    insertar(3);
    insertar(6);
    mostrarLista();
    deleteList(&lis);
    mostrarLista();
}
