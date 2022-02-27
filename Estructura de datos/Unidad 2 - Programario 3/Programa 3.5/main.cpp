#include <iostream>

using namespace std;
template <class T>
class Profesor{
private:
    char *nombreProfesor;
    char *departamento;
    int anio;
    T *Materia;

public:
    Profesor(char*n, char*d, int a, T *mat){
        nombreProfesor=n;
        departamento=d;
        anio=a;
        Materia=mat;
    }
    void cambiaDpto(char*);
    void cambiaMat(T*);
    void imprime();
};
template <class T>
void Profesor<T>::imprime(){
    cout<<"\nNombre: "<<nombreProfesor<<"\nDepartamento: "<<departamento<<"\nAnio de Ingreso: "<<anio<<"\nMateria a Cargo: "<<Materia<<endl;
}
template <class T>
void Profesor<T>::cambiaDpto(char*nvoDep){
    departamento=nvoDep;
}
template <class T>
void Profesor<T>::cambiaMat(T *nvaMateria){
    Materia=nvaMateria;
}
int main()
{
    Profesor<char> nuevo("Armando","Oficina",2017,"Materia");
    nuevo.imprime();
    nuevo.cambiaMat("Matematicas");
    nuevo.imprime();
}
