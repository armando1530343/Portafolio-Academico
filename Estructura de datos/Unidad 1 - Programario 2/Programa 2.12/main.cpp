#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//template <typename Tipo>
class MatrizPD{
    private:
        int **matriz;
        int **mTrans;
        int **mSuma;
        int **mResta;
        int **mMulti;
        int filas, columnas;
    public:
        //MatrizPD(){}
        MatrizPD(int, int);
        void traspuesta();
        int simetrica();
        void operator+(MatrizPD);
        void operator-(MatrizPD);
        void operator*(MatrizPD);
        int getFilas();
        int getColumnas();
};
MatrizPD::MatrizPD(int f, int c){
    filas=f;
    columnas=c;
    int ceros = columnas*.7;
    int n = columnas-ceros;
    int i, j, num;
    matriz=new int*[filas];
    for(i=0;i<filas;i++){
        matriz[i]=new int[columnas];
    }
    for(i=0;i<filas;i++){
        num=0;
        for(j=0;j<columnas;j++){
            matriz[i][j]=rand()%2;
            if(matriz[i][j]!=0){
                matriz[i][j]=1+rand()%9;
                num++;
            }
            if(num>n){
                matriz[i][j]=0;
            }
            else if(num==0){
                matriz[i][rand()%columnas]=1+rand()%9;
            }
            cout<<"["<<matriz[i][j]<<"] ";
        }
        cout<<"\n";
    }
}
void MatrizPD::traspuesta(){
    int i, j;
    mTrans=new int*[columnas];
    for (i=0;i<columnas;i++){
        mTrans[i]=new int[filas];
    }
    cout<<"\nMatriz Transpuesta"<<endl;
    for(i=0;i<columnas;i++){
        for(j=0;j<filas;j++){
            mTrans[i][j]=matriz[j][i];
            cout<<"["<<mTrans[i][j]<<"] ";
        }
        cout<<"\n";
    }
}
void MatrizPD::operator+(MatrizPD b){
    int i, j;
    if(filas==b.getFilas()&&columnas==b.getColumnas()){
        mSuma = new int*[filas];
        cout<<"\nSuma"<<endl;
        for(i=0;i<filas;i++){
            mSuma[i] = new int[columnas];
            for(j=0;j<columnas;j++){
                mSuma[i][j]=matriz[i][j]+b.matriz[i][j];
                cout<<"["<<mSuma[i][j]<<"] ";
            }
            cout<<"\n";
        }
    }
}
void MatrizPD::operator-(MatrizPD b){
    int i, j;
    if(filas==b.getFilas()&&columnas==b.getColumnas()){
        mResta = new int*[filas];
        cout<<"\nResta"<<endl;
        for(i=0;i<filas;i++){
            mResta[i] = new int[columnas];
            for(j=0;j<columnas;j++){
                mResta[i][j]=matriz[i][j]-b.matriz[i][j];
                cout<<"["<<mResta[i][j]<<"] ";
            }
            cout<<"\n";
        }
    }
}
void MatrizPD::operator*(MatrizPD b){
    int i, j, k;
    if(columnas==b.getFilas()){
        mMulti = new int*[filas];
        for(i=0;i<filas;i++){
            mMulti[i] = new int[b.getColumnas()];
        }
        cout<<"Multiplicacion"<<endl;
        for (i=0;i<filas;i++){
            for(j=0;j<b.getColumnas();j++){
                mMulti[i][j]=0;
                for(k=0;k<b.getFilas();k++){
                    mMulti[i][j]+=matriz[i][k]*b.matriz[k][j];
                }
                cout<<"["<<mMulti[i][j]<<"] ";
            }
            cout<<"\n";
        }
    }
}
int MatrizPD::simetrica(){
    if(filas==columnas){
        return 1;
    }
    return 0;
}
int MatrizPD::getFilas(){
    return filas;
}
int MatrizPD::getColumnas(){
    return columnas;
}

int main()
{
    srand(time(NULL));
    cout<<"\nMatriz A"<<endl;
    MatrizPD a = MatrizPD(5,5);
    cout<<"\nMatriz B"<<endl;
    MatrizPD b = MatrizPD(4,5);
    cout<<"A simetrica = "<<a.simetrica()<<endl;
    cout<<"B simetrica = "<<b.simetrica()<<endl;
    a.traspuesta();
    a+b;
    a-b;
    a*b;
    return 0;
}
