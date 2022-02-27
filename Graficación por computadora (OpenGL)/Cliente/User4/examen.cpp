#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;


int main(int argc, char const *argv[])
{
	ifstream archivo_entrada(argv[1]);
    string linea;

    float coordenadas[29][3];
    int i = 0, cont = 0;

    while(getline(archivo_entrada, linea)) {

    	if(i >= 7 && i < 36){
    		//cout << linea.length() << endl;
    		string numero1 = "";
            string numero2 = "";
            cout << linea << endl;
    		int col = 0;
    		for(int j = 0; j < linea.length(); j++){
    			if((i <= 15 && j > 0) || (i > 15 && j > 1)){
                    if(linea[j] != ' ' && col == 0){
                        numero1 += linea[j];
                        //cout << numero1 << endl;
                    }

                    else{
                        break;
                        col ++;
                        
                        //coordenadas[cont][0] = std::stof(numero1);
                    }

                    if(col > 0){
                        if(linea[j] != ' ')
                            numero2 += linea[j];
                        else
                            coordenadas[cont][1] = 1.0;
                        
                    }
    				/*if(linea[j] != ' '){
    					numero1 += linea[j];

    					//cout << numero << endl;
    				}
    				else{
    					cout << numero1 << endl;
    					if(numero.length() > 0)
    						coordenadas[cont][col] = std::stof(numero);
    					numero = "";
    					col++;
    				}*/

    				//if(linea[j] != '\n') col = 0;
    			}
    		}
    		//cout << coordenadas[cont][0] << ", " << coordenadas[cont][1] << endl;
    		cont ++;
    	}
    	i++;        
    }

	return 0;
}