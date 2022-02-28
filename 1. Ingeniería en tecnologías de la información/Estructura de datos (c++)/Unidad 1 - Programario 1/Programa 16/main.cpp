#include <iostream>

using namespace std;

int main()
{
    float calif[4], promedio=0;
    int i;
    for(i=0;i<4;i++){
        do{
            cout<<"Calificacion "<<i+1<<": "; cin>>calif[i];
        }
        while(calif[i]<0||calif[i]>10);
        promedio = promedio + calif[i];
    }
    promedio = promedio/4;
    cout<<"Promedio: "<<promedio<<endl;
    if(promedio>=6){cout<<"Aprobado"<<endl;}
    else if(promedio>=5&&promedio<6){cout<<"Derecho a Extraordinario"<<endl;}
    else if(promedio>=2&&promedio<5){cout<<"Derecho a Titulo"<<endl;}
    else{cout<<"Sin derecho a acreditar"<<endl;}

    return 0;
}
