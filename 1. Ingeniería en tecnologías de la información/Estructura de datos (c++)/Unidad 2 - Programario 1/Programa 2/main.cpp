#include <iostream>

using namespace std;
class Pila{
private:
    int *p=NULL, *aux=NULL;
    int *tope=NULL;
    int tam, cont;
public:
    Pila(){}
    Pila(int t){
        tam=t;
        p=new int[tam];
        aux=new int[tam];
        cont = 0;
    }
    void push(int);
    void voltearPila();
    void imprime();
};
void Pila::push(int n){
    if(cont<tam){
        p[cont]=n;
        tope=&p[cont];
        cont++;
    }
    else{
        cout<<"La pila esta llena"<<endl;
    }
}
void Pila::voltearPila(){
    int i;
    cout<<"\nPila volteada"<<endl;
    for (i=0;i<cont;i++){
        aux[i]=*tope;
        cout<<"["<<aux[i]<<"]";
        tope--;
    }
    cout<<endl;
}
void Pila::imprime(){
    int i;
    if(cont>0){
        for(i=0;i<cont;i++){
            cout<<"["<<p[i]<<"]";
        }
        cout<<"\nTope = "<<*tope<<endl;
    }
    else{
        cout<<"No hay elementos en la Pila"<<endl;
    }
}
int main()
{
    Pila p = Pila(5);
    p.push(4);
    p.push(3);
    p.push(7);
    p.push(8);
    p.push(2);
    p.imprime();
    p.voltearPila();
}
