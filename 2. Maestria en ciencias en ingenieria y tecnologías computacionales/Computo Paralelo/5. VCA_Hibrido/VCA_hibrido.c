#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>
#include<pthread.h>
#include "barrier.h"

//numero de columnas del covering array
int k=0;
//fuerza
int t=0;
//se define el alfabeto
int v=0;
//numero del filas del covering array
int n=0;
//longitud del gtp
int m=0;

int **covering_array = NULL;
int **covering_array2 = NULL;
int filas_ca = 0;
char *filename_c_array = NULL;
int **alfabeto = NULL;
int c_array_correct = 0;
int **c_array_alfabeto=NULL;
int **c_array=NULL;
int num_c_array=0;
int num_hilos = 0;
int **local_n = NULL;
int fila = 0;
int **gtps=NULL;
int coeficiente=0;

int **local_covering_array = NULL;

int **tareas_hilos = NULL;

int exist_all = 0;
int exist = 0;

pthread_barrier_t barrier;
pthread_mutex_t mutex;

void free_memory(){
    for (int i = 0; i < filas_ca; ++i)
        free(covering_array[i]);
    free(covering_array);

    free(filename_c_array);
    int f = pow(v, t);
    for (int i = 0; i < f; ++i)
        free(alfabeto[i]);
    free(alfabeto);
}

int free_m(int ***array) {
       /* free the memory - the first element of the array is at the start */
       free(&((*array)[0][0]));

       /* free the pointers into the memory */
       free(*array);

       return 0;
}

void createVector(int **vector, int size){
    (*vector) = (int*)malloc(sizeof(int)*size);
}
void createMatrix(int ***matrix, int size){
    (*matrix) = (int**)malloc(sizeof(int*) * size);
}
int memory(int ***array, int n, int m) {

    (*array) = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; ++i)
        (*array)[i] = (int*)malloc(m * sizeof(int));

    //return 0;

    /* allocate the n*m contiguous items */
    int *p = (int *)malloc(n*m*sizeof(int));
    if (!p) return -1;

    /* allocate the row pointers into the memory */
    (*array) = (int **)malloc(n*sizeof(int*));
    if (!(*array)) {
        free(p);
        return -1;
    }

    /* set up the pointers into the contiguous memory */
    for (int i=0; i<n; i++)
        (*array)[i] = &(p[i*m]);

    return 0;
}

//calculo de coeficiente binomial
int binomial(int k, int r){
    int a =(int)k, b =(int)r;
    //printf("%d*", a);
    for (int i = 1; i <= r-1; ++i){
        a *= (k-i);
        b *= (r-i);
    }    
    return (int)(a/b);
}

//metodo factorial recursivo
int factorial(int n){
    if(n == 0)
        return 1;
    return n * factorial(n-1);
}

int nextBinomial(int p, int k, int r){
    if(k + 1 < r)
        return 0;   
    if(k + 1 == r)
        return 1;
    return p * (k + 1) / (k + 1 - r);
}

//implementacion del metodo inverso de natural a GTP
int *inverseGTP(int alpha, int m){

    int *vector = NULL;
    createVector(&vector, m);

    int f = factorial(m);
    for (int i = m; i >= 1; i--)
    {
        int a = pow(f * alpha, 1.0/i);
        vector[i-1] = a;
        int delta = binomial(vector[i-1], i);
        while(nextBinomial(delta, vector[i-1], i) <= alpha){
            delta = nextBinomial(delta, vector[i-1], i);
            vector[i-1]++;
        }
        alpha -= delta;
        f = f / i;
    }
    return vector;
}

int N_value(int k){
    int n = 4;
    while(1){
        if(binomial(n-1,ceil((float)n/2)) >= k)
            break;
        n++;
    }
    return n;
}

void printCA(){
    printf("\nCovering Array:\n");
    for (int i = 0; i < filas_ca; i++){
        for (int j = 0; j < k; ++j)
            printf("%d ", covering_array2[i][j]);
        printf("\n");
    }
}


void *CoveringArray(void *id_hilo/*int **local_covering_array , int count, int inicio, int id*/){

    long _id = (long)id_hilo;
    int id = (int)_id;
    int tareas = (int)tareas_hilos[(int)id][0];
    int inicio = (int)tareas_hilos[(int)id][1];
    int fin = (int)tareas_hilos[(int)id][2];
    int inicio_global = (int)tareas_hilos[(int)id][3];
    int id_proc = (int)tareas_hilos[(int)id][4];

    int fila_global = inicio_global;
    int c = 0;

    for (int i = inicio; i < fin; ++i)
    {
        c=0;
        for (int j = 1; j <= num_c_array; ++j){
            if(fila_global >= n * j)
                c++;
        }

        for (int j = 0; j < k; ++j){
            local_covering_array[i][j] = c_array_alfabeto[c][0];   

            int *gtp = inverseGTP(j, m);
            int f = fila_global%n;
            //printf("f=%d\n", f);
            for (int x= 0; x < m; ++x)
            {
                if(gtp[x]+1 == f){
                    local_covering_array[ i ][j] = c_array_alfabeto[c][1];
                    break;
                }
            }
        }

        fila_global++;
    }

    return NULL;    
}

char* PrintCoveringArray(){

    char *filename = (char*)malloc(100*sizeof(char));

    sprintf(filename, "Resultados/N%dk%dv%d^%dt%d.ca", filas_ca, k, v, k, t);

    FILE *data = fopen(filename, "w");

    fprintf(data, "C Covering array with N=%d k=%d v=%d^%d t=%d\n", filas_ca, k, v, k, t);
    fprintf(data, "%d %d %d^%d %d\n", n, k, v, k, t);  

    for (int i = 0; i < n*num_c_array; i++){
        for (int j = 0; j < k; ++j){
            fprintf(data, "%d ", covering_array[i][j]);
        }
        fprintf(data, "\n");
    }
    fclose(data);
    free(data);
    //free(filename);

    return filename;
}



//convierte de numero natural a polinomio
int* Numero_Factoradico(int num, int v, int t){
    int *factoradico = (int*)malloc(t * sizeof(int));
    for (int i = t-1; i >= 0; i--){
        factoradico[i] = num % v;
        num /= v;
    }
    return factoradico;
}

void C_Alfabeto(){

    //total de combinaciones
    //v = alfabeto
    //t = fuerza (2 para este caso)
    int f = pow(v, t);

    //se crean todas las filas de la matriz de combinaciones
    //createMatrix(&alfabeto, f);
    memory(&alfabeto, f, t);
    //printf("\nAlfabeto:\n");
    for (int i = 0; i < f; ++i){
        alfabeto[i] = Numero_Factoradico(i, v, t);

        /*for (int j = 0; j < t; ++j)
            printf("%d, ", alfabeto[i][j]);
        printf("\n");*/
    }
    //printf("\n");
}

int ** leer_CoveringArray(char *filename, int n, int k, int v){
    
    int **covering_array = (int**)malloc(n*num_c_array *sizeof(int*));
    FILE *c_array_file = fopen(filename, "r");
    //printf("Leyendo Covering Array\n");

    char linea[2000];
    int f = 0;
    int num_linea = 0;
    while(fgets(linea, 2000, (FILE*)c_array_file)){
        if(num_linea >= 2){
            covering_array[f] = (int*)malloc(k * sizeof(int));
            for (int i = 0, j = 0; i < k*2-1; i+=2, j++)
                covering_array[f][j] = linea[i]-48;
            //printf("\n");
            f++;
        }      
        num_linea++;
    }
    fclose(c_array_file);
    return covering_array;
}

void *Comparations(void *id_hilo/*int **CA, int counts, int inicio, int id*/){
    
    long _id = (long)id_hilo;
    int id = (int)_id;
    int tareas = (int)tareas_hilos[(int)id][0];
    int inicio = (int)tareas_hilos[(int)id][1];
    int fin = (int)tareas_hilos[(int)id][2];
    int inicio_global = (int)tareas_hilos[(int)id][3];
    int id_proc = (int)tareas_hilos[(int)id][4];

    int existentes = 0;
    int f = pow(v, t);

    int fila_global = inicio_global;

    for (int i = inicio; i < fin; ++i){
        
        existentes=0;

        for (int x = 0; x < f; ++x){

            int digito2 = 0;
            for (int y = t-1, p = 0; y >= 0; y--, p++)
                digito2 += alfabeto[x][y] * pow(10, p);

            for (int j = 0; j < n * num_c_array; ++j){

                int digito = 0;
                for (int l = t-1, p = 0; l >= 0; l--, p++){
                    //pthread_barrier_wait(&barrier);
                    digito += covering_array2[ j ][ gtps[fila_global][l] ] * pow(10, p);
                    
                }
                //printf("p%d h%d: %d == %d\n",id_proc, id, digito2, digito);
                if(digito2 == digito){
                    existentes++;
                    break;
                }
            }
        }

        //no existe , covering array incorrecto
        //printf("EXIST=%d\n", existentes);
        if(existentes < f)
            break;

        fila_global++;
    }


    pthread_mutex_lock(&mutex);
    exist_all += existentes;
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barrier);

    //if(id==0)
        //printf("exist_all=%ld\n", exist_all);
    if(exist_all == f * num_hilos){
        exist_all = f;
        //printf("p%d h%d: exist_all=%d\n",id_proc, id, exist_all);
    }

    return NULL;
}

int main(int argc, char *argv[])
{

    struct timeval stop, start;//taking time  
    
    //numero de columnas del covering array
    k = atoi(argv[1]);

    //fuerza
    t = atoi(argv[2]);

    //se define el alfabeto
    v = atoi(argv[3]);

    num_hilos = atoi(argv[4]);

    //numero del filas del covering array
    n = N_value(k);

    //longitud del gtp
    m = ceil((float)n/2);

    num_c_array = binomial(v, 2);
    filas_ca = num_c_array * n;

    int procesos, id;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    gettimeofday(&start, NULL);///--------------------------------

    //se crea el alfabeto para los CA
    //createMatrix(&c_array_alfabeto, num_c_array);
    memory(&c_array_alfabeto, num_c_array, 2);
    for (int i = 0; i < num_c_array; ++i){
        c_array_alfabeto[i] = inverseGTP(i, 2);
    }

    if(id == 0){      
        memory(&covering_array, filas_ca, k);        
        //se inicializa el CA global    
        //createMatrix(&covering_array, filas_ca);
        for (int i = 0; i < filas_ca; ++i){
            //createVector(&covering_array[i], k);
            for (int j = 0; j < k; ++j)
                covering_array[i][j] = -1;    
        }    
    }  

    MPI_Barrier(MPI_COMM_WORLD);

    //se definen la cantidad de tareas por hilo --------------------

    int restantes = filas_ca % procesos;
    int inicio=0;
    int counts[procesos];
    int displs[procesos];
    
    for (int i = 0; i < procesos; ++i)
    {
        counts[i] = (i < restantes) ? filas_ca/procesos + 1 : filas_ca/procesos; //numero de tareas por hilo
        displs[i] = inicio;
        inicio += counts[i];
    }
    printf("ca %d: %dx%d\n",id,counts[id], k );
    memory(&local_covering_array, counts[id], k);

    int sizes[2] = {filas_ca , k};  //dimensiones del CA final
    int sizes_proc[2] = {counts[id], k};
    int starts[2] = {0,0};

    MPI_Datatype type, subarrtype;
    MPI_Type_create_subarray(2, sizes, sizes_proc, starts, MPI_ORDER_C, MPI_INT, &type);
    MPI_Type_create_resized(type, 0, k*sizeof(int), &subarrtype);
    MPI_Type_commit(&subarrtype);
    
    int *globalptr = NULL;
    if(id == 0) globalptr = &(covering_array[0][0]);

    int sendcounts[procesos];

    if (id == 0) {
        for (int i=0; i<procesos; i++)
            sendcounts[i] = 1;//gridsize/size;
    }

            memory(&tareas_hilos, num_hilos, 5);
            restantes = counts[id] % num_hilos;
            inicio=0;
            int inicio_g = displs[id];
            for (int i = 0; i < num_hilos; ++i)
            {
                tareas_hilos[i][0] = (i < restantes) ? counts[id]/num_hilos + 1 : counts[id]/num_hilos; //numero de tareas por hilo
                tareas_hilos[i][1] = inicio;
                tareas_hilos[i][2] = inicio + tareas_hilos[i][0];
                tareas_hilos[i][3] = inicio_g;
                tareas_hilos[i][4] = id;
                inicio += tareas_hilos[i][0];
                inicio_g += tareas_hilos[i][0];
            }

            pthread_t *hilos = (pthread_t*)malloc(sizeof(pthread_t) * num_hilos);

            for (long i = 0; i < num_hilos; ++i)
            {
                pthread_create(&hilos[i], NULL, CoveringArray, (void*)i);
            }
            
            for (int i = 0; i < num_hilos; ++i)
            {
                pthread_join(hilos[i], NULL);
            }
            free(hilos);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gatherv(&(local_covering_array[0][0]), counts[id]*k, MPI_INT, 
        globalptr, sendcounts, displs, subarrtype, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    int **M=NULL;
    memory(&M, filas_ca, k);

    if(id == 0){
        //printf("filas=%d\n", filas_ca);
        for (int i = 0; i < filas_ca; ++i)
        {
            for (int j = 0; j < k; ++j)
                M[i][j] = covering_array[i][j];
        }
    }

    MPI_Bcast(&(M[0][0]), filas_ca*k, MPI_INT, 0, MPI_COMM_WORLD);
    
    MPI_Barrier(MPI_COMM_WORLD);

    memory(&covering_array2, filas_ca, k);

    for (int i = 0; i < filas_ca; ++i)
    {
        for (int j = 0; j < k; ++j)
        {

            covering_array2[i][j] = M[i][j];
            //printf("[%d]", M[i][j]);
        }
        //printf("\n");
    }

    C_Alfabeto();

    MPI_Barrier(MPI_COMM_WORLD);


    coeficiente = binomial(k, t);
    int f = pow(v, t);
    //createMatrix(&gtps, coeficiente);
    memory(&gtps, coeficiente, t);

    for (int i = 0; i < coeficiente; ++i){
        gtps[i] = inverseGTP(i, t);
    }

    restantes = coeficiente % procesos;
    inicio=0;
    
    for (int i = 0; i < procesos; ++i)
    {
        counts[i] = (i < restantes) ? coeficiente/procesos + 1 : coeficiente/procesos; //numero de tareas por hilo
        displs[i] = inicio;
        inicio += counts[i];
    }


            restantes = counts[id] % num_hilos;
            inicio=0;
            inicio_g = displs[id];
            for (int i = 0; i < num_hilos; ++i)
            {
                tareas_hilos[i][0] = (i < restantes) ? counts[id]/num_hilos + 1 : counts[id]/num_hilos; //numero de tareas por hilo
                tareas_hilos[i][1] = inicio;
                tareas_hilos[i][2] = inicio + tareas_hilos[i][0];
                tareas_hilos[i][3] = inicio_g;
                tareas_hilos[i][4] = id;
                
                inicio += tareas_hilos[i][0];
                inicio_g += tareas_hilos[i][0];
                
            }

            // Initialize barrier
            pthread_barrier_init(&barrier, NULL, num_hilos);
            // Initialize mutex
            pthread_mutex_init(&mutex, NULL);


            hilos = (pthread_t*)malloc(sizeof(pthread_t) * num_hilos);

            for (long i = 0; i < num_hilos; ++i)
            {
                //printf("VCA\n");

                pthread_create(&hilos[i], NULL, Comparations, (void*)i);
                
            }
            //printf("aqui\n");


            MPI_Barrier(MPI_COMM_WORLD);
            

            for (int i = 0; i < num_hilos; ++i)
            {
                
                //printf("p%d ii=%d\n",id, i);
                //if(id == 0) printf("i=%d/%d : %d\n", i, num_hilos-1, exist_all);
                pthread_join(hilos[i], NULL);
                //printf("p%d j=%d\n", id, i);
            }
            
            // Destroy mutex
            pthread_mutex_destroy(&mutex);
            // Destroy barrier
            pthread_barrier_destroy(&barrier);

            //printf("termina2\n");
            free(hilos);

    int existentes;

    MPI_Reduce(&exist_all, &existentes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if(id == 0){
        //printCA();


        if(existentes == f * procesos){
            printf("correcto\n");
        }
        else
            printf("incorrecto\n");

        gettimeofday(&stop, NULL);// FIN CRONOMETRO---
        float time = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0;
        printf("Time (s): %f\n\n", time);

        char filename[100];
        sprintf(filename, "Tiempos/Hibrido/N%dk%dv%d^%dt%d_%s_%dP_%dH.txt", filas_ca, k, v, k, t, 
        existentes == f * procesos ? "S" : "N", procesos, num_hilos);
        FILE * file = fopen(filename, "a");
        fprintf(file, "%f\n", time);
        fclose(file);
        free_m(&covering_array);
        
    }

    free_m(&covering_array2);
    free(filename_c_array);
    free_m(&alfabeto);
    free_m(&gtps);

    //printf("Covering Array Correcto: %s \n", c_array_correct == 1 ? "si" : "no");*/
    MPI_Finalize();
    return 0;
}