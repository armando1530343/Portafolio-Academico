#include <iostream>
#include <stdlib.h>

using namespace std;

class CadenaCar{
private:
    int tam;
    char *cadena;
public:
    CadenaCar(){}
    CadenaCar(int);
    int operator==(CadenaCar);
    int operator!=(CadenaCar);
    int operator<(CadenaCar);
    int operator>(CadenaCar);
    char* operator+(CadenaCar);
    char* getCadena();
    int getTam();
};
CadenaCar::CadenaCar(int t){
    tam=t;
    cadena=new char[tam];
    cout<<"Ingrese "<<tam<<" caracteres:"; cin>>cadena;
}
char* CadenaCar::getCadena(){
    return cadena;
}
int CadenaCar::getTam(){
    return tam;
}
int CadenaCar::operator==(CadenaCar cad){
    int i;
    for(i=0;i<tam;i++){
        if(cadena[i]!=cad.getCadena()[i]){
            return 0;
            break;
        }
    }
    return 1;
}
int CadenaCar::operator!=(CadenaCar cad){
    int i;
    for(i=0;i<tam;i++){
        if(cadena[i]!=cad.getCadena()[i]){
            return 1;
            break;
        }
    }
    return 0;
}
int CadenaCar::operator<(CadenaCar cad){
    int i;
    for(i=0;i<tam;i++){
        if(cadena[i]>cad.getCadena()[i]){
            return 1;
            break;
        }
    }
    return 0;
}
int CadenaCar::operator>(CadenaCar cad){
    int i;
    for(i=0;i<tam;i++){
        if(cadena[i]<cad.getCadena()[i]){
            return 1;
            break;
        }
    }
    return 0;
}
char* CadenaCar::operator+(CadenaCar cad){
    int t = tam+cad.getTam();
    char subcadena[t];
    cout<<t<<endl;
    int i, j, k=0;
    for(i=0;i<tam;i++){
        subcadena[i]=cadena[i];
    }
    for(j=i;j<t;j++){
        subcadena[j]=cad.getCadena()[k];
        k++;
    }
    cout<<subcadena<<endl;
    system("pause");
    return subcadena;
}


int main()
{
    CadenaCar cad1, cad2;
    int igual, dif, mayor, menor;
    char *concatenar;
    cad1=CadenaCar(5);
    cad2=CadenaCar(5);
    igual=cad1==cad2;
    dif=cad1!=cad2;
    menor=cad1<cad2;
    mayor=cad1>cad2;
    concatenar=cad1+cad2;
    cout<<"\nIguales: "<<igual;
    cout<<"\nDiferentes: "<<dif;
    cout<<"\nCadena1 < Cadena2: "<<menor;
    cout<<"\nCadena1 > Cadena2: "<<mayor;
    cout<<"\nCadena1 + Cadena2: "<<concatenar;
    return 0;
}
