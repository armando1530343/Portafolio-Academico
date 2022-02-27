#include <iostream>
#include <stdlib.h>

using namespace std;

template<class T>
class DobleCola{
private:
    T *cola;
    int primero, ultimo, longitud, cont;
public:
    DobleCola(){}
    DobleCola(int t){
        longitud=t;
        cola=new T[longitud];
        primero=0, ultimo=0;
        cont=0;
    }
    int insertaIzq(T);
    int insertaDer(T);
    int eliminaIzq();
    int eliminaDer();
    int colaLlena();
    int colaVacia();
    void imprime();
};
template<class T>
int DobleCola<T>::insertaIzq(T elemento){
    int i,j;
    if(colaLlena()==0){
        if(cont>0){
            for(i=primero;i<longitud;i++){
                if(cola[i]==NULL){
                    ultimo=i;
                    break;
                }
            }
            for(j=i;j>primero;j--)
                cola[j]=cola[j-1];
        }
        cola[primero]=elemento;
    }
    cont++;
    imprime();
}
template<class T>
int DobleCola<T>::insertaDer(T elemento){
    int i,j;
    if(colaLlena()==0){
        cola[ultimo]=elemento;
        ultimo++;
    }
    cont++;
    imprime();
}
template <class T>
int DobleCola<T>::eliminaIzq(){
    int i;
    if(colaVacia()==0){
        for(i=0;i<cont-1;i++)
            cola[i]=cola[i+1];
    }
    else
        cout<<"No hay elementos"<<endl;
    cont--;
    imprime();
}
template <class T>
int DobleCola<T>::eliminaDer(){
    int i;
    if(colaVacia()==0){
        cola[ultimo]=NULL;
        ultimo--;
    }
    else
        cout<<"No hay elementos"<<endl;
    cont--;
    imprime();
}
template <class T>
int DobleCola<T>::colaLlena(){
    int i;
    if(cont>=longitud)
        return 1;
    return 0;
}
template <class T>
int DobleCola<T>::colaVacia(){
    int i;
    if(cont==0)
        return 1;
    return 0;
}
template <class T>
void DobleCola<T>::imprime(){
    int i;
    for(i=0;i<cont;i++)
        cout<<"["<<cola[i]<<"]";
    cout<<endl;
}
int main()
{
    DobleCola<int> dc(5);
    dc.insertaIzq(3);
    dc.insertaIzq(4);
    dc.insertaDer(5);
    dc.insertaIzq(2);
    dc.eliminaIzq();
    dc.eliminaDer();
    dc.insertaDer(9);
}
