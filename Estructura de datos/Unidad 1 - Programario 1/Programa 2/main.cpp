#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float a=-2,b=8,c=-4;
    double x1,x2;
    cout<<"a = "<<a<<"\nb = "<<b<<"\nc = "<<c<<endl;
    x1 = (-c+(sqrt((b*b)-(4*a*c))))/(2*a);
    x2 = (-c-(sqrt((b*b)-(4*a*c))))/(2*a);
    cout << "x1 = "<<x1<<endl;
    cout << "x2 = "<<x2<<endl;
    return 0;
}
