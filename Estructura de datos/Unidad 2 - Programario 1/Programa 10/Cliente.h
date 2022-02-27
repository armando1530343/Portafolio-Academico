#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <string.h>
//#include<stdio.h>

using namespace std;

class Cliente{
private:
    string nombre;
    int numCasilla, turno;
public:
    Cliente(){}
    Cliente(string n, int t){
        //nombre=new char[30];
        nombre=n;
        numCasilla=0;
        turno=t;
    }
    string getNombre();
    void setCasilla(int);
    int getCasilla();
    int getTurno();
};
string Cliente::getNombre(){
    return nombre;
}
void Cliente::setCasilla(int num){
    numCasilla=num;
}
int Cliente::getCasilla(){
    return numCasilla;
}
int Cliente::getTurno(){
    return turno;
}

#endif // CLIENTE_H_INCLUDED
