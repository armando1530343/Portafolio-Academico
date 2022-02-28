#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

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
    void InsertSort(Nodo **);
    Nodo** getLista(){
        return &lis;
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
        tope->sig->ant = tope;
        tope = tope->sig;
        tope->dato = n;
    }
    nodos++;
    //mostrar();
}
template<class Tipo>
void Lista<Tipo>::InsertSort(Nodo **nod){
    Nodo *tope2;
    Tipo aux;
    int i, j;
    if((*nod)!=NULL){
        /*while(tope2->ant!=NULL){
            if(tope2->dato < tope2->ant->dato){
                aux = tope2->dato;
                tope2->dato = tope2->ant->dato;
                tope2->ant->dato = aux;
            }
            tope2 = tope2->ant;
        }*/
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
        cout<<"Lista Ordenada: ";
        mostrar();
    }
    else
        cout<<"No hay datos"<<endl;
}
template<class Tipo>
void Lista<Tipo>::mostrar(){
    Nodo *aux = lis;
    if(lis!=NULL){
        //cout<<"Lista: ";
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
