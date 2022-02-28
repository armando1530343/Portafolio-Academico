#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;


int menu = 0; //identifica el boton que fue seleccionado del menu
int limiteNodos = 15; //limite de nodos permitidos
int limiteY = 600; //limite de la altura de los nodos
int entrada = 0; //valor de entrada al seleccionar un boton
int cantidad = 0; //cantidad de nodos que se crearon
int separacion = 60; //distancia entre cada nodo respecto al nodo padre
int color[] = {0,0,0,0}; //color del nodo dependiendo de la accion
// Estructura de cada nodo con sus caracteristicas
// Cada uno de estos tiene contiene dos apuntadores, que identifican el nodo siguiente y el anterior
struct Nodo
{	
	int valor, posx, posy;
	int r, v, a;
	string value;
	Nodo *sig = NULL;
	Nodo *ant = NULL;

}*nodos;


int width = 0, height = 0; //dimensiones de la ventana

void writeBitmapString(void *font, string str)
{
	int i;
	for(i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}


//funcion que grafica las funciones de los botones

void hash(){

	int i, j;
	int posX, posY, auxX;
	bool existe = false;

	int posicion, indice;
	stringstream num;
	string cadena;

	Nodo *recorrido; //se crea un apuntador auxiliar


	if(menu == 1){//seleccion del boton crear (1)
		do{
    		cout<<"Nuevo HashTable (Tamaño maximo = 15): "; cin>>cantidad; //se inicializa la variable de cantidad de nodos
    	}
    	while(entrada < 0 || entrada > 15);
    	menu = 0;
	}
	else if(menu == 2 || menu == 4){ //seleccion de los botones buscar y remover (comparten la mayoria de las acciones)

		if(menu == 2){//accion del boton buscar(2)
			cout<<"Buscar Valor: "; cin>>entrada;
		}
		else{
			//accion del boton Remover(4)
			do{
				cout<<"Borrar Valor: "; cin>>entrada;
			}
			while(entrada < 0 || entrada > 99);
		}

		posicion = entrada % cantidad; //se calcula la posicion a la que se desea acceder

		//se recorre la longitud de cada uno de los nodos padres (nodos H)
		for(i = 0; i < cantidad; i++){
			recorrido = &nodos[i];//se obtiene la direccionde memoria del nodo H de cada posicion
			j=0;
			//se recorren todos los valores de cada nodo H y se colorea dependiendo de la accion
			do{
				if(j == 0){
					recorrido->r = 1;
					recorrido->v = 0;
					recorrido->a = 0;
				}
				else{
					recorrido->r = 0;
					recorrido->v = 0;
					recorrido->a = 1;
					
				}
				recorrido = recorrido->sig;
				j++;
			}
			while(recorrido != NULL);
		}

		recorrido = &nodos[posicion];//se selecciona la direccion de memoria de la posicion seleccionada
		indice = 0;

		//se reccorren los valores de esa posicion y se colorea a que se coincida con el valor de entrada
		do{

			if((indice == 0 && recorrido->sig == NULL) || recorrido->valor == entrada){
				recorrido->r = 1;
				recorrido->v = 1;
				recorrido->a = 0;
				existe = true;
				break;
			}

			recorrido = recorrido->sig;
			indice++;


		}
		while(recorrido != NULL);

		//si no existen valores en esa posicion se colorea el nodo padre

		if(existe == false){
			nodos[posicion].r = 1;
			nodos[posicion].v = 1;
			nodos[posicion].a = 0;
		}

		if(menu == 4){

			//se borra el valor de entrada
			
			if(recorrido->sig == NULL && indice > 0){
				recorrido->ant->sig = NULL;
			}
			else if(recorrido->sig != NULL && indice > 0){
				do{
					if(recorrido->sig != NULL){
						recorrido->valor = recorrido->sig->valor;
						recorrido->value = recorrido->sig->value;
					}
					else{
						recorrido->ant->sig = NULL;
						break;						
					}
					recorrido = recorrido->sig;
				}
				while(recorrido != NULL);
				
			}
		}

		menu = 0;
	}

	else if(menu == 3){//seleccion del boton de Insertar(3)

		do{
    		cout<<"Insertar Valor (rango 0-99): "; cin>>entrada; //se inicializa el valor de entrada de insercion
    	}
    	while(entrada < 0 || entrada > 99); 

		posicion = entrada % cantidad;
		num<<entrada<<endl;
		cadena = num.str();

		//se colorean los nodos en su forma normal
		for(i = 0; i < cantidad; i++){
			recorrido = &nodos[i];
			j=0;
			do{
				if(j == 0){
					recorrido->r = 1;
					recorrido->v = 0;
					recorrido->a = 0;
				}
				else{
					recorrido->r = 0;
					recorrido->v = 0;
					recorrido->a = 1;
					
				}
				recorrido = recorrido->sig;
				j++;
			}
			while(recorrido != NULL);
		}

		recorrido = &nodos[posicion];
		indice = 0;

		//se inserta el nodo en la posicion en base a la formula de insercion

		do{
			//si el valor ya existe en el nodo se ignora y se cancela
			if(indice > 0 && recorrido->valor == entrada){break;}
			//cout<<recorrido->valor<<",";
			if(recorrido->sig == NULL){
				posX = recorrido->posx;
				posY = recorrido->posy - separacion;

				recorrido->sig = new Nodo();
				recorrido->sig->posx = posX;
				recorrido->sig->posy = posY;
				recorrido->sig->valor = entrada;
				recorrido->sig->value = cadena;
				recorrido->sig->r = 0;
				recorrido->sig->v = 0;
				recorrido->sig->a = 1;
				recorrido->sig->ant = recorrido;

				break;
			}
			
			recorrido = recorrido->sig;
			indice++;
		}
		while(true);

		menu = 0;
	}

	glutPostRedisplay();

}



void drawScene(){

	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	int i,j;

	int posX = width / (cantidad+1);
	int auxX = posX;
	int posY;

	//botones del menu

	glBegin(GL_QUADS);
	glColor3f(color[0],0,0);//boton Crear HT
	glVertex2f(20, 20);
	glVertex2f(20, 50);
	glVertex2f(120, 50);
	glVertex2f(120, 20);

	glColor3f(color[1],0,0);//boton Buscar
	glVertex2f(140, 20);
	glVertex2f(140, 50);
	glVertex2f(240, 50);
	glVertex2f(240, 20);

	glColor3f(color[2],0,0);//Boton Insertar
	glVertex2f(260, 20);
	glVertex2f(260, 50);
	glVertex2f(360, 50);
	glVertex2f(360, 20);

	glColor3f(color[3],0,0);//Boton Remover
	glVertex2f(380, 20);
	glVertex2f(380, 50);
	glVertex2f(480, 50);
	glVertex2f(480, 20);
	glEnd();

	glColor3f(1,1,1);
	
	glRasterPos2f(30, 30);   	
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Crear HT");

	glRasterPos2f(150, 30);   	
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Buscar V");

	glRasterPos2f(270, 30);   	
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Insertar");

	glRasterPos2f(390, 30);   	
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Remover");

	
	for(i = 0; i < cantidad; i++){

		glPointSize(30);
		glBegin(GL_POINTS);
		glColor3f(nodos[i].r,nodos[i].v,nodos[i].a);
		glVertex2f(posX, limiteY);
		glEnd();
		nodos[i].posx = posX;
		nodos[i].posy = limiteY;

		glColor3f(1,1,1);
		glRasterPos2f(posX-5, limiteY-5);   	
   		writeBitmapString(GLUT_BITMAP_HELVETICA_18, "H");
		posX += auxX;
	}


	hash();
	

	Nodo *recorrido;

	//en este ciclo se dibujan los nodos

	for(i = 0; i < cantidad; i++){
		recorrido = &nodos[i];		

		j = 0;
		do{
			if(j > 0){// && recorrido->valor != 100){				

				posX = recorrido->posx;
				posY = recorrido->posy;
				string cadena = recorrido->value;

				glPointSize(30);
				glBegin(GL_POINTS);
				glColor3f(recorrido->r, recorrido->v, recorrido->a);
				glVertex2f(posX, posY);
				glEnd();

				glColor3f(1,1,1);
				glRasterPos2f(posX-5, posY-5);   	
				writeBitmapString(GLUT_BITMAP_HELVETICA_18, cadena);

				glBegin(GL_LINES);
				glColor3f(0,0,0);

				glVertex2f(recorrido->ant->posx, recorrido->ant->posy - 15);
				glVertex2f(posX, posY + 15);
				glEnd();
			}			

			recorrido = recorrido->sig;
			j++;
		}
		while(recorrido != NULL);
	}

	glFlush();
}



void mouseControl(int button, int state, int x, int y){

	y = height - y;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(x > 20 && x < 120 && y > 20 && y < 50){
			color[0] = 1; color[1] = 0; color[2] = 0; color[3] = 0;			
	     	menu = 1;	     	
		}
		else if(x > 140 && x < 240 && y > 20 && y < 50){
			color[0] = 0; color[1] = 1; color[2] = 0; color[3] = 0;			 
			menu = 2;
		}
		else if(x > 260 && x < 360 && y > 20 && y < 50){
			color[0] = 0; color[1] = 0; color[2] = 1; color[3] = 0;			
			menu = 3;
		}
		else if(x > 380 && x < 480 && y > 20 && y < 50){
			color[0] = 0; color[1] = 0; color[2] = 0; color[3] = 1;			
			menu = 4;
		}
		else{
			menu = 0;
		}

	}

	glutPostRedisplay();
	return;
}


void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   width = w;
   height = h;
   glLoadIdentity();
}


int main(int argc, char **argv){

	
	nodos = new Nodo[limiteNodos];

	//se inicializan las cabeceras en color rojo

	for(int i = 0; i < limiteNodos; i++){
		nodos[i].r = 1;
		nodos[i].v = 0;
		nodos[i].a = 0;
		nodos[i].valor = 100;
	}
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	
	glutInitWindowSize(1000, 650);	
	glutInitWindowPosition(0, 10);	
	glutCreateWindow("Practica 03");

	glutDisplayFunc(drawScene);	
	glutReshapeFunc(resize);	
	glutMouseFunc(mouseControl);
	glutMainLoop();

	return 0;
}