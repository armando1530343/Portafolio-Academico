#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
struct nuevosLibros{
    int id; char t[30],a[30],e[15];
};

int recibeLibros(nuevosLibros **,FILE *, FILE *, FILE *, int);
int leerLibros(nuevosLibros **, FILE *);
int misAlumnos();

int main(){
    FILE *lib, *Al, *bib, *myAl, *nL;
    nuevosLibros *libro=NULL;
    //struct nuevosLibros *libro;
    //struct tempLibro temp[30];
    //system("cls");
    int opc,numLibros=0;
    numLibros=leerLibros(&libro,nL);
    int salir=0;
    do{
        system("cls");
        //printf("\nn = %d",numLibros);system("pausa");
        printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n");
        printf("\n1.Recibir Libros\n2.Mis Alumnos\n3.Prestamo de libro\n4.Entrega de Libros\n5.Busqueda\n6.Salir del Sistema\n7.Recuperar ultima copia de seguridad\n\n");
        do{
            printf("Elige opcion: ");scanf("%d",&opc);
        }while(opc<1||opc>7);
        //system("cls");
        switch(opc){

            case 1:
                printf("numLibros: %d",numLibros);system("pause");
                numLibros=recibeLibros(&libro,lib,bib,nL,numLibros);  //system("pause");
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:salir=1;
                break;
            case 7://remove("Mi Biblioteca.txt");
                break;
        }
    }while(salir!=1);
}
int leerLibros(nuevosLibros **libro, FILE *nL){
    int n;
    nL=fopen("CantidadLibros.txt","r");
    while(!feof(nL)){
        fscanf(nL,"%d",&n);
    }
    printf("\nn = %d\n",n);system("pause");
    fclose(nL);
    return n;
}
//
int recibeLibros(nuevosLibros **libro, FILE *lib, FILE *bib, FILE *nL, int numLibros){

    system("cls");
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\nRECIBIR LIBROS\n");
    printf("\n1.Aleatorio desde la libreria\n2.Manual\n3.Eliminar todos los libros\n");
    int opc,id;
    char t[30],a[30],e[15];
    do{
        printf("\nElige opcion: ");scanf("%d",&opc);
    }while(opc<1||opc>3);
    struct tempLibro{
        int id; char t[30],a[30],e[15];
    }temp[30];
    bib=fopen("MiBiblioteca.txt","ab");
    nL=fopen("CantidadLibros.txt","w");
    int c, i=0, n;
    if(opc==1){
        lib=fopen("libreria.txt","r");
        do{
            printf("\nCuantos Libros: ");scanf("%d",&c);
        }while(c<1||c>30);
        while(!feof(lib)){
            fscanf(lib,"%d%s%s%s",&temp[i].id,&temp[i].t,&temp[i].a,&temp[i].e);
            i++;
            if(i==30){
                printf("\n\n");
                break;
            }
        }
        printf("\nLibros Agregados\n");
        for(i=0;i<c;i++){
            n=rand()%30;
            *libro=(nuevosLibros*)realloc(*libro,sizeof(nuevosLibros)*(numLibros+(i+1)));
            (*libro)[numLibros+i].id=temp[n].id;
            strcpy((*libro)[numLibros+i].t,temp[n].t);
            strcpy((*libro)[numLibros+i].a,temp[n].a);
            strcpy((*libro)[numLibros+i].e,temp[n].e);
            fwrite(&((*libro)[numLibros+i]),sizeof((*libro)[numLibros+i]),1,bib);
            printf("%d  %s  %s  %s\n",temp[n].id,temp[n].t,temp[n].a,temp[n].e);
        }
        fclose(lib);
        numLibros=numLibros+c;
        /*fclose(bib);
        bib=fopen("MiBiblioteca.txt","wb");
        fprintf(nL,"%d",0);
        numLibros=0;*/
    }
    else if(opc==2){
        *libro=(nuevosLibros*)realloc(*libro,sizeof(nuevosLibros)*(numLibros+1));
        do{
           printf("\nISBN (10 cifras enteras): ");scanf("%d",&id);//system("cls");
        }while(id/1000000000<1||id>9999999999);
        //(*libro+j)->id=isbn;
        printf("\nTitulo: ");scanf(" %[^\n]",&t);//system("pause");
        printf("\nAutor: ");scanf(" %[^\n]",&a);
        printf("\nEditorial: ");scanf(" %[^\n]",&e);
        (*libro)[numLibros].id=id;
        strcpy((*libro)[numLibros].t,t);
        strcpy((*libro)[numLibros].a,a);
        strcpy((*libro)[numLibros].e,e);
        printf("\n*libro = %p",*libro);
        fwrite(&((*libro)[numLibros]),sizeof((*libro)[numLibros]),1,bib);
        //libro[j].id=isbn;
        numLibros++;
    }
    else{
        fclose(bib);
        bib=fopen("MiBiblioteca.txt","wb");
        //fprintf(nL,"%d",0);
        numLibros=0;
    }

    fprintf(nL,"%d",numLibros);
    fclose(nL);

    fclose(bib);
    system("pause");
    return numLibros;
}
