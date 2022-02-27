#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED

using namespace std;

class Alumno{
private:
    string materia, nombre;
public:
    Alumno(){}
    Alumno(string n, string m){
        nombre=n;
        materia=m;
    }
    string getNombre(){
        return nombre;
    }
    void setNombre(string n){
        nombre=n;
    }
    string getMateria(){
        return materia;
    }
};



#endif // ALUMNO_H_INCLUDED
