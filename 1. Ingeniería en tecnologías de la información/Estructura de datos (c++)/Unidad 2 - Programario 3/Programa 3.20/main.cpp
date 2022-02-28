#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    int numeros[50], *punteros[50];
    int i;
    for(i=0;i<50;i++){
        numeros[i]=rand()%100;
        punteros[i]=&numeros[i];
        cout<<*punteros[i]<<" ";
    }
    cout<<endl;
}
