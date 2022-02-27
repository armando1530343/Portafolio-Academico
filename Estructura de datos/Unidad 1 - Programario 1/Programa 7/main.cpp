#include <iostream>
#include <math.h>
#define PI 3.1416

using namespace std;

int main()
{
    float radio, perimetro, area;
    cout << "Ingresa radio de la circunferencia: " << endl;
    cin >> radio;
    perimetro = PI*(radio*2);
    area = PI*(radio*radio);
    cout << "Perimetro: " << perimetro <<endl;
    cout << "Area: " << area <<endl;
    return 0;
}
