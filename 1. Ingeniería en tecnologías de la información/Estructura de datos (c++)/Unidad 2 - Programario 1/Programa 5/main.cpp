#include <iostream>
#include <stdlib.h>

using namespace std;
class Cola{
private:
    int *cola, *aux, *aux2;
    int *tope;
    int cont, itr;
public:
    Cola(){
        cola=NULL;
        aux=NULL, aux2=NULL;
        cont=0;
        tope=NULL;
        itr=0;
    }
    void push(int);
    void pop();
    void invertir();
    void imprime();
};
void Cola::push(int n){
    int i;
    cont++;
    if(tope==NULL){
        cola=new int [cont];
        cola[0]=n;
        //tope=&cola[0];
    }
    else{
        aux=cola;
        cola=new int[cont];
        for(i=0;i<cont-1;i++){
            cola[i]=aux[i];
        }
        cola[cont-1]=n;
    }
    aux2=new int[cont];
    for(i=0;i<cont;i++)
        aux2[i]=cola[i];
    itr=cont-1;
    tope=&aux2[0];
}
void Cola::pop(){
    int i;
    cola[0]=NULL;
    for(i=0;i<cont-1;i++){
        cola[i]=cola[i+1];
    }
    cont--;
}
void Cola::invertir(){
    if(itr>=0){
        cola[itr]=*tope;
        itr--;
        tope++;
        invertir();
    }
}
void Cola::imprime(){
    int i;
    for(i=0;i<cont;i++)
        cout<<"["<<cola[i]<<"]";
    cout<<endl;
}
int main()
{
    Cola c = Cola();
    c.push(3);
    c.push(2);
    c.push(5);
    c.imprime();system("pause");
    c.pop();
    c.imprime();system("pause");
    c.push(1);
    c.push(7);
    c.imprime();system("pause");
    c.invertir();
    c.imprime();system("pause");
    c.push(8);
    c.imprime();
}
