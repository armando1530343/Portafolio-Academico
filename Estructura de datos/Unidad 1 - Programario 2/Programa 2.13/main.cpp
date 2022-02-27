#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    int n, i, j, k;
    cout <<"Ingrese un numero: ";cin>>n;
    int x=1+rand()%5;
    int vec[n], matriz[x][n];
    int vecR[n];
    cout<<"\nMatriz"<<endl;
    for(i=0;i<x;i++){
        for(j=0;j<n;j++){
            matriz[i][j]=rand()%10;
            cout<<"["<<matriz[i][j]<<"] ";
        }
        cout<<"\n";
    }
    cout<<"\nVector"<<endl;
    for(i=0;i<n;i++){
        vec[i]=rand()%10;
        cout<<"["<<vec[i]<<"] ";
    }
    cout<<"\nM*V\n"<<endl;
    for(i=0;i<n;i++){
        vecR[i]=0;
        for(j=0;j<x;j++){
            vecR[i]+=vec[i]*matriz[j][i];
        }
        cout<<"["<<vecR[i]<<"] ";
        //cout<<"\n";
    }
    return 0;
}
