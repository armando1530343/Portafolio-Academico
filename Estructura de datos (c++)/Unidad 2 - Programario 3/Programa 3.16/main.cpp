#include <iostream>

using namespace std;

int main()
{
    double millas[]={240.5, 300, 189.6, 310.6, 280.7,216.9, 199.4, 160.3, 177.4, 192.3};
    double galones[]={10.3, 15.6, 8.7, 14, 16.3, 15.7, 14.9, 10.7, 8.3, 8.4};
    double *mpg = new double;
    int i;
    cout<<"MPG = ";
    for(i=0;i<10;i++){
        *(mpg+i)=*(millas+i)/(*(galones+i));
        cout<<*(mpg+i)<<", ";
    }
    cout<<endl;
}
