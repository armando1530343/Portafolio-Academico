#ifndef IMPRESION_H_INCLUDED
#define IMPRESION_H_INCLUDED

using namespace std;

class Impresion{
private:
    char *nombreArchivo;
    char *autor;
    char *hora;
public:
    Impresion(){}
    Impresion(char n[30], char a[20], char h[5]){
        nombreArchivo = new char[30];
        autor = new char[20];
        hora = new char[5];

        nombreArchivo = n;
        autor = a;
        hora = h;
    }
    char* getNombre();
    char* getAutor();
    char* getHora();
};
char* Impresion::getNombre(){
    return nombreArchivo;
}
char* Impresion::getAutor(){
    return autor;
}
char* Impresion::getHora(){
    return hora;
}


#endif // IMPRESION_H_INCLUDED
