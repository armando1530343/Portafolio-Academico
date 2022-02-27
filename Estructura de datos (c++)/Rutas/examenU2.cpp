#include <iostream>
#include <cmath> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <time.h>
#include "ListaCircular.h"

#define NUM_RUTAS 3

using namespace std;

/* Creamos un struct para simular la bateria (acumulador o pila)*/
struct Battery{
    Battery() {carga = 120;} // Constructor y Duracion max de 120 Km
    double carga;
    double reduce(double charge); // Metodo para reducir carga de la bateria
    void recarga(); // Metodo para recargar la bateria
    bool vacia(); // Metodo para validar si la bateria esta vacia
};

// Metodo para validar si la bateria esta vacia
bool Battery::vacia(){

     return carga <= 0;
}

// Metodo para recargar la bateria
void Battery::recarga(){
     carga = 120; // Recargamos la bateria al max. (120 km)
}

// Metodo para reducir carga de la bateria
double Battery::reduce(double charge)
{
   if(charge<=carga){ // Si la carga a reducir es menor o igual a la actual
     carga -= charge; // Reducimos la carga 
     return carga; // Devolvemos la carga restante
   }else{
     return -1; // Se devuelve -1 en caso de error al decrementar valor mayor a la capacidad actual
   }
}

struct coordenadas
{
    float x, y, num_lineas=0;
};

ListaCircular *lista;

vector <coordenadas> coord_estRch;
vector <coordenadas> coord_problem10;
vector <coordenadas> coord_prueba;

ListaCircular *PuntoActual[NUM_RUTAS]; // lista de recorrido
Battery pila[NUM_RUTAS]; // Pila para controlar la energia del recorrido
vector <int> puntos_de_recarga[NUM_RUTAS]; // Vector para guardar los puntos de recarga

int* getPermutacion(int n){

    /*
        
    la funcion 'getPermutacion' genera un arreglo de indices desordenados pasando como referencia
    el parametro que indica la longitud de dicho arreglo (n) y retornara una variable de tipo
    puntero que se refiere a un arreglo

    */

    int *permutacion = new int[n];
    
    for(int i = 0; i < n; i++){
        int num;
        if(i == 0){
           permutacion[i] = 1 + rand() % n;
        }
        else{
            
            while(true){
                permutacion[i] = 1 + rand() % n;

                bool existe = false;
                for(int j = 0; j < i; j++){
                    if(permutacion[i] == permutacion[j]){
                        existe = true;
                        break;
                    }
                }
                if(existe == false)
                    break;
            }

        }
        cout << permutacion[i] << ", ";
    }

    return permutacion;
}

ListaCircular* generarListaCircular(int *permutacion, int n){

    ListaCircular *lista = NULL;
    ListaCircular *ultimo = NULL;
    int cantidad = 0;
    /*

    la funcion 'generarListaCircular' genera un lista enlazada usando la clase 'ListaCircular' y se añaden
        las coordenadas del archivo a un nodo segun el orden de la permutacion generada (*permutacion)

    */

    for(int i = 0; i < n; i++){
        for(int j = 0; j < coord_problem10.size(); j++){
            if(permutacion[i]-1 == j){

                if(cantidad == 0){
                    lista = new ListaCircular();
                    lista->setX(coord_problem10[j].x);
                    lista->setY(coord_problem10[j].y);
                    lista->setNoCliente(permutacion[i]);
                    lista->setDistLocal(0);
                    lista->setDistTotal(0);
                    ultimo = lista;
                }
                else{
                    ultimo->setSiguiente(new ListaCircular());
                    ultimo->getSiguiente()->setAnterior(ultimo);
                    ultimo = ultimo->getSiguiente();
                    ultimo->setX(coord_problem10[j].x);
                    ultimo->setY(coord_problem10[j].y);
                    ultimo->setDistLocal(sqrt(pow(ultimo->getX() - ultimo->getAnterior()->getX(),2) + pow(ultimo->getY() - ultimo->getAnterior()->getY(),2)));
                    ultimo->setDistTotal(ultimo->getAnterior()->getDistTotal() + ultimo->getDistLocal());
                    ultimo->setNoCliente(permutacion[i]);
                }
                ultimo->setSiguiente(lista);
                lista->setAnterior(ultimo);
                lista->setDistLocal(sqrt(pow(lista->getX() - lista->getAnterior()->getX(),2) + pow(lista->getY() - lista->getAnterior()->getY(),2)));
                lista->setDistTotal(lista->getAnterior()->getDistTotal() + lista->getDistLocal());

                cantidad ++;
            }
        }
    }
    return lista;
}

float generarRutas(int indiceRuta, int n){

    int *permutacion = getPermutacion(n);

    PuntoActual[indiceRuta] = generarListaCircular(permutacion, n);

    float distancia_recorrida = 0;

    cout << "\n\n>>> Ruta " << indiceRuta+1 <<  " - Control de una pila (Duracion Max: 120 Km.)\n" << endl;
    
    for(int i = 0; i < n+1; i++){
        if (i == 0){ // Mostramos la ubicacion inicial
            cout << "\n ->[No.Cliente:" << PuntoActual[indiceRuta]->getNoCliente() << 
            "\tDistLocal: 0\t DistTotal: 0\tBattery: " << pila[indiceRuta].carga << " km]" << endl;
        }
        else{
            // Recargamos pila en caso de estar descargada.
            if(pila[indiceRuta].vacia())
                pila[indiceRuta].recarga();
                       
            // Validamos si la distancia recorrida actual es menor o igual a la carga actual
            if(PuntoActual[indiceRuta]->getDistLocal() <= pila[indiceRuta].carga){ 
               pila[indiceRuta].reduce(rint(PuntoActual[indiceRuta]->getDistLocal()));// Si es se reduce la carga.
            }            
                                    
            cout << " ->[No.Cliente:" << PuntoActual[indiceRuta]->getNoCliente();
            cout << "\tDistLocal: " << PuntoActual[indiceRuta]->getDistLocal();
            cout << "\tDistTotal: " << PuntoActual[indiceRuta]->getDistTotal();
            cout << "\tBattery: " << rint(pila[indiceRuta].carga) << " km]" << endl;

            // Validamos si la distancia siguiente es mayor a la carga actual
            if(PuntoActual[indiceRuta]->getSiguiente()->getDistLocal()>pila[indiceRuta].carga){                
               puntos_de_recarga[indiceRuta].push_back(PuntoActual[indiceRuta]->getNoCliente());                                                                        
               pila[indiceRuta].recarga();// Si es, recargamos la pila
            } 
                                              
        }
        PuntoActual[indiceRuta] = PuntoActual[indiceRuta]->getSiguiente();  // Pasamos al siguiente nodo 

        if(i == n-1)
            distancia_recorrida = PuntoActual[indiceRuta]->getDistTotal();      
    }
    
    // Mostramos puntos de recarga
    cout << "\n\n " << puntos_de_recarga[indiceRuta].size() << " puntos de recarga de " << n << ": " << endl;
    for(int i=0;i<puntos_de_recarga[indiceRuta].size();i++){
            if(i==0){
                 cout << "  No. de Clientes:\n   [" << puntos_de_recarga[indiceRuta][i] << ", "; 
            }else if(i==puntos_de_recarga[indiceRuta].size()-1){
                  cout << puntos_de_recarga[indiceRuta][i] << "]" << endl;
            }else{
                 cout << puntos_de_recarga[indiceRuta][i] << ", ";
            }
    }

    return distancia_recorrida;
}

vector<coordenadas> leer_archivo_coordenadas(const char *name){

    fstream archivo(name);
    vector<coordenadas> archivo_coords;

    if(archivo.fail()){
        cout << " El archivo " << name << " no existe" << endl;
        exit(0);
    }

    /*
    
    3. En el siguiente ciclo while se lee cada linea del archivo "EstRch.txt" tomando en cuenta a partir de la linea 3
    4. Cada linea leida se guarda en la variable string llamada "linea" que leera las coordenadas X y Y
    5. La variable "linea" se debera separar por valores numericos con ayuda del caracter de espacio 

    */    

    string linea;
    int lineas = 0;

    // esta variable guarda el numero de coordenadas del archivo Problem10-Fisher.txt
    int n = 0;

    while(getline(archivo, linea)){


        if(linea[0] == '\t' && (linea[1] >= 48 && linea[1] <= 57)){
        

            string numero = "";
            int cont_num = 0;

            coordenadas coord;
            
            /*

            6.la variable 'coord' un objeto del struct 'coordenadas' que contiene las variables 'x' y 'y'
            7.en la variable 'coord.x' se guardara el valor de la coordenada x
            8.en la variable 'coord.y' se guardara el valor de la coordenada y

            */

            int inicio;

            if(lineas <= 11)
                inicio = 3;
            else
                inicio = 4;

            for(int i = inicio; i < linea.length(); i++){
                if(linea[i] != ' '){
                    numero += linea[i];
                }
                else{
                    coord.x = strtof((numero).c_str(), 0);
                    numero = "";
                    cont_num++;
                }
                if(i == linea.length()-1){
                    coord.y = strtof((numero).c_str(), 0);

                    /*
                    
                    9.en el vector llamado 'coord_estRch' se iran almacenando las coordenadas del objeto 'coord'
                    10.se trabajara con este vector mas adelante

                    */
                    archivo_coords.push_back(coord);
                }
            }
            n++;
        }
        lineas++;
    }

    archivo_coords[0].num_lineas = n;


    return archivo_coords;
}

int main(int argc, char const *argv[])
{	


    srand(time(NULL));

    /*

    1.se guardan los nombres de los archivos en la variable 'argv'
    2.se verifica si los archivos existen en el directorio
    
    */

    argv[1] = "Problem11-Fisher.txt";
    argv[2] = "Problem10-Fisher.txt"; 

    // la funcion 'leer_archivo_coordenadas' lee un archivo de texto con el parametro del nombre del archivo
    // y devuelve un vector con las coordenadas leidas numericamente  

    coord_estRch = leer_archivo_coordenadas(argv[1]);
    coord_problem10 = leer_archivo_coordenadas(argv[2]);

    int n = coord_problem10[0].num_lineas;

    //.-----------------------------------

    /*
    
    11. se imprimen las coordenadas del archivo EstRch.txt para verificar que se guardaron correctamente
    12. se imprimen las coordenadas del archivo Problem10-Fisher.txt para verificar que se guardaron correctamente

    */

    cout << "\n\n Archivo: EstRch.txt" << endl;

    for(int i = 0; i < coord_estRch.size(); i++){
        
        /*
        
        13. se imrimen las coordenadas almacenadas en el arreglo 'coord_estRch'   
        14. accediendo a los valores 'x' y 'y' del objeto 'coord' que se almaceno
        
        */
        cout << "x: " << coord_estRch[i].x << "\ty: " << coord_estRch[i].y << endl;
    }

    cout << "\n Archivo: Problem10-Fisher.txt" << endl;

    for(int i = 0; i < coord_problem10.size(); i++){
        /*
        
        15. se imrimen las coordenadas almacenadas en el arreglo 'coord_problem10'   
        16. accediendo a los valores 'x' y 'y' del objeto 'coord' que se almaceno
        
        */
        cout << "x: " << coord_problem10[i].x << "\ty: " << coord_problem10[i].y << endl;
    }

    //-----PUNTO 1------

    cout << "\n\n --- PUNTO 1: Elaborar una matriz de distancias relacionando los puntos de EstRch.txt entre si mismos\n" << endl;

    /*

        17.se crea una matriz de dimensiones iguales haciendo referencia al numero de coordenadas del archivo EstRch.txt 
            (16 x 16)

        18.se recorre el vector 'coord_estRch' con dos ciclos anidados para comparar filas y columnas 
            (se comparan las coordenadas de los puntos)


    */

    float matriz_distancias[coord_estRch.size()][coord_problem10.size()];

    for(int i = 0; i < coord_estRch.size(); i++){
        for(int j = 0; j < coord_problem10.size(); j++){
            
            float x1 = coord_estRch[i].x;
            float y1 = coord_estRch[i].y;
            float x2 = coord_problem10[j].x;
            float y2 = coord_problem10[j].y;

            /*
            
            19. Se implementa la formula de distancia entre dos puntos

            */
            matriz_distancias[i][j] = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

            printf("[%.2f] ", matriz_distancias[i][j]);

        }
        cout << endl;
    }

    
    /*--- PUNTO 2: Generar un arreglo llamado permutacion de tamano n donde n representa el numero de puntos 
    contenidos en el archivo de texto Problem10-Fisher.txt */
    
    //int permutacion[n];

    cout << "\n\n Permutacion Problem10-Fisher (Orden de los nodos):\n " << endl;

    /*
    
    20.la funcion 'getPermutacion' genera un arreglo de indices desordenados pasando como referencia
        el parametro que indica la longitud de dicho arreglo (n) y retornara una variable de tipo
        puntero que se refiere a un arreglo

    21.como sofia no entiende que valor tiene n, aqui yo le recuerdo que n=45 que es el numero de coordenadas 
        del archivo Problem10-Fisher.txt

    22.la variable '*permutacion' guardara lo que devuelva la funcion 'getPermutacion' ya con los
        valores desordenados

    */

    int *permutacion = getPermutacion(n);   
    cout << endl;

    /*---PUNTO 4: Crear una lista circular que una todos los puntos en el orden que marca la
    permutacion teniendo en cuenta que se debera regresar al punto de inicio*/

    /*
    
    23.la funcion 'generarListaCircular' genera un lista enlazada usando la clase 'ListaCircular' y se añaden
        las coordenadas del archivo a un nodo segun el orden de la permutacion generada (*permutacion)

    */

    lista = generarListaCircular(permutacion, n);
    
    ListaCircular *recorrido = lista;

    cout << "\n\nLista Circular - Problem10-Fisher (Coordenadas de Puntos):\n " << endl;

    /*
    
    24. Se imprimen los valores X y Y de los nodos de la lista circular generada

    */

    for(int i = 0; i < n; i++){
        cout << "--->[" << recorrido->getX() << "," << recorrido->getY() << "]";
        recorrido = recorrido->getSiguiente();
    }
    cout << endl;

    recorrido = lista;



    cout << "\n\n Lista Circular - CIRCUITO Problem10-Fisher (iniciando y terminando con el primer nodo):\n " << endl;

    for(int i = 0; i < n+1; i++){
        if (i == 0){
            cout << " ->[No.Cliente:" << recorrido->getNoCliente() << "\tDistLocal: 0\t DistTotal: 0]" << endl;
        }
        else{
            cout << " ->[No.Cliente:" << recorrido->getNoCliente();
            cout << "\tDistLocal: " << recorrido->getDistLocal();
            cout << "\tDistTotal: " << recorrido->getDistTotal();
            cout  << "]" << endl;
        }
        recorrido = recorrido->getSiguiente();
    }
    cout << endl;
    
    /*------ RUTAS ALEATORIAS  >>  Control de una pila (bateria) */    
    
    float distancias[NUM_RUTAS];// = generarRutas(0, n);
    float mayor = 0;
    float menor = 1000000;
    int indice_mayor = 0;
    int indice_menor = 0;
    for(int i = 0; i < NUM_RUTAS; i++){
        distancias[i] = generarRutas(i, n);
        cout << "Distancia Ruta " << i+1 << ": " << distancias[i] << endl;

        if(distancias[i] > mayor){
            mayor = distancias[i];
            indice_mayor = i;
        }
        if(distancias[i] < menor){
            menor = distancias[i];
            indice_menor = i;
        }
    }

    cout << "\n\n  << La Ruta " << indice_menor+1 << " es la mas corta con un recorrido de " << menor << endl;
    cout << "\n\n  << La Ruta " << indice_mayor+1 << " es la mas larga con un recorrido de " << mayor << endl;
    return 0;

}