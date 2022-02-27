#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct nuevosLibros{
    long int isbn;
    int id;
    char t[30],a[30],e[15];
};
struct nuevosAlumnos{
    char n1[12],n2[12],a1[12],a2[12],nc[50],carrera[12],modo;
    int mat;
};
void calendario();
int recibeLibros(struct nuevosLibros **, FILE *, int);
int leerLibros(struct nuevosLibros **, FILE *);
void mostrarLibros(struct nuevosLibros **, int);
int misAlumnos(struct nuevosAlumnos **, FILE *, int);
int leerAlumnos(struct nuevosAlumnos **, FILE *);

int main(){
    srand(time(NULL));
    FILE *nL;//abrira el archivo CantidadLibros
    FILE *nA;//abrira el archivo CantidadAlumnos
    struct nuevosLibros *libro=NULL;
    struct nuevosAlumnos *alumno=NULL;
    int opc,numLibros=0,numAlumnos=0;
    numLibros=leerLibros(&libro,nL);
    numAlumnos=leerAlumnos(&alumno,nA);
    int salir=0;
    do{
        system("cls");
        calendario();
        printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n");
        printf("\n1.Recibir Libros\n2.Mis Alumnos\n3.Prestamo de libro\n4.Entrega de Libros\n5.Busqueda\n6.Salir del Sistema\n7.Recuperar ultima copia de seguridad\n\n");
        do{
            printf("Elige opcion: ");scanf("%d",&opc);
        }while(opc<1||opc>7);
        //system("cls");
        switch(opc){

            case 1://RECIBIR LIBROS
                printf("\nCantidad de Libros: %d  ",numLibros);system("pause");
                numLibros=recibeLibros(&libro,nL,numLibros);mostrarLibros(&libro,numLibros);system("pause");
                break;
            case 2://MIS ALUMNOS
                printf("\nCantidad de Alumnos: %d  ",numAlumnos);system("pause");
                numAlumnos=misAlumnos(&alumno,nA,numAlumnos);verAlumnos(&alumno,numAlumnos);system("pause");
                break;
            case 3://PRESTAMOS DE LIBROS
                break;
            case 4://ENTREGA DE LIBROS
                break;
            case 5://BUSQUEDA
                break;
            case 6:system("cls");printf("\nSALIO DEL SISTEMA\n\n");salir=1;
                break;
            case 7:
                break;
        }
    }while(salir!=1);
    //free(libro);
    //free(alumno);
}
int leerLibros(struct nuevosLibros **libro, FILE *nL){
    int n;
    nL=fopen("CantidadLibros.txt","r");
    while(!feof(nL)){
        fscanf(nL,"%d",&n);
    }
    fclose(nL);
    return n;
}
int leerAlumnos(struct nuevosAlumnos **alumno, FILE *nA){
    int n;
    nA=fopen("CantidadAlumnos.txt","r");
    while(!feof(nA)){
        fscanf(nA,"%d",&n);
    }
    fclose(nA);
    return n;
}
void mostrarLibros(struct nuevosLibros **libro, int numLibros){
    system("cls");
    calendario();
    FILE *bib;
    int i,id,opc;
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n");
    printf("\n  Visualizar Biblioteca Actualizada\n\n  1.Si  2.No  Elige opcion: ");scanf("%d",&opc);
    if(opc==1){
        if(numLibros>0){
            bib=fopen("MiBiblioteca.txt","rb");
            for(i=0;i<numLibros;i++){
                fread(&((*libro)[i]),sizeof(struct nuevosLibros),1,bib);
                printf("\n  %d  %d  %s  %s  %s",(*libro)[i].id,(*libro)[i].isbn,(*libro)[i].t,(*libro)[i].a,(*libro)[i].e);//break;
            }
            fclose(bib);
        }
        else{
            printf("\n  Biblioteca Vacia\n");
        }
    }
    printf("\n\n");
}
void verAlumnos(struct nuevosAlumnos **alumno, int numAlumnos){
    system("cls");
    calendario();
    FILE *alum;
    int i,id,opc;
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n");
    printf("\n  Visualizar Alumnos Actuales\n\n  1.Si  2.No  Elige opcion: ");scanf("%d",&opc);
    if(opc==1){
        if(numAlumnos>0){
            alum=fopen("MisAlumnos.txt","rb");
            for(i=0;i<numAlumnos;i++){
                fread(&((*alumno)[i]),sizeof(struct nuevosAlumnos),1,alum);
                if((*alumno)[i].modo=='A'){
                    printf("\n  %d | %s %s %s %s | %s\n",(*alumno)[i].mat,(*alumno)[i].n1,(*alumno)[i].n2,(*alumno)[i].a1,(*alumno)[i].a2,(*alumno)[i].carrera);//break;
                }
                else{
                    printf("\n  %d | %s | %s\n",(*alumno)[i].mat,(*alumno)[i].nc,(*alumno)[i].carrera);//break;
                }
            }
            fclose(alum);
        }
        else{
            printf("\n  No hay Alumnos\n");
        }
    }
    printf("\n\n");
}
int recibeLibros(struct nuevosLibros **libro, FILE *nL, int numLibros){
    system("cls");
    calendario();
    FILE *lib;//abrira el archivo de libreria
    FILE *bib;//abrira el archivo MiBiblioteca
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n  RECIBIR LIBROS\n");
    printf("\n  1.Aleatorio desde la libreria\n  2.Manual\n  3.Eliminar todos los libros\n");
    int opc,id;
    char t[30],a[30],e[15];
    do{printf("\n  Elige opcion: ");scanf("%d",&opc);}while(opc<1||opc>4);
    struct tempLibro{
        int isbn; char t[30],a[30],e[15];
    }temp[30];
    int c, i=0, n;
    bib=fopen("MiBiblioteca.txt","ab");
    //nL=fopen("CantidadLibros.txt","w");
    //fprintf(nL,"%d",numLibros);fclose(nL);

    if(opc==1){
        i=0;
        lib=fopen("libreria.txt","r");
        do{printf("\n  Cuantos Libros: ");scanf("%d",&c);}while(c<1||c>5);
        while(!feof(lib)){
            fscanf(lib,"%d%s%s%s",&temp[i].isbn,&temp[i].t,&temp[i].a,&temp[i].e);
            i++;
            if(i==30){
                //printf("\n\n");
                break;
            }
        }
        printf("\n    Libros Agregados\n\n");
        for(i=0;i<c;i++){
            n=rand()%30;
            *libro=(struct nuevosLibros*)realloc(*libro,sizeof(struct nuevosLibros)*(numLibros+(i+1)));
            (*libro)[numLibros+i].isbn=temp[n].isbn;
            (*libro)[numLibros+i].id=numLibros+(i+1);
            strcpy((*libro)[numLibros+i].t,temp[n].t);
            strcpy((*libro)[numLibros+i].a,temp[n].a);
            strcpy((*libro)[numLibros+i].e,temp[n].e);
            fwrite(&((*libro)[numLibros+i]),sizeof((*libro)[numLibros+i]),1,bib);
            printf("    %d  %d  %s  %s  %s\n\n",numLibros+(i+1),temp[n].isbn,temp[n].t,temp[n].a,temp[n].e);
        }
        fclose(lib);
        numLibros=numLibros+c;
    }
    else if(opc==2){
        *libro=(struct nuevosLibros*)realloc(*libro,sizeof(struct nuevosLibros)*(numLibros+1));
        do{
           printf("\n  ISBN (10 cifras enteras): ");scanf("%d",&(*libro)[numLibros].isbn);//system("cls");
        }while((*libro)[numLibros].isbn<10000000);
        printf("\n  Titulo: ");scanf(" %[^\n]",&(*libro)[numLibros].t);//system("pause");
        printf("\n  Autor: ");scanf(" %[^\n]",&(*libro)[numLibros].a);
        printf("\n  Editorial: ");scanf(" %[^\n]",&(*libro)[numLibros].e);
        (*libro)[numLibros+i].id=numLibros+1;
        fwrite(&((*libro)[numLibros]),sizeof((*libro)[numLibros]),1,bib);
        numLibros++;
    }
    else{
        fclose(bib);
        bib=fopen("MiBiblioteca.txt","wb");
        //fprintf(nL,"%d",0);
        numLibros=0;
    }

    nL=fopen("CantidadLibros.txt","w");
    fprintf(nL,"%d",numLibros);
    fclose(nL);
    fclose(bib);
    system("pause");
    return numLibros;
}
int misAlumnos(struct nuevosAlumnos **alumno, FILE *nA, int numAlumnos){
    system("cls");
    calendario();
    FILE *alum;//abrira el archivo MisAlumnos
    FILE *nom;//abrira el archivo de nombres F ó M
    FILE *nM, *nF;
    FILE *apA;//abrira el archivo de apellidos
    FILE *carr;
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n  REGISTRAR ALUMNOS\n");
    printf("\n  1.Aleatoriamente\n  2.Manual\n  3.Eliminar Datos\n");
    int opc;
    do{printf("\n  Elige opcion: ");scanf("%d",&opc);}while(opc<1||opc>3);
    alum=fopen("MisAlumnos.txt","ab");
    char archivo[15];
    int c;
    int mat;
    char nomb[50];
    if(opc==1){
        do{printf("\n  Cuantos Alumnos: ");scanf("%d",&c);}while(c<1);
        apA=fopen("apellidos.txt","r");
        struct nombres{
            char na[12];
        }nombre[70],apellido[35],carrera[5];
        strcpy(carrera[0].na,"ITI");
        strcpy(carrera[1].na,"MECATRONICA");
        strcpy(carrera[2].na,"MANUFACTURA");
        strcpy(carrera[3].na,"ISA");
        strcpy(carrera[4].na,"PYMES");
        int i=0;
        nF=fopen("nombresFF.txt","r");
        nM=fopen("nombresMM.txt","r");
        while(!feof(nF)){fscanf(nF,"%s",nombre[i].na); i++; if(i==35){break;}}
        while(!feof(nM)){fscanf(nM,"%s",nombre[i].na); i++; if(i==70){break;}}
        fclose(nF); fclose(nM);
        i=0;
        while(!feof(apA)){fscanf(apA,"%s",apellido[i].na); i++; if(i==35){break;}}
        printf("\n  Nuevos Alumnos\n\n");
        int a,b,x;
        for(i=0;i<c;i++){
            b=rand()%2;
            if(b==0){a=0;}
            if(b==1){a=35;}
            nom=fopen(archivo,"r");
            *alumno=(struct nuevosAlumnos*)realloc(*alumno,sizeof(struct nuevosAlumnos)*(numAlumnos+(i+1)));
            x=rand()%35+a; strcpy((*alumno)[numAlumnos+i].n1,nombre[x].na);
            x=rand()%35+a; strcpy((*alumno)[numAlumnos+i].n2,nombre[x].na);
            x=rand()%35; strcpy((*alumno)[numAlumnos+i].a1,apellido[x].na);
            x=rand()%35; strcpy((*alumno)[numAlumnos+i].a2,apellido[x].na);
            x=rand()%5; strcpy((*alumno)[numAlumnos+i].carrera,carrera[x].na);
            //x=rand()%9999+1530001;
            x=1530101+(numAlumnos+i);(*alumno)[numAlumnos+i].mat = x;
            (*alumno)[numAlumnos+i].modo='A';
            fwrite(&((*alumno)[numAlumnos+i]),sizeof((*alumno)[numAlumnos+i]),1,alum);
            fclose(nom);
            printf("    Modo: %c  Nombre: %s %s %s %s\n    Matricula: %d  Carrera: %s\n\n",(*alumno)[numAlumnos+i].modo,(*alumno)[numAlumnos+i].n1,(*alumno)[numAlumnos+i].n2,(*alumno)[numAlumnos+i].a1,(*alumno)[numAlumnos+i].a2,x,(*alumno)[numAlumnos+i].carrera);
        }
        numAlumnos=numAlumnos+c;
        fclose(apA);
    }
    else if(opc==2){
        *alumno=(struct nuevosAlumnos*)realloc(*alumno,sizeof(struct nuevosAlumnos)*(numAlumnos+1));
        (*alumno)[numAlumnos].modo='M';
        printf("\n  Modo: %c",(*alumno)[numAlumnos].modo);
        printf("\n  Nombre del Alumno: ");scanf(" %[^\n]",&(*alumno)[numAlumnos].nc);
        printf("\n  Matricula: ");scanf("%d",&(*alumno)[numAlumnos].mat);
        printf("\n  Carrera: ");scanf(" %[^\n]",&(*alumno)[numAlumnos].carrera);
        fwrite(&((*alumno)[numAlumnos]),sizeof((*alumno)[numAlumnos]),1,alum);
        numAlumnos++;
    }
    else{
        fclose(alum);
        alum=fopen("MisAlumnos.txt","wb");
        numAlumnos=0;
    }
    nA=fopen("CantidadAlumnos.txt","w");
    fprintf(nA,"%d",numAlumnos);
    fclose(nA); fclose(alum);
    system("pause");
    return numAlumnos;
}
void calendario(){
    time_t tiempo;
    struct tm *t;
    tiempo = time(NULL);
    t=localtime(&tiempo);
    int dia = t->tm_mday;
    int mes = t->tm_mon+1;
    int year = t->tm_year+1900;
    struct a2016{
        int dia,mes,anio;
        char day[10],month[10];
    }fecha[366];
    struct dias{
        char dia[10];
    }d[7];
    strcpy(d[0].dia,"LUNES");
    strcpy(d[1].dia,"MARTES");
    strcpy(d[2].dia,"MIERCOLES");
    strcpy(d[3].dia,"JUEVES");
    strcpy(d[4].dia,"VIERNES");
    strcpy(d[5].dia,"SABADO");
    strcpy(d[6].dia,"DOMINGO");
    int finMes;
    int i=0,j=i,k=1,n;
    for(n=213;n<366;n++){
        if(j>=7){j=0;}
        if(k>finMes){k=1;}
        strcpy(fecha[i].day,d[j].dia);
        if(n<244){fecha[i].mes = 8;strcpy(fecha[i].month,"AGOSTO");finMes=31;fecha[i].dia = k;}
        if(n>=244){fecha[i].mes = 9;strcpy(fecha[i].month,"SEPTIEMBRE");finMes=30;fecha[i].dia = k;}
        if(n>=274){fecha[i].mes = 10;strcpy(fecha[i].month,"OCTUBRE");finMes=31;fecha[i].dia = k;}
        if(n>=305){fecha[i].mes = 11;strcpy(fecha[i].month,"NOVIEMBRE");finMes=30;fecha[i].dia = k;}
        if(n>=335){fecha[i].mes = 12;strcpy(fecha[i].month,"DICIEMBRE");finMes=31;fecha[i].dia = k;}
        //printf("\ndia:%d  mes:%s  %s",fecha[i].dia,fecha[i].month,fecha[i].day);
        i++; j++; k++;
    }
    for(i=0;i<153;i++){
        if(dia==fecha[i].dia&&mes==fecha[i].mes){
            printf("\nFECHA: %s %d DE %s DEL %d",fecha[i].day,fecha[i].dia,fecha[i].month,2016);
            break;
        }
    }
    printf("\n\n");
}
