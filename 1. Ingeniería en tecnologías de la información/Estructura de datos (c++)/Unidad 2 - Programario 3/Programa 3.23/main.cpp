#include <iostream>

using namespace std;

void Mostrar(double *tasas, int t){
    int i=0;
    cout<<"*(tasas+i): ";
    while(i<t){
        cout<<"["<<*(tasas+i)<<"] ";
        i++;
    }
    i=0;
    cout<<"\n\n*tasas: "<<*tasas;
    cout<<endl;
}

int main()
{
    double tasas[]={6.5, 7.2, 7.5, 8.3, 8.6, 9.4, 9.6, 9.8, 10.0};
    Mostrar(tasas, 9);
}
