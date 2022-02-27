#include <iostream>

using namespace std;

int main()
{
    int elementos[]={1,2,3,4,4,7,8,9,5,4};
    int *p[10], i;
    for(i=0;i<10;i++){
        p[i]=&elementos[i];
        cout<<"Elemento:"<<elementos[i]<<"  Direccion de Memoria = "<<p[i]<<endl;
    }
}
