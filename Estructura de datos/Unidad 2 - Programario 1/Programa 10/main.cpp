#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Cola.h"
using namespace std;

int main()
{
    ColaCircular cola = ColaCircular(3);
    Cliente cl;
    int opc;
    string nombre;
    int turno=1;
    do{
        system("cls");
        cout<<"1.Registrar Cliente\n2.Asignar ventanilla a cliente\n3.Ver Clientes en la cola\n4.Cerrar"<<endl;
        do{
            cout<<"Elige opcion: ";cin>>opc;
        }while(opc<1||opc>4);
        if(opc==1){
            system("cls");
            if(cola.colaLlena()==0){
                cout<<"Registro Cliente\n\n Turno: "<<turno<<"\n Nombre: "; cin>>nombre;//scanf(" %[^\n]",&nombre);
                cl=Cliente(nombre, turno);
                cola.push(cl);
                turno++;
            }
            system("pause");
        }
        else if(opc==2){
            system("cls");
            cola.pop();
            system("pause");
        }
        else if(opc==3){
            system("cls");
            cola.imprimir();
            system("pause");
        }
    }while(opc!=4);
    cout<<"Total de Clientes Atendidos: "<<cola.getTotalClientes()<<endl;
}
