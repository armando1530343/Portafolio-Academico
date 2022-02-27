#include <iostream>
#include <string.h>

using namespace std;

class Auto{
    private:
        double tamanioMotor;
        string estiloModelo;
        int codigoColor;
    public:
        Auto(){tamanioMotor=0;estiloModelo="";codigoColor=0;}
        Auto(double t, string e, int c){
            tamanioMotor=t;
            estiloModelo=e;
            codigoColor=c;
        }
        double getTamanioMotor();
        string getEstiloModelo();
        int getCodigoColor();
};
double Auto::getTamanioMotor(){
    return tamanioMotor;
}
string Auto::getEstiloModelo(){
    return estiloModelo;
}
int Auto::getCodigoColor(){
    return codigoColor;
}

int main()
{
    Auto a1, a2;
    a1 = Auto(1.123,"modelo",100);
    a2 = a1;
    cout << "Objeto 1"<<endl;
    cout << a1.getTamanioMotor()<<endl;
    cout << a1.getEstiloModelo()<<endl;
    cout << a1.getCodigoColor()<<endl;
    cout << "\nObjeto 2"<<endl;
    cout << a2.getTamanioMotor()<<endl;
    cout << a2.getEstiloModelo()<<endl;
    cout << a2.getCodigoColor()<<endl;
    return 0;
}
