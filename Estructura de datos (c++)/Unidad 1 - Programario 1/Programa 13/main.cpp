#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float a,b,c, x1, x2, raiz;
    int tipo;
    cout << "Coeficiente 1: "; cin>>a;
    cout << "Coeficiente 2: "; cin>>b;
    cout << "Coeficiente 3: "; cin>>c;
    raiz = (b*b)-(4*a*c);
    if(raiz<0){tipo=1;/*Imaginaria/Compleja*/}
    else{tipo=2;/*Real*/}
    x1 = (-b+sqrt(raiz))/(2*a);
    x2 = (-b-sqrt(raiz))/(2*a);

    if(tipo==1){
        cout<<"x1 = ("<<-b<<" + i)/"<<2*a<<endl;
        cout<<"x2 = ("<<-b<<" - i)/"<<2*a<<endl;
        cout<<"Raices Complejas"<<endl;
    }
    else{
        cout<<"x1 = "<<x1<<endl;
        cout<<"x2 = "<<x2<<endl;
        cout<<"Raices Reales"<<endl;
    }

    return 0;
}
