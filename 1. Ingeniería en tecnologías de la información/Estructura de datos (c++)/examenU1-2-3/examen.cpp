#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

/*
INTEGRANTES DEL EQUIPO:

- 1530425 JESUS EDUARDO GARCIA RIOS
- 1630237 HECTOR ABRAHAM POSADA REYNA

*/


using namespace std;

struct Ciudad{
    float coord_X;
    float coord_Y;
    float distancia_recorrida;
    Ciudad *siguiente = NULL;
    Ciudad *anterior = NULL;
};


int main(int argc, char const *argv[])
{

	/*----------------------------------------------------------------------------------------------------*/
    /*--------------------------------------------EXAMEN 1------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------*/
	ifstream archivo_entrada(argv[1]);
    string linea;

    Ciudad *ciudades = NULL, *inicio = NULL, *inicio1 = NULL, *inicio2 = NULL;

    float distancia_total = 0;


    float coordenadas[29][3];
    int i = 0, j, cont = 0;

    while(getline(archivo_entrada, linea)) {

    	if(i >= 7 && i < 36){
    		string numero1 = "";
            string numero2 = "";
            string numero3 = "";
            int espacios = 0;
    		for(int j = 0; j < linea.length(); j++){
                if(linea[j] == ' '){
                    espacios++;
                    continue;
                }
                if(espacios == 0)
                    numero1 += linea[j];

                if(espacios == 1)                    
                    numero2 += linea[j];

                if(espacios == 2)
                    numero3 += linea[j];
    		}
            coordenadas[cont][0] = std::stof(numero1);
            coordenadas[cont][1] = std::stof(numero2);
            coordenadas[cont][2] = std::stof(numero3);
            //cout << numero1 << " " << numero2 << " " << numero3 << endl;
    		//cout << coordenadas[cont][0]<< " " << coordenadas[cont][1] << " " << coordenadas[cont][2] << endl;
            //cout << coordenadas[cont][0] << ", " << coordenadas[cont][1] << endl;
    		cont ++;
    	}
    	i++;       
    }
    /*----------------------------------------------------------------------------------------------------*/
    /*--------------------------------------------EXAMEN 2------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------*/
    float x1, y1, x2, y2;
    //se construye la lista circular
    for (i = 0; i < 29; ++i){
        if(i == 0){
            ciudades = new Ciudad();
            
            ciudades->coord_X = coordenadas[i][1];
            ciudades->coord_Y = coordenadas[i][2];
            
            inicio = ciudades;
            inicio1 = ciudades;
            inicio2 = ciudades;
        }
        else{
            ciudades->siguiente = new Ciudad();
            ciudades->siguiente->anterior = ciudades;//apunta a la posicion anterior de la lista
            ciudades = ciudades->siguiente; //apunta a la posicion siguiente de la lista
            ciudades->coord_X = coordenadas[i][1];
            ciudades->coord_Y = coordenadas[i][2];
            x1 = ciudades->coord_X;
            y1 = ciudades->coord_Y;
            x2 = ciudades->anterior->coord_X;
            y2 = ciudades->anterior->coord_Y;

            //calculo de distancia entre la ciudad actual con la anterior (formula de distancia euclidiana)
            ciudades->distancia_recorrida = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));

            distancia_total += ciudades->distancia_recorrida;

            if(i == 28){
                ciudades->siguiente = inicio;
                x2 = inicio->coord_X;
                y2 = inicio->coord_Y;
                inicio->distancia_recorrida = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
            }

        }
    }
    cout << "<< COORDENADAS DE CIUDADES >>\n" << endl;
    for (i = 1; i <= 29; ++i){
        cout << "Ciudad " << i << " = coord_X: " << inicio->coord_X << " - coord_Y: " << inicio->coord_Y << endl;
        //if(i == 1) cout << " - Recorrido (Cd." << i << " - Cd.29):";
        //else cout << " - Recorrido (Cd." << i << " - Cd." << i-1 << "):";
        //cout << inicio->distancia_recorrida << endl;
        inicio = inicio->siguiente;
    }
    cout << "\n\n<< DISTANCIA RECORRIDA POR CIUDAD (LISTA CIRCULAR)>>\n" << endl;

    for (i = 1; i <= 30; ++i){
        if(i == 30)
            cout << "[Cd.1: ";
        else
            cout << "[Cd." << i << ": ";

        cout << inicio->distancia_recorrida << "] -> ";

        inicio = inicio->siguiente;
    }
    cout << "\n\n\n>> DISTANCIA TOTAL RECORRIDA: " << distancia_total << endl;

 
    /*----------------------------------------------------------------------------------------------------*/
    /*--------------------------------------------EXAMEN 3------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------*/
    cout << "\n\n>> MATRIZ DE DISTANCIAS\n" << endl;
    float matriz[29][29];

    for (i = 0; i < 29; ++i){
    	x1 = inicio1->coord_X;
    	y1 = inicio1->coord_Y;
    	for (j = 0; j < 29; j++)
    	{
    		x2 = inicio2->coord_X;
    		y2 = inicio2->coord_Y;
    		matriz[i][j] = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    		cout<<"["<< matriz[i][j] << "] ";
    		inicio2 = inicio2->siguiente;
    	}
    	cout<<endl;
    	inicio1 = inicio1->siguiente;
    }

	return 0;
}