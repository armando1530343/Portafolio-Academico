#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int gato[3][3];
    int n1,n2,n3,linea;
    gato[0][0]=1; gato[0][1]=2; gato[0][2]=3;
    gato[1][0]=4; gato[1][1]=5; gato[1][2]=6;
    gato[2][0]=7; gato[2][1]=8; gato[2][2]=9;
    while(true){
        n1 = 1+rand()%9;
        n2 = 1+rand()%9;
        n3 = 1+rand()%9;
        if(n1<n2&&n2<n3){
            break;
        }
    }
    if(n1==gato[0][0]&&n2==gato[0][1]&&n3==gato[0][2]||
       n1==gato[1][0]&&n2==gato[1][1]&&n3==gato[1][2]||
       n1==gato[2][0]&&n2==gato[2][1]&&n3==gato[2][2]){
        linea=1;
    }
    else{
        linea=0;
    }
    cout<<"n1="<<n1<<"\nn2="<<n2<<"\nn3="<<n3<<"\nLinea="<<linea<<endl;


    return 0;
}
