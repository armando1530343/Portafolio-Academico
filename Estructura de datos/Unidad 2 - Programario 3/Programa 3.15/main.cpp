#include <iostream>

using namespace std;

int main()
{
    int millas[]={15, 22, 16, 18, 27, 23, 20};
    int *dist=new int;
    int i;
    for(i=0;i<7;i++){
        *(dist+i)=millas[i];
        cout<<*(dist+i)<<", ";
    }
    cout<<endl;
}
