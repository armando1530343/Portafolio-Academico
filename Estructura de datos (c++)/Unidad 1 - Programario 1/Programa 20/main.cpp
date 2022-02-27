#include <iostream>

using namespace std;

int main()
{
    int n, i, j, aux;
    do{cout<<"Ingresa un entero positivo: "; cin>>n;}while(n<=0);
    int numeros[n];
    float promedio=0;
    for(i=0;i<n;i++){
        cout<<"ingrese numero "<<i+1<<endl;
        cin>>numeros[i];
        promedio = promedio + numeros[i];
    }
    for(i=0;i<n;i++){
        for(j=0;j<n-1;j++){
            if(numeros[j]>numeros[j+1]){
                aux=numeros[j];
                numeros[j]=numeros[j+1];
                numeros[j+1]=aux;
            }
        }
    }
    cout<<"\nNumero Mayor: "<<numeros[n-1]<<endl;
    cout<<"Numero Menor: "<<numeros[0]<<endl;
    cout<<"Promedio: "<<promedio/n<<endl;
    return 0;
}
