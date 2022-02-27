#include <iostream>
#include <stdlib.h>

using namespace std;

class Cola{
private:
    int *cola, *aux;
    int *tope;
    int cont;
public:
    Cola(){
        cola=NULL;
        aux=NULL;
        cont=0;
        tope=NULL;
    }
    void push(int);
    void invertir();
    void imprime();
};
void Cola::push(int n){
    int i;
    cont++;
    if(tope==NULL){
        cola=new int [cont];
        cola[0]=n;
        tope=&cola[0];
    }
    else{
        aux=cola;
        cola=new int[cont];
        for(i=0;i<cont-1;i++){
            cola[i]=aux[i];
        }
        cola[cont-1]=n;
    }
}
void Cola::invertir(){
    aux=cola;
    int aux2[cont];
    int i,j=0;;
    for (i=cont-1;i>=0;i--){
        aux2[i]=cola[j];
        j++;
    }
    for(i=0;i<cont;i++)
        cola[i]=aux2[i];

}
void Cola::imprime(){
    int i;
    for(i=0;i<cont;i++)
        cout<<"["<<cola[i]<<"]";
    cout<<endl;
}

int main(){
    Cola c = Cola();
    c.push(3);
    c.push(2);
    c.push(5);
    c.push(9);
    c.imprime();system("pause");
    c.invertir();
    c.imprime();system("pause");
    c.push(8);
    c.imprime();
}
