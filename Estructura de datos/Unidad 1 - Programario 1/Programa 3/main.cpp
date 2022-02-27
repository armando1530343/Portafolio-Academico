#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    float a,b,c;
    double x1,x2;
    cout << "Coeficiente A: " << endl; cin>>a;
    cout << "Coeficiente B: " << endl; cin>>b;
    cout << "Coeficiente C: " << endl; cin>>c;
    x1 = (-c+(sqrt((b*b)-(4*a*c))))/(2*a);
    x2 = (-c-(sqrt((b*b)-(4*a*c))))/(2*a);
    cout << "x1 = "<<x1<<endl;
    cout << "x2 = "<<x2<<endl;
    return 0;
}
