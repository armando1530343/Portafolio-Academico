#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int matriz[6][8], vec[6*8], i, j, k=0;
    cout<<"[Matriz]"<<endl;
    for(i=0;i<6;i++){
        for(j=0;j<8;j++){
            matriz[i][j]=rand()%10;
            vec[k]=matriz[i][j];
            k++;
            cout<<"["<<matriz[i][j]<<"] ";
        }
        cout<<"\n";
    }
    cout<<"\n[Vector]"<<endl;
    for(i=0;i<6*8;i++){
        cout<<"["<<vec[i]<<"]";
    }
    return 0;
}
