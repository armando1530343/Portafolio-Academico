#include <iostream>
#include <math.h>
#define PI 3.14159265

using namespace std;

class Coord{
    private:
        double val_x, val_y;
    public:
        Coord(){val_x=0;val_y=0;}
        Coord(double x, double y){
            val_x = x;
            val_y = y;
        }
        friend void conv_pol(Coord&,double,float);
        void imprime();
};
void conv_pol(Coord &c, double radio, float angulo){
    double x, y;
    x = radio*(cos(angulo*PI/180));
    y = radio*(sin(angulo*PI/180));
    c.val_x=x;
    c.val_y=y;
}
void Coord::imprime(){
    cout<<"Coordenadas rectangulares: ("<<val_x<<","<<val_y<<")"<<endl;
}


int main()
{
    Coord c1, c2;
    c1 = Coord(2,6);
    c1.imprime();

    conv_pol(c2,6,30);
    c2.imprime();

    return 0;
}
