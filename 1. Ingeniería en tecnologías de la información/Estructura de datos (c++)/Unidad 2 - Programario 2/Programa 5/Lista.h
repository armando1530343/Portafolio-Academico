#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

using namespace std;

template <class Tipo>
class Lista{
private:
    struct Nodo{
        Tipo dato;
        Nodo *sig = NULL;
    }*lis=NULL, *tope=NULL;
public:
    Lista(){}
    void InsertNth(int,Tipo);
    void mostrar();
    /*Nodo** getLista(){
        return &lis;
    }*/
};
template <class Tipo>
void Lista<Tipo>::InsertNth(int pos, Tipo n){
    int i;
    pos++;
    Nodo *tope2;
    for(i=0;i<pos;i++){
        if(lis==NULL){
            lis = new Nodo();
            tope=lis;
        }
        else if(tope->sig==NULL){
            tope->sig = new Nodo();
            tope = tope->sig;
        }
        else{
            tope=tope->sig;
        }
        if(i==pos-1){
            tope->dato = n;
        }
        //tope2=tope2->sig;
        //tope=lis;
    }
    tope=lis;
    mostrar();
}
template <class Tipo>
void Lista<Tipo>::mostrar(){
    Nodo *aux = lis;
    if(lis!=NULL){
        while(aux!=NULL){
            if(aux->dato!=NULL)
                cout<<"["<<aux->dato<<"]";
            else
                cout<<"[NULL]";
            aux=aux->sig;
        }
        cout<<endl;
    }
    else
        cout<<"No hay datos"<<endl;
}

#endif // LISTA_H_INCLUDED
