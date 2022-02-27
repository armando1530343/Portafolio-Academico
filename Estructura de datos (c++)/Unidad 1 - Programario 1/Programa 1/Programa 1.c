#include <stdio.h>

int main(){

    int i;
    char nombre[30];
    printf("Ingresa tu nombre: "); scanf(" %[^\n]",nombre);
    //printf("Ingresa tu nombre: ");
    int largo = strlen(nombre)+6;
    int cant = (largo*2)+4;


    for (i=1;i<=cant;i++){
        printf("*");
        if(i==largo){printf("\n");}
        if(i==largo+2){printf(" %s ",nombre);}
        if(i==largo+4){printf("\n");}
    }
}
