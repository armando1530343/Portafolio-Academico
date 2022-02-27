#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int x[2], y[2], i;
    double distancia;
    cout << "Primer punto" << endl;
    cout << "x1: "; cin >> x[0];
    cout << "y1: "; cin >> y[0];
    cout << "\nSegundo punto" << endl;
    cout << "x2: "; cin >> x[1];
    cout << "y2: "; cin >> y[1];
    distancia = sqrt((x[1]-x[0])*(x[1]-x[0])+(y[1]-y[0])*(y[1]-y[0]));
    cout << "\nDistancia entre los dos puntos: " << distancia << endl;

    return 0;
}
