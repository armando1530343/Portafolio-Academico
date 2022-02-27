#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Mapa.h"
using namespace std;

float colores_piezas[6][3] = {
    {1,0,0}, //rojo
    {1,1,0}, //amarillo
    {0,0,1}, //azul
    {0,1,0}, //verde
    {1,0,1}, //morado
    {1,1,0}  //otro
};


class Game{
private:
	float width const; 
    float height const;
    int Retardo;
	struct Pieza{
	    char **mapa;
	    int *dimension;
	}_pieza;

	float ***coords_mapa;
	char **mapa_bits;
	vector <Pieza> datos_pieza;
	vector <int> coord_piezasX;
	vector <int> coord_piezasY;
	int numero_piezas;

	int tam_hexagono_pieza;

	bool *piezaSeleccionada;
	int *distanciaX_piezas;
	int *distanciaY_piezas;

	
	Mapa nivel[3];
    int indice_nivel;
public:
	//Game(){}
	Game();
	void Run() const;
	void nivel1();
    void nivel2();
    void nivel3();
	void writeBitmapString(void *, string);
	void reshape(int, int) const;
	void display(void) const;
	void TimerFunction(int);
	void mouseControl(int, int, int, int);
	void mouseMotion(int, int);
	void keyInput(unsigned char, int, int);
};
Game::Game(){
    Retardo = 12;
	coords_mapa = NULL;
	mapa_bits = NULL;
	tam_hexagono_pieza = 15.0;
	piezaSeleccionada = new bool[5]{false, false, false, false, false};
	distanciaX_piezas = new int[5]{25,75,125,175,225};
	distanciaY_piezas = new int[5]{200,200,200,200,200};

    nivel[0] = Mapa("Level-Maps/nivel1/nivel1.txt");

}
void Game::Run() const{
    
    
	glutDisplayFunc(display);
    /*glutReshapeFunc(reshape);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
    */
}

void Game::nivel1(){
    if(datos_pieza.size() > 0)
        datos_pieza.clear();

    indice_nivel = 0;

    
    coords_mapa = nivel[indice_nivel].generar_coords_mapa();
    mapa_bits = nivel[indice_nivel].mapa_bits();
    _pieza.mapa = nivel[indice_nivel].mapa_bits_pieza("Level-Maps/nivel1/pieza3.txt");
    _pieza.dimension = nivel[indice_nivel].dimension_mapa_bits_pieza();
    datos_pieza.push_back(_pieza);
    numero_piezas = datos_pieza.size();
}

void Game::writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);
}

void Game::reshape(int w, int h) const
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Game::display(void) const
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    float *color = new float[3]{.2,.2,.2};

    //SE DIBUJA EL MAPA DEL NIVEL
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(coords_mapa[i][j][0] > -1)
                nivel[indice_nivel].dibuja_hexagono(coords_mapa[i][j][0], coords_mapa[i][j][1], 25, color);
        }
    }
    //SE DIBUJAN LAS PIEZAS DEL NIVEL
    int dist_x_pieza = 25;

    for(int p = 0; p < numero_piezas; p++){
        glPopMatrix();
        glTranslatef(0, 0, 0);
        glRotatef(0,0,0,0);

        for(int f = 0; f < datos_pieza[p].dimension[0]; f++){
            for(int c = 0; c < datos_pieza[p].dimension[1]; c++){
                if(datos_pieza[p].mapa[f][c] == '1'){
                    float x = (c+1)*tam_hexagono_pieza + tam_hexagono_pieza/2 + distanciaX_piezas[p];
                    float y = -((f+1)*tam_hexagono_pieza - tam_hexagono_pieza/2) + distanciaY_piezas[p];
                    color = colores_piezas[p];
                    nivel[indice_nivel].dibuja_hexagono(x, y, tam_hexagono_pieza, color);
                }
            }
            //cout << endl;
        }

        glPopMatrix();
    }


    /*
    for(int i = 0; i < coords_pieza[0][2]; i++){
        cout << coords_pieza[i][0] << ", " << coords_pieza[i][1] << endl;
    }*/

    glFlush();


}
void Game::TimerFunction(int value){



    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);

}

void Game::mouseControl(int button, int state, int x, int y){

    y = height - y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        /*for(int p = 0; p <  numero_piezas; p++){
            for(int i = 0; i < coords_hexs_piezas[p][0][2]; i++){
                for(int f = 0; f < 15; f++){
                    for(int c = 0; c < 15; c++){
                        if(f == coords_hexs_piezas[p][i][0] && c == coords_hexs_piezas[p][i][1]){
                            if(x >= coords_hexs_piezas[p][i][3] - tam_hexagono_pieza && x <= coords_hexs_piezas[p][i][3] + tam_hexagono_pieza &&
                               y >= coords_hexs_piezas[p][i][4] - tam_hexagono_pieza && y <= coords_hexs_piezas[p][i][4] + tam_hexagono_pieza){

                                piezaSeleccionada[p] = true;
                            }

                        }

                    }

                }
            }
        }*/

    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        piezaSeleccionada = new bool[5]{false, false, false, false, false};
        distanciaX_piezas = new int[5]{25,75,125,175,225};
        distanciaY_piezas = new int[5]{200,200,200,200,200};
    }

    glutPostRedisplay();
}

void Game::mouseMotion(int x, int y){

    y = height - y;

    int dist = 50;
    for(int i = 0; i < numero_piezas; i++){
        if(piezaSeleccionada[i]){
            cout << "Pieza " << i+1 << " seleccionada" << endl;
            cout << x << "," << y << endl;
            distanciaX_piezas[i] = x - dist;
            distanciaY_piezas[i] = y + 50;
        }
        else{
            //distanciaX_piezas = new int[5]{25,75,125,175,225};
            //distanciaY_piezas = new int[5]{200,200,200,200,200};
        }
        dist += 50;
    }

    glutPostRedisplay();
}


void Game::keyInput(unsigned char key, int x, int y)
{
	glutPostRedisplay();
}