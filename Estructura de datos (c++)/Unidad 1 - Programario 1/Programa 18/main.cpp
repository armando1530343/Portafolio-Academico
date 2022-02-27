#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    string notas;
    char nota;
    int i=0;
    cout<<"Ingresa Letra: "; cin >>nota;

    switch(nota){
        case 'c': notas="do"; break;
        case 'C': notas="do"; break;
        case 'd': notas="re"; break;
        case 'D': notas="re"; break;
        case 'e': notas="mi"; break;
        case 'E': notas="mi"; break;
        case 'f': notas="fa"; break;
        case 'F': notas="fa"; break;
        case 'g': notas="so"; break;
        case 'G': notas="so"; break;
        case 'a': notas="la"; break;
        case 'A': notas="la"; break;
        case 'b': notas="si"; break;
        case 'B': notas="si"; break;
        default:cout<<"Sin datos"<<endl; i=1;
    }
    if(i==0){cout<<"Nota: "<<notas<<endl;}
    return 0;
}
