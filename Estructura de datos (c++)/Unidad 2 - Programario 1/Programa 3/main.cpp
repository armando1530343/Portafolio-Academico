#include <iostream>

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
    void operator+(int);
    void operator-(int);
    void imprime();
};
void Cola::operator+(int n){
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
void Cola::operator-(int n){
    int i,j;
    int existe=0;
    if(cont>0){
        for(i=0;i<cont;i++){
            if(cola[i]==n){
                for(j=i;j<cont-1;j++)
                    cola[j]=cola[j+1];
                existe=1;
                break;
            }
        }
        if(existe==1){
            cont--;
            imprime();
        }
        else
            cout<<"No existe el numero "<<n<<" en la cola"<<endl;
    }
    else
        cout<<"La cola no tiene elementos"<<endl;

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
    c+5;
    c+4;
    c+2;
    c.imprime();
    c-5;
    c+6;
    c.imprime();
}
