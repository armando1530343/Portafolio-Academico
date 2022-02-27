#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int i, j, fila, columna, ceros, n, num;
    cout<<"Matriz poco densa"<<endl;
    cout<<"Filas: "; cin>>fila;
    cout<<"Columnas: "; cin>>columna;
    ceros = columna*.7;
    n = columna-ceros;
    //cout<<ceros<<" "<<n;
    int matrizPD[fila][columna];
    //int matrizPD2[fila][columna];
    for(i=0;i<fila;i++){
        num=0;
        for(j=0;j<columna;j++){
            matrizPD[i][j]=rand()%2;
            if(matrizPD[i][j]!=0){
                matrizPD[i][j]=1+rand()%9;
                num++;
            }
            if(num>n){
                matrizPD[i][j]=0;
            }
            else if(num==0){
                matrizPD[i][rand()%columna]=1+rand()%9;
            }
            cout<<"["<<matrizPD[i][j]<<"] ";
        }
        cout<<"\n";
    }
    int k, aux;
    for(i=0;i<columna;i++){
        for(j=0;j<fila;j++){
            for(k=0;k<fila-1;k++){
                if(matrizPD[k][j]>matrizPD[k+1][j]){
                    aux=matrizPD[k+1][j];
                    matrizPD[k+1][j]=matrizPD[k][j];
                    matrizPD[k][j]=aux;
                }
            }
        }
        cout<<"Columna "<<i+1<<": Mayor = "<<matrizPD[fila-1][i]<<endl;
    }

    //int matrizPD
    return 0;
}
