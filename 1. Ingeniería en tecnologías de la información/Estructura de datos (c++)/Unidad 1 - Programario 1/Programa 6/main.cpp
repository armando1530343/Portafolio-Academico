#include <iostream>

using namespace std;

class Tiempo{
    private:
        int horas, minutos, segundos;
    public:
        Tiempo(){horas=0;minutos=0;segundos=0;}
        Tiempo(int h, int m, int s){
            horas = h;
            minutos = m;
            segundos = s;
        }
        void datosObjeto();
};
void Tiempo::datosObjeto(){
    cout << "Horas: " << horas << " Minutos: " << minutos << " Segundos: " << segundos << endl;
}

int main()
{
    Tiempo t1, t2;
    t1 = Tiempo(10,13,56);
    t2 = t1;
    t1.datosObjeto();
    t2.datosObjeto();
    return 0;
}
