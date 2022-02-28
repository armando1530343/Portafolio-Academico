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
public:
    Lista(){}
    void push(Tipo);
    void inversa();
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
    mostrar();
}
template<class Tipo>
void Lista<Tipo>::inversa(){
    Nodo *inv=NULL;
    Nodo *top=NULL;
    Nodo *tope2 = tope;
    if(lis!=NULL){
        while(tope2!=NULL){
            if(inv == NULL){
                inv = new Nodo();
                inv->dato = tope2->dato;
                top = inv;
            }
            else{
                top->sig = new Nodo();
                top = top->sig;
                top->dato = tope2->dato;
            }
            tope2=tope2->ant;
        }
        lis = inv;
        cout<<"Inversa: ";
        mostrar();
    }
    else{
        cout<<"Lista Vacia"<<endl;
    }


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
