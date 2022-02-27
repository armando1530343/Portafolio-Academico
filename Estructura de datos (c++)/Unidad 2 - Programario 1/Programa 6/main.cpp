#include <iostream>
#include <stdlib.h>

using namespace std;
template <class T>
class ColaCircular{
private:
    int primero, longitud, elementos, ubicacion;
    T *cola = NULL;
public:
    ColaCircular(int);
    void push(T);
    void pop();
    void eliminaRepetidos();
    void imprimir();
};
template <class T>
ColaCircular<T>::ColaCircular(int l){
    longitud=l;
    cola = new T[longitud];
    elementos=0;
    primero=0;
}
template <class T>
void ColaCircular<T>::push(T dato){
    if(elementos<longitud){
        ubicacion = (primero+elementos)%longitud;
        *(cola+ubicacion) = dato;
        if(ubicacion>0){
            if(cola[ubicacion]==cola[ubicacion-1])
                cola[ubicacion]=NULL;
            else
                elementos++;

        }
        else{
            if(cola[0]==cola[longitud-1]||cola[0]==cola[1])
                cola[0]=NULL;
            else
                elementos++;
        }
    }
    else{
        cout<<"El dato "<<dato<<" no se almaceno, la cola esta llena\n"<<endl;
    }
}
template <class T>
void ColaCircular<T>::pop(){
    T aux;
    if(elementos>0){
        *(cola+primero)=NULL;
        primero = (primero+1)%longitud;
        elementos--;
    }
    else{
        cout<<"La cola esta vacia"<<endl;
    }
    cout<<endl;
}
template <class T>
void ColaCircular<T>::imprimir(){
    int i,j;
    if(elementos>0){
        j=primero;
        for(i=1;i<=elementos;i++){
            cout<<"cola["<<j<<"]="<<*(cola+j)<<endl;
            if(j==longitud-1){
                j=-1;
            }
            j++;
        }
    }
    else{
        cout<<"La cola esta vacia"<<endl;
    }

    cout<<endl;
}
int main()
{
    ColaCircular<int> cola(5);
    cola.push(4);
    cola.push(4);
    cola.push(5);
    cola.push(3);
    cola.push(4);
    cola.push(9);
    cola.push(9);
    cola.imprimir();
    system("pause");

    cola.pop();
    cola.push(9);
    cola.imprimir();
}
