#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Matriz{
    private:
        int filas, columnas;
        float **matriz, **matrizSuma, **matrizProducto, **matrizTranspuesta;
    public:
        Matriz(int, int);
        void crear();
        void cambiar(int, int, float);
        void imprime();
        int getFilas();
        int getColumnas();
        void suma(Matriz);
        void multiplicacion(Matriz);
        void operator * (Matriz);
        void transpuesta();
};
Matriz::Matriz(int f, int c){

    filas=f;
    columnas=c;
    int i, j;
    matriz = new float*[filas];
    for(i=0;i<filas;i++){
        matriz[i] = new float[columnas];
    }

    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            matriz[i][j]=rand()%10;
        }
    }
}
void Matriz::cambiar(int f, int c, float valor){
    matriz[f][c]=valor;
}
void Matriz::imprime(){
    int i, j;
    //cout<<"\n";
    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            cout<<"["<<matriz[i][j]<<"] ";
        }
        cout<<"\n";
    }
}
void Matriz::suma(Matriz b){
    int i, j;
    if(filas==b.getFilas()&&columnas==b.getColumnas()){
        matrizSuma = new float*[filas];
        for(i=0;i<filas;i++){
            matrizSuma[i] = new float[columnas];
            for(j=0;j<columnas;j++){
                matrizSuma[i][j]=matriz[i][j]+b.matriz[i][j];
                cout<<"["<<matrizSuma[i][j]<<"] ";
            }
            cout<<"\n";
        }
    }
}
void Matriz::multiplicacion(Matriz b){
    int i, j, k;
    if(columnas==b.getFilas()){
        matrizProducto = new float*[filas];
        for(i=0;i<filas;i++){
            matrizProducto[i] = new float[b.getColumnas()];
        }
        for (i=0;i<filas;i++){
            for(j=0;j<b.getColumnas();j++){
                matrizProducto[i][j]=0;
                for(k=0;k<b.getFilas();k++){
                    matrizProducto[i][j]+=matriz[i][k]*b.matriz[k][j];
                }
                cout<<"["<<matrizProducto[i][j]<<"] ";
            }
            cout<<"\n";
        }
    }
}
void Matriz::operator*(Matriz b){
    multiplicacion(b);
}
void Matriz::transpuesta(){
    int i, j;
    matrizTranspuesta=new float*[columnas];
    for (i=0;i<columnas;i++){
        matrizTranspuesta[i]=new float[filas];
    }
    for(i=0;i<columnas;i++){
        for(j=0;j<filas;j++){
            matrizTranspuesta[i][j]=matriz[j][i];
            cout<<"["<<matrizTranspuesta[i][j]<<"] ";
        }
        cout<<"\n";
    }
}
int Matriz::getFilas(){
    return filas;
}
int Matriz::getColumnas(){
    return columnas;
}

int main()
{
    srand(time(NULL));
    int i, j;
    Matriz a = Matriz(2,2);
    Matriz b = Matriz(2,2);
    cout<<"\nA:"<<endl;
    a.imprime();
    cout<<"\nB:"<<endl;
    b.imprime();
    cout<<"\nA + B:\n"<<endl;
    a.suma(b);
    cout<<"\nA x B:\n"<<endl;
    a.multiplicacion(b);
    cout<<"\nA x B (con sobrecarga de operador):\n"<<endl;
    a*b;
    cout<<"\nTranspuesta:\n"<<endl;
    a.transpuesta();
    //a.cambiar(0,1,1.2);
    //a.imprime();
    return 0;
}
