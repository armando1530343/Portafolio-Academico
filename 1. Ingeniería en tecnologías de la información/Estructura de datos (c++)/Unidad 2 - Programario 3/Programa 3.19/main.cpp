#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

int main()
{
    srand(time(NULL));
    char letras[1000];
    vector<char> aux;
    int repite;
    int i, j;
    for(i=0;i<1000;i++){
        letras[i]=65+rand()%26;
        cout<<letras[i]<<" ";
        if(i==0){aux.push_back(letras[i]);}
        if(i>0){
            for(j=i-1;j>=0;j--){
                if(letras[i]==letras[j]){
                    break;
                }
                else if(j==0){
                    aux.push_back(letras[i]);
                }
            }
        }
    }
    cout<<"\n"<<endl;
    for(i=0;i<aux.size();i++){
        repite=0;
        for(j=0;j<1000;j++){
            if(aux[i]==letras[j]){
                repite++;
            }
        }
        cout<<aux[i]<<" = "<<repite<<endl;
    }
}
