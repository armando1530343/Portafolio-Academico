#include <iostream>

using namespace std;

int main()
{
    int x,y;
    cout<<"ingresa x: "; cin>>x;
    cout<<"ingresa y: "; cin>>y;
    cout<<"\nPunto("<<x<<","<<y<<") Posicion: ";
    if(x==0&&y==0){cout<<"Origen"<<endl;}
    if(x==0){cout<<"Eje Y"<<endl;}
    if(y==0){cout<<"Eje X"<<endl;}
    if(x>0&&y>0){cout<<"Primer Cuadrante"<<endl;}
    if(x<0&&y>0){cout<<"Segundo Cuadrante"<<endl;}
    if(x<0&&y<0){cout<<"Tercer Cuadrante"<<endl;}
    if(x>0&&y<0){cout<<"Cuarto Cuadrante"<<endl;}
    return 0;
}
