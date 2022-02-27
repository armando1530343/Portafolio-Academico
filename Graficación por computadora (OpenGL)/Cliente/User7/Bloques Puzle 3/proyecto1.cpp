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

// ESTRUCTURA PIEZA
struct Pieza{
    char **mapa;
    float ***posiciones;
    int num_pieza;
}_pieza;

// VARIABLES POR NIVEL
struct Nivel
{
    Mapa nivel;
    float ***coords_mapa = NULL;
    vector <Pieza> datos_pieza;
    int numero_piezas;

}niveles[3];

// VARIABLES GENERALES
static int tam_hexagono_pieza = 15.0;
int indice_pieza_seleccionada;
int num_pieza_seleccionada;
bool *piezaSeleccionada = new bool[5]{false, false, false, false, false};
int *distanciaX_piezas = new int[5]{50,150,250,350,450};
int *distanciaX_piezas_lejos = new int[5]{0,0,0,0,0};
int *distanciaY_piezas = new int[5]{200,200,200,200,200};
bool pieza_encima = false;
bool seleccion_pieza = false;
bool *piezas_completadas = new bool[5]{false, false, false, false, false};
int piezas_completas = 0;

// LISTA DE COLORES DEL JUEGO
static float colores_piezas[7][3] = {
    {1,0,0}, //rojo
    {1,1,0}, //amarillo
    {0,0,1}, //azul
    {0,1,0}, //verde
    {1,0,1}, //morado
    {.2,.2,.2},  //otro
    {.3,.3,.3}  //otro
};

int numero_nivel =0;

bool end_game = false;


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

    if(end_game == false){
        //SE DIBUJA EL MAPA DEL NIVEL
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                if(niveles[numero_nivel].coords_mapa[i][j][0] > -1){

                    color = colores_piezas[int(niveles[numero_nivel].coords_mapa[i][j][3])];

                    if(seleccion_pieza && pieza_encima &&  niveles[numero_nivel].coords_mapa[i][j][2] == 48 + num_pieza_seleccionada)
                        color = colores_piezas[6];
                    
                    niveles[numero_nivel].nivel.dibuja_hexagono(niveles[numero_nivel].coords_mapa[i][j][0], niveles[numero_nivel].coords_mapa[i][j][1], 25, color);
                    
                }
            }
        }



        //SE DIBUJAN LAS PIEZAS DEL NIVEL
        int dist_x_pieza = 25;

        for(int p = 0; p < niveles[numero_nivel].numero_piezas; p++){
            glPopMatrix();
            glTranslatef(0, 0, 0);
            glRotatef(0,0,0,0);

            for(int f = 0; f < niveles[numero_nivel].datos_pieza[p].posiciones[0][0][2]; f++){
                for(int c = 0; c < niveles[numero_nivel].datos_pieza[p].posiciones[0][0][3]; c++){
                    if(niveles[numero_nivel].datos_pieza[p].mapa[f][c] !=  '0'){
                        float x = (c+1)*tam_hexagono_pieza + tam_hexagono_pieza/2 + distanciaX_piezas[p];
                        float y = -((f+1)*tam_hexagono_pieza - tam_hexagono_pieza/2) + distanciaY_piezas[p];
                        niveles[numero_nivel].datos_pieza[p].posiciones[f][c][0] = x;
                        niveles[numero_nivel].datos_pieza[p].posiciones[f][c][1] = y;
                        color = colores_piezas[p];
                        niveles[numero_nivel].nivel.dibuja_hexagono(x, y, tam_hexagono_pieza, color);
                    }
                }
            }

            glPopMatrix();
        }

        if(piezas_completas == niveles[numero_nivel].datos_pieza.size()){
            indice_pieza_seleccionada;
            num_pieza_seleccionada;
            piezaSeleccionada = new bool[5]{false, false, false, false, false};
            distanciaX_piezas = new int[5]{50,150,250,350,450};
            distanciaX_piezas_lejos = new int[5]{0,0,0,0,0};
            distanciaY_piezas = new int[5]{200,200,200,200,200};
            pieza_encima = false;
            seleccion_pieza = false;
            piezas_completadas = new bool[5]{false, false, false, false, false};
            piezas_completas = 0;

            //cout << "Nivel: " << numero_nivel << endl;

            numero_nivel++;
            if(numero_nivel == 3){
                cout << "FIN" << endl;
                end_game = true;
                
            }

            glutPostRedisplay();
            //exit(0);
        }
    }
    else{
        glColor3f(1,1,1);
        glRasterPos2f(200, 400);
        writeBitmapString(GLUT_BITMAP_HELVETICA_18, "NIVELES COMPLETADOS!!!");
        glRasterPos2f(200, 300);
        writeBitmapString(GLUT_BITMAP_HELVETICA_18, "FIN DEL JUEGO");
    }

    

    glFlush();


}
void TimerFunction(int value){



    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);

}

void mouseControl(int button, int state, int x, int y){

    y = height - y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        for(int p = 0; p < niveles[numero_nivel].numero_piezas; p++){
            for(int f = 0; f < niveles[numero_nivel].datos_pieza[p].posiciones[0][0][2]; f++){
                for(int c = 0; c < niveles[numero_nivel].datos_pieza[p].posiciones[0][0][3]; c++){
                    if(x >= niveles[numero_nivel].datos_pieza[p].posiciones[f][c][0] - tam_hexagono_pieza && 
                       x <= niveles[numero_nivel].datos_pieza[p].posiciones[f][c][0] + tam_hexagono_pieza &&
                       y >= niveles[numero_nivel].datos_pieza[p].posiciones[f][c][1] - tam_hexagono_pieza &&
                       y <= niveles[numero_nivel].datos_pieza[p].posiciones[f][c][1] + tam_hexagono_pieza){
                        
                        piezaSeleccionada[p] = true;
                        indice_pieza_seleccionada = p;
                        num_pieza_seleccionada = niveles[numero_nivel].datos_pieza[p].num_pieza;
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
        			if(niveles[numero_nivel].coords_mapa[i][j][2] == 48 + num_pieza_seleccionada){
        				niveles[numero_nivel].coords_mapa[i][j][3] = indice_pieza_seleccionada;
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
    for(int i = 0; i < niveles[numero_nivel].numero_piezas; i++){
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
            if(niveles[numero_nivel].coords_mapa[i][j][0] > -1 && niveles[numero_nivel].coords_mapa[i][j][2] == 48 + num_pieza_seleccionada){
                if(x >= niveles[numero_nivel].coords_mapa[i][j][0] - 25 && x <= niveles[numero_nivel].coords_mapa[i][j][0] + 25 &&
                   y >= niveles[numero_nivel].coords_mapa[i][j][1] - 25 && y <= niveles[numero_nivel].coords_mapa[i][j][1] + 25){

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
    
    // DECLARACION DE VARIABLES DEL NIVEL 1


    niveles[0].nivel = Mapa("Level-Maps/nivel1/nivel1.txt");
    niveles[0].coords_mapa = niveles[0].nivel.generar_coords_mapa();
    
    _pieza.mapa = niveles[0].nivel.mapa_bits_pieza("Level-Maps/nivel1/pieza3.txt");
    _pieza.posiciones = niveles[0].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 3;
    niveles[0].datos_pieza.push_back(_pieza);

    _pieza.mapa = niveles[0].nivel.mapa_bits_pieza("Level-Maps/nivel1/pieza1.txt");
    _pieza.posiciones = niveles[0].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 1;
    niveles[0].datos_pieza.push_back(_pieza);

    _pieza.mapa = niveles[0].nivel.mapa_bits_pieza("Level-Maps/nivel1/pieza2.txt");
    _pieza.posiciones = niveles[0].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 2;
    niveles[0].datos_pieza.push_back(_pieza);
    niveles[0].numero_piezas = niveles[0].datos_pieza.size();

    // DECLARACION DE VARIABLES DEL NIVEL 2


    niveles[1].nivel = Mapa("Level-Maps/nivel2/nivel2.txt");
    niveles[1].coords_mapa = niveles[1].nivel.generar_coords_mapa();
    
    _pieza.mapa = niveles[1].nivel.mapa_bits_pieza("Level-Maps/nivel2/pieza3.txt");
    _pieza.posiciones = niveles[1].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 3;
    niveles[1].datos_pieza.push_back(_pieza);

    _pieza.mapa = niveles[1].nivel.mapa_bits_pieza("Level-Maps/nivel2/pieza1.txt");
    _pieza.posiciones = niveles[1].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 1;
    niveles[1].datos_pieza.push_back(_pieza);

    _pieza.mapa = niveles[1].nivel.mapa_bits_pieza("Level-Maps/nivel2/pieza2.txt");
    _pieza.posiciones = niveles[1].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 2;
    niveles[1].datos_pieza.push_back(_pieza);
    niveles[1].numero_piezas = niveles[1].datos_pieza.size();

    // DECLARACION DE VARIABLES DEL NIVEL 3


    niveles[2].nivel = Mapa("Level-Maps/nivel3/nivel3.txt");
    niveles[2].coords_mapa = niveles[2].nivel.generar_coords_mapa();
    
    _pieza.mapa = niveles[2].nivel.mapa_bits_pieza("Level-Maps/nivel3/pieza3.txt");
    _pieza.posiciones = niveles[2].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 3;
    niveles[2].datos_pieza.push_back(_pieza);

    _pieza.mapa = niveles[2].nivel.mapa_bits_pieza("Level-Maps/nivel3/pieza2.txt");
    _pieza.posiciones = niveles[2].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 2;
    niveles[2].datos_pieza.push_back(_pieza);

    _pieza.mapa = niveles[2].nivel.mapa_bits_pieza("Level-Maps/nivel3/pieza1.txt");
    _pieza.posiciones = niveles[2].nivel.coords_mapa_bits_pieza();
    _pieza.num_pieza = 1;
    niveles[2].datos_pieza.push_back(_pieza);
    niveles[2].numero_piezas = niveles[2].datos_pieza.size();


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

/*




*/
