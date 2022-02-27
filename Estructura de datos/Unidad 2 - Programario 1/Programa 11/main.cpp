#include <iostream>
#include "Cola.h"
#include <stdlib.h>
using namespace std;

int main()
{
    ColaCircular cola = ColaCircular(5);
    Alumno alm;
    int opc;
    string nombre, materia;
    do{
        system("cls");
        cout<<"1.Registrar alumno\n2.Pasar alumno a la direccion\n3.Eliminar alumnos de la cola\n4.Ver alumnos en la cola\n5.Cerrar"<<endl;
        do{
            cout<<"Elige opcion: ";cin>>opc;
        }while(opc<1||opc>5);
        if(opc==1){
            system("cls");
            if(cola.colaLlena()==0){
                cout<<"Registro alumno\n\n Nombre: "; cin>>nombre;
                cout<<" Materia:"; cin>>materia;
                alm=Alumno(nombre,materia);
                cola.push(alm);
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
            cout<<"Materia: "; cin>>materia;
            cola.eliminarAlumnos(materia);
            system("pause");
        }
        else if(opc==4){
            system("cls");
            cola.imprimir();
            system("pause");
        }
    }while(opc!=5);
}
