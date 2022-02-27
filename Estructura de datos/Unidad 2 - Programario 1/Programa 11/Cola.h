#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include "Alumno.h"

using namespace std;

class ColaCircular{
private:
    int primero, longitud, elementos, ubicacion;
    //int totalClientes, numCliente;
    Alumno *cola = NULL;
public:
    ColaCircular(int);
    void push(Alumno);
    void pop();
    void eliminarAlumnos(string);
    void imprimir();
    int colaLlena();
};
ColaCircular::ColaCircular(int l){
    longitud=l;
    cola = new Alumno[longitud];
    elementos=0;
    primero=0;
}
void ColaCircular::push(Alumno datos){
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
    Alumno aux;
    if(elementos>0){
        //totalClientes++;
        //cola[primero].setCasilla((rand()%3)+1);
        //cout<<"Turno: "<<cola[primero].getTurno()<<endl;
        cout<<"Nombre: "<<cola[primero].getNombre()<<endl;
        cout<<"Materia: "<<cola[primero].getMateria()<<endl;
        //cout<<"No.Ventanilla: "<<cola[primero].getCasilla()<<endl;
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
void ColaCircular::imprimir(){
    int i,j;
    if(elementos>0){
        j=primero;
        for(i=1;i<=elementos;i++){
            //cout<<"cola["<<j<<"]="<<*(cola+j)<<endl;
            cout<<"Alumno: "<<cola[j].getNombre()<<" Materia: "<<cola[j].getMateria()<<endl;
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
void ColaCircular::eliminarAlumnos(string mat){
    int i, j, existe=0;
    int cambiaPrimero=0;
    Alumno *aux=NULL;
    if(elementos>0){
        for(i=0;i<longitud;i++){
            //if(i==longitud-1)
               // i=-1;
            if(cola[i].getMateria()==mat){
                cout<<cola[i].getNombre()<<" salio de la cola"<<endl;
                cola[i].setNombre("");
                if(i==primero){
                    if(elementos>1)
                        if(primero==longitud-1)
                            primero=0;
                        else
                            primero++;
                    else
                        primero=0;
                }
                    //cambiaPrimero=1;
                existe=1;
                elementos--;
            }
            /*else{
                if(cambiaPrimero==1)
                    primero=i;
            }*/
        }
        if(existe==0){
            cout<<"No hay aumnos con esa materia"<<endl;
        }
        else{
            aux=new Alumno[longitud];
            j=primero;
            for(i=primero;i<longitud;i++){
                if(cola[i].getNombre()!=""){
                    aux[j]=cola[i];
                    if(j==longitud-1)
                        j=-1;
                    j++;
                }
            }
            //j=0;
            for(i=0;i<primero;i++){
                if(cola[i].getNombre()!=""){
                    aux[j]=cola[i];
                    if(j==longitud-1)
                        j=-1;
                    j++;
                }
            }
            for(i=0;i<longitud;i++)
                cola[i]=aux[i];
        }
    }
}
int ColaCircular::colaLlena(){
    if(elementos>=longitud){
        cout<<"La cola esta llena"<<endl;
        return 1;
    }
    return 0;
}

#endif // COLA_H_INCLUDED
