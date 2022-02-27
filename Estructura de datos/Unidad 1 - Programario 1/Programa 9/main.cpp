#include <iostream>

using namespace std;

int main()
{
    int numeros[5];
    float promedio=0;

    cout << "ingresa numero 1" << endl; cin >> numeros[0];promedio = promedio + numeros[0];
    cout << "ingresa numero 2" << endl; cin >> numeros[1];promedio = promedio + numeros[1];
    cout << "ingresa numero 3" << endl; cin >> numeros[2];promedio = promedio + numeros[2];
    cout << "ingresa numero 4" << endl; cin >> numeros[3];promedio = promedio + numeros[3];
    cout << "ingresa numero 5" << endl; cin >> numeros[4];promedio = promedio + numeros[4];
    promedio = promedio/5;
    cout << "Promedio: " << promedio << endl;
    return 0;
}
