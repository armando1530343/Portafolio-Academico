#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include "Cliente.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

class ColaCircular{
private:
    int primero, longitud, elementos, ubicacion;
    int totalClientes, numCliente;
    Cliente *cola = NULL;
public:
    ColaCircular(int);
    void push(Cliente);
    void pop();
    int getTotalClientes();
    void imprimir();
    int colaLlena();
};
ColaCircular::ColaCircular(int l){
    longitud=l;
    cola = new Cliente[longitud];
    elementos=0;
    primero=0;
    totalClientes=0;
}
void ColaCircular::push(Cliente datos){
    if(elementos<longitud){
        ubicacion = (primero+elementos)%longitud;
        cola[ubicacion] = datos;
        elementos++;
    }
    else{
        cout<<"La cola esta llena\n"<<endl;
    }
}
void ColaCircular::pop(){
    srand(time(NULL));
    Cliente aux;
    if(elementos>0){
        totalClientes++;
        cola[primero].setCasilla((rand()%3)+1);
        cout<<"Turno: "<<cola[primero].getTurno()<<endl;
        cout<<"Nombre: "<<cola[primero].getNombre()<<endl;
        cout<<"No.Ventanilla: "<<cola[primero].getCasilla()<<endl;
        //cola[primero] = NULL;
        primero = (primero+1)%longitud;
        elementos--;
        //totalClientes++;
    }
    else{
        cout<<"La cola esta vacia"<<endl;
    }
    cout<<endl;
}
int ColaCircular::getTotalClientes(){
    return totalClientes;
}
void ColaCircular::imprimir(){
    int i,j;
    if(elementos>0){
        j=primero;
        for(i=1;i<=elementos;i++){
            //cout<<"cola["<<j<<"]="<<*(cola+j)<<endl;
            cout<<"Turno "<<cola[j].getTurno()<<": "<<cola[j].getNombre()<<endl;
            if(j==longitud-1){
                j=-1;
            }
            j++;
        }
    }
    else{
        cout<<"La cola esta vacia"<<endl;
    }
    cout<<endl;
}
int ColaCircular::colaLlena(){
    if(elementos>=longitud){
        cout<<"La cola esta llena"<<endl;
        return 1;
    }
    return 0;
}

#endif // COLA_H_INCLUDED
