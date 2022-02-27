#include <iostream>

using namespace std;

int main()
{
    int numeros[5], i, j, aux;
    for(i=0;i<5;i++){
        cout<<"ingrese numero "<<i+1<<endl;
        cin>>numeros[i];
    }
    for(i=0;i<5;i++){
        for(j=0;j<4;j++){
            if(numeros[j]>numeros[j+1]){
                aux=numeros[j];
                numeros[j]=numeros[j+1];
                numeros[j+1]=aux;
            }
        }
    }
    cout<<"\nNumero Mayor: "<<numeros[4]<<endl;
    cout<<"Numero Menor: "<<numeros[0]<<endl;
    return 0;
}
