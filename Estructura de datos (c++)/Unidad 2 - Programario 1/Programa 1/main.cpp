#include <iostream>

using namespace std;

class Pila{
private:
    int *p=NULL;
    int *tope=NULL;
    int tam, cont;
public:
    Pila(){}
    Pila(int t){
        tam=t;
        p=new int[tam];
        cont = 0;
    }
    void push(int);
    void imprime();
};
void Pila::push(int n){
    if(cont<tam){
        p[cont]=n;
        tope=&p[cont];

        if(cont>0){
            if(p[cont]==p[cont-1]){
                tope=&p[cont-1];
                p[cont]=NULL;
            }
            else
                cont++;
        }
        else
            cont++;
    }
    else{
        cout<<n<<" no se almaceno, pila llena"<<endl;
    }
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
    Pila p = Pila(7);
    p.push(1);
    p.push(1);
    p.push(3);
    p.push(2);
    p.push(4);
    p.push(5);
    p.push(5);
    p.push(7);
    p.imprime();
}
