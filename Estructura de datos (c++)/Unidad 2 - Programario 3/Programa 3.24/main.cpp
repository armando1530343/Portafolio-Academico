#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int n =10, i, j;
    int numeros[n], aux;
    for(i=0;i<n;i++){
        numeros[i]=rand()%100;
        if(i>0){
            for(j=i;j>0;j--){
                if(numeros[j]>numeros[j-1]){
                    aux=numeros[j];
                    numeros[j]=numeros[j-1];
                    numeros[j-1]=aux;
                }
            }
        }
    }
    for(i=0;i<n;i++){
        cout<<numeros[i]<<", ";
    }
    cout<<endl;
}
