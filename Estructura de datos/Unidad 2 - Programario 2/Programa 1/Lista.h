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
    void ccount(Tipo);
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
    mostrar();
}
template<class Tipo>
void Lista<Tipo>::ccount(Tipo n){
    Nodo *aux=lis;
    int cont=0;
    if(lis!=NULL){
        while(aux!=NULL){
            if(aux->dato==n)
                cont++;
            aux = aux->sig;
        }
        cout<<"El valor "<<n<<" aparece "<<cont<<" veces en la lista"<<endl;
    }
    else
        cout<<"No hay datos"<<endl;
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
