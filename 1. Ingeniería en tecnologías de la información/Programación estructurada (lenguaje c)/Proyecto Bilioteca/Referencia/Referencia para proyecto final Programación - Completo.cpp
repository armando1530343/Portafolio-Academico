/*
Universidad Politécniva de Victoria
Programación estructurada
Genera una estructura en la memoria principal y guarda en archivo.
Cuando el programa se inicia carga la información del archivo a la RAM.
Emplea asignación dinámica de memoria, struct, archivos binarios, funciones con paso de parámetros por valor y por referencia,
estructuras de control, puntero simple y doble, contadores, banderas, estructuras de control repetitivas y de decisión.
20110708
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct agenda{
       char nombre[30];
       int edad;
};
void menu();
int agregar(agenda **,int );
void mostrar(agenda **,int);
void modificar(agenda **,int );
int eliminar(agenda **,int);
int leer_archivo(agenda **,FILE*);
char salir();

main(){
   agenda *pAgendaO=NULL;
   char salida ='n';
   FILE *p;
   int opc,numContactos=1,i;
   if((p=fopen("contactosP.txt","r"))!=NULL){
      //Carga la información del archivo y la coloca en la RAM
      numContactos=leer_archivo(&pAgendaO,p);
      printf("\nNum: %d",numContactos);system("pause");
      fclose(p);
   }

   while(salida=='n'){
       menu();
       printf("\n\t Opcion: ");
       scanf("%d",&opc);
       switch(opc){
              case 1:
                   numContactos=agregar(&pAgendaO,numContactos);
                   break;
              case 2:
                   mostrar(&pAgendaO,numContactos);
                   break;
              case 3:
                     mostrar(&pAgendaO,numContactos);
                     modificar(&pAgendaO,numContactos);
                   break;

              case 4:
                   mostrar(&pAgendaO,numContactos);
                   if(numContactos>1)
                      numContactos=eliminar(&pAgendaO,numContactos);
                   break;
              case 5:
                   salida=salir();
                   break;
              default:
                   printf("\n Opcion invalida");
      }//cierra switch
      system("PAUSE");
     }//cierra while
     p=fopen("contactosP.txt","wb");//Abre para guardar toda la estructura generada en la RAM
     fwrite(&numContactos,sizeof(int),1,p); //Lo primero que guarda es el numero de bloques generados
     if(numContactos>1)
        //Guarda bloque por bloque
        for(i=0;i<numContactos-1;i++)
            fwrite(pAgendaO+i,sizeof(agenda),1,p);
     fclose(p);
}//cierra main

void menu(){
   system("cls");
   printf("\n\n MENU\n\n");
   printf("\n 1) Agregar contacto");
   printf("\n 2) Mostrar contactos");
   printf("\n 3) Modificar contacto");
   printf("et\n 4) Eliminar contacto");
   printf("\n 5) Salir");
}//cierra menu

int agregar(agenda **pAgenda,int n){
  *pAgenda=(agenda*)realloc(*pAgenda,sizeof(agenda)*n);
  printf("\npAgenda:%p",**pAgenda);
   printf("\n Contaco: #%d",n);
   printf("\n\t Nombre: ");
   scanf(" %[^\n]",(*pAgenda)[n-1].nombre);
   printf("\t Edad: ");
   scanf("%d",&(*pAgenda)[n-1].edad);
   n++;
   return(n);
}//cierra agregar

void mostrar(agenda **pAgenda, int n){
     int i;
     if(n==1){
        printf("No hay contactos\n\n");
     }
     for(i=0;i<n-1;i++){
        printf("\n Contaco: # %d",i+1);
        printf("\n\tNOMBRE : %s\n\tEDAD : %d\n",(*pAgenda)[i].nombre,(*pAgenda)[i].edad);
     }
}//cierra mostrar

void modificar(agenda **pAgenda,int n){
    int num;
     do{
       printf("Ingresa el numero de contacto que deseas modificar? ");
       scanf("%d",&num);
       } while(num<1 || num>n-1);
       printf("\n Contaco: #%d",num);
       printf("\n Nombre: ");
       scanf(" %[^\n]",(*pAgenda)[num-1].nombre);
       printf("\n Edad: ");
       scanf("%d",&(*pAgenda)[num-1].edad);
       printf("\n\n Datos actualizados OK");
}//cierra modificar

int eliminar(agenda **pAgenda,int n){
     int num,i;
     do{
        printf("Ingresa el numero de contacto que deseas eliminar? ");
        scanf("%d",&num);
     }while(num<1 || num>n-1);
     if(num!=n-1){
        for(i=num;i<n-1;i++){
            strcpy((*pAgenda)[i-1].nombre,(*pAgenda)[i].nombre);
            (*pAgenda)[i-1].edad=(*pAgenda)[i].edad;
        }
     }
     n--;
     printf("\n\n Contacto eliminado OK\n\n");
     return(n);
}//cierra eliminar

char salir(){
   printf("\n\n TERMINAMOS \n\n");
   return ('s');
}//cierra salir

int leer_archivo(agenda **pAgenda,FILE* p){
    int i,n=1;

     fread(&n,sizeof(int),1,p); //Primero lee el numero de bloques tiene guardado
     if(n>1){
        *pAgenda=(agenda*)realloc(*pAgenda,sizeof(agenda)*n-1); //Crea el espacio en la RAM
        for(i=0;i<n-1;i++){
           //Obtiene bloque por bloque del archivo y lo va colocando en la RAM
           fread(&((*pAgenda)[i]),sizeof(agenda),1, p);
       }
     }
   return(n);
}//cierra lee_archivo
