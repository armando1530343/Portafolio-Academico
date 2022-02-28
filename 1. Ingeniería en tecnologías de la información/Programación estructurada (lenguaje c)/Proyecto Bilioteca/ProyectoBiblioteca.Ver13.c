#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct nuevosLibros{
    long int isbn;
    int id, rep, disp;
    char t[30],a[30],e[20];
};
struct nuevosAlumnos{
    char n1[12],n2[12],a1[12],a2[12],nc[50],carrera[12],modo;
    int mat, libros;
};
struct prestamos{
    long int isbn; int id, mat, dia, diaE, mes, mesE, fp, fe, retraso, tiempo, multa, entregado;
    char t[30],a[30],e[20],n1[12],n2[12],a1[12],a2[12],nombre[50],carrera[12],day[10],dayE[10],month[10],monthE[10],modo;
};
struct a2016{
    int dia,mes,anio;
    char day[10],month[10];
}fecha[366];
int calendario(int,int);
int recibeLibros(struct nuevosLibros **, FILE *, int);
int leerLibros(FILE *);
void mostrarLibros(struct nuevosLibros **, int);
int misAlumnos(struct nuevosAlumnos **, FILE *, int);
int leerAlumnos(FILE *);
//void prestamosLibros(struct nuevosLibros **, int);
int prestamoLibros(struct prestamos **, struct nuevosLibros **,  struct nuevosAlumnos **, int, int, int, int, FILE *);

int main(){
    srand(time(NULL));
    time_t tiempo;
    struct tm *t;
    tiempo = time(NULL);
    t=localtime(&tiempo);
    int dia = t->tm_mday;
    int mes = t->tm_mon+1;
    int year = t->tm_year+1900;
    FILE *nL;//abrira el archivo CantidadLibros
    FILE *nA;//abrira el archivo CantidadAlumnos
    FILE *nP;//abrira el archivo CantidadPrestamos
    //FILE *nR;
    struct nuevosLibros *libro=NULL;
    struct librosRep *repetido=NULL;
    struct nuevosAlumnos *alumno=NULL;
    struct prestamos *presta=NULL;
    int f;
    int opc,numLibros=0,numAlumnos=0,numPrestamos=0;//,numRep=0;
    numLibros=leerLibros(nL);
    numAlumnos=leerAlumnos(nA);
    numPrestamos=leerPrestamos(nP);
    //numRep=leerRepetidos(nR);
    int salir=0;
    do{
        system("cls");
        f=calendario(dia,mes);
        //printf("\n f: %d",f);
        printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n");
        printf("\n1.Recibir Libros\n2.Mis Alumnos\n3.Prestamo de libro\n4.Entrega de Libros\n5.Busqueda\n6.Salir del Sistema\n7.Recuperar ultima copia de seguridad\n8.Eliminar datos para pruebas\n\n");
        do{
            printf("Elige opcion: ");scanf("%d",&opc);
        }while(opc<1||opc>7);
        //system("cls");
        switch(opc){

            case 1://RECIBIR LIBROS
                printf("\nCantidad de Libros: %d  ",numLibros);system("pause");
                calendario(dia,mes);numLibros=recibeLibros(&libro,nL,numLibros);
                //calendario(dia,mes);librosRepetidos(&libro,numLibros);
                //calendario(dia,mes);mostrarLibros(&libro,numLibros);
               system("pause");
                break;
            case 2://MIS ALUMNOS
                printf("\nCantidad de Alumnos: %d  ",numAlumnos);system("pause");
                calendario(dia,mes);numAlumnos=misAlumnos(&alumno,nA,numAlumnos);
                //calendario(dia,mes);verAlumnos(&alumno,numAlumnos);system("pause");
                break;
            case 3://PRESTAMOS DE LIBROS
                printf("\nCantidad de Prestamos: %d  ",numPrestamos);system("pause");
                //prestamosLibros(&libro,numLibros);
                calendario(dia,mes);numPrestamos=prestamoLibros(&presta,&libro,&alumno,numPrestamos,numLibros,numAlumnos,f,nP);system("pause");
                break;
            case 4://ENTREGA DE LIBROS
                calendario(dia,mes);entregaLibros(&presta,&alumno,numPrestamos,numAlumnos,f);system("pause");
                break;
            case 5://BUSQUEDA
                calendario(dia,mes);busqueda(&libro,&alumno,numLibros,numAlumnos);system("pause");
                break;
            case 6:system("cls");printf("\nSALIO DEL SISTEMA\n\n");salir=1;
                break;
            case 7:
                system("copy PrestamosLibros.txt PrestamosRecuperado.txt");
                break;
            case 8:
                break;
        }
    }while(salir!=1);
    //free(libro);
    //free(alumno);
}
int leerLibros(FILE *nL){
    int n;
    nL=fopen("CantidadLibros.txt","r");
    while(!feof(nL)){
        fscanf(nL,"%d",&n);
    }
    fclose(nL);
    return n;
}
int leerAlumnos(FILE *nA){
    int n;
    nA=fopen("CantidadAlumnos.txt","r");
    while(!feof(nA)){
        fscanf(nA,"%d",&n);
    }
    fclose(nA);
    return n;
}
int leerPrestamos(FILE *nP){
    int n;
    nP=fopen("CantidadPrestamos.txt","r");
    while(!feof(nP)){
        fscanf(nP,"%d",&n);
    }
    fclose(nP);
    return n;
}
/*int leerRepetidos(FILE *nR){
    int n;
    nR=fopen("CantidadRepetidos.txt","r");
    while(!feof(nR)){
        fscanf(nR,"%d",&n);
    }
    fclose(nR);
    return n;
}*/
void mostrarLibros(struct nuevosLibros **libro, int numLibros){
    //system("cls");
    FILE *bib;
    //FILE *bib_tx=fopen("MiBiblioteca_tx.txt","wb");
    int i,id,opc;
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n");
    printf("\n  Visualizar Biblioteca Actualizada\n\n  1.Si  2.No  Elige opcion: ");scanf("%d",&opc);
    if(opc==1){
        if(numLibros>0){
            bib=fopen("MiBiblioteca.txt","rb");
            for(i=0;i<numLibros;i++){
                fread(&((*libro)[i]),sizeof(struct nuevosLibros),1,bib);
                printf("\n  %d %d %s %s %s",(*libro)[i].id,(*libro)[i].isbn,(*libro)[i].t,(*libro)[i].a,(*libro)[i].e);//break;
            }
            fclose(bib);
        }
        else{
            printf("\n  Biblioteca Vacia\n");
        }
    }
    /*if(numLibros>0){
        for(i=0;i<numLibros;i++){
            fprintf(bib_tx, "%d %d %s %s %s  ",(*libro)[i].id,(*libro)[i].isbn,(*libro)[i].t,(*libro)[i].a,(*libro)[i].e);
        }
    }
    else{
        fclose(bib_tx);
        fopen("MiBiblioteca_tx.txt","wb");
    }
    fclose(bib_tx);*/
    printf("\n\n");
}
void verAlumnos(struct nuevosAlumnos **alumno, int numAlumnos){
    //system("cls");
    FILE *alum;
    //FILE *alum_tx=fopen("MisAlumnos_tx.txt","wb");
    int i,id,opc;
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n");
    printf("\n  Visualizar Alumnos Actuales\n\n  1.Si  2.No  Elige opcion: ");scanf("%d",&opc);
    if(opc==1){
        if(numAlumnos>0){
            alum=fopen("MisAlumnos.txt","rb");
            for(i=0;i<numAlumnos;i++){
                fread(&((*alumno)[i]),sizeof(struct nuevosAlumnos),1,alum);
                if((*alumno)[i].modo=='A'){
                    printf("\n  %d | %s %s %s %s | %s  Libros: %d\n",(*alumno)[i].mat,(*alumno)[i].n1,(*alumno)[i].n2,(*alumno)[i].a1,(*alumno)[i].a2,(*alumno)[i].carrera,(*alumno)[i].libros);//break;
                }
                else{
                    printf("\n  %d | %s | %s  Libros: %d\n",(*alumno)[i].mat,(*alumno)[i].nc,(*alumno)[i].carrera,(*alumno)[i].libros);//break;
                }
            }
            fclose(alum);
        }
        else{
            printf("\n  No hay Alumnos\n");
        }
    }
    /*if(numAlumnos>0){
        if((*alumno)[i].modo=='A'){
            fprintf(alum_tx,"%d %s %s %s %s %s  \n",(*alumno)[i].mat,(*alumno)[i].n1,(*alumno)[i].n2,(*alumno)[i].a1,(*alumno)[i].a2,(*alumno)[i].carrera);//break;
        }
        else{
            fprintf(alum_tx,"%d %s %s  \n",(*alumno)[i].mat,(*alumno)[i].nc,(*alumno)[i].carrera);//break;
        }
    }
    else{
        fclose(bib_tx);
        fopen("MisAlumnos_tx.txt","wb");
    }
    fclose(alum_tx);*/
    printf("\n\n");
}
void librosRepetidos(struct nuevosLibros **libro, int numLibros){
    //system("cls");
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n");
    printf("\n  LIBROS REPETIDOS \n");
    FILE *bib=fopen("MiBiblioteca.txt","rb");
    FILE *libRep=fopen("LibrosRepetidos.txt","wb");
    FILE *disp=fopen("librosDisponibles","wb");
    int rep=1, i, j, isbn;
    struct librosRep{
        long int isbn;
        int rep;
    }repetido[numLibros];
    for(i=0;i<numLibros;i++){
        fread(&((*libro)[i]),sizeof(struct nuevosLibros),1,bib);
    }
    fclose(bib);
    bib=fopen("MiBiblioteca.txt","wb");
    for(i=0;i<numLibros;i++){
        repetido[i].isbn=(*libro)[i].isbn;
        for(j=0;j<numLibros;j++){
            if((*libro)[i].isbn==(*libro)[j].isbn){rep++;}
            if(j==i){rep--;}
        }
        //(*libro)[i].cant=rep;
        //fwrite(&((*libro)[i].cant),sizeof((*libro)[i].cant),1,bib);
        repetido[i].rep=rep;
        fprintf(libRep,"%d ",repetido[i].rep);
        //if(numPrestamos==0){
            (*libro)[i].rep=rep;
            fwrite(&((*libro)[i]),sizeof((*libro)[i]),1,bib);
        //}

        fprintf(libRep,"%d ",repetido[i].isbn,rep);
        printf("\n  ISBN:%d  Libros:%d",repetido[i].isbn,rep);
        rep=1;
    }
    printf("\n\n");
    fclose(bib);
    fclose(libRep);
    system("pause");
}
int recibeLibros(struct nuevosLibros **libro, FILE *nL, int numLibros){
    //system("cls");
    FILE *lib;//abrira el archivo de libreria
    FILE *bib;//abrira el archivo MiBiblioteca
    FILE *libRep;
    FILE *repe;
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n  RECIBIR LIBROS\n");
    printf("\n  1.Aleatorio desde la libreria\n  2.Manual\n  3.Eliminar todos los libros\n");
    int opc,id;
    char t[30],a[30],e[15];
    do{printf("\n  Elige opcion: ");scanf("%d",&opc);}while(opc<1||opc>3);
    struct tempLibro{
        int isbn; char t[30],a[30],e[20];
    }temp[30];
    int c, i=0, j, k, n;
    bib=fopen("MiBiblioteca.txt","ab");
    //nL=fopen("CantidadLibros.txt","w");
    //fprintf(nL,"%d",numLibros);fclose(nL);

    if(opc==1){
        i=0;
        lib=fopen("libreria.txt","r");
        do{printf("\n  Cuantos Libros: ");scanf("%d",&c);}while(c<1||c>30);
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
            /*k=1;
            for(j=0;j<numLibros+i;j++){
                    if((*libro)[j].isbn==(*libro)[numLibros+i].isbn){
                        k++;
                        //fwrite(&((*libro)[j].cant),sizeof((*libro)[j].cant),1,bib);
                        if(j==i){k--;}
                    }

                    (*libro)[j].rep=k;
            }*/
            //(*libro)[numLibros+i].cant=k;
            strcpy((*libro)[numLibros+i].t,temp[n].t);
            strcpy((*libro)[numLibros+i].a,temp[n].a);
            strcpy((*libro)[numLibros+i].e,temp[n].e);
            fwrite(&((*libro)[numLibros+i]),sizeof((*libro)[numLibros+i]),1,bib);
            printf("    %d  %d  %s  %s  %s\n\n",numLibros+(i+1),temp[n].isbn,temp[n].t,temp[n].a,temp[n].e);
        }
        /*for(i=0;i<numLibros+c;i++){
            k=1;
            for(j=0;j<numLibros+c;j++){
                //if(j!=i){
                    if((*libro)[i].isbn==(*libro)[j].isbn){
                        k++;
                    }
                    if(j==i){k--;}
                //}
            }
            (*libro)[i].rep=k;
            //fwrite(&((*libro)[i].rep),sizeof((*libro)[i].rep),1,bib);
        }
        for(i=0;i<c;i++){
            fwrite(&((*libro)[numLibros+i]),sizeof((*libro)[numLibros+i]),1,bib);
            printf("    %d  %d  %s  %s  %s  %d\n\n",numLibros+(i+1),(*libro)[numLibros+i].isbn,(*libro)[numLibros+i].t,(*libro)[numLibros+i].a,(*libro)[numLibros+i].e,(*libro)[numLibros+i].rep);
        }*/

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
        /*for(i=0;i<numLibros;i++){
            k=1;
            for(j=0;j<numLibros+c;j++){
                //if(j!=i){
                    if((*libro)[i].isbn==(*libro)[j].isbn){
                        k++;
                    }
                    if(j==i){k--;}
                //}
            }
            (*libro)[i].rep=k;
            //fwrite(&((*libro)[i].rep),sizeof((*libro)[i].rep),1,bib);
        }
        for(i=0;i<c;i++){
            fwrite(&((*libro)[numLibros+i]),sizeof((*libro)[numLibros+i]),1,bib);
            printf("    %d  %d  %s  %s  %s  %d\n\n",numLibros+(i+1),(*libro)[numLibros+i].isbn,(*libro)[numLibros+i].t,(*libro)[numLibros+i].a,(*libro)[numLibros+i].e,(*libro)[numLibros+i].rep);
        }*/
    }
    else if(opc==3){
        fclose(bib);
        bib=fopen("MiBiblioteca.txt","wb");
        libRep=fopen("LibrosRepetidos.txt","wb");
        fclose(libRep);
        numLibros=0;
    }
    /*fclose(bib);
    bib=fopen("MiBiblioteca.txt","wb");
    if(opc==1||opc==2){
    for(i=0;i<numLibros;i++){
            k=1;
            for(j=0;j<numLibros+c;j++){
                //if(j!=i){
                    if((*libro)[i].isbn==(*libro)[j].isbn){
                        k++;
                    }
                    if(j==i){k--;}
                //}
            }
            (*libro)[i].rep=k;
            fwrite(&((*libro)[i].rep),sizeof((*libro)[i].rep),1,bib);
    }
    for(i=0;i<c;i++){
        //fwrite(&((*libro)[numLibros+i].rep),sizeof((*libro)[numLibros+i].rep),1,bib);
        printf("    %d  %d  %s  %s  %s  %d\n\n",numLibros+(i+1),(*libro)[numLibros+i].isbn,(*libro)[numLibros+i].t,(*libro)[numLibros+i].a,(*libro)[numLibros+i].e,(*libro)[numLibros+i].rep);
    }
    }*/
    nL=fopen("CantidadLibros.txt","w");
    fprintf(nL,"%d",numLibros);
    fclose(nL);
    fclose(bib);
    system("pause");
    return numLibros;
}
int misAlumnos(struct nuevosAlumnos **alumno, FILE *nA, int numAlumnos){
    //system("cls");
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
            (*alumno)[numAlumnos+i].libros=0;
            (*alumno)[numAlumnos+i].modo='A';
            fwrite(&((*alumno)[numAlumnos+i]),sizeof((*alumno)[numAlumnos+i]),1,alum);
            fclose(nom);
            printf("    Modo: %c  Nombre: %s %s %s %s\n    Matricula: %d  Carrera: %s  ",(*alumno)[numAlumnos+i].modo,(*alumno)[numAlumnos+i].n1,(*alumno)[numAlumnos+i].n2,(*alumno)[numAlumnos+i].a1,(*alumno)[numAlumnos+i].a2,x,(*alumno)[numAlumnos+i].carrera);
            printf("Libros: %d\n\n",(*alumno)[numAlumnos+i].libros);
        }
        numAlumnos=numAlumnos+c;
        fclose(apA);
    }
    else if(opc==2){
        *alumno=(struct nuevosAlumnos*)realloc(*alumno,sizeof(struct nuevosAlumnos)*(numAlumnos+1));
        (*alumno)[numAlumnos].modo='M';
        (*alumno)[numAlumnos].libros=0;
        printf("\n  Modo: %c",(*alumno)[numAlumnos].modo);
        printf("\n  Nombre del Alumno: ");scanf(" %[^\n]",&(*alumno)[numAlumnos].nc);
        printf("\n  Matricula: ");scanf("%d",&(*alumno)[numAlumnos].mat);
        printf("\n  Carrera: ");scanf(" %[^\n]",&(*alumno)[numAlumnos].carrera);
        printf("\n  Libros: %d",(*alumno)[numAlumnos].libros);
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
int prestamoLibros(struct prestamos **presta, struct nuevosLibros **libro, struct nuevosAlumnos **alumno,
                             int numPrestamos, int numLibros, int numAlumnos, int f, FILE *nP){
    //system("cls");
    //FILE *bib;
    printf("\n  Num Libros = %d",numLibros);//system("pause");
    FILE *pre=fopen("PrestamosLibros.txt","ab");
    FILE *bib=fopen("MiBiblioteca.txt","rb");
    FILE *alum=fopen("MisAlumnos.txt","rb");
    FILE *libRep=fopen("LibrosRepetidos.txt","r");
    FILE *disp;
    int opc, c;
    int i, j, n, x, y;
    //bib=fopen("MiBiblioteca.txt","rb");

    for(i=0;i<numLibros;i++){
            *libro=(struct nuevosLibros*)realloc(*libro,sizeof(struct nuevosLibros)*(i+1));
            fread(&((*libro)[i]),sizeof(struct nuevosLibros),1,bib);
            //printf("\n  antes de for libro: %p   &((*libro)[i])= %d",*libro,(*libro)[i].isbn);system("pause");
    }

    for(i=0;i<numAlumnos;i++){
            *alumno=(struct nuevosAlumnos*)realloc(*alumno,sizeof(struct nuevosAlumnos)*(i+1));
            fread(&((*alumno)[i]),sizeof(struct nuevosAlumnos),1,alum);
    }
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n  PRESTAR LIBROS\n");
    printf("\n  TIEMPO LIMITE DE ENTREGA = 3 DIAS\n  $10 PESOS DE MULTA POR CADA DIA DE RETRASO\n  DIAS INHABILES = SABADO Y DOMINGO\n");
    printf("\n  1.Aleatoria\n  2.Manual\n  3.Eliminar Datos\n");
    do{
        printf("\n  Elige opcion: ");scanf("%d",&opc);
    }while(opc<1||opc>3);
    //fread(&x,sizeof(int),1,bib);
    //fread(&y,sizeof(int),1,alum);
    if(numLibros==0||numAlumnos==0){
        if(numLibros==0){printf("\n  No hay libros en la Biblioteca\n\n");}
        if(numAlumnos==0){printf("\n  No hay Alumnos Registrados\n\n");}
        fclose(pre);
        pre=fopen("PrestamosLibros.txt","wb");
        numPrestamos=0;
        for(i=0;i<numAlumnos;i++){
            (*alumno)[i].libros=0;
        }
    }
    else{
        int aux;
        int compara,compara2, entrega, libros;
        fclose(alum);
        alum=fopen("MisAlumnos.txt","wb");
        if (opc==1){
                int retraso=0,multa=0,rep=1,y=0;
                libros=0;
            do{printf("\n  Cuantos prestamos quieres generar: ");scanf("%d",&c);}while(c<1);
            i=0;
            for(i=0;i<c;i++){
                //printf("\n  antees de realloc");
                *presta=(struct prestamos*)realloc(*presta,sizeof(struct prestamos)*(numPrestamos+(i+1)));
                n=rand()%numLibros;
                //fread(&((*libro)[n]),sizeof(struct nuevosLibros),1,bib);
                (*presta)[numPrestamos+i].id=(*libro)[n].id;
                (*presta)[numPrestamos+i].isbn=(*libro)[n].isbn;
                strcpy((*presta)[numPrestamos+i].t,(*libro)[n].t);
                strcpy((*presta)[numPrestamos+i].a,(*libro)[n].a);
                strcpy((*presta)[numPrestamos+i].e,(*libro)[n].e);
                //(*libro)[n].rep--;

                x=rand()%numAlumnos;
                //fread(&((*alumno)[x]),sizeof(struct nuevosAlumnos),1,alum);
                (*presta)[numPrestamos+i].mat=(*alumno)[x].mat;
                (*alumno)[x].libros++;

                if((*alumno)[x].modo=='A'){
                    strcpy((*presta)[numPrestamos+i].n1,(*alumno)[x].n1);
                    strcpy((*presta)[numPrestamos+i].n2,(*alumno)[x].n2);
                    strcpy((*presta)[numPrestamos+i].a1,(*alumno)[x].a1);
                    strcpy((*presta)[numPrestamos+i].a2,(*alumno)[x].a2);
                }
                else{
                    strcpy((*presta)[numPrestamos+i].nombre,(*alumno)[x].nc);
                }
                strcpy((*presta)[numPrestamos+i].carrera,(*alumno)[x].carrera);
                while(1){
                    n=rand()%(f+1);
                    compara=strcmp(fecha[n].day,"SABADO");
                    compara2=strcmp(fecha[n].day,"DOMINGO");
                    if(compara!=0&&compara2!=0){
                        break;
                    }
                }//while(fecha[n].day=="SABADO"||fecha[n].day=="DOMINGO");
                //printf("\n  fecha[n].day = %s",fecha[n].day);

                (*presta)[numPrestamos+i].dia=fecha[n].dia;
                (*presta)[numPrestamos+i].mes=fecha[n].mes;
                strcpy((*presta)[numPrestamos+i].day,fecha[n].day);
                strcpy((*presta)[numPrestamos+i].month,fecha[n].month);
                (*presta)[numPrestamos+i].fp=n;
                y=n;
                j=0;
                compara=strcmp(fecha[n].day,"JUEVES");
                compara2=strcmp(fecha[n].day,"VIERNES");
                if(compara==0){
                    aux=n+4;
                }
                if(compara2==0){
                    aux=n+4;
                }
                if(compara!=0 && compara2!=0){
                    aux=n+2;
                }
                if(n>f-2&&n<=f){entrega=0;}
                else{entrega=rand()%2;}
                /*if(aux>f){entrega==0;}
                if(n<f-2){
                    entrega=0;
                }
                else{
                    entrega=rand()%2;
                }*/
                (*presta)[numPrestamos+i].fe=aux;
                (*presta)[numPrestamos+i].entregado=entrega;
                (*presta)[numPrestamos+i].diaE=fecha[aux].dia;
                (*presta)[numPrestamos+i].mesE=fecha[aux].mes;
                strcpy((*presta)[numPrestamos+i].dayE,fecha[aux].day);
                strcpy((*presta)[numPrestamos+i].monthE,fecha[aux].month);
                //printf("\n  f+1 = %d",fecha[n].day);
                int w=2;

                for(j=aux+1;j<=f;j++){
                    compara=strcmp(fecha[j].day,"SABADO");
                    compara2=strcmp(fecha[j].day,"DOMINGO");
                    if(compara!=0 && compara2!=0){
                        if(entrega==0){
                            retraso++;
                            multa=multa+10;
                            //printf("\n  %s %d",fecha[j].day,fecha[j].dia);
                        }
                    }
                }
                (*presta)[numPrestamos+i].retraso=retraso;
                (*presta)[numPrestamos+i].multa=multa;
                printf("\n  DATOS DEL ALUMNO");
                if((*alumno)[x].modo=='A'){
                    printf("\n    Alumno: %s %s %s %s",(*presta)[numPrestamos+i].n1,(*presta)[numPrestamos+i].n2,(*presta)[numPrestamos+i].a1,(*presta)[numPrestamos+i].a2);
                }
                else{
                    printf("\n    Alumno: %s",(*presta)[numPrestamos+i].nombre);
                }
                printf("\n    Matricula: %d\n    Carrera: %s\n    Libros: %d\n",(*alumno)[x].mat,(*alumno)[x].carrera,(*alumno)[x].libros);
                //fwrite(&((*alumno)[x].libros),sizeof((*alumno)[x].libros),1,alum);
                if((*alumno)[x].libros<=2){
                    printf("\n  DATOS DEL LIBRO");
                    printf("\n    ISBN: %d\n    Titulo: %s\n    Autor: %s\n    Editorial: %s\n",(*presta)[numPrestamos+i].isbn,(*presta)[numPrestamos+i].t,(*presta)[numPrestamos+i].a,(*presta)[numPrestamos+i].e);
                    printf("\n    Fecha de Prestamo: %s  %d de %s del %d\n",(*presta)[numPrestamos+i].day,(*presta)[numPrestamos+i].dia,(*presta)[numPrestamos+i].month,2016);
                    printf("\n    Fecha de Entrega: %s  %d de %s del %d\n",(*presta)[numPrestamos+i].dayE,(*presta)[numPrestamos+i].diaE,(*presta)[numPrestamos+i].monthE,2016);
                    if(entrega==0){
                        printf("\n    Entregado: No");
                        if(aux>=f){
                            printf("\n    Pendiente por entregar");
                        }
                        else{
                            printf("\n    Dias de retraso: %d\n    Multa: $%d.00\n",(*presta)[numPrestamos+i].retraso,(*presta)[numPrestamos+i].multa);
                        }
                    }
                    else{
                        printf("\n    Entregado: Si");
                    }
                    printf("\n-----------------------------------------------------------\n-----------------------------------------------------------\n");
                    fwrite(&((*presta)[numPrestamos+i]),sizeof((*presta)[numPrestamos+i]),1,pre);
                    numPrestamos++;
                }
                else{
                    printf("\n  No Puedes hacer mas prestamos");
                }
                printf("\n");


                retraso=1;
                multa=0;
            }
            //numPrestamos=numPrestamos+c;

        }
        else if(opc==2){
            *presta=(struct prestamos*)realloc(*presta,sizeof(struct prestamos)*(numPrestamos+1));
            (*presta)[numPrestamos].modo='M';
            printf("\n  DATOS DEL ALUMNO\n");
            printf("\n    Ingresa Matricula: ");scanf("%d",&(*presta)[numPrestamos].mat);
            i=0;
            //for(i=0;i<numAlumnos;i++){
            int existe=0, auxi;
            //while(!feof(alum)){
            for(i=0;i<numAlumnos;i++){
                fread(&((*alumno)[i]),sizeof(struct nuevosAlumnos),1,alum);
                //printf("\n  mat: %d alumno: %s",(*alumno)[i].mat,(*alumno)[i].n1);system("pause");
                if((*presta)[numPrestamos].mat==(*alumno)[i].mat){
                    existe=1;break;
                }
                //i++;
                if(i==numAlumnos-1){printf("\n  No existe el Alumno\n");break;}
            }
            //printf("\n  existe: %d",existe);
            if(existe==1){
                    auxi=i;
                if((*alumno)[i].modo=='A'){
                    printf("\n    Alumno: %s %s %s %s\n",(*alumno)[i].n1,(*alumno)[i].n2,(*alumno)[i].a1,(*alumno)[i].a2);
                    strcpy((*presta)[numPrestamos].n1,(*alumno)[i].n1);
                    strcpy((*presta)[numPrestamos].n2,(*alumno)[i].n2);
                    strcpy((*presta)[numPrestamos].a1,(*alumno)[i].a1);
                    strcpy((*presta)[numPrestamos].a2,(*alumno)[i].a2);
                }
                else{
                    printf("\n    Alumno: %s\n",(*alumno)[i].nc);
                    strcpy((*presta)[numPrestamos].nombre,(*alumno)[i].nc);
                }
                printf("\n    Carrera: %s\n",(*alumno)[i].carrera);
                strcpy((*presta)[numPrestamos].carrera,(*alumno)[i].carrera);
                //(*alumno)[i].libros++;//printf("\n  libros: %d",(*alumno)[i].libros);system("pause");
                //fwrite(&((*alumno)[i]),sizeof((*alumno)[i]),1,alum);
                if((*alumno)[i].libros<=2){

                printf("\n  DATOS DEL LIBRO\n");
                printf("\n    Ingresa ID: ");scanf("%d",&(*presta)[numPrestamos].id);
                existe=0;
                for(i=0;i<numLibros;i++){
                    fread(&((*libro)[i]),sizeof(struct nuevosLibros),1,bib);
                    if((*presta)[numPrestamos].id==(*libro)[i].id){
                        existe=1;break;
                    }
                    if(i==numLibros-1){printf("\n  No existe el libro\n");break;}//break;}
                }
                if(existe==1){
                    //int repeticion, repeticion2;
                    /*disp=fopen("librosDisponibles.txt","wb");
                    while(!feof(libRep)){
                        fscanf(libRep,"%d ",&repeticion);
                        fprintf(disp,"%d ",repeticion);
                    }
                    fclose(disp);
                    disp=fopen("librosDisponibles.txt","r");
                    j=0;
                    do{
                        fscanf(disp,"%d ",&repeticion);
                        j++;
                    }while(j<(*libro)[i].id);
                    fclose(disp);*/
                    printf("\n    Titulo: %s\n    Autor: %s\n    Editorial: %s\n",(*libro)[i].t,(*libro)[i].a,(*libro)[i].e);
                    //printf("\n    Repeticiones: %d\n",repeticion);
                    strcpy((*presta)[numPrestamos].t,(*libro)[i].t);
                    strcpy((*presta)[numPrestamos].a,(*libro)[i].a);
                    strcpy((*presta)[numPrestamos].e,(*libro)[i].e);


                        /*repeticion2=repeticion-1;
                        printf("\n    Disponibles ahora: %d\n",repeticion2);
                        disp=fopen("librosDisponibles.txt","wb");
                        j=0;
                        do{
                            fscanf(libRep,"%d ",&repeticion);
                            if((*libro)[j].isbn==(*libro)[i].isbn){
                                fprintf(disp,"%d ",repeticion2);
                            }else if(j==(*libro)[i].id){
                                fprintf(disp,"%d ",repeticion2);
                            }
                            else{
                                fprintf(disp,"%d ",repeticion);
                            }
                            j++;
                        }while(j<numLibros);*/
                        //fclose(disp);
                        printf("\n    Fecha de prestamo: %s %d de %s del %d\n",fecha[f].day,fecha[f].dia,fecha[f].month,2016);
                        strcpy((*presta)[numPrestamos].day,fecha[f].day);
                        strcpy((*presta)[numPrestamos].month,fecha[f].month);
                        (*presta)[numPrestamos].dia=fecha[f].dia;
                        compara=strcmp(fecha[f].day,"JUEVES");
                        compara2=strcmp(fecha[f].day,"VIERNES");
                        if(compara==0){
                            aux=f+4;
                        }
                        if(compara2==0){
                            aux=f+4;
                        }
                        if(compara!=0 && compara2!=0){
                            aux=f+2;
                        }
                        printf("\n    Fecha de Entrega: %s %d de %s del %d\n",fecha[aux].day,fecha[aux].dia,fecha[aux].month,2016);
                        strcpy((*presta)[numPrestamos].dayE,fecha[aux].day);
                        strcpy((*presta)[numPrestamos].monthE,fecha[aux].month);
                        (*presta)[numPrestamos].diaE=fecha[aux].dia;
                        (*alumno)[auxi].libros++;

                        printf("\n  El prestamo se realizo correctamente\n\n");
                        numPrestamos++;
                    }
                    else{
                        printf("\n    No hay dispnibles\n\n");
                    }
                }
                else{
                    printf("\n  No puedes hacer mas prestamos\n");
                }

            }
            else{
                printf("\n  El Alumno no existe\n");
            }
        }
        else if(opc==3){
            fclose(pre);
            pre=fopen("PrestamosLibros.txt","wb");
            numPrestamos=0;
            for(i=0;i<numAlumnos;i++){
                (*alumno)[i].libros=0;
            }
        }

    }
    for(i=0;i<numAlumnos;i++){
        fwrite(&((*alumno)[i]),sizeof((*alumno)[i]),1,alum);
    }
    nP=fopen("CantidadPrestamos.txt","w");
    fprintf(nP,"%d",numPrestamos);
    fclose(nP);
    fclose(libRep);
    fclose(pre);
    fclose(bib);
    fclose(alum);
    return numPrestamos;
}
int entregaLibros(struct prestamos **presta, struct nuevosAlumnos **alumno, int numPrestamos, int numAlumnos, int f){
    FILE *pre;
    //FILE *alum=fopen("MisAlumnos.txt","rb");
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n  ENTREGAR LIBRO\n");
    if(numPrestamos>0){
        pre=fopen("PrestamosLibros.txt","rb");
        int i, j, existe=0, matricula;
        for(i=0;i<numPrestamos;i++){
            *presta=(struct prestamos*)realloc(*presta,sizeof(struct prestamos)*(i+1));
            fread(&((*presta)[i]),sizeof(struct prestamos),1,pre);
            //printf("\n  antes de for libro: %p   &((*libro)[i])= %d",*libro,(*libro)[i].isbn);system("pause");
        }
        i=0;
        printf("\n  Ingresa Matricula: ");scanf("%d",&matricula);
        while(!feof(pre)){
            //fread(&((*presta)[i]),sizeof(struct prestamos),1,pre);
            if((*presta)[i].mat==matricula){
                existe=1;break;
            }
            i++;
            if(i==numPrestamos){printf("\n  No existe el prestamo\n");break;}
        }

        if(existe==1){
            printf("\n  DATOS DEL ALUMNO");
            if((*presta)[i].modo=='A'){
                printf("\n    Alumno: %s %s %s %s",(*presta)[i].n1,(*presta)[i].n2,(*presta)[i].a1,(*presta)[i].a2);
            }
            else{
                printf("\n    Alumno: %s",(*presta)[i].nombre);
            }
            printf("\n    Carrera: %s\n",(*presta)[i].carrera);
            printf("\n  DATOS DEL LIBRO");
            printf("\n    ID: %d\n    ISBN: %d\n    Titulo: %s\n    Autor: %s\n    Editorial: %s\n",(*presta)[i].id,(*presta)[i].isbn,(*presta)[i].t,(*presta)[i].a,(*presta)[i].e);
            printf("\n  Fecha de Prestamo: %s %d de %s del %d\n",(*presta)[i].day,(*presta)[i].dia,(*presta)[i].month,2016);
            int compara, compara2,retraso=0;
            if(f>=(*presta)[i].fe){
                for(j=(*presta)[i].fe+1;j<=f;j++){
                    compara=strcmp(fecha[j].day,"SABADO");
                    compara2=strcmp(fecha[j].day,"DOMINGO");
                    if(compara!=0 && compara2!=0){
                        //if(entrega==0){
                            retraso++;
                            //multa=multa+10;
                            //printf("\n  %s %d",fecha[j].day,fecha[j].dia);
                        //}
                    }
                }
                printf("\n  Tiene un retraso de %d dias\n  Su multa sera de: $%d.00\n\n",retraso,retraso*10);
            }
        }
        else{
            printf("\n  No se encontro el registro\n\n");
        }
        fclose(pre);
    }
    else{
        printf("\n  No se ha hecho ningun Prestamo\n\n");
    }
}
int busqueda(struct nuevosLibros **libro, struct nuevosAlumnos **alumno, int numLibros, int numAlumnos){
    FILE *bib=fopen("MiBiblioteca.txt","rb");
    FILE *alum=fopen("MisAlumnos.txt","rb");
    int i, opc, opc2;
    for(i=0;i<numLibros;i++){
        *libro=(struct nuevosLibros*)realloc(*libro,sizeof(struct nuevosLibros)*(i+1));
        fread(&((*libro)[i]),sizeof(struct nuevosLibros),1,bib);
    }
    for(i=0;i<numAlumnos;i++){
        *alumno=(struct nuevosAlumnos*)realloc(*alumno,sizeof(struct nuevosAlumnos)*(i+1));
        fread(&((*alumno)[i]),sizeof(struct nuevosAlumnos),1,alum);
    }
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n  BUSQUEDA\n\n  1.Buscar Libros\n  2.Buscar Alumno\n");
    do{
        printf("\n  Elige opcion: ");scanf("%d",&opc);
    }while(opc<1||opc>2);
    int isbn,id,  j;
    char t[30],a[30],e[15],nombre[30];
    if(opc==1){
        printf("\n  Buscar por:  1.ISBN  2.Titulo  3.Autor  4.Editorial  5.Id  6.Ver todo\n");
        do{
            printf("\n  Elige opcion: ");scanf("%d",&opc2);
        }while(opc2<1||opc2>6);
        switch(opc2){
            case 1:
                printf("\n  Ingresa ISBN: ");scanf("%d",&isbn);
                j=0;
                while(!feof(bib)){
                    if(isbn==(*libro)[j].isbn){
                        printf("\n  %d %d %s %s %s",(*libro)[j].id,(*libro)[j].isbn,(*libro)[j].t,(*libro)[j].a,(*libro)[j].e);
                        break;
                    }
                    j++;
                    if(j==numLibros){printf("\n  No existe el libro\n\n");break;}
                }
                break;
            case 2:
                printf("\n  Ingresa Titulo: ");scanf(" %[^\n]",&t);
                j=0;
                while(!feof(bib)){
                    if(strstr(t,(*libro)[j].t)!=NULL){
                        printf("\n  %d %d %s %s %s",(*libro)[j].id,(*libro)[j].isbn,(*libro)[j].t,(*libro)[j].a,(*libro)[j].e);
                        break;
                    }
                    j++;
                    if(j==numLibros){printf("\n  No existe el libro\n\n");break;}
                }
                break;
            case 3:
                printf("\n  Ingresa Autor: ");scanf(" %[^\n]",&a);
                j=0;
                while(!feof(bib)){
                    if(strstr(a,(*libro)[j].a)!=NULL){
                        printf("\n  %d %d %s %s %s",(*libro)[j].id,(*libro)[j].isbn,(*libro)[j].t,(*libro)[j].a,(*libro)[j].e);
                        break;
                    }
                    j++;
                    if(j==numLibros){printf("\n  No existe el libro\n\n");break;}
                }
                break;
            case 4:
                printf("\n  Ingresa Editorial: ");scanf(" %[^\n]",&e);
                j=0;
                while(!feof(bib)){
                    if(strstr(e,(*libro)[j].e)!=NULL){
                        printf("\n  %d %d %s %s %s",(*libro)[j].id,(*libro)[j].isbn,(*libro)[j].t,(*libro)[j].a,(*libro)[j].e);
                        break;
                    }
                    j++;
                    if(j==numLibros){printf("\n  No existe el libro\n\n");break;}
                }
                break;
            case 5:
                printf("\n  Ingresa Id: ");scanf("%d",&id);
                j=0;
                while(!feof(bib)){
                    if(id==(*libro)[j].id){
                        printf("\n  %d %d %s %s %s",(*libro)[j].id,(*libro)[j].isbn,(*libro)[j].t,(*libro)[j].a,(*libro)[j].e);
                        break;
                    }
                    j++;
                    if(j==numLibros){printf("\n  No existe el libro");break;}
                }
                break;
            case 6:
                if(numLibros>0){
                    for(j=0;j<numLibros;j++){
                        printf("\n  %d %d %s %s %s",(*libro)[j].id,(*libro)[j].isbn,(*libro)[j].t,(*libro)[j].a,(*libro)[j].e);
                    }
                }
                else{
                    printf("\n  No Hay libros");
                }
                printf("\n");
                break;

        }
    }
    else{
        printf("\n    Buscar por:  1.Nombre  2.Matricula  3.Carrera  4.Ver todo\n");
        do{
            printf("\n    Elige opcion: ");scanf("%d",&opc2);
        }while(opc2<1||opc2>4);
        int existe=0;
        switch(opc2){
            case 1:
                printf("\n    Ingresa Nombre: ");scanf(" %[^\n]",&nombre);
                j=0;
                while(!feof(bib)){
                    if(strstr(nombre,(*alumno)[j].n1)){
                        printf("\n    %s %s %s %s %d %s\n",(*alumno)[j].n1,(*alumno)[j].n2,(*alumno)[j].a1,(*alumno)[j].a2,(*alumno)[j].mat,(*alumno)[j].carrera);
                        existe=1;
                    }
                    if(strstr(nombre,(*alumno)[j].nc)){
                        printf("\n    %s %d %s\n",(*alumno)[j].nc,(*alumno)[j].mat,(*alumno)[j].carrera);
                        existe=1;
                    }
                    j++;
                    if(j==numAlumnos){
                        if(existe==0){
                            printf("\n    No existe el Alumno\n\n");
                        }
                        break;
                    }
                }
                break;
            case 4:
                for(j=0;j<numAlumnos;j++){
                    printf("\n--------------------------------------------------------");
                    if((*alumno)[j].modo=='A'){
                        printf("\n    Matricula: %d  Carrera: %s\n    Nombre: %s %s %s %s\n",(*alumno)[j].mat,(*alumno)[j].carrera,(*alumno)[j].n1,(*alumno)[j].n2,(*alumno)[j].a1,(*alumno)[j].a2);
                    }
                    else{
                        printf("\n    Matricula: %d  Carrera: %s\n    Nombre: %s\n",(*alumno)[j].mat,(*alumno)[j].carrera,(*alumno)[j].nc);
                    }
                }
                printf("\n--------------------------------------------------------\n");
        }
    }
    fclose(bib);
}
int calendario(int dia, int mes){
    system("cls");
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
    return i;
}
