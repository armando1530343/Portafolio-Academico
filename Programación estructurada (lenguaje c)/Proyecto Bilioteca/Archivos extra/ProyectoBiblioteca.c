#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void recibeLibros(FILE *lib, FILE *bib);
int main(){
    FILE *lib, *Al, *bib, *myAl;
    //system("cls");
    int salir=0;
    do{
        system("cls");
        int opc;
        printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n");
        printf("\n1.Recibir Libros\n2.Mis Alumnos\n3.Prestamo de libro\n4.Entrega de Libros\n5.Busqueda\n6.Salir del Sistema\n7.Recuperar ultima copia de seguridad\n\n");
        do{
            printf("Elige opcion: ");scanf("%d",&opc);
        }while(opc<1||opc>7);
        //system("cls");
        switch(opc){
            case 1:recibeLibros(lib,bib);  //system("pause");
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
struct Libros{
    int id;
    char t[30],autor[30],e[15];
}*book;

/*int menu(){
    system("cls");
    int opc;
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n");
    printf("\n1.Recibir Libros\n2.Mis Alumnos\n3.Prestamo de libro\n4.Entrega de Libros\n5.Busqueda\n6.Salir del Sistema\n7.Recuperar ultima copia de seguridad\n\n");
    do{
        printf("Elige opcion: ");scanf("%d",&opc);
    }while(opc<1||opc>7);
    system("cls");
    return opc;
}*/
struct TempLibros{
    int id;
    char t[30],a[30],e[15];
}*libro;
void recibeLibros(FILE *lib, FILE *bib){
    system("cls");
    srand(time(NULL));
    int opc,c;
    //remove("Mi Biblioteca.txt");
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\nRECIBIR LIBROS\n");
    printf("\n1.Forma Aleatoria desde la Libreria\n2.Forma Manual\n");

    do{
        printf("\nElige opcion: ");scanf("%d",&opc);
    }while(opc<1||opc>2);
    printf("\nCuantos quieres: ");scanf("%d",&c);
    int i,j,n;
    j=0;
    bib=fopen("MiBiblioteca.txt","rb");
    if((fread(&book,sizeof(struct Libros),1,bib))==NULL){
        j=0;
    }
    else{
        while(!feof(bib)){
            fread(&book,sizeof(struct Libros),1,bib);
            j++;
        }
        j--;
    }
    fclose(bib);
    bib=fopen("MiBiblioteca.txt","ab");
    int ej;
    FILE*numEj=fopen("NumeroEjecucion.txt","a");
    fscanf(numEj,"%d",ej);
    printf("Numero de ejecucion: %d",ej);system("pause");
    /*if(j>0){
        j--;
    }*/
    //fclose(bib);
    //bib=fopen("Mi Biblioteca.txt","ab");
    /*struct Libros{
        int id;
        char t[30],a[30],e[15];
    }libro[30];*/
    if(opc==1){
        printf("\nLibros=%d",j);//system("pause");
        libro=(struct TempLibros*)realloc(libro,(sizeof(struct TempLibros)*30)*(ej+1));
        /*do{
            printf("\nCuantos quieres: ");scanf("%d",&c);
        }while(c<1||c>30);*/
        lib=fopen("libreria.txt","r");
        i=0;
        while(!feof(lib)){
            fscanf(lib,"%d%s%s%s",&libro[i].id,&libro[i].t,&libro[i].a,&libro[i].e);
            //printf("\n%d %s %s %s",libro[i].id,libro[i].t,libro[i].a,libro[i].e);
            i++;
            if(i==30){
                printf("\n\n");
                break;
            }
        }
        system("cls");
        for(i=0;i<c;i++){
            n=rand()%30;
            book=(struct Libros *)realloc(book,sizeof(struct Libros)*(j+(i+1)));
            book[j+i].id=libro[n].id;
            strcpy(book[j+i].t,libro[n].t);
            strcpy(book[j+i].autor,libro[n].a);
            strcpy(book[j+i].e,libro[n].e);

            //fprintf(bib,"%d %s %s %s",book[i].id,book[i].t,book[i].autor,book[i].e);
            fwrite(&book[j+i],sizeof(book[j+i]),1,bib);
        }
        //numEj=fopen("NumEjecucion.txt","wb");
        //fprintf(numEj,"%d",ej);
        //fclose(numEj);

        fclose(lib);
        system("pause");
    }
    else{
        fclose(bib);
        bib=fopen("MiBiblioteca.txt","wb");
    }
    //free(libro);
    fclose(bib);

}
