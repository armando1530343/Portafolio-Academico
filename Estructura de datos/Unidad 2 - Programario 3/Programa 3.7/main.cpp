#include <iostream>

using namespace std;

class Cuadrilatero{
protected:
    double base, altura;
public:
    Cuadrilatero(){base=0; altura=0;}
    Cuadrilatero(double b, double a){
        base=b;
        altura=a;
    }
    double calculaArea(){
        return base*altura;
    }
};
class Cuadrado:public Cuadrilatero{
public:
    //Cuadrado(){}
    Cuadrado(double b, double a){
        base=b;
        altura=a;
        cout<<"\nArea del Cuadrado"<<endl;
    }
};
class Rectangulo:public Cuadrilatero{
public:
    Rectangulo(double b, double a){
        base=b;
        altura=a;
        cout<<"\nArea del Rectangulo"<<endl;
    }
};
class Trapezoide:public Cuadrilatero{
private:
    double altura2;
public:
    Trapezoide(double b, double a1, double a2){
        base=b;
        altura=a1;
        altura2=a2;
        cout<<"\nArea del Trapezoide"<<endl;
    }
    double areaT(){
        return ((base*altura)/2)+((base*altura2)/2);
    }
};

int main()
{
    Cuadrilatero fig;
    fig = Cuadrado(5,7);
    cout<<fig.calculaArea()<<endl;
    fig = Rectangulo(7.8,9.5);
    cout<<fig.calculaArea()<<endl;
    fig = Trapezoide(8.6, 4.5, 3.2);
    cout<<fig.calculaArea()<<endl;
}
