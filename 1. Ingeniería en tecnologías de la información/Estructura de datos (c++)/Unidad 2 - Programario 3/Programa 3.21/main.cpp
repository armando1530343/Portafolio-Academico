#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char *palabra[5];
    int i, j;
    for(i=0;i<5;i++){
        palabra[i]=new char;
        cout<<"Palabra "<<i+1<<": "; cin>>palabra[i];
    }
    char *aux = new char;
    for(i=0;i<5;i++){
        for(j=0;j<4;j++){
            if(strcmp(palabra[j],palabra[j+1])==-1){
                aux=palabra[j];
                palabra[j]=palabra[j+1];
                palabra[j+1]=aux;
            }
        }
    }
    cout<<"\nOrden Descendente"<<endl;
    for(i=0;i<5;i++){
        cout<<palabra[i]<<endl;
    }
}
