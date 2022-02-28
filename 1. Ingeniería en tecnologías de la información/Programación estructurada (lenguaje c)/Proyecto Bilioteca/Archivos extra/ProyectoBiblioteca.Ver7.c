#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct nuevosLibros{
    int id; char t[30],a[30],e[15];
};
struct nuevosAlumnos{
    char n1[12],n2[12],a1[12],a2[12],nc[50],carrera[10];

    int mat;
};
void calendario();
int recibeLibros(struct nuevosLibros **, FILE *, FILE *, FILE *, int);
int leerLibros(struct nuevosLibros **, FILE *);
int misAlumnos(struct nuevosAlumnos **, FILE *, FILE *, FILE *, FILE *, int);
int leerAlumnos(struct nuevosAlumnos **, FILE *);

int main(){
    srand(time(NULL));
    FILE *lib;//abrira el archivo de libreria
    FILE *bib;//abrira el archivo MiBiblioteca
    FILE *alum;//abrira el archivo MisAlumnos
    FILE *nom;//abrira el archivo de nombres F ó M
    FILE *apA;//abrira el archivo de apellidos
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
                numLibros=recibeLibros(&libro,lib,bib,nL,numLibros);  //system("pause");
                break;
            case 2://MIS ALUMNOS
                printf("\nCantidad de Alumnos: %d  ",numAlumnos);system("pause");
                numAlumnos=misAlumnos(&alumno,alum,nom,apA,nA,numAlumnos);
                break;
            case 3://PRESTAMOS DE LIBROS
                break;
            case 4://ENTREGA DE LIBROS
                break;
            case 5://BUSQUEDA
                break;
            case 6:salir=1;
                break;
            case 7:
                break;
        }
    }while(salir!=1);
    free(libro);
    free(alumno);
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
int recibeLibros(struct nuevosLibros **libro, FILE *lib, FILE *bib, FILE *nL, int numLibros){
    system("cls");
    calendario();
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\n  RECIBIR LIBROS\n");
    printf("\n  1.Aleatorio desde la libreria\n  2.Manual\n  3.Visualizar\n  4.Eliminar todos los libros\n");
    int opc,id;
    char t[30],a[30],e[15];
    do{printf("\n  Elige opcion: ");scanf("%d",&opc);}while(opc<1||opc>4);
    struct tempLibro{
        int id; char t[30],a[30],e[15];
    }temp[30];
    bib=fopen("MiBiblioteca.txt","ab");
    //nL=fopen("CantidadLibros.txt","w");
    //fprintf(nL,"%d",numLibros);fclose(nL);
    int c, i=0, n;
    if(opc==1){
        lib=fopen("libreria.txt","r");
        do{printf("\n  Cuantos Libros: ");scanf("%d",&c);}while(c<1||c>5);
        while(!feof(lib)){
            fscanf(lib,"%d%s%s%s",&temp[i].id,&temp[i].t,&temp[i].a,&temp[i].e);
            i++;
            if(i==30){
                printf("\n\n");
                break;
            }
        }
        printf("\n  Libros Agregados\n\n");
        for(i=0;i<c;i++){
            n=rand()%30;
            *libro=(struct nuevosLibros*)realloc(*libro,sizeof(struct nuevosLibros)*(numLibros+(i+1)));
            (*libro)[numLibros+i].id=temp[n].id;
            strcpy((*libro)[numLibros+i].t,temp[n].t);
            strcpy((*libro)[numLibros+i].a,temp[n].a);
            strcpy((*libro)[numLibros+i].e,temp[n].e);
            fwrite(&((*libro)[numLibros+i]),sizeof((*libro)[numLibros+i]),1,bib);
            printf("  %d  %s  %s  %s\n\n",temp[n].id,temp[n].t,temp[n].a,temp[n].e);
        }
        fclose(lib);
        numLibros=numLibros+c;
    }
    else if(opc==2){
        *libro=(struct nuevosLibros*)realloc(*libro,sizeof(struct nuevosLibros)*(numLibros+1));
        do{
           printf("\nISBN (10 cifras enteras): ");scanf("%d",&id);//system("cls");
        }while(id/1000000000<1);
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
        numLibros++;
    }
    else if(opc==3){

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
int misAlumnos(struct nuevosAlumnos **alumno, FILE *alum, FILE *nom, FILE *apA, FILE *nA, int numAlumnos){
    system("cls");
    calendario();
    printf("\nSISTEMA DE PRESTAMOS DE LIBROS\n\nREGISTRAR ALUMNOS\n");
    printf("\n1.Aleatoriamente\n2.Manual\n3.Eliminar Datos\n");
    int opc;
    do{printf("\nElige opcion: ");scanf("%d",&opc);}while(opc<1||opc>3);
    alum=fopen("MisAlumnos.txt","ab");
    char archivo[15];
    int x,c;
    int mat;
    char nomb[50];
    if(opc==1){
        do{printf("\nCuantos Alumnos: ");scanf("%d",&c);}while(c<1);
        x=rand()%2;
        if(x==0){
            strcpy(archivo,"nombresFF.txt");
        }
        else{
            strcpy(archivo,"nombresMM.txt");
        }
        printf("\narchivo = %s  ",archivo);system("pause");
        nom=fopen(archivo,"r");
        apA=fopen("apellidos.txt","r");
        struct nombres{
            char na[12];
        }nombre[35],apellido[35];
        int i=0;
        while(!feof(nom)){
            fscanf(nom,"%s",nombre[i].na);
            i++;
            if(i==35){break;}
        }
        i=0;
        while(!feof(apA)){
            fscanf(apA,"%s",apellido[i].na);
            i++;
            if(i==35){break;}
        }
        printf("\nNuevos Alumnos\n\n");
        for(i=0;i<c;i++){
            *alumno=(struct nuevosAlumnos*)realloc(*alumno,sizeof(struct nuevosAlumnos)*(numAlumnos+(i+1)));
            x=rand()%30; strcpy((*alumno)[numAlumnos+i].n1,nombre[x].na);
            x=rand()%30; strcpy((*alumno)[numAlumnos+i].n2,nombre[x].na);
            x=rand()%30; strcpy((*alumno)[numAlumnos+i].a1,apellido[x].na);
            x=rand()%30; strcpy((*alumno)[numAlumnos+i].a2,apellido[x].na);
            x=rand()%9999+1530001; (*alumno)[numAlumnos+1].mat = x;
            fwrite(&((*alumno)[numAlumnos+i]),sizeof((*alumno)[numAlumnos+i]),1,alum);
            printf("Matricula: %d  Nombre: %s %s %s %s\n\n",x,(*alumno)[numAlumnos+i].n1,(*alumno)[numAlumnos+i].n2,(*alumno)[numAlumnos+i].a1,(*alumno)[numAlumnos+i].a2);

        }
        numAlumnos=numAlumnos+c;
        fclose(nom);
        fclose(apA);
    }
    else if(opc==2){
        *alumno=(struct nuevosAlumnos*)realloc(*alumno,sizeof(struct nuevosAlumnos)*(numAlumnos+1));
        printf("\nNombre del Alumno: ");scanf(" %[^\n]",&nomb);
        printf("\nMatricula: ");scanf("%d",&mat);
        strcpy((*alumno)[numAlumnos].nc,nomb);
        (*alumno)[numAlumnos].mat = mat;
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
    fclose(nA);
    fclose(alum);
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
