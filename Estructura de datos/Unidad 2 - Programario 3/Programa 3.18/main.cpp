#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int asientos[25][4], i, j, opc, fila, col;
    for(i=0;i<25;i++){
        for(j=0;j<4;j++){
            asientos[i][j]=0;
        }
    }
    do{
            system("cls");
        cout<<"1.Reservar\n2.Cancelar\n3.Mostrar Asientos\n"<<endl;
        do{cin>>opc;}while(opc<0||opc>3);
        switch(opc){
            case 1:
                system("cls");
                cout<<"Fila(1-25): ";cin>>fila;
                cout<<"Columna(1-4): ";cin>>col;
                if(fila>0&&fila<=25&&col>0&&col<=4){
                if(asientos[fila-1][col-1]==0){
                    asientos[fila-1][col-1]=1;
                    cout<<"--Reservado--"<<endl;
                }
                else{
                    cout<<"--Ocupado--"<<endl;
                }
                }
                else{
                    cout<<"--No Existe el asiento--"<<endl;
                }
                system("pause");
                break;
            case 2:
                system("cls");
                cout<<"Fila(1-25): ";cin>>fila;
                cout<<"Columna(1-4): ";cin>>col;
                if(fila>0&&fila<=25&&col>0&&col<=4){
                if(asientos[fila-1][col-1]==1){
                    asientos[fila-1][col-1]=0;
                    cout<<"--Cancelado--"<<endl;
                }
                else{
                    cout<<"--No habia sido reservado--"<<endl;
                }
                }
                else{
                    cout<<"--No Existe el asiento--"<<endl;
                }
                system("pause");
                break;
            case 3:
                system("cls");
                cout<<"Asientos: Libres=0  Reservados=1"<<endl;
                cout<<"\n    C1  C2  C3  C4"<<endl;
                for(i=0;i<25;i++){
                    cout<<"F"<<i+1<<": ";
                    for(j=0;j<4;j++){
                        cout<<"["<<asientos[i][j]<<"] ";
                    }
                    cout<<"\n";
                }
                system("pause");
                break;
        }
    }
    while(opc>0&&opc<4);
}
