#include <iostream>

using namespace std;

int main()
{
    int n, i, j, cont;
    cout<<"Ingresa un entero: ";cin>>n;
    int matriz[n+1][n+1];
    for(i=0;i<n+1;i++){
        cont=i;
        for(j=0;j<n+1;j++){
            matriz[i][j]=cont;
            cont++;
            cout<<"["<<matriz[i][j]<<"] ";
        }
        cout<<"\n";
    }

    return 0;
}
