#include <stdio.h>
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLUT/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif                //GLUT toolkit
#include <time.h>
//definimos variables globales, tales como tamano, vista inicial en todos los angulos
#define SIZE 600
#define INIT_VIEW_X 1.0
#define INIT_VIEW_Y 0.0
#define INIT_VIEW_Z -10.0
#define VIEW_LEFT -2.0
#define VIEW_RIGHT 2.0
#define VIEW_BOTTOM -2.0
#define VIEW_TOP 2.0
#define VIEW_NEAR 1.0
#define VIEW_FAR 200.0

#include "imageloader.h"
GLuint *_textureId;
GLUquadric *quad1, *quad2;

int T = 3;

////////////
//funcion para mostrar el menu en la terminal.
void showMenu();
////////////////////
//variables de opengl para hacer el efecto de luz en el gorro, y la ropa.
//tambien para la posicion la luz, y el reflejo.
GLfloat AmbientLight[]={0.3,0.3,0.3,1.0};
GLfloat DiffuseLight[] ={0.8,0.8,0.8,1.0};
GLfloat SpecularLight[] ={1.0,1.0,1.0,1.0};
GLfloat SpecRef[] = {0.7,0.7,0.7,1.0};
GLfloat LightPos[] = {-50.0,50.0,100.0,1.0};
GLint Shine =128;
GLint walkX=0,walkY=0,lookX=0,lookY=0;
GLint oldX=-1,oldY=-1;

GLuint loadTexture(Image* image, GLuint texture) {
    //glGenTextures(1, &texture); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, texture); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
     0,                            //0 for now
     GL_RGB,                       //Format OpenGL uses for image
     image->width, image->height,  //Width and height
     0,                            //The border of the image
     GL_RGB, //GL_RGB, because pixels are stored in RGB format
     GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                       //as unsigned numbers
     image->pixels);               //The actual pixel data

    return texture; //Returns the id of the texture
}


static void init2(void)
{
   //DefinirMisColores ();
   
   glEnable(GL_DEPTH_TEST);
   //glShadeModel(GL_FLAT);
   glClearColor(0.5, 0.5, 0.5, 0.5);
   Image* image;
   
   _textureId = new GLuint[T];
    glGenTextures(T, _textureId);

    quad1 = gluNewQuadric();
    quad2 = gluNewQuadric();

   
   //Image* image = loadBMP("vtr.bmp");
   //Image* image = loadBMP("upv.bmp");
   //TEXTURAS  
   
   image = loadBMP("gorro.bmp");
   loadTexture(image, _textureId[0]);
   image = loadBMP("abrigo.bmp");
   loadTexture(image, _textureId[1]);
   image = loadBMP("fondo.bmp");
   loadTexture(image, _textureId[2]);

   delete image;

}

//funcion para dibujar el ojo derecho con una esfera
void eyeright()
{
    glPushMatrix();
    glTranslatef(.17,1.1,.75);
    glRotatef(-45,0,0,1);
    glScalef(.9,.7,.7);
    glColor3f(1.0,1.0,1.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
//funcion para dibujar el ojo izquierdo con una esfera
void eyeleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.75);
    glRotatef(45,0,0,1);
    glScalef(.9,.7,.7);
    glColor3f(1.0,1.0,1.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
//funcion para dibujar la pierna izquierda con un cilindro
void legleft()
{
    glPushMatrix();
    glTranslatef(.3,-.5,0);
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}
//funcion para dibujar la pierna derecha con un cilindro
void legright()
{
    glPushMatrix();
    glTranslatef(-.3,-.5,0);
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}
//funcion para dibujar el brazo izquierdo con un cilindro
void armleft()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[1]);

    //Bottom
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
    glTranslatef(-.82,0,.1);
    glRotatef(90,0,1,0);
    glRotatef(-50,1,0,0);

    gluQuadricTexture(quad1,1);
    gluCylinder(quad1,.15,.15,.48,30,6);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
//funcion para dibujar el brazo derecho con un cilindro
void armright()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[1]);

    //Bottom
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
    glTranslatef(.82,0,.1);
    glRotatef(90,0,1,0);
    glRotatef(-130,1,0,0);
    gluQuadricTexture(quad1,1);
    gluCylinder(quad1,.15,.15,.48,30,6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
//funcion para dibujar la mano izquierda con una esfera
void handleft()
{
    glPushMatrix();
    glTranslatef(.82,0,.1);
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}
//funcion para dibujar la mano derecha con una esfera
void handright()
{
    glPushMatrix();
    glTranslatef(-.82,0,.1);
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}
//funcion para dibujar la boca con una esfera
void mouth()
{
    glPushMatrix();
    glTranslatef(0,.78,.74);
    glScalef(.4,.2,.1);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}
//funcion para dibujar la bufanda con torus
void neckring()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(.59,.59,.59);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();
}
//funcion para dibujar el gorro, es la cabeza/3
void hat()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[0]);

    //Bottom
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
    glTranslatef(0,1.5,0);
    glScalef(.9 ,.6,.9 );  
    gluQuadricTexture(quad1,1);
    gluSphere(quad1,1,100,100);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
//funcion para dibujar la cabeza con una esfera
void head()
{
    glPushMatrix();
    glTranslatef(0,1.2,0);
    glScalef(.9 ,.9,.9 );
    glColor3f(1.0,0.8,0.6);
    gluSphere(gluNewQuadric(),1,100,100);
    glPopMatrix();
}
//funcion para dibujar la bola sobre el gorro con una esfera
void maintopball()
{
    glPushMatrix();
    glTranslatef(0,2.2,0);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.18,100,100);
    glPopMatrix();
}
//funcion para dibujar la base del gorro con un torus
void hatring()
{
    glPushMatrix();
    glTranslatef(0,1.4,0);
    glScalef(.84,.84,.84);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();
}
//funcion para dibujar el pie derecho con una esfera
void footleft()
{
    glPushMatrix();
    glTranslatef(-.3,-.5,0);
    glScalef(1.5,.3,1.5);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
//funcion para dibujar el pie derecho con una esfera
void footright()
{
    glPushMatrix();
    glTranslatef(.3,-.5,0);
    glScalef(1.5,.3,1.5);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
//funcion para dibujar la base de la chaqueta con un disco
void bellyCoatbottom()
{
    glPushMatrix();
    glTranslatef(0,-.2,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluDisk(gluNewQuadric(),0,.8,30,30);
    glPopMatrix();
}
//funcion para dibujar la chaqueta con un cilindro
void BellyCoat()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[1]);

    //Bottom
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluQuadricTexture(quad1,1);
    gluCylinder(quad1,.6,.8,1,100,100);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
//funcion para dibujar la pupila de los ojos con una esfera
void pupilleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}
//funcion para dibujar la pupila derecha de los ojos con una esfera
void pupilright()
{
    glPushMatrix();
    glTranslatef(.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}
//funcion para dibujar el primer boton de arriba hacia abajo con una esfera
void topbutton()
{
    glPushMatrix();
    glTranslatef(-.1,.4,.70);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
//funcion para dibujar la linea de los botones se realizo en dos partes
//esta es la parte del boton de en medio para arriba
void linescoath()
{
	glPushMatrix();
	glScalef(0,0.5,1.0);
	glLineWidth(3);
	glTranslatef(-.1,.15,.85);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.85, 0);
	glEnd();
	glPopMatrix();
}
//la parte del boton de en medio hacia abajo
void linescoath1()
{
	glPushMatrix();
	glScalef(0,0.5,1.0);
	glLineWidth(3);
	glTranslatef(-.1,-.30,.85);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.85, 0);
	glEnd();
	glPopMatrix();
}
//boton de en medio con una esfera
void middlebutton(){
    glPushMatrix();
    glTranslatef(-.1,.15,.75);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
//boton del final con una esfera
void bottombutton(){
    glPushMatrix();
    glTranslatef(-.1,-.1,.85);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
//funcion donde mostramos todas nuestras partes terminadas
void Display()
{		

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glTranslatef(0.0f, 1.0f, -16.0f);

    		
		// primero se hace una limpia de los buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//se asignan los colores
    glColor3ub(50, 50, 150);
    	//como cada funcion esta metida en nuestra matrix, empezamos a sacarlas
    	// una por una
    glPushMatrix();
    	//este translate y rotate es para mover el personaje.
    	glTranslatef(walkX,-1,walkY);
    glRotatef(lookY,0,1,0);
    glRotatef(lookX,1,0,0);	
		//aqui empiezan a llamarse las funciones y asignandoles colores.
    eyeright();
    eyeleft();
    glColor3f(1.0,0.0,0.0);
		hatring();
    neckring();
    glColor3f(0.439216,0.3,1.958824);
    legright();
    legleft();
		hat();
    glColor3f(0.65,0.49,0.24);
    armleft();
    armright();
    BellyCoat();
    bellyCoatbottom();
    glColor3f(1.0,0.0,0.0);		
    handleft();
		maintopball();
    handright();
    mouth();  
    glColor3ub(255,222,173);
    head();
		glColor3ub(255,222,173);
    footleft();
    footright();
		glColor3f(0.329412,0.329412,0.329412);
    topbutton();
		middlebutton();
    bottombutton();
		linescoath();
		linescoath1();
		glColor3f(0.0,0.0,0.0);
    pupilleft();
    pupilright();
    glPopMatrix();
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glTexCoord2f(-7,-5);
    glVertex2f(-7,-5);
    glTexCoord2f(5,-5);
    glVertex2f(5,-5);
    glTexCoord2f(5,5);
    glVertex2f(5,5);
    glTexCoord2f(-7,5);
    glVertex2f(-7,5);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    
    
    //gluQuadricTexture(quad,1);
    //gluSphere(quad,1,100,100);


    glutSwapBuffers();		
}
//Aqui se hace lo de la luz, el reflejo, y el resplandor
void SetupRend()
{
    glClearColor(0.7,0.7,1.0,1.0);
    glEnable(GL_DEPTH_TEST);         
    glEnable(GL_LIGHTING);          
    glLightfv(GL_LIGHT0,GL_AMBIENT,AmbientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,DiffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);                   
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT,GL_SPECULAR,SpecRef);
    glMateriali(GL_FRONT,GL_SHININESS,Shine);
}
//Aqui es para que el personaje se mueva sobre su propio eje.
void walk(int key,int x,int y)
{
    if(key==GLUT_KEY_UP)    lookX+=1;
    if(key==GLUT_KEY_DOWN)  lookX-=1;
    if(key==GLUT_KEY_RIGHT) lookY+=1;
    if(key==GLUT_KEY_LEFT)  lookY-=1;
    
}
//este es para que el personaje se mueva por el mundo
void keyInput(unsigned char key, int x, int y)
{
   switch(key)
   {
			case 'x':
			walkX += 1;
			break;
		case 'X':
			walkX -= 1;
			break;
		case 'y':
			walkY += 1;
			break;
		case 'Y':
			walkY -= 1;
			break;   
		case 'm':
			showMenu();
			break; 
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}
//este es el reshape para que todo se dibuje bien
void myReshape(int w, int h)
{
    GLfloat Ratio;
    glViewport(0,0,w,h);
    Ratio=1.0*w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,Ratio,VIEW_NEAR,VIEW_FAR);
    glMatrixMode(GL_MODELVIEW);
		
    glLoadIdentity();
    glTranslatef(INIT_VIEW_X,INIT_VIEW_Y,INIT_VIEW_Z);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
}
//el init para el menu
void init (void)						
{	
	showMenu();

    /*glEnable(GL_DEPTH_TEST);
    glClearColor(0.5, 0.5, 0.5, 0.5);
    Image* image;

    _textureId = new GLuint[T];
    glGenTextures(T, _textureId);

    image = loadBMP("gorro.bmp");
    loadTexture(image, _textureId[0]);
    image = loadBMP("abrigo.bmp");
    loadTexture(image, _textureId[1]);
    image = loadBMP("fondo.bmp");
    loadTexture(image, _textureId[2]);

    delete image;*/
}
//nuestro menu
void showMenu(void)
{
	printf("\n\n Operations: ");
	printf("\n Use the x/X,y/Y for rotations about x,y and arrows keys, UP, DOWN, LEFT or Right.");
	printf("\n Use m or M to see this menu again.\n");
}
int main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); 
    glutInitWindowSize(SIZE, SIZE);
    glutCreateWindow("Stan");
    init();
    init2();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutSpecialFunc(walk);
    glutKeyboardFunc(keyInput);
    SetupRend();
    glEnable(GL_NORMALIZE);
    glutMainLoop();
}
