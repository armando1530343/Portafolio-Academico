#include <iostream>
#include <iomanip>

using namespace std;

class Fecha
{
    private:
        int mes;
        int dia;
        int anio;
    public:
        Fecha(int =7, int = 4, int = 2005);
        Fecha operator+(int);
        void mostrarFecha();
};
Fecha::Fecha(int mm, int dd, int aaaa){
    mes = mm;
    dia = dd;
    anio = aaaa;
}
/*Fecha Fecha::operator+(int dias){
    Fecha temp;
    temp.dia = dia + dias;
    temp.mes = mes;
    temp.anio = anio;
    while (temp.dia > 30){
        temp.mes++;
        temp.dia -=30;
    }
    while (temp.mes > 12){
        temp.anio++;
        temp.mes -=12;
    }
    return temp;
}*/
Fecha Fecha::operator+(int dias){
    Fecha temp;
    temp.dia = dia + dias;
    temp.mes = mes + int(dia/30);
    temp.dia = temp.dia %30;
    temp.anio = anio + int(temp.mes/12);
    return temp;
}
void Fecha::mostrarFecha(){
    cout << setfill('0')<< setw(2) << mes << '/'<< setw(2) << dia << '/'<< setw(2) << anio % 100;
    return;
}
int main()
{
    Fecha a(4,1,2007), b;
    cout << "La fecha inicial es ";
    a.mostrarFecha();
    b = a + 284;
    cout << "\nLa nueva fecha es ";
    b.mostrarFecha();
    return 0;
}
