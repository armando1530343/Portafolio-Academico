#include <iostream>
#include <string.h>

using namespace std;

class Herramientas{
protected:
    string color;
    double precio;
public:
    void cambiaColor(string c){
        color=c;
    }
    void cambiaPrecio(double p){
        precio=p;
    }
    void imprimir(){
        cout<<"Color:"<<color<<" Precio:"<<precio<<endl;
    }
};
class HerramientasPlomero:public Herramientas{
public:
    HerramientasPlomero(string c, double p){
        color=c;
        precio=p;
    }
};
class HerramientasCarpintero:public Herramientas{
public:
    HerramientasCarpintero(string c, double p){
        color=c;
        precio=p;
    }
};

int main()
{
    HerramientasPlomero soldadora = HerramientasPlomero("roja",350);
    HerramientasCarpintero serrucho = HerramientasCarpintero("verde", 100);
    cout<<"Soldadora"<<endl;
    soldadora.imprimir();
    soldadora.cambiaPrecio(540);
    soldadora.imprimir();
    cout<<"\nSerrucho"<<endl;
    serrucho.imprimir();
    serrucho.cambiaColor("azul");
    serrucho.imprimir();
}
