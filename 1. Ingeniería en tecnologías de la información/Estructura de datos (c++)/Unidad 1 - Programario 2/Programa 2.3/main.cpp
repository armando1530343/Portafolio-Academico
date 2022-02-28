#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int matriz[20][20], i, j, columnas[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, columnas2[20];
    int aux;
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            matriz[i][j]=rand()%10;
            cout<<"["<<matriz[i][j]<<"] ";
            columnas[j]+=matriz[i][j];
            columnas2[j]=columnas[j];
        }
        cout<<"\n";
    }
    for(i=0;i<20;i++){
        cout<<"Columna"<<i+1<<"= "<<columnas[i]<<endl;
    }
    for(i=0;i<20;i++){
        for(j=0;j<19;j++){
            if(columnas2[j]>columnas2[j+1]){
                aux=columnas2[j+1];
                columnas2[j+1]=columnas2[j];
                columnas2[j]=aux;
            }
        }
    }
    for(i=0;i<20;i++){
        if(columnas[i]==columnas2[19]){
            break;
        }
    }
    cout<<"\nColumna Mayor: Columna "<<i+1<<" = "<<columnas[i]<<"\n"<<endl;
    return 0;
}
