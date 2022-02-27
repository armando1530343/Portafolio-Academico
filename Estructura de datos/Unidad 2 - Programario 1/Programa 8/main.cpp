#include <iostream>
#include "Cola.h"
#include <stdlib.h>
using namespace std;

int main()
{
    Cola c = Cola();
    Impresion archivo1, archivo2, archivo3;
    archivo1 = Impresion("archivo 1","armando","9:45");
    archivo2 = Impresion("archivo 2","isaac","8:40");
    archivo3 = Impresion("archivo 3","luis","10:45");
    c.encolarArchivo(archivo1);
    c.encolarArchivo(archivo2);
    c.encolarArchivo(archivo3);
    c.imprime();
    system("pause");system("cls");
    c.imprimeArchivo();
    system("pause");system("cls");
    c.imprime();
}
