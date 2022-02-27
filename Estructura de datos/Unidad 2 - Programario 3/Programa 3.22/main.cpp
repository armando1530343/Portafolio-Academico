#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char **frases, *frase;
    int i, j, f=5;
    frases=new char*[f];
    for(i=0;i<f;i++){
        frase=new char[30];
        cout<<"Frase "<<i+1<<": ";
        cin.getline(frase,30,'\n');
        *(frases+i)=new char[strlen(frase)];
        strcpy(*(frases+i),frase);
    }
    cout<<"\nFrases:"<<endl;
    for(i=0;i<f;i++){
        cout<<*(frases+i)<<endl;
    }
}
