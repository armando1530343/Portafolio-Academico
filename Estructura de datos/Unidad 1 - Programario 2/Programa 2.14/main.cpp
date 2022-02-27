#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int fa, ca, fb, cb;
    int i, j, k;
    cout<<"Matriz A:"<<endl;
    cout<<"  Filas: "; cin>>fa;
    cout<<"  Columnas: "; cin>>ca;
    cout<<"Matriz B:"<<endl;
    cout<<"  Filas: "; cin>>fb;
    cout<<"  Columnas: "; cin>>cb;
    int matrizA[fa][ca], matrizB[fb][cb];
    cout<<"\nMatriz A:"<<endl;
    for(i=0;i<fa;i++){
        for(j=0;j<ca;j++){
            matrizA[i][j]=rand()%10;
            cout<<"["<<matrizA[i][j]<<"] ";
        }
        cout<<"\n";
    }
    cout<<"\nMatriz B:"<<endl;
    for(i=0;i<fb;i++){
        for(j=0;j<cb;j++){
            matrizB[i][j]=rand()%10;
            cout<<"["<<matrizB[i][j]<<"] ";
        }
        cout<<"\n";
    }

    if(ca==fb){
        int AxB[fa][cb];
        cout<<"\nAxB:"<<endl;
        for(i=0;i<fa;i++){
            for(j=0;j<cb;j++){
                AxB[i][j]=0;
                for(k=0;k<fb;k++){
                    AxB[i][j]=matrizA[i][k]*matrizB[k][j];
                }
                cout<<"["<<AxB[i][j]<<"] ";
            }
            cout<<"\n";
        }
    }
    else{
        cout<<"No se pueden multiplicar"<<endl;
    }
    return 0;
}
