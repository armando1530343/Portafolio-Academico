#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAXFILAS 31
#define MAXCOLS 28

using namespace std;

struct Nodo{
    Nodo *nodoPadre;
    int g;
    int h;
    int f;
    int posX;
    int posY;
    bool listaAb;
    bool listaCe;

};

struct Dato{
    Nodo* nodoA;
    Dato* siguiente;
};


int **laberinto=NULL;
int **matrizPrincipal=NULL;
int **matrizAdyacente=NULL;
int **matrizRecorridos=NULL;
int matrizpond[MAXFILAS][MAXCOLS];
Nodo matrizNod[MAXFILAS][MAXCOLS];

FILE *lab;
int  filas, columnas, bolas=0;
int fi, co, posInicial;
int fiA, coA;
int f1x=26, f1y=29;
int f2x=26, f2y=1;
int f3x=1, f3y=1;
int f4x=1*15, f4y=29*15;
int dirAleatorio = 0;
int vidas=2;
BITMAP *buffer, *bloque, *ball, *vacio;
BITMAP *pac1, *pac2, *pac3, *pac4, *pac5, *vida, *vacioVid;
BITMAP *fan1, *fan2, *fan3, *fan4, *cambioPac;
BITMAP *muertePac1, *muertePac2, *muertePac3, *muertePac4, *muertePac5, *muertePac6, *muertePac7;
BITMAP *perdiste;

int speed_counter = 0;

void incrementa_counter(){
    speed_counter++;
}
END_OF_FUNCTION(incrementa_counter);

int** crear_laberinto(int** laber){
    char a;
    int n, c=-1, f=1, i, j;
    char archivo[] = {"laberinto1_pacman.txt"};
    lab = fopen(archivo,"rb");
    if(lab!=NULL){
        while(!feof(lab)){
           if(getc(lab)!='\n')
              c++;
           else{
              c=-1;
              f++;
           }
        }
        //cout<<"Columnas: "<<c<<endl;
        //cout<<"Filas: "<<f<<endl;
        filas=f;
        columnas=c;
        fclose(lab);
        fopen(archivo,"rb");
        laber = new int*[f];
        for(i=0;i<f;i++)
            *(laber+i)=new int[c];

        i=0, j=0;
        while(!feof(lab)){
           a=getc(lab);
           if(a!='\n'){
              n = (int)a - 48;
              if(n==1||n==0||n==2||n==3){
                laber[i][j]=n;
                if(n==1)bolas++;
                //cout<<laber[i][j];
              }
              j++;
           }
           else{
                i++;
                j=0;
                //cout<<endl;
           }
           if(j==c)j--;
           if(i==f)break;
        }
    }
    else
        cout<<"El Archivo no Existe"<<endl;

    return laber;
}
void dibujar_laberinto(int ** laber){

    int i, j;

    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            if(laber[i][j]==0){
                draw_sprite(buffer, bloque, j*15, i*15);
                //blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
            }
            else if(laber[i][j]==1)
                draw_sprite(buffer, ball, j*15, i*15);
            else if(laber[i][j]==2||laber[i][j]==3)
                draw_sprite(buffer, vacio, j*15, i*15);
        }
    }

}


void push(Dato*& lista,Nodo* nod){
    Dato* aux=new Dato; //Se crea un nuevo elemento
    aux->nodoA=nod; //Se le asigna el valor al nuevo elemento
    aux->siguiente=lista; //El nuevo elemento apunta al primer elemento de la lista
    lista=aux;
}

void ordenar(Dato*& lista){
    Dato *i,*j; //Auxiliares para recorrer y controlar la lista
    Nodo* aux; //Auxiliar para guarar un valor
    i=lista; //Se asigna el primer elemento de la lista


    while(i!=NULL){//Primer ciclo para recorrer la lista
        j=i; //A j se le asigna el valor de i
        while(j->siguiente!=NULL){//Segundo ciclo para recorrer la lista
            j=j->siguiente; //Se recorre j
            if(i->nodoA->f > j->nodoA->f){//Si el valor de i es mayor que el de j
                aux = i->nodoA; //Se guarda el valor de i
                i->nodoA = j->nodoA; //El valor de j se pasa a i
                j->nodoA = aux; //El anterior valor de i se pasa a j
            }
        }
        i=i->siguiente; //Se recorre i
    }
}

void pop(Dato*& lista, int* x, int* y){
    if(lista!=NULL){
        *x=lista->nodoA->posX;
        *y=lista->nodoA->posY;
        lista->nodoA->listaCe=1;
        Dato* aux=lista;
        lista=lista->siguiente;
        delete[] aux;
        aux=NULL;
    }
}

void muerte(){

    for(int i=0;i<30;i++){
        if(i==0){
            draw_sprite(buffer, muertePac1, co*15, fi*15 );
        }
        if(i==1){
            draw_sprite(buffer, muertePac2, co*15, fi*15 );
        }
        if(i==2){
            draw_sprite(buffer, muertePac3, co*15, fi*15 );
        }
        if(i==3){
            draw_sprite(buffer, muertePac4, co*15, fi*15 );
        }
        if(i==4){
            draw_sprite(buffer, muertePac5, co*15, fi*15 );
        }
        if(i==5){
            draw_sprite(buffer, muertePac6, co*15, fi*15 );
        }
        if(i==6){
            draw_sprite(buffer, muertePac7, co*15, fi*15 );
        }

        rest(1);
    }

}


void reiniciarJuego(){
    muerte();
    vidas--;
    if(vidas<0){
            while(!key[KEY_ESC]){
                textout(screen,font,"¡¡¡PERDISTE!!!",160,215,makecol(255,196,126));
            }
            cout<<"***\255\255\255PERDISTE!!!***"<<endl;
            cout<<"Bolas comidas: "<<298-bolas<<endl;
        exit(-1);
    }
    else{
        fi=17;
        co=14;
        f1x=26;
        f1y=26;
        f2x=26;
        f2y=1;
        f3x=1;
        f3y=1;
        f4x=1*15;
        f4y=29*15;
    }
}


void getpond(){
    for(int i=0;i<MAXFILAS;i++){
        for(int j=0;j<MAXCOLS;j++){
            if(laberinto[i][j]!=0){
                matrizpond[i][j]=(sqrt(pow((i-(fi)),2)))+(sqrt(pow((j-(co)),2)));
            }
            else{
                matrizpond[i][j]=1000;
            }
            matrizNod[i][j].posY=i;
            matrizNod[i][j].posX=j;
            matrizNod[i][j].h=matrizpond[i][j];
            matrizNod[i][j].listaAb=0;
            matrizNod[i][j].listaCe=0;
        }
    }
}

void getpond2(){
    int cont=0;
    for(int i=0;i<MAXFILAS;i++){
        for(int j=0;j<MAXCOLS;j++){
            if(laberinto[i][j]!=0){
                matrizpond[i][j]=cont+(sqrt(pow(i-fi,2)+pow(j-co,2)));
            }
            else{
                matrizpond[i][j]=1000;
            }
            matrizNod[i][j].posY=i;
            matrizNod[i][j].posX=j;
            matrizNod[i][j].h=matrizpond[i][j];
            matrizNod[i][j].listaAb=0;
            matrizNod[i][j].listaCe=0;
            cont++;
        }

    }
}

void reiniciarNodos(){
    for(int i=0;i<MAXFILAS;i++){
        for(int j=0;j<MAXCOLS;j++){
            matrizNod[i][j].listaAb=0;
            matrizNod[i][j].listaCe=0;
            matrizNod[i][j].h=matrizpond[i][j];
        }
    }
}

/*************************************************************************************************************
*************************************************A-STAR*******************************************************
**************************************************************************************************************/

void aStar(BITMAP*& fant,int* fpX, int* fpY){
    draw_sprite(buffer, fant, *fpX*15, *fpY*15 );
    int actX,actY,i,j;
    Dato* listaAbierta=NULL;
    actX=*fpX;
    actY=*fpY;

    push(listaAbierta,&matrizNod[actY][actX]);

    pop(listaAbierta,&actX,&actY);

    while(actX!=(co) || actY!=(fi)){
        for(i=actY-1;i<(actY+2);i++){
            for(j=actX-1;j<(actX+2);j++){
                if((i==actY-1 && j==actX) || (i==actY+1 && j==actX) || (i==actY && j==actX-1) || (i==actY && j==actX+1)){
                    if(matrizNod[i][j].listaAb==0 && matrizNod[i][j].listaCe==0 && matrizpond[i][j]!=1000){
                        matrizNod[i][j].listaAb=1;
                        matrizNod[i][j].nodoPadre=&matrizNod[actY][actX];
                        matrizNod[i][j].g=matrizNod[i][j].nodoPadre->g+(1);
                        matrizNod[i][j].f=matrizNod[i][j].g+matrizNod[i][j].h;
                        push(listaAbierta,&matrizNod[i][j]);
                        ordenar(listaAbierta);
                    }
                    else if(matrizNod[i][j].listaAb==1 && matrizNod[i][j].listaCe==0){
                        if((matrizNod[actY][actX].g+1) < matrizNod[i][j].g){
                            matrizNod[i][j].nodoPadre=&matrizNod[actY][actX];
                            matrizNod[i][j].g=matrizNod[i][j].nodoPadre->g+(1);
                            matrizNod[i][j].f=matrizNod[i][j].g+matrizNod[i][j].h;
                            ordenar(listaAbierta);
                        }
                    }

                }
            }
        }
        pop(listaAbierta,&actX,&actY);
    }



    Dato* camino=NULL;
    Nodo* pos=&matrizNod[actY][actX];

    if((*fpX==co && *fpY==fi)||(*fpX==(coA*15)&&*fpY==(fiA*15))){
        reiniciarJuego();
    }else{
        while(pos->posX!=(*fpX) || pos->posY!=(*fpY)){
            push(camino,pos);
            pos=pos->nodoPadre;
        }

        *fpX=(camino->nodoA->posX);
        *fpY=(camino->nodoA->posY);
    }
}

/*************************************************************************************************************
************************************************DIJKSTRA******************************************************
**************************************************************************************************************/

void Dijkstra(){
    reiniciarNodos();

    draw_sprite(buffer, fan2, f2x*15, f2y*15 );

    int actX,actY,i,j;
    Dato* nodosMarcados=NULL;
    actX=f2x;
    actY=f2y;


    push(nodosMarcados,&matrizNod[actY][actX]);
    matrizNod[actY][actX].f=matrizNod[actY][actX].h;

    pop(nodosMarcados,&actX,&actY);


    while(actX!=(co) || actY!=(fi)){
        for(i=actY-1;i<(actY+2);i++){
            for(j=actX-1;j<(actX+2);j++){
                if((i==actY-1 && j==actX) || (i==actY+1 && j==actX) || (i==actY && j==actX-1) || (i==actY && j==actX+1)){
                    if(matrizNod[i][j].listaAb==0 && matrizNod[i][j].listaCe==0 && matrizNod[i][j].h!=1000){
                        matrizNod[i][j].listaAb=1;
                        matrizNod[i][j].nodoPadre=&matrizNod[actY][actX];
                        matrizNod[i][j].f=matrizNod[i][j].h;
                        matrizNod[i][j].f=matrizNod[i][j].f+matrizNod[i][j].nodoPadre->f;
                        push(nodosMarcados,&matrizNod[i][j]);
                        ordenar(nodosMarcados);
                    }
                    else if(matrizNod[i][j].listaAb==1 && matrizNod[i][j].listaCe==0){
                        if((matrizNod[actY][actX].f+matrizpond[i][j]) < matrizNod[i][j].f){
                            matrizNod[i][j].nodoPadre=&matrizNod[actY][actX];
                            matrizNod[i][j].f+=matrizNod[i][j].nodoPadre->f;
                            ordenar(nodosMarcados);
                        }
                    }

                }
            }
        }
        pop(nodosMarcados,&actX,&actY);
    }


    Dato* camino=NULL;
    Nodo* pos=&matrizNod[actY][actX];

    if((f2x==co && f2y==fi)||(f2x==(coA*15)&&f2y==(fiA*15))){
        reiniciarJuego();
    }else{
        while(pos->posX!=(f2x) || pos->posY!=(f2y)){
            push(camino,pos);
            pos=pos->nodoPadre;
        }

        f2x=(camino->nodoA->posX);
        f2y=(camino->nodoA->posY);
    }

}

/*************************************************************************************************************
**********************************************ALEATORIO*******************************************************
**************************************************************************************************************/
void aleatorio(){

    draw_sprite(buffer, fan4, f4x, f4y);

    if((f4x==co*15 && f4y==fi*15)||(f4x==(coA)&&f4y==(fiA))){
        reiniciarJuego();
    }else{
        if(dirAleatorio == 0){
            if(laberinto[f4y/15][(f4x-15)/15]!=0){
                f4x = f4x-15;
            }else{
                dirAleatorio = rand()%4;
            }
        }

        if(dirAleatorio == 1){
            if(laberinto[f4y/15][(f4x+15)/15]!=0){
                f4x = f4x+15;
            }else{
                dirAleatorio = rand()%4;
            }
        }

        if(dirAleatorio == 2){
            if(laberinto[(f4y-15)/15][f4x/15]!=0){
                f4y = f4y-15;
            }else{
                dirAleatorio = rand()%4;
            }
        }

        if(dirAleatorio == 3){
            if(laberinto[(f4y+15)/15][f4x/15]!=0){
                f4y = f4y+15;
            }else{
                dirAleatorio = rand()%4;
            }
        }

        if(f4x<=-15){
            f4x = 610;
        }else if(f4x>=620){
            f4x = -15;
    }
    }
}

void dibVidas(){

        if(vidas==2){
            draw_sprite(buffer, vida, 29*15, 28*15);
            draw_sprite(buffer, vida, 30*15, 28*15);
        }

        if(vidas==1){
            draw_sprite(buffer, vida, 29*15, 28*15);
            draw_sprite(buffer, vacioVid, 30*15, 28*15);
        }

        if(vidas==0){
            draw_sprite(buffer, vacioVid, 29*15, 28*15);
            draw_sprite(buffer, vacioVid, 30*15, 28*15);
        }




}


/*************************************************************************************************************
***************************************************MAIN*******************************************************
**************************************************************************************************************/

int main()
{
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,620,480,0,0);

    int i, j;
    bool cambio = true;

    //int **matrizPrincipal=NULL;

    buffer = create_bitmap(620,620);
    bloque = load_bitmap("bloque.bmp",NULL);
    ball = load_bitmap("ball.bmp",NULL);
    pac1 = load_bitmap("pac1.bmp",NULL);
    pac2 = load_bitmap("pac2.bmp",NULL);
    pac3 = load_bitmap("pac3.bmp",NULL);
    pac4 = load_bitmap("pac4.bmp",NULL);
    pac5 = load_bitmap("pac5.bmp",NULL);
    vida = load_bitmap("pac5.bmp",NULL);
    fan1 = load_bitmap("fan1.bmp",NULL);
    fan2 = load_bitmap("fan2.bmp",NULL);
    fan3 = load_bitmap("fan3.bmp",NULL);
    fan4 = load_bitmap("fan4.bmp",NULL);
    vacio = load_bitmap("vacio.bmp",NULL);
    vacioVid = load_bitmap("vacio.bmp",NULL);
    muertePac1 = load_bitmap("muerte1.bmp",NULL);
    muertePac2 = load_bitmap("muerte2.bmp",NULL);
    muertePac3 = load_bitmap("muerte3.bmp",NULL);
    muertePac4 = load_bitmap("muerte4.bmp",NULL);
    muertePac5 = load_bitmap("muerte5.bmp",NULL);
    muertePac6 = load_bitmap("muerte6.bmp",NULL);
    muertePac7 = load_bitmap("muerte7.bmp",NULL);
    perdiste = load_bitmap("perdiste.bmp",NULL);

    LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(incrementa_counter);
    install_int_ex(incrementa_counter,BPS_TO_TIMER(7));

    laberinto = crear_laberinto(laberinto);
    matrizPrincipal=laberinto;
    /*for(i=0;i<filas;i++){
            for(j=0;j<columnas;j++)
                cout<<laberinto[i][j];
            cout<<endl;
    }
    //cout<<"bolas: "<<bolas<<endl;*/
    if(laberinto!=NULL){
        fi=17;
        co=14;
        laberinto[fi][co]=2;
        bolas--;
        cambioPac=pac1;
        char score[5];
        while(!key[KEY_ESC]){
            itoa(297-bolas,score,10);
            textout(screen,font,"SCORE:",460,15,makecol(138,10,10));
            textprintf(screen,font,460,30,makecol(255,255,255),score);
            dibujar_laberinto(laberinto);
             getpond();
             dibVidas();
            fiA = fi*15;
            coA = co*15;



            if(speed_counter>0){
                speed_counter--;

                if(bolas>0){

                if(key[KEY_RIGHT]){
                    cambio=!cambio;
                    if (cambio==true)cambioPac=pac1;
                    else cambioPac=pac2;

                    if(laberinto[fi][co+1]==1||laberinto[fi][co+1]==2){
                            if(laberinto[fi][co+1]==1)bolas--;
                            laberinto[fi][co+1]=2;
                            co++;
                    }
                    else if(laberinto[fi][co+1]==3)
                        co=0;

                }
                if(key[KEY_LEFT]){
                    cambio=!cambio;
                    if (cambio==true)cambioPac=pac1;
                    else cambioPac=pac5;
                    if(laberinto[fi][co-1]==1||laberinto[fi][co-1]==2){
                        if(laberinto[fi][co-1]==1)bolas--;
                        laberinto[fi][co-1]=2; co--;}
                    else if(laberinto[fi][co-1]==3)
                        co=columnas-1;
                }
                if(key[KEY_UP]){
                    cambio=!cambio;
                    if (cambio==true)cambioPac=pac1;
                    else cambioPac=pac4;
                    if(laberinto[fi-1][co]==1||laberinto[fi-1][co]==2){
                        if(laberinto[fi-1][co]==1)bolas--;
                        laberinto[fi-1][co]=2; fi--;}
                }
                if(key[KEY_DOWN]){
                    cambio=!cambio;
                    if (cambio==true)cambioPac=pac1;
                    else cambioPac=pac3;
                    if(laberinto[fi+1][co]==1||laberinto[fi+1][co]==2){
                        if(laberinto[fi+1][co]==1)bolas--;
                        laberinto[fi+1][co]=2; fi++;}
                }

                draw_sprite(buffer, cambioPac, co*15, fi*15 );
                }
                else
                    draw_sprite(buffer, pac1, co*15, fi*15 );


                if(bolas==0){
                    while(!key[KEY_ESC]){
                        textout(screen,font,"¡¡¡GANASTE!!!",160,215,makecol(202,159,76));
                    }
                    cout<<"***\255\255\255GANASTE!!!***"<<endl;
                    exit(-1);
                }

                if(!key[KEY_P]){



                aStar(fan3,&f3x,&f3y);
                Dijkstra();
                getpond2();
                aStar(fan1,&f1x,&f1y);
                aleatorio();
                }

                blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);



            }

            rest(1);
        }
    }
    //cout<<"Bolas: "<<bolas<<endl;
    readkey();
    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN();
