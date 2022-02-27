#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include "Impresion.h"

using namespace std;

class Cola{
private:
    Impresion *cola, *aux;
    Impresion *tope;
    int cont;
public:
    Cola(){
        cola=NULL;
        aux=NULL;
        cont=0;
        tope=NULL;
    }
    void encolarArchivo(Impresion);
    void imprimeArchivo();
    void imprime();
};
void Cola::encolarArchivo(Impresion n){
    int i;
    cont++;
    if(tope==NULL){
        cola=new Impresion [cont];
        cola[0]=n;
        tope=&cola[0];
    }
    else{
        aux=cola;
        cola=new Impresion[cont];
        for(i=0;i<cont-1;i++){
            cola[i]=aux[i];
        }
        cola[cont-1]=n;
    }
    //imprime();
}
void Cola::imprimeArchivo(){
    int i;
    if(cont>0){
        cout<<"\n-----------------------------------"<<endl;
        cout<<"Archivo Impreso (Sale de la cola)"<<endl;
        cout<<"Nombre Archivo: "<<cola[0].getNombre()<<endl;
        cout<<"Autor: "<<cola[0].getAutor()<<endl;
        cout<<"Hora: "<<cola[0].getHora()<<endl;
        cout<<"-----------------------------------"<<endl;
        for(i=0;i<cont-1;i++)
            cola[i]=cola[i+1];
        cont--;
    }
    else
        cout<<"No hay archivos en la cola"<<endl;
}
void Cola::imprime(){
    int i;
    for(i=0;i<cont;i++){
        cout<<"--------------------------------"<<endl;
        cout<<"Nombre Archivo: "<<cola[i].getNombre()<<endl;
        cout<<"Autor: "<<cola[i].getAutor()<<endl;
        cout<<"Hora: "<<cola[i].getHora()<<endl;
        cout<<"--------------------------------"<<endl;
    }
}


#endif // COLA_H_INCLUDED
