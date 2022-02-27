#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    double ingresos[18][10], ing, total1=0, total2=0;
    int i, j, ven, pro, opc;
    for(i=0;i<18;i++){
        for(j=0;j<10;j++){
            ingresos[i][j]=0;
        }
    }
    do{
        system("cls");
        cout<<"1.Agregar Ingresos\n2.Ingresos Totales\n3.Ingresos por Vendedor\n4.Mostrar datos\nOpcion: ";
        do{cin>>opc;}while(opc<1||opc>4);
        switch(opc){
            case 1:
                system("cls");
                cout<<"No. Vendedor (1-18): "; cin>>ven;
                cout<<"No. Producto (1-10): "; cin>>pro;
                cout<<"Ingreso Producto: "; cin>>ing;
                ingresos[ven-1][pro-1]=ing;
                system("pause");
                break;
            case 2:
                system("cls");
                for(i=0;i<18;i++){
                    for(j=0;j<10;j++){
                        total1+=ingresos[i][j];
                    }
                }
                cout<<"Total de Ingresos = "<<total1<<endl;
                system("pause");
                break;
            case 3:
                system("cls");
                cout<<"No. Vendedor (1-18): "; cin>>ven;
                for(i=0;i<10;i++){
                    total2+=ingresos[ven-1][i];
                }
                cout<<"Total de Ingresos = "<<total2<<endl;
                system("pause");
                break;
            case 4:
                system("cls");
                for(i=0;i<18;i++){
                    cout<<"Vendedor "<<i+1<<": ";
                    for(j=0;j<10;j++){
                        cout<<"["<<ingresos[i][j]<<"] ";
                    }
                    cout<<"\n";
                }
                system("pause");
                break;
        }
    }
    while(opc>0&&opc<5);
}
