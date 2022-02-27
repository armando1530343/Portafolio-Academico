#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <GL/glut.h>
#include "Mapa.h"

#define Retardo 12
#define PI 3.141592654

using namespace std;

float width, height;

float ***coords_mapa = NULL;
char **mapa_bits = NULL;
vector <int**> coords_hexs_piezas;
vector <int> coord_piezasX;
vector <int> coord_piezasY;

int numero_piezas;

int *permutacion_piezas;

Mapa nivel1;

int tam_hexagono_pieza = 15.0;

bool *piezaSeleccionada = new bool[5]{false, false, false, false, false};
int *distanciaX_piezas = new int[5]{25,75,125,175,225};
int *distanciaY_piezas = new int[5]{200,200,200,200,200};

float colores_piezas[6][3] = {
    {1,0,0}, //rojo
    {1,1,0}, //amarillo
    {0,0,1}, //azul
    {0,1,0}, //verde
    {1,0,1}, //morado
    {1,1,0}  //otro
};

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


    float *color = new float[3]{.2,.2,.2};

    //SE DIBUJA EL MAPA DEL NIVEL
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(coords_mapa[i][j][0] > -1)
                nivel1.dibuja_hexagono(coords_mapa[i][j][0], coords_mapa[i][j][1], 25, color);
        }
    }
    //SE DIBUJAN LAS PIEZAS DEL NIVEL
    int dist_x_pieza = 25;

    for(int p = 0; p < numero_piezas; p++){
        glPopMatrix();
        glTranslatef(0, 0, 0);
        glRotatef(0,0,0,0);
        //cout << "size: " << coords_hexs_piezas[p][0][2] << endl;

        for(int i = 0; i < coords_hexs_piezas[p][0][2]; i++){
            //cout << coords_hexs_piezas[0][i][0] << "," << coords_hexs_piezas[0][i][1] << endl;
            for(int f = 0; f < 15; f++){
                int cc;

                for(int c = 0; c < 15; c++){
                    if(f == coords_hexs_piezas[p][i][0] && c == coords_hexs_piezas[p][i][1]){
                        float x = (c+1)*tam_hexagono_pieza + tam_hexagono_pieza/2 + distanciaX_piezas[p];// - 50*permutacion_piezas[p];
                        float y = -((f+1)*tam_hexagono_pieza - tam_hexagono_pieza/2) + distanciaY_piezas[p];// + 600;
                        coords_hexs_piezas[p][i][3] = x;
                        coords_hexs_piezas[p][i][4] = y;
                        color = colores_piezas[p];
                        nivel1.dibuja_hexagono(x, y, tam_hexagono_pieza, color);
                        cc++;
                    }
                }
            }
        }
        glPopMatrix();
        //dist_x_pieza += 10;
    }
    /*
    cout << "----------------" << endl;

    for(int i = 0; i < coords_hexs_piezas.size(); i++){
        cout << "Pieza " << i+1 << ": " << piezaSeleccionada[i] << endl;
    }


    /*
    for(int i = 0; i < coords_pieza[0][2]; i++){
        cout << coords_pieza[i][0] << ", " << coords_pieza[i][1] << endl;
    }*/

    glFlush();


}
void TimerFunction(int value){



    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);

}

void mouseControl(int button, int state, int x, int y){

    y = height - y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        for(int p = 0; p <  numero_piezas; p++){
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
        }

    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        piezaSeleccionada = new bool[5]{false, false, false, false, false};
        distanciaX_piezas = new int[5]{25,75,125,175,225};
        distanciaY_piezas = new int[5]{200,200,200,200,200};
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


void keyInput(unsigned char key, int x, int y)
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    nivel1 = Mapa("Level-Maps/nivel1/nivel1.txt");
    coords_mapa = nivel1.generar_coords_mapa();
    mapa_bits = nivel1.mapa_bits();

    coords_hexs_piezas.push_back(nivel1.nuevaPieza("Level-Maps/nivel1/pieza1.txt"));
    coords_hexs_piezas.push_back(nivel1.nuevaPieza("Level-Maps/nivel1/pieza2.txt"));
    coords_hexs_piezas.push_back(nivel1.nuevaPieza("Level-Maps/nivel1/pieza3.txt"));


    numero_piezas = coords_hexs_piezas.size();

    permutacion_piezas = new int[numero_piezas];

    srand(time(NULL));

    //PERMUTACION

    for(int i = 0; i < numero_piezas; i++){
        if (i == 0)
            permutacion_piezas[i] = rand()%numero_piezas;
        else{
            while(true){
                permutacion_piezas[i] = rand()%numero_piezas;
                bool existe = false;
                for(int j = 0; j < i; j++){
                    if(permutacion_piezas[i] == permutacion_piezas[j]){
                        existe = true;
                        break;
                    }

                }
                if(existe == false)
                    break;
            }
        }
    }



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
