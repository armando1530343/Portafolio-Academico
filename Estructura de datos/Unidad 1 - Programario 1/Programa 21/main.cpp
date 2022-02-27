#include <iostream>

using namespace std;

int main()
{
    int numero, i=0, promedio=0;

    do{
        cout<<"Ingresa numero: "; cin>>numero;
        if(numero>0){
            promedio = promedio + numero;
            i++;
        }
    }
    while(numero>0);
    cout<<"Promedio: "<<promedio/i<<endl;
    return 0;
}
