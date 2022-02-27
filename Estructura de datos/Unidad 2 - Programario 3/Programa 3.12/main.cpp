#include <iostream>
#include<stdlib.h>
#include <time.h>
#include<vector>

using namespace std;

int main()
{
    srand(time(NULL));
    int numeros[100], i, j=0;
    int *aux=new int, par=0, impar=0;
    for(i=0;i<100;i++){
        numeros[i]=1+rand()%1000;
        if(numeros[i]%2==0)
            par++;
        else
            impar++;
        cout<<numeros[i]<<",";
    }
    cout<<endl;
    cout<<endl;
    for(i=0;i<100;i++){
        if(numeros[i]%2==0){
            *(aux+j)=numeros[i];cout<<*(aux+j)<<",";
            j++;
        }
    }
    for(i=0;i<100;i++){
        if(numeros[i]%2!=0){
            *(aux+j)=numeros[i];cout<<*(aux+j)<<",";
            j++;
        }
    }
    cout<<"\n\nPares="<<par<<"  Impares="<<impar<<endl;
    cout<<endl;
}
