#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int matriz[5][6], i, j;
    int pos=0, neg=0, ceros=0;
    for(i=0;i<5;i++){
        for(j=0;j<6;j++){
            matriz[i][j]=-10+rand()%21;
            cout<<"["<<matriz[i][j]<<"] ";
            if(matriz[i][j]<0){
                neg++;
            }
            else if(matriz[i][j]>0){
                pos++;
            }
            else{
                ceros++;
            }
        }
        cout<<"\n";
    }
    cout<<"\nPositivos = "<<pos<<endl;
    cout<<"Negativos = "<<neg<<endl;
    cout<<"Ceros = "<<ceros<<endl;
    return 0;
}
