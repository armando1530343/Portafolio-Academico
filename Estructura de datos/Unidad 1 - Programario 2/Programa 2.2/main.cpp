#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int matriz[7][7], i, j, k=0;
    int fila[7]={0,0,0,0,0,0,0}, columna[7]={0,0,0,0,0,0,0};

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            matriz[i][j]=rand()%10;
            fila[i]+=matriz[i][j];
            columna[j]+=matriz[i][j];
        }
    }
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            cout<<"["<<matriz[i][j]<<"] ";
        }
        cout<<"\n";
    }
    for(i=0;i<7;i++){
        cout<<"\nFila "<<i+1<<" = "<<fila[i];
        cout<<"  Columna "<<i+1<<" = "<<columna[i]<<"\n";
    }


    return 0;
}
