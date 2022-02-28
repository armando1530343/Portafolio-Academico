#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct nuevosLibros{
    int id; char t[30],a[30],e[15];
}*libro;

void recibeLibros(FILE *lib, FILE *bib, int numLibros);
int leerLibros(FILE *bib);

int main(){
    FILE *lib, *Al, *bib, *myAl;
    //struct nuevosLibros *libro;
    //struct tempLibro temp[30];
    //system("cls");
    int salir=0;
    do{
        system("cls");
        int opc,numLibros;
        printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n");
        printf("\n1.Recibir Libros\n2.Mis Alumnos\n3.Prestamo de libro\n4.Entrega de Libros\n5.Busqueda\n6.Salir del Sistema\n7.Recuperar ultima copia de seguridad\n\n");
        do{
            printf("Elige opcion: ");scanf("%d",&opc);
        }while(opc<1||opc>7);
        //system("cls");
        switch(opc){

            case 1: numLibros=leerLibros(bib);
                printf("numLibros: %d",numLibros);system("pause");
                recibeLibros(lib,bib,numLibros);  //system("pause");
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
            case 7:remove("Mi Biblioteca.txt");
                break;
        }
    }while(salir!=1);
}
int leerLibros(FILE *bib){
    bib=fopen("MiBiblioteca.txt","rb");
    if(bib==NULL){
        bib=fopen("MiBiblioteca.txt","wb");
        fclose(bib);
        bib=fopen("MiBiblioteca.txt","rb");
    }
    int j=0;
    if((fread(&libro,sizeof(struct nuevosLibros),1,bib))!=NULL){
        while(!feof(bib)){
            fread(&libro,sizeof(struct nuevosLibros),1,bib);
            j++;
        }
    }
    fclose(bib);
    return j;
}

void recibeLibros(FILE *lib, FILE *bib, int numLibros){
    system("cls");
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n");
    printf("\n1.Aleatorio desde la libreria\n2.Manual\n");
    int opc,id;
    char t[30],a[30],e[15];
    do{
        printf("\nElige opcion: ");scanf("%d",&opc);
    }while(opc<1||opc>2);

    lib=fopen("libreria.txt","r");
    /*bib=fopen("MiBiblioteca.txt","rb");
    if(bib==NULL){
        bib=fopen("MiBiblioteca.txt","wb");
        fclose(bib);
        bib=fopen("MiBiblioteca.txt","rb");
    }
    int j=0;
    if((fread(&libro,sizeof(struct nuevosLibros),1,bib))!=NULL){
        while(!feof(bib)){
            fread(&libro,sizeof(struct nuevosLibros),1,bib);
            j++;
        }
        //j--;
    }
    fclose(bib);
    printf("\nj: %d",j);
   // printf("\nLibros: %d",j);*/
   int j=numLibros;
    struct tempLibro{
        int id; char t[30],a[30],e[15];
    }temp[30];
    bib=fopen("MiBiblioteca.txt","ab");
    if(opc==1){
        fclose(bib);
        bib=fopen("MiBiblioteca.txt","wb");
    }
    else{
        libro=(struct nuevosLibros*)realloc(libro,sizeof(struct nuevosLibros)*(j+1));
        do{
           printf("\nISBN (10 cifras enteras): ");scanf("%d",&id);//system("cls");
        }while(id/1000000000<1||id>9999999999);
        //(*libro+j)->id=isbn;
        printf("\nTitulo: ");scanf(" %[^\n]",libro[j].t);system("pause");
        printf("\nAutor: ");scanf(" %[^\n]",libro[j].a);
        printf("\nEditorial: ");scanf(" %[^\n]",libro[j].e);
        libro[j].id=id;
        /*strcpy(libro[j].t,t);
        strcpy(libro[j].a,a);
        strcpy(libro[j].e,e);*/
        fwrite(&libro[j],sizeof(libro[j]),1,bib);
        //libro[j].id=isbn;
    }
    fclose(bib);
    system("pause");
}
