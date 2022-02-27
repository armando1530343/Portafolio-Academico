#include <iostream>

using namespace std;

int main()
{
    int a,b,aux;
    cout << "valor de A:" << endl; cin >> a;
    cout << "valor de B:" << endl; cin >> b;
    aux = a;
    a = b;
    b = aux;
    cout << "A = " << a << endl;
    cout << "B = " << b << endl;
    return 0;
}
