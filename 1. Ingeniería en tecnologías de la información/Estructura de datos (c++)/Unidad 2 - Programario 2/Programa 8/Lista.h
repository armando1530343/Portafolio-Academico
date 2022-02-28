#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

using namespace std;
template<class Tipo>
class Lista{
private:
    struct Nodo{
        Tipo dato;
        Nodo *sig = NULL;
    }*lis=NULL, *tope=NULL;
public:
    Lista(){}
    void push(Tipo);
    void Append(Nodo**);
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
        tope = tope->sig;
        tope->dato = n;
    }
    //mostrar();
}
template<class Tipo>
void Lista<Tipo>::Append(Nodo** nod){
    Nodo *raiz = (*nod);
    //Nodo *tope1, *tope2;
    if((*nod)==lis){
        cout<<"No se puede adjuntar la misma lista"<<endl;
    }
    else if((*nod)!=NULL && lis!=NULL){
        while(raiz!=NULL){
            tope->sig = new Nodo();
            tope = tope->sig;
            tope->dato = raiz->dato;
            raiz = raiz->sig;
        }
        (*nod)=NULL;
        cout<<"Listas adjuntas: ";
        mostrar();
        /*while(raiz2!=NULL){
            if(raiz2->sig==NULL)
                tope1 = raiz1;
            raiz1=raiz1->sig;
        }*/
    }
    else
        cout<<"Listas Vacias"<<endl;
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
