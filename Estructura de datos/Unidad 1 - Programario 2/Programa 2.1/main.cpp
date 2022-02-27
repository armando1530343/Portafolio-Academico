#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    float matriz[3][5];
    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            matriz[i][j]=(rand()%50)/1.5;
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            cout<<"["<<matriz[i][j]<<"] ";
        }
        cout<<"\n";
    }
    return 0;
}
