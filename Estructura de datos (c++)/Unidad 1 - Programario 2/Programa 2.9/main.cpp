#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

class ADN{
    private:
        char matrizADN[8];
    public:
        ADN(char,char,char,char,char,char,char,char);
        bool comparar(ADN);
};
ADN::ADN(char c1,char c2,char c3,char c4,char c5,char c6,char c7,char c8){
    matrizADN[0]=c1;
    matrizADN[1]=c2;
    matrizADN[2]=c3;
    matrizADN[3]=c4;
    matrizADN[4]=c5;
    matrizADN[5]=c6;
    matrizADN[6]=c7;
    matrizADN[7]=c8;
    int i, j;
    for(i=0;i<8;i++){
        cout<<""<<matrizADN[i]<<" ";
    }
    cout<<"\n";
}
bool ADN::comparar(ADN b){
    int i, j, k;
    int matriz[8];
    string secuencia="", compara;
    for(i=0;i<8;i++){
        secuencia+=matrizADN[i];
        //cout<<secuencia[i];
    }
    //cout<<secuencia;
    char aux;
    for(i=0;i<8;i++){
        compara="";
        for(j=0;j<8;j++){
            compara+=b.matrizADN[j];
        }
        if(secuencia!=compara){
            aux=b.matrizADN[7];
            for(k=7;k>0;k--){
                b.matrizADN[k]=b.matrizADN[k-1];
            }
            b.matrizADN[0]=aux;
        }
        else{
            return true;
            break;
        }
    }
    return false;
}

int main()
{
    srand(time(NULL));
    ADN a = ADN('A', 'C', 'C', 'T', 'A', 'T', 'C', 'T');
    ADN b = ADN('T', 'A', 'C', 'C', 'T', 'A', 'T', 'C');
    cout<<"\n\nSecuencias Iguales = "<<a.comparar(b);
    return 0;
}
