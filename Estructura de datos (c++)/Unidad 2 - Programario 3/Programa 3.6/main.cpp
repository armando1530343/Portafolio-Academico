  #include <iostream>
#include <string.h>

using namespace std;

template <class T>
class Profesor{
private:
    char *nombreProfesor;
    char *departamento;
    int anio;
    T Materia;

public:
    Profesor(char*n, char*d, int a, T mat){
        nombreProfesor=n;
        departamento=d;
        anio=a;
        Materia=mat;
    }
    void cambiaDpto(char*nvoDep){
        departamento=nvoDep;
    }
    void cambiaMat(T*nvaMat){
        Materia=nvaMat;
    }
    void imprime(){
        cout<<"\nNombre: "<<nombreProfesor<<"\nDepartamento: "<<departamento<<"\nAnio de Ingreso: "<<anio<<endl;
        Materia.imprime();
    }
};
template<class T2>
class Materia{
private:
    char *nombre;
    int clave;
    T2 calificacion;
public:
    Materia(){}
    Materia(char*n, int c, T2 calif){
        nombre=n;
        clave=c;
        calificacion=calif;
    }
    void imprime(){
        cout<<"Materia a cargo:"<<nombre<<"  Clave:"<<clave<<"  Calificacion:"<<calificacion<<endl;
    }
};

int main()
{
    Materia<string> mat1("Matematicas",1234,"excelente");
    Materia<double> mat2("Matematicas",1234,9.8);

    Profesor< Materia<string> > profe1("Juan","escolares",2017,mat1);
    profe1.imprime();

    Profesor< Materia<double> > profe2("Pedro","financieros",2017,mat2);
    profe2.imprime();
}
