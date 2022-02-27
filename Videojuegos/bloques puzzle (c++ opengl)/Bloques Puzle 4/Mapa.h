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
		const char *path_pieza;
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
		char** mapa_bits_pieza(const char *);
		float*** coords_mapa_bits_pieza();
		
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
			coord_mapa[i][j] = new float[4];
		
	}

	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 15; j++){
			coord_mapa[i][j][0] = -1;
			coord_mapa[i][j][1] = -1;
			if(matriz[i][j] != '0'){
				float x = (j+1)*casilla + casilla/2 + 50;
				float y = -((i+1)*casilla - casilla/2) + 600;
				coord_mapa[i][j][0] = x;
				coord_mapa[i][j][1] = y;
				int c = matriz[i][j];
				coord_mapa[i][j][2] = float(c);
				coord_mapa[i][j][3] = 5; //indice color

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

char** Mapa::mapa_bits_pieza(const char *path_pieza){

	this->path_pieza = path_pieza;
	
	fstream pieza_file(path_pieza);

	int f = 0;
	int c = 0;
	string linea;
	while(getline(pieza_file, linea)){
		c = linea.size();
		f++;
	}

	pieza_file.close();

	char **pieza_bits = new char*[f];
	for(int i = 0; i < f; i++)
		pieza_bits[i] = new char[c];


	fstream pieza_file2(path_pieza);
	int i = 0;
	while(getline(pieza_file2, linea)){
		for(int j = 0; j < linea.size(); j++){
			pieza_bits[i][j] = linea[j];
		}
		i++;
	}
	pieza_file2.close();

	//cout << "bits: " << pieza_bits[0][0] << endl;

	return pieza_bits;
}
float*** Mapa::coords_mapa_bits_pieza(){
	
	fstream pieza_file(path_pieza);

	int f = 0;
	int c = 0;
	string linea;
	while(getline(pieza_file, linea)){
		c = linea.size();
		f++;
	}
	float ***coords = new float**[f];
	for(int i = 0; i < f; i++){
		coords[i] = new float*[c];
		for(int j = 0; j < c; j++){
			coords[i][j] = new float[4];
			coords[i][j][2] = f;
			coords[i][j][3] = c;
		}
	}

	return coords;
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