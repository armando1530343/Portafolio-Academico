
#include <iostream>

using namespace std;

class Complejo{
    private:
        double real, imaginario;
    public:
        Complejo(){real=0;imaginario=0;}
        Complejo(double r, double i){
            real = r;
            imaginario = i;
        }
        void despliegue();
};
void Complejo::despliegue(){
    if(imaginario>0){
        cout << "Numero Complejo: " << real << " + " << imaginario <<"i"<< endl;
    }
    else if (imaginario<0){
        cout << "Numero Complejo: " << real << " " << imaginario <<"i"<< endl;
    }
    else{
        cout<<"No es un numero Complejo"<<endl;
    }

}

int main()
{
    Complejo c1,c2;
    c1 = Complejo(1.23, 3.34);
    c2 = c1;
    c1.despliegue();
    c2.despliegue();
    return 0;
}
