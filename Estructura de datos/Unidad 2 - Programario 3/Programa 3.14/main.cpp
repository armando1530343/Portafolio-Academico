
#include <iostream>

using namespace std;

int main()
{
    float tasas[]={6.25,6.5,6.8,7.2,7.35,7.5,7.65,7.8,8.2,8.4,8.6,8.8,9.0};
    float *dispPT = tasas;
    int i, j=0;
    cout<<"\nciclo FOR "<<endl;
    for(i=0;i<13;i++){
        cout<<*(dispPT+i)<<", ";
    }
    cout<<"\n\nciclo WHILE "<<endl;
    while(j<13){
        cout<<*(dispPT+j)<<", ";
        j++;
    }
    cout<<endl;
}
