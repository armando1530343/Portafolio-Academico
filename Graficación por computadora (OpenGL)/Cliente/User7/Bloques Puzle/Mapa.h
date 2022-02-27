#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Mapa{
	
	private:
		char **matriz;
		const char *path_nivel;
		float casilla;

		struct coord{
			int fila, columna;			
		};

		vector <coord> piezas;
		int num_piezas;

	public:
		Mapa();
		Mapa(const char *);
		float*** generar_coords_mapa();
		char **mapa_bits();
		void ver_mapa();
		void dibuja_hexagono(float, float, int, float*);
		int** nuevaPieza(const char *);
		
};

Mapa::Mapa(){
	
}

Mapa::Mapa(const char *path_nivel){
	this->path_nivel = path_nivel;
	num_piezas = 1;

	matriz = new char*[15];
	for(int i = 0; i < 15;i++)
		matriz[i] = new char[15];

	fstream mapa_nivel(path_nivel);

	string linea;
	int f = 0;
	while(getline(mapa_nivel, linea)){
		for(int i = 0; i < linea.size(); i++){
			matriz[f][i] = linea[i];
		}
		f++;
	}
	casilla = 25.0;
}

char **Mapa::mapa_bits(){return matriz;}

float*** Mapa::generar_coords_mapa(){
	
	float ***coord_mapa = NULL;
	coord_mapa = new float**[15];
	for(int i = 0; i < 15; i++){
		coord_mapa[i] = new float*[15];
		for(int j = 0; j < 15; j++)
			coord_mapa[i][j] = new float[2];
		
	}

	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 15; j++){
			coord_mapa[i][j][0] = -1;
			coord_mapa[i][j][1] = -1;
			if(matriz[i][j] == '1'){
				float x = (j+1)*casilla + casilla/2 + 50;
				float y = -((i+1)*casilla - casilla/2) + 600;
				coord_mapa[i][j][0] = x;
				coord_mapa[i][j][1] = y;

				//cout << "x: " << x << "\ty: " << y << endl;  
				//dibuja_hexagono(x, y);
			}

		}
	}
	return coord_mapa;

}
void Mapa::dibuja_hexagono(float x, float y, int tam, float *color){
	
	for(int i = 0; i < 2; i++){

		glColor3f(i == 0 ? color[0] : 1, i == 0 ? color[1] : 1, i == 0 ? color[2] : 1);
		glBegin(i == 0 ? GL_POLYGON : GL_LINE_LOOP);
		glVertex2f(x - tam/2, y + tam);
		glVertex2f(x + tam/2, y + tam);
		glVertex2f(x + tam*1.5, y);
		glVertex2f(x + tam/2, y - tam);
		glVertex2f(x - tam/2, y - tam);
		glVertex2f(x - tam*1.5, y);
		glEnd();
	}
	
}

int** Mapa::nuevaPieza(const char *path_pieza){
	FILE *archivo_pieza = fopen(path_pieza, "r");

	int f = 0;
	while(!feof(archivo_pieza)){
		int a, b;
		fscanf(archivo_pieza, "%d,%d", &a, &b);
		f++;
	}
	fclose(archivo_pieza);
	archivo_pieza = fopen(path_pieza, "r");

	int **coords_pieza = new int*[f];

	int i = 0;
	while(!feof(archivo_pieza)){
		coords_pieza[i] = new int[5];
		fscanf(archivo_pieza, "%d,%d", &coords_pieza[i][0], &coords_pieza[i][1]);
		coords_pieza[i][2] = f;
		i++;
	}

	fclose(archivo_pieza);
	//cout << "sale" << endl;
	//for(int i = 0; i < piezas.size(); i++)
		//cout << piezas[i].fila << ", " << piezas[i].columna << endl;
	return coords_pieza;
}

void Mapa::ver_mapa(){
	cout << "mapa" << endl;
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 15; j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}



