#include <iostream>
#include <string.h>

using namespace std;

void palindromo(char *frase){
    int tam=0, i, j;
    while(*(frase+tam)!=NULL){
        tam++;
    }
    char frase1[tam];
    j=0;
    for(i=0;i<tam;i++){
        if(frase[i]!=32){
            frase1[j]=frase[i];
            j++;
        }
    }
    int x=j, dif=0;
    char frase2[x];
    j=tam-1;
    for(i=0;i<x;i++){
        frase2[i]=frase1[(x-1)-i];
    }
    cout<<"Frase Volteada: "<<frase2<<endl;
    for(i=0;i<x;i++){
        if(frase1[i]!=frase2[i])
            dif=1;
    }
    if(dif==0){
        cout<<"\nEs Palindromo"<<endl;
    }
    else{
        cout<<"\nNo es Palindromo"<<endl;
    }
}

int main()
{
    char *frase = NULL;
    frase=new char[50];
    cout<<"Ingresa Frase: "; cin.getline(frase,50,'\n');
    palindromo(frase);
}
