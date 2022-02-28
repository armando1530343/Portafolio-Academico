#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <string>
#include <sstream>


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define WIDTH 700
#define HEIGHT 650


using namespace std;

std::vector<string> palabras;

int width, height; //valores de la dimension de la pantalla

int *aleatorias;//


//esta funcion es encargada de leer un archivo de texto el cual contiene las palabras para jugar

void leerFichero(){
	ifstream archivo;
	char letra;
	string palabra = "";
	string aux = "";

	archivo.open("palabras.txt", ios::in);//se abre el archivo

	if(archivo.fail()){
		cout<<"No se encontro el archivo"<<endl;//no se encontro el archivo
		exit(1);
	}
	int j = 0;

	//se leen las palabras que contiene el archivo de texto
	while(!archivo.eof()){
		//letra = '';
		archivo.get(letra);
		palabra += letra;
		if(letra == '\n'){
			for(int i = 0; i < palabra.length()-1; i++){
				aux += palabra[i];//se suma cada letra de la palabra en una variable cadena
			}
			palabra = aux;			
			palabras.push_back(palabra);
			aux = "";
			palabra = "";
			//cout<<palabras[j]<<endl;
			j++;
		}
	}
	archivo.close();//se cierra el archivo

	//este arreglo contiene las palabras leidas en un orden aleatorio
	aleatorias = new int[palabras.size()-1];

	int num[palabras.size()];
	int num2[palabras.size()];

	bool repetido;

	//cout<<endl;
	int limite = palabras.size();

	//se cambia el orden en que fueron leidas las palabras del archivo
	//con un orden aleatorio distinto
	for(int i = 0; i < palabras.size()-1; i++){
		
		do{
			repetido = false;
			num[i] = rand()%(palabras.size()-1);

			if(i > 0){
				for(int j = 0; j < i; j++){
					if(num[i] == num[j]){
						repetido = true;
						break;
					}
				}
			}

		}
		while(repetido == true);
		aleatorias[i] = num[i];
		//cout<<num[i]<<" "<<palabras[num[i]]<<endl;
	}




}


std::vector<int> posx;//vector de posiciones en x
std::vector<int> posy;

std::vector<int> rojo;
std::vector<int> verde;
std::vector<int> azul;



void writenBitmapString(void *font, char string)
{
	char *c;
	glutBitmapCharacter(font, string);
}
void writenBitmapString2(void *font, char *string)
{
	char *c;
	for(c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}



//esta clase guarda los datos de una letra de cada palabra de la que fue seleccionada del archivo

class casilla{
private:
	int posx, posy, fila, columna, indice;
	int rojo, verde, azul, c;
	int letraX, letraY;
	char letra;
public:
	casilla(int x, int y, int colorLetra, char let, int fil, int col, int ind){
		
		posx = x; posy = y;  //guarda las posiciones de la casilla en la matriz
		fila = fil; columna = col; //se guarda la fila y columna en la que esta posicionada
		letraX = x; letraY = y; //se guarda la posicion en la que será impresa la letra de la casilla
		rojo = colorLetra; verde = colorLetra; azul = colorLetra; //color de la letra
		letra = let; //se guarda el caracter de la letra
		c = 1;
		indice = ind; //se guarda en indice de posicion de la casilla


	}
	casilla(){}

	//se retornan todos los valores de la clase
	int getPosX(){return posx;}
	int getPosY(){return posy;}
	int getFil(){return fila;}
	int getCol(){return columna;}
	int getLetraX(){return letraX;}
	int getLetraY(){return letraY;}
	int getColor(){return rojo;}
	int getIndice(){return indice;}
	char getLetra(){return letra;}
	void setColor(int c){rojo = c; verde = c; azul = c;}
	void colorCasilla(){c = 0;}
	void dibujar(){

		//funcion que dibuja la casilla y la posicion

		glPointSize(25);
		glBegin(GL_POINTS);
		glColor3f(1,1,c);
		glVertex2f(posx, posy);
		glEnd();

		
	}
};

std::vector<casilla> crucigrama[15];//guada las palabras en el crucigrama

std::vector<string> aceptadas;//guarda la cadena de la  palabra que es aceptada

int veces = 0;

int numPalabras = 0;

int palabrasAceptadas = 0;

// matriz de posiciones
 double posiciones[24][20][3];//guarda las posiciones de las casillas en la matriz

 bool presiona = false; 

 int nuevoOrden = 0;

 bool palabraPresionada = false; //cuando una palabra es presionada

 bool palabraCorrecta = false; //cuando la verificacion de la palabra con el crucigrama es correcto o no

 int indicePalabra;

 std::vector<int> palabrasAcertadas;//palabras que son destapadas



 

 int forma = 1;

 //funcion que posiciona la palabra en un lugar de la matriz para formar el crucigrama

void formaPalabra(int i, int hv){

	
	int longitud = palabras[i].length();
	int fil, col;

	int distanciaLetra;
	bool encuentraLetra = false;

	int ff, cc;

	string cadena;

	casilla cas;


	if(numPalabras == 0){//solo lo hará para la primera palabra
		col = 20 - longitud;
		col = rand()%col;
		fil = 4;
		cadena = "";

		//posiciona la palabra en el crucigrama letra por letra

		for(int j = 0; j < palabras[i].length(); j++){			
			//str = ""+palabras[i][j];		
			cas = casilla(posiciones[fil][col][0], posiciones[fil][col][1], 1, palabras[i][j], fil, col, numPalabras);
			cadena += palabras[i][j];
			if(j==0)posiciones[fil][col][2] = 2; //inicio(amarillo)
			else posiciones[fil][col][2] = 1;//ocupado
			//cas.dibujar();
			crucigrama[numPalabras].push_back(cas);
			if(posiciones[fil][col][2] == 2)crucigrama[numPalabras][j].colorCasilla();
			crucigrama[numPalabras][j].dibujar();	

			if(hv % 2 == 0) fil++;
			else col++;
		}
		aceptadas.push_back(cadena);
		//cout<<"error aqui "<<hv<<endl; 
		palabrasAceptadas++;
		numPalabras++;
	}
	else if(hv % 2 == 0){//vertical
		//cout<<crucigrama[numPalabras-1][0].getLetra()<<endl;
		//cout<<"error aqui "<<hv<<endl; 

		distanciaLetra = 0;
		cadena = "";

		//posiciona la palabra en el crucigrama letra por letra

		for(int k = 0; k < palabras[i].length(); k++){
		//for (int j = 0; j < crucigrama[numPalabras-1].size(); j++){
			
			std::vector<int> lugaresV;
			std::vector<int> indiceV;

			//int lug = 0;
			
			for (int j = 0; j < crucigrama[numPalabras-1].size(); j++){
			//for(int k = 0; k < palabras[i].length(); k++){
				if (palabras[i][k] == crucigrama[numPalabras-1][j].getLetra()){
					
					ff = crucigrama[numPalabras-1][j].getFil()-distanciaLetra;//obtiene la fila de la letra con la que coinciden las palabras
					cc = crucigrama[numPalabras-1][j].getCol();//obtiene la columna de la letra con la que coinciden las palabras
					//cout<<"letra: "<<palabras[i][k]<<" distancia:"<<distanciaLetra<<endl;
					//k = palabras[i].length();
					lugaresV.push_back(ff);
					indiceV.push_back(j);
					
				}				
			}

			for(int j = 0; j < lugaresV.size(); j++){
				if(lugaresV[j] >= 0 && lugaresV[j] <= 23){
					ff = lugaresV[j];	
					int i1 = crucigrama[numPalabras-1][indiceV[j]].getFil();
					int i2 = crucigrama[numPalabras-1][indiceV[j]].getCol();
					//posiciones[i1][i2][2] = 2;//punto de inicio(amarillo)				
					encuentraLetra = true;
					//cout<<crucigrama[numPalabras-1][indiceV[j]].getLetra()<<endl;
					break;
				}
			}
			if(encuentraLetra == true) break;
			
			distanciaLetra ++;

		}

		//cout <<"ff: "<< ff <<  " long: "<< longitud << " = " << ff+longitud-1<<endl;

		if(encuentraLetra == true && ff >= 0 && ff+longitud-1 <=23){

			int auxff = ff;
			bool empalme = false;
			int toca_inicio = 0;
			int cruces = 0;

			for(int j = 0; j < palabras[i].size(); j++){
				//cout<<posiciones[auxff][cc][2]<<endl;

				if(posiciones[auxff][cc][2]==1)cruces++;
				if(posiciones[auxff][cc][2]==2)toca_inicio++;

				if((posiciones[auxff][cc][2] == 1 && cruces > 1) || (posiciones[auxff][cc][2] == 2 && toca_inicio > 1)){
					empalme = true;
				}
				auxff++;

			}

			if(empalme == false){
				for(int j = 0; j < palabras[i].length(); j++){
					//cout<<ff<<endl;
					cas = casilla(posiciones[ff][cc][0], posiciones[ff][cc][1], 1, palabras[i][j], ff, cc, numPalabras);
					cadena += palabras[i][j];
					if(j==0) posiciones[ff][cc][2] = 2; //posicion de inicio
					else posiciones[ff][cc][2] = 1; //ocupado
					//cas.dibujar();
					crucigrama[numPalabras].push_back(cas);
					if(posiciones[ff][cc][2] == 2) crucigrama[numPalabras][j].colorCasilla();
					crucigrama[numPalabras][j].dibujar();
					ff++;
				}
				palabrasAceptadas++;
				numPalabras++;
				aceptadas.push_back(cadena);
			}			
		}
			

	}
	else{

		//cout<<"error aqui "<<hv<<endl; 

		distanciaLetra = 0;
		cadena = "";

		for(int k = 0; k < palabras[i].length(); k++){
		//for (int j = 0; j < crucigrama[numPalabras-1].size(); j++){
			
			std::vector<int> lugaresH;
			std::vector<int> indiceH;
			//int lug = 0;
			
			for (int j = 0; j < crucigrama[numPalabras-1].size(); j++){
			//for(int k = 0; k < palabras[i].length(); k++){
				if (palabras[i][k] == crucigrama[numPalabras-1][j].getLetra()){
					
					ff = crucigrama[numPalabras-1][j].getFil();//obtiene la fila de la letra con la que coinciden las palabras
					cc = crucigrama[numPalabras-1][j].getCol()-distanciaLetra;//obtiene la columna de la letra con la que coinciden las palabras
					//cout<<"letra: "<<palabras[i][k]<<" distancia:"<<distanciaLetra<<endl;
					//k = palabras[i].length();
					lugaresH.push_back(cc);
					indiceH.push_back(j);
				}				
			}

			for(int j = 0; j < lugaresH.size(); j++){
				//cout<<lugaresH[j]<<endl;
				if(lugaresH[j] >= 0 && lugaresH[j] <= 19){
					cc = lugaresH[j];
					int i1 = crucigrama[numPalabras-1][indiceH[j]].getFil();
					int i2 = crucigrama[numPalabras-1][indiceH[j]].getCol();
					//posiciones[i1][i2][2] = 2;//punto de inicio(amarillo)
					//cout<<crucigrama[numPalabras-1][indiceH[j]].getLetra()<<endl;
					encuentraLetra = true;
					break;
				}
			}
			if(encuentraLetra == true) break;
			
			distanciaLetra ++;
		}

		//cout <<"cc: "<< cc <<  " long: "<< longitud << " = " << cc+longitud-1<<endl;

		if(encuentraLetra == true && cc >= 0 && cc+longitud-1 <=19){
			int auxcc = cc;
			bool empalme = false;
			int toca_inicio = 0;
			int cruces = 0;

			for(int j = 0; j < palabras[i].size(); j++){
				//cout<<posiciones[auxcc][cc][2]<<endl;

				if(posiciones[ff][auxcc][2]==1)cruces++;
				if(posiciones[ff][auxcc][2]==2)toca_inicio++;

				if((posiciones[ff][auxcc][2] == 1 && cruces > 1) || (posiciones[ff][auxcc][2] == 2 && toca_inicio > 1)){
					empalme = true;
				}
				auxcc++;

			}

			if(empalme == false){
				for(int j = 0; j < palabras[i].length(); j++){
					//cout<<ff<<endl;
					cas = casilla(posiciones[ff][cc][0], posiciones[ff][cc][1], 1, palabras[i][j], ff, cc, numPalabras);
					cadena += palabras[i][j];
					if(j==0) posiciones[ff][cc][2] = 2; //posicion de inicio
					else posiciones[ff][cc][2] = 1; //ocupado
					//cas.dibujar();
					crucigrama[numPalabras].push_back(cas);
					if(posiciones[ff][cc][2] == 2) crucigrama[numPalabras][j].colorCasilla();
					crucigrama[numPalabras][j].dibujar();
					cc++;
				}
				palabrasAceptadas++;
				numPalabras++;
				aceptadas.push_back(cadena);
			}
		}

	}

	
	//glEnd();

}

double clic = 1;
double clic2 = 1;
int formas[100][1000];

bool conLetras = false;

int intentos = 5;
int destapadas = 0;

int colorPalabra[15][3];
double posicionPalabra[15][2];
int colorIntentos[5];

bool ganar = false;
bool perder = false;

//colorIntentos[0] = 1;


void drawScene(void);


void drawButtons(void){
   //glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);

   

   //botones
   glBegin(GL_QUADS);
   glColor3f(clic,0,0);
   //ver respuestas
   glVertex2f(WIDTH-150,30);
   glVertex2f(WIDTH-150,70);
   glVertex2f(WIDTH-20,70);
   glVertex2f(WIDTH-20,30);

   glEnd();

   glColor3f(0, 1, 0);
   glRasterPos3f(WIDTH-150, HEIGHT-80, 0.0);
   writenBitmapString2(GLUT_BITMAP_8_BY_13, "<< Lista de palabras >>");





   stringstream stream;
   string in = "Intentos: ";
   int num;// = intentos;
   //stream << num;
   string ns;// = stream.str();
   char inte[15] = "";
   //char inte2[5] = "";
   char inte3[15] = "";
   char inte4[5] = "";
   int ii, jj;
   
   for(ii = 0; ii < in.length(); ii++){
   		inte[ii] = in[ii];
   }
   glColor3f(1, 1, 1);
   glRasterPos3f(WIDTH-150, HEIGHT-30, 0.0);
   writenBitmapString2(GLUT_BITMAP_8_BY_13, inte);

   
   int color;
   for(int i = 1; i <= 5; i++){

   		stringstream stream;   		  		
   		int num = i;
	    stream << num;
	    string ns = stream.str();
	    char inte2[5] = "";


	    if(i == intentos) colorIntentos[i-1] = 1;
	    else {colorIntentos[i-1] = 0;}
	    //colorIntentos[i-1] = 1;

	    for(jj = 0; jj < ns.length(); jj++){
   			inte2[jj] = ns[jj];
   		}

   		int color = colorIntentos[i-1];

   		glColor3f(color, color, color);
	    glRasterPos3f(WIDTH-70 + (7*(i-1)), HEIGHT-30, 0.0);
	    writenBitmapString2(GLUT_BITMAP_8_BY_13, inte2);
   }
   //colorIntentos[intentos-1] = 1;
   
   if(intentos == 0){
	   glColor3f(0, 0, 1);
	   glRasterPos3f(WIDTH-150, HEIGHT-50, 0.0);
	   writenBitmapString2(GLUT_BITMAP_8_BY_13, "PERDISTE :'(");
   }

   if(destapadas == aceptadas.size()){
	   glColor3f(0, 0, 1);
	   glRasterPos3f(WIDTH-150, HEIGHT-50, 0.0);
	   writenBitmapString2(GLUT_BITMAP_8_BY_13, "GANASTE !!!");
   }
   
     

   int numLetras;
   int pos = 0;
   int cant;

   for(int j = 1; j <= 15; j++){
   		cant=0;

	   	for(int i = 0; i < aceptadas.size(); i++){

	   		if(aceptadas[i].length() == j){
	   			char cadena[20] = "";
		   		for (int k = 0; k < aceptadas[i].length(); k++){
		   			
		   			cadena[k] = aceptadas[i][k];
		   		}
		   		if(cant == 0){		   			
				    in = "letras: ";
				    num = j;
				    stringstream stream;
				    stream << num;
				    ns = stream.str();
				    			   
				    for(ii = 0; ii < in.length(); ii++){
				   		 inte3[ii] = in[ii];
				    }
		   			glColor3f(1, 0, 0);
					glRasterPos3f(WIDTH-150, HEIGHT-(100+(pos*35)), 0);
					writenBitmapString2(GLUT_BITMAP_8_BY_13, inte3);

				    for(jj = 0; jj < ns.length(); jj++){
				   		 inte4[jj] = ns[jj];
				    }
				    glRasterPos3f(WIDTH-90, HEIGHT-(100+(pos*35)), 0.0);
				    writenBitmapString2(GLUT_BITMAP_8_BY_13, inte4); 
		   		}

		   		posicionPalabra[i][0] = WIDTH-150;
				posicionPalabra[i][1] = HEIGHT-(110+(pos*35));

		   		glColor3f(colorPalabra[i][0], colorPalabra[i][1], colorPalabra[i][2]);
				glRasterPos3f(posicionPalabra[i][0], posicionPalabra[i][1], 0);
				writenBitmapString2(GLUT_BITMAP_8_BY_13, cadena);

				pos++;
				cant++;

	   		}
	   	}
   }

   glColor3f(1, 1, 1);
   glRasterPos3f(WIDTH-145, 45, 0.0);
   writenBitmapString2(GLUT_BITMAP_8_BY_13, "Ver respuestas");

   bool rompe;

   if(conLetras == true){//se muestran las palabras cuando el boton es presionado
   		
   		for(int i = 0; i < aceptadas.size(); i++){
   			for(int j = 0; j < crucigrama[i].size(); j++){
   				
   				glColor3f(0, 0, 0);
				glRasterPos3f(crucigrama[i][j].getPosX(), crucigrama[i][j].getPosY(), 0.0);
				writenBitmapString(GLUT_BITMAP_8_BY_13, crucigrama[i][j].getLetra());
			
   			}   			
   		}

   }
   else{
   		//exit(0);
   		for(int i = 0; i < aceptadas.size(); i++){
   			for(int j = 0; j < crucigrama[i].size(); j++){
				if(j == 0)glColor3f(1, 1, 0);
   				else glColor3f(1,1,1);
				glRasterPos3f(crucigrama[i][j].getPosX(), crucigrama[i][j].getPosY(), 0.0);
				writenBitmapString(GLUT_BITMAP_8_BY_13, crucigrama[i][j].getLetra());
			}   			
   		}

   }
   //if(palabraCorrecta == true){
   if(palabrasAcertadas.size()>0){
   		//cout<<crucigrama[indicePalabra][0].getLetra()<<endl;

   		for(int i = 0; i < palabrasAcertadas.size(); i++){
   			colorPalabra[palabrasAcertadas[i]][0] = 0;
   			colorPalabra[palabrasAcertadas[i]][1] = 0;
   			colorPalabra[palabrasAcertadas[i]][2] = 0;
   			for(int j = 0; j < crucigrama[palabrasAcertadas[i]].size(); j++){
				glColor3f(0, 0, 0);
				glRasterPos3f(crucigrama[palabrasAcertadas[i]][j].getPosX(), crucigrama[palabrasAcertadas[i]][j].getPosY(), 0.0);
				writenBitmapString(GLUT_BITMAP_8_BY_13, crucigrama[palabrasAcertadas[i]][j].getLetra());
			} 
   		}

   		

   }




 

   glFlush();
}


void drawScene(void){


   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);

   //instrucciones
   glColor3f(1, 1, 1);
   glRasterPos3f(10,HEIGHT+10, 0.0);
   writenBitmapString2(GLUT_BITMAP_8_BY_13, "Clic en pantalla para comenzar");


   //se imprimen los cuadros rojos de la matriz
   glPointSize(25);
   glBegin(GL_POINTS);
   glColor3f(.35,0,0);
   for(int i = 0; i < 24; i++){
		for(int j = 0; j < 20; j++){
			glVertex2f(posiciones[i][j][0], posiciones[i][j][1]);
			
		}
		//f-=12.5;
	}

   glEnd();

   
   //mandan las palabras a la matriz de crucigrama
   for(int i = 0; i < palabras.size(); i++){  

   		formaPalabra(aleatorias[i], forma);
   		forma++;
   }

   //muestra las palabras aceptadas
   
   //cout<<"aceptadas:------------- "<<palabrasAceptadas<<endl;
   for(int i = 0; i < aceptadas.size(); i++){
   		//cout<<aceptadas[i]<<endl;
   }

   glFlush();
   glutDisplayFunc(drawButtons);
   
   
}

void keyInput(unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}





int clicPalabra=0;

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{

	y = height - y;

   // Store the clicked point in the currentPoint variable when left button is pressed.
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
   		//cout<<x<<","<<y<<endl;
   		
   		//si se presiona una letra
	   	if(x > WIDTH-150 && x <WIDTH-20 && y > 30 && y < 70 && presiona == false){
	   		clic = .5;
	   		presiona = true;
	   		conLetras = true;
	   	}

	   	//Si se preciona algun cuadro amarillo

	   	for(int i = 0; i < 15; i++){

		   	if(x > posicionPalabra[i][0] && x < posicionPalabra[i][0]+50 && y > posicionPalabra[i][1] && y < posicionPalabra[i][1]+10){
		   		
		   		palabraPresionada = !palabraPresionada;

		   	 	if(palabraPresionada==true) colorPalabra[i][2] = 0;
		   	 	else colorPalabra[i][2] = 1;

		   		indicePalabra = i;
		   		//cout<<indicePalabra<<endl;

		   		//clicPalabra++;
		   		//
		   		for(int j = 0; j < 15; j++){
		   			if(j != i){
		   				colorPalabra[j][2] = 1;
		   			}
		   			
		   		}
		   	}
		   	else{
		   		//palabraPresionada = false;
		   	}
	    }
	    //cout<<"boton: "<<crucigrama[indicePalabra][0].getPosX()<<","<<crucigrama[indicePalabra][0].getPosY()<<endl;

	    if(x > crucigrama[indicePalabra][0].getPosX()-12.5 && x < crucigrama[indicePalabra][0].getPosX()+12.5 && 
	       y > crucigrama[indicePalabra][0].getPosY()-12.5 && y < crucigrama[indicePalabra][0].getPosY()+12.5){
	    	//cout<<"palabra correcta"<<endl;
	    	palabraCorrecta = true;
	    	palabraPresionada = false;
	    	palabrasAcertadas.push_back(indicePalabra);
	    	destapadas++;
	    	//cout<<"destapadas: "<<destapadas<<endl;
	    }
	    else{
	    	palabraCorrecta = false;
	    	if(palabraPresionada==true){

	    		bool breakk = false;
	    		for(int i = 0; i < 15; i ++){
	    			for(int j = 0; j < crucigrama[i].size(); j++){
	    				if(x > crucigrama[i][0].getPosX()-12.5 && x < crucigrama[i][0].getPosX()+12.5 && 
	      				   y > crucigrama[i][0].getPosY()-12.5 && y < crucigrama[i][0].getPosY()+12.5){
	    					intentos--;
	    					breakk = true;
	    					break;
	    				}
	    					
	    			}	
	    			if (breakk == true) break;
	    		}

	    		
	    	}
	    	//cout<<"intentos: "<<intentos<<endl;
	    }
   }      

   // Store the currentPoint in the points vector when left button is released.
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
	   	if(x > WIDTH-150 && x <WIDTH-20 && y > 30 && y < 70 && presiona == true){
	   		clic = 1;
	   		presiona = false;
	   		conLetras = false;
	   	}
   }

   glutPostRedisplay();
}

void mouseMotion(int x, int y){

	y = (height - y);

	cout<<x<<","<<y<<endl;

	glutPostRedisplay();
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

	srand(time(NULL));

	leerFichero();

	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 3; j++)
			colorPalabra[i][j] = 1;
	}
	
	double f = HEIGHT-13, c;//variables de incremento de filas y columnas

   for(int i = 0; i < 24; i++){
   		c = 13.0;
		for(int j = 0; j < 20; j++){
			posiciones[i][j][0] = c;//posicion en X
			posiciones[i][j][1] = f;//posicion en Y
			posiciones[i][j][2] = 0;//desocupado(sin letra)
			c+=26;
		}
		f-=26;
	}

	//cout<<f<<" "<<c<<endl;
	//
	cout<<"**********NORBERTO III MORALES AVITIA*************"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"<< INSTRUCCIONES >>"<<endl;
	cout<<endl;
	cout<<"-Clic al inicio para comenzar"<<endl;
	cout<<"-En la lista de palabras estan las palabras ordenadas por numero de letras"<<endl;
	cout<<"-Las palabras son tomadas desde un archivo pero no siempre immprime debido a que no encuentra coincidencias con los cruces"<<endl;
	cout<<"-Para tomar una palabra de la lista, se debe hacer clic sobre ella, cuando esta en amarillo significa que esta seleccionada"<<endl;
	cout<<"-Para colocar la palabra en el crucigrama se debe dar clic sobre los cuadros amarillos para su verificacion"<<endl;
	cout<<"-El usuario pierde cuando llega a 0 intentos"<<endl;
	cout<<"-El usuario gana cuando completa el crucigrama"<<endl;




	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH+100, HEIGHT+50);
    glutInitWindowPosition(300, 0);
    glutCreateWindow("Crucigrama");
    glutReshapeFunc(resize);
    glutDisplayFunc(drawScene); 

    glutKeyboardFunc(keyInput);

    glutMouseFunc(mouseControl);

    glutMotionFunc(mouseMotion); 
    cout<<"error"<<endl;
    glutMainLoop(); 
}