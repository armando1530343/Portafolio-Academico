#include <iostream>

using namespace std;

int main()
{
    double *pt[10], x=1;
    double n[10], suma=0, *s;
    int i;
    pt[0]=&x;
    for(i=0;i<10;i++){
        pt[i]=&n[i];
        cout<<"n"<<i+1<<": ";cin>>*pt[i];
        suma+=*pt[i];
    }
    s=&suma;
    cout<<"Suma: "<<*s<<endl;
    for(i=0;i<10;i++){
        cout<<"Pt["<<i<<"]: "<<pt[i]<<" = "<<*pt[i]<<endl;
    }
}
