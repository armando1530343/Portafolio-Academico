#include <iostream>

using namespace std;

int main()
{
    int n[3],i,rango[3]={1,1,1};
    float c=0;
    for(i=0;i<3;i++){
        cout<<"Ingresa nimero "<<i+1<<endl;
        cin >> n[i];
        c=c+n[i];
        if (n[i]<-1||n[i]>11){rango[i]=0;}
    }
    if (rango[0]==1 && rango[1]==1 && rango[2]==1){
        cout<<"Promedio: "<<c/3<<endl;
    }
    else{
        for(i=0;i<3;i++){
            if(rango[i]==0){
                cout<<"Numero "<<n[i]<<" fuera del rango (-1,11)"<<endl;
            }
        }
    }
    return 0;
}
