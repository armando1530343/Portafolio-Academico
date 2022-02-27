#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <GL/glut.h>

//#include "Game.h"
#include "Mapa.h"

#define Retardo 12
#define PI 3.141592654

using namespace std;

float width, height;

struct Pieza{
    char **mapa;
    float ***posiciones;
    int num_pieza;
}_pieza;

float ***coords_mapa = NULL;
char **mapa_bits = NULL;
vector <Pieza> datos_pieza;

int numero_piezas;

int *permutacion_piezas;

Mapa nivel1;//niveles[3];

int tam_hexagono_pieza = 15.0;

int indice_pieza_seleccionada;
int num_pieza_seleccionada;
bool *piezaSeleccionada = new bool[5]{false, false, false, false, false};

int *distanciaX_piezas = new int[5]{50,150,250,350,450};
int *distanciaX_piezas_lejos = new int[5]{0,0,0,0,0};

int *distanciaY_piezas = new int[5]{200,200,200,200,200};

bool pieza_encima = false;
bool seleccion_pieza = false;
bool piezas_completadas[5] = {false, false, false, false, false};

int piezas_completas = 0;

float colores_piezas[7][3] = {
    {1,0,0}, //rojo
    {1,1,0}, //amarillo
    {0,0,1}, //azul
    {0,1,0}, //verde
    {1,0,1}, //morado
    {.2,.2,.2},  //otro
    {.3,.3,.3}  //otro
};

vector<int> indice_pieza_fuera;



void writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);
}

void reshape(int w, int h)
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

void display(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    float *color;

    //cout << "seleccion pieza: " << seleccion_pieza << endl;
    //cout << "pieza encima: " << pieza_encima << "\n" << endl;

    //SE DIBUJA EL MAPA DEL NIVEL
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(coords_mapa[i][j][0] > -1){

            	color = colores_piezas[int(coords_mapa[i][j][3])];

                if(seleccion_pieza && pieza_encima &&  coords_mapa[i][j][2] == 48 + num_pieza_seleccionada)
                    color = colores_piezas[6];
                
                nivel1.dibuja_hexagono(coords_mapa[i][j][0], coords_mapa[i][j][1], 25, color);
                
            }
        }
    }


    //SE DIBUJAN LAS PIEZAS DEL NIVEL
    int dist_x_pieza = 25;

    for(int p = 0; p < numero_piezas; p++){
        glPopMatrix();
        glTranslatef(0, 0, 0);
        glRotatef(0,0,0,0);

        for(int f = 0; f < datos_pieza[p].posiciones[0][0][2]; f++){
            for(int c = 0; c < datos_pieza[p].posiciones[0][0][3]; c++){
                if(datos_pieza[p].mapa[f][c] !=  '0'){
                    float x = (c+1)*tam_hexagono_pieza + tam_hexagono_pieza/2 + distanciaX_piezas[p];
                    float y = -((f+1)*tam_hexagono_pieza - tam_hexagono_pieza/2) + distanciaY_piezas[p];
                    datos_pieza[p].posiciones[f][c][0] = x;
                    datos_pieza[p].posiciones[f][c][1] = y;
                    color = colores_piezas[p];
                    nivel1.dibuja_hexagono(x, y, tam_hexagono_pieza, color);
                }
            }
        }

        glPopMatrix();
    }

    if(piezas_completas == datos_pieza.size())
    	exit(0);

    glFlush();


}
void TimerFunction(int value){



    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);

}

void mouseControl(int button, int state, int x, int y){

    y = height - y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        for(int p = 0; p < numero_piezas; p++){
            for(int f = 0; f < datos_pieza[p].posiciones[0][0][2]; f++){
                for(int c = 0; c < datos_pieza[p].posiciones[0][0][3]; c++){
                    if(x >= datos_pieza[p].posiciones[f][c][0] - tam_hexagono_pieza && x <= datos_pieza[p].posiciones[f][c][0] + tam_hexagono_pieza &&
                       y >= datos_pieza[p].posiciones[f][c][1] - tam_hexagono_pieza && y <= datos_pieza[p].posiciones[f][c][1] + tam_hexagono_pieza){
                        piezaSeleccionada[p] = true;
                        indice_pieza_seleccionada = p;
                        num_pieza_seleccionada = datos_pieza[p].num_pieza;
                        seleccion_pieza = true;
                    }
                }
                //cout << endl;
            }
        }

    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        piezaSeleccionada = new bool[5]{false, false, false, false, false};
        seleccion_pieza = false;
        //pieza_encima = false;
        
        distanciaY_piezas = new int[5]{200,200,200,200,200};

        cout << pieza_encima << endl;

        if(piezaSeleccionada[indice_pieza_seleccionada] == false && pieza_encima == true){
                cout << "suelta" << endl;
                pieza_encima = false;
            piezas_completadas[num_pieza_seleccionada-1] = true;
            piezas_completas++;
            distanciaX_piezas_lejos[indice_pieza_seleccionada] = 1000;
            for(int i = 0; i < 15; i++){
        		for(int j = 0; j < 15; j++){
        			if(coords_mapa[i][j][2] == 48 + num_pieza_seleccionada){
        				coords_mapa[i][j][3] = indice_pieza_seleccionada;
        			}
        		}
        	}

        }
        else{

        }

        distanciaX_piezas = new int[5]{50 + distanciaX_piezas_lejos[0],
        							   150 + distanciaX_piezas_lejos[1],
        							   250 + distanciaX_piezas_lejos[2],
        							   350 + distanciaX_piezas_lejos[3],
        							   450 + distanciaX_piezas_lejos[4]};

    }

    glutPostRedisplay();
}

void mouseMotion(int x, int y){

    y = height - y;

    int dist = 50;
    for(int i = 0; i < numero_piezas; i++){
        if(piezaSeleccionada[i]){
            //cout << "Pieza " << i+1 << " seleccionada" << endl;
            //cout << x << "," << y << endl;
            distanciaX_piezas[i] = x - 50;
            distanciaY_piezas[i] = y + 50;
        }
        else{
            //distanciaX_piezas = new int[5]{25,75,125,175,225};
            //distanciaY_piezas = new int[5]{200,200,200,200,200};
        }
        dist += 50;
    }

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(coords_mapa[i][j][0] > -1 && coords_mapa[i][j][2] == 48 + num_pieza_seleccionada){
                if(x >= coords_mapa[i][j][0] - 25 && x <= coords_mapa[i][j][0] + 25 &&
                   y >= coords_mapa[i][j][1] - 25 && y <= coords_mapa[i][j][1] + 25){

                    pieza_encima = true;
                    //cout << "Pieza: " << char(coords_mapa[i][j][2]) << endl;
	                if(piezaSeleccionada[indice_pieza_seleccionada] == false){
			                //cout << "suelta" << endl;
			            //piezas_completadas[num_pieza_seleccionada-1] = true;
			            //piezas_completas++;
			            //distanciaX_piezas_lejos[indice_pieza_seleccionada] = 1000;
			        }
			        else{

			        }


                }
                else
                    pieza_encima = false;
            }
        }
    }

    glutPostRedisplay();
}


void keyInput(unsigned char key, int x, int y)
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    //int t = sizeof(&x);//sizeof(*x);
    //cout << "tamaño: " << t << endl;



    nivel1 = Mapa("Level-Maps/nivel1/nivel1.txt");
    coords_mapa = nivel1.generar_coords_mapa();
    //mapa_bits = nivel1.mapa_bits();

    _pieza.mapa = nivel1.mapa_bits_pieza("Level-Maps/nivel1/pieza3.txt");
    _pieza.posiciones = nivel1.coords_mapa_bits_pieza();
    _pieza.num_pieza = 3;
    datos_pieza.push_back(_pieza);

    _pieza.mapa = nivel1.mapa_bits_pieza("Level-Maps/nivel1/pieza1.txt");
    _pieza.posiciones = nivel1.coords_mapa_bits_pieza();
    _pieza.num_pieza = 1;
    datos_pieza.push_back(_pieza);

    _pieza.mapa = nivel1.mapa_bits_pieza("Level-Maps/nivel1/pieza2.txt");
    _pieza.posiciones = nivel1.coords_mapa_bits_pieza();
    _pieza.num_pieza = 2;
    datos_pieza.push_back(_pieza);
    numero_piezas = datos_pieza.size();


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 10);
    glutCreateWindow("");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
    //glutTimerFunc(Retardo,TimerFunction, 1);
    glutMainLoop();
    return 0;
}
