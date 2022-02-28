#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include<pthread.h>
#include "barrier.h"

long k = 0;  //numero de columnas del covering array
long t = 0;  //fuerza
long v = 0;  //se define el alfabeto
long n = 0;  //numero del filas del covering array
long m = 0;  //longitud del gtp
long **covering_array = NULL;
long filas_ca = 0;
char *filename_c_array = NULL;
long **alfabeto = NULL;
long c_array_correct = 0;
long **c_array_alfabeto=NULL;
long **c_array=NULL;
long num_c_array=0;
long num_hilos = 0;
long **tareas_hilos = NULL;
long fila = 0;
long **gtps=NULL;
long coeficiente=0;

long exist_all = 0;
long exist = 0;

pthread_barrier_t barrier;
pthread_mutex_t mutex;

void free_memory(){
    for (int i = 0; i < filas_ca; ++i)
        free(covering_array[i]);
    free(covering_array);

    free(filename_c_array);
    long f = pow(v, t);
    for (int i = 0; i < f; ++i)
        free(alfabeto[i]);
    free(alfabeto);

    for (int i = 0; i < num_c_array; ++i)
        free(c_array_alfabeto[i]);
    free(c_array_alfabeto);

    for (int i = 0; i < num_hilos*num_c_array; ++i)
        free(tareas_hilos[i]);
    free(tareas_hilos);

    for (int i = 0; i < coeficiente; ++i)
        free(gtps[i]);
    free(gtps);
}
long *createVector(long size){
    long *vector = (long*)malloc(sizeof(long)*size);
    return vector;
}
long **createMatrix(long f){
    long **matrix = (long**)malloc(sizeof(long*) * f);
    return matrix;
}

//calculo de coeficiente binomial
long binomial(long k, long r){
    long a =(long)k, b =(long)r;
    //printf("%ld*", a);
    for (long i = 1; i <= r-1; ++i){
        a *= (k-i);
        b *= (r-i);
    }    
    return (long)(a/b);
}
//metodo factorial recursivo
long factorial(long n){
    if(n == 0)
        return 1;
    return n * factorial(n-1);
}

long nextBinomial(long p, long k, long r){
    if(k + 1 < r)
        return 0;   
    if(k + 1 == r)
        return 1;
    return p * (k + 1) / (k + 1 - r);
}

//implementacion del metodo inverso de natural a GTP
long *inverseGTP(long alpha, long m){

    long *vector = createVector(m);

    //printf("a:%ld\n", alpha);

    long f = factorial(m);
    for (long i = m; i >= 1; i--)
    {
        long a = pow(f * alpha, 1.0/i);
        vector[i-1] = a;
        long delta = binomial(vector[i-1], i);
        while(nextBinomial(delta, vector[i-1], i) <= alpha){
            delta = nextBinomial(delta, vector[i-1], i);
            vector[i-1]++;
        }
        alpha -= delta;
        f = f / i;
    }
    return vector;
}

long N_value(long k){
    long n = 4;
    while(1){
        if(binomial(n-1,ceil((float)n/2)) >= k)
            break;
        n++;
    }
    return n;
}

void printCA(){
    printf("\nCovering Array:\n");
    for (long i = 0; i < filas_ca; i++){
        for (long j = 0; j < k; ++j)
            printf("%ld ", covering_array[i][j]);
        printf("\n");
    }
}

void *CoveringArray(void *id_hilo){

    long id = (long)id_hilo;
    long tareas = (long)tareas_hilos[(int)id][0];
    long inicio = (long)tareas_hilos[(int)id][1];
    long fin = (long)tareas_hilos[(int)id][2];

    
    //printf("id=%ld, tareas=%ld, inicio=%ld, fin=%ld\n", id, tareas, inicio, fin);

    for (int i = inicio; i < fin; ++i)
    {
        //if(covering_array[i] == NULL)
            //covering_array[i] = createVector(k);

        int c = 0;
        for (int a = 1; a <= num_c_array; ++a)
        {
            if(i >= n * a){
                c++;
            }
        }
        //printf("hilo=%ld, i=%d, c=%d\n",id, i, c );
        
        
        if(i % n == 0){
            //printf("hilo=%ld, i=%d, c=%d\n",id, i, c );
            //se crea el covering array inicializado en ceros
            for (long a = i, x = 0; a < i + n; ++a){
                //covering_array[a] = createVector(k);
                for (long b = 0; b < k; ++b)
                    covering_array[a][b] = c_array_alfabeto[c][0];
            }

            //se obtienen los gtp por columna
            for (long a = 0; a < k; a++){
                
                long *gtp = inverseGTP(a, m);
                //free(gtp);

                for (long j = 0; j < m; j++){
                    covering_array[gtp[j]+1 + n*c][a] = c_array_alfabeto[c][1];
                }
            }
        }

        
    }

    return NULL;
}

//convierte de numero natural a polinomio
long* Numero_Factoradico(long num, long v, long t){
    long *factoradico = (long*)malloc(t * sizeof(long));
    for (long i = t-1; i >= 0; i--){
        factoradico[i] = num % v;
        num /= v;
    }
    return factoradico;
}

void C_Alfabeto(){

    //total de combinaciones
    //v = alfabeto
    //t = fuerza (2 para este caso)
    long f = pow(v, t);

    //se crean todas las filas de la matriz de combinaciones
    alfabeto = createMatrix(f);
    //printf("\nAlfabeto:\n");
    for (long i = 0; i < f; ++i){
        alfabeto[i] = Numero_Factoradico(i, v, t);

        /*for (long j = 0; j < t; ++j)
            printf("%ld, ", alfabeto[i][j]);
        printf("\n");*/
    }
    //printf("\n");
}
void* Comparations(void *id_hilo){

    long id = (long)id_hilo;
    long tareas = (long)tareas_hilos[(int)id][0];
    long inicio = (long)tareas_hilos[(int)id][1];
    long fin = (long)tareas_hilos[(int)id][2];
    long f = pow(v, t);

    long existentes = 0;

    //printf("id=%ld, tareas=%ld, inicio=%ld, fin=%ld\n", id, tareas, inicio, fin);
    
    //se recorren todas las comparaciones
    for (long i = inicio; i < fin; ++i){
        
        existentes=0;
    
        for (long x = 0; x < f; ++x){
            long digito2 = 0;
            for (long y = t-1, p = 0; y >= 0; y--, p++)
                digito2 += alfabeto[x][y] * pow(10, p);

            for (long j = 0; j < n * num_c_array; ++j){
                long digito = 0;
                for (long l = t-1, p = 0; l >= 0; l--, p++)
                    digito += covering_array[ j ][ gtps[i][l] ] * pow(10, p);

                if(digito2 == digito){
                    existentes++;
                    break;
                }
            }
        }
        //no existe , covering array incorrecto
        if(existentes < f)
            break;
    }

    pthread_mutex_lock(&mutex);
    exist_all += existentes;
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barrier);

    //if(id==0)
        //printf("exist_all=%ld\n", exist_all);
    if(exist_all == f * num_hilos)
        exist = 1;

    return NULL;
}
char* PrintCoveringArray(){

    char *filename = (char*)malloc(100*sizeof(char));

    sprintf(filename, "Resultados/N%ldk%ldv%ld^%ldt%ld.ca", filas_ca, k, v, k, t);

    FILE *data = fopen(filename, "w");

    fprintf(data, "C Covering array with N=%ld k=%ld v=%ld^%ld t=%ld\n", filas_ca, k, v, k, t);
    fprintf(data, "%ld %ld %ld^%ld %ld\n", n, k, v, k, t);  

    for (long i = 0; i < n*num_c_array; i++){
        for (long j = 0; j < k; ++j){
            fprintf(data, "%ld ", covering_array[i][j]);
        }
        fprintf(data, "\n");
    }

    fclose(data);
    free(filename);
    free(data);

    return filename;
}

int main(int argc, char const *argv[])
{
    
    struct timeval stop, start;//taking time    
    k = atoi(argv[1]);//numero de columnas del covering array    
    t = atoi(argv[2]);//fuerza    
    v = atoi(argv[3]); //se define el alfabeto
    num_hilos = atoi(argv[4]);//numero de hilos
    n = N_value(k);//numero del filas del covering array
    m = ceil((float)n/2);//longitud del gtp

    num_c_array = binomial(v, 2);
    filas_ca = num_c_array * n;
    //se crea el alfabeto para los CA
    c_array_alfabeto = createMatrix(num_c_array);
    for (long i = 0; i < num_c_array; ++i)
        c_array_alfabeto[i] = inverseGTP(i, 2);
    covering_array = createMatrix(filas_ca);

    for (int i = 0; i < filas_ca; ++i)
        covering_array[i] = createVector(k);

    //printf("K=%ld, N=%ld, M=%ld, alfabeto=%ld, filas=%ld\n", k,n,m,num_c_array,filas_ca);

//se definen la cantidad de tareas por hilo --------------------
    tareas_hilos = createMatrix(num_hilos * num_c_array);
    long restantes = filas_ca % num_hilos;
    long inicio=0;
    for (int i = 0; i < num_hilos; ++i)
    {
        tareas_hilos[i] = createVector(3);
        tareas_hilos[i][0] = (i < restantes) ? filas_ca/num_hilos + 1 : filas_ca/num_hilos; //numero de tareas por hilo
        tareas_hilos[i][1] = inicio;
        tareas_hilos[i][2] = inicio + tareas_hilos[i][0];
        inicio += tareas_hilos[i][0];
        //printf("hilo %d = %ld\n", i, tareas_hilos[i][0]);
    }


//Creacion del Covering Array --------------------------------------------------------------

    gettimeofday(&start, NULL);// INICIO CRONOMETRO---

    pthread_t *hilos = (pthread_t*)malloc(sizeof(pthread_t) * num_hilos);

    for (long i = 0; i < num_hilos; ++i)
    {
        pthread_create(&hilos[i], NULL, CoveringArray, (void*)i);
    }
    //printf("aqui\n");

    for (int i = 0; i < num_hilos; ++i)
    {
        pthread_join(hilos[i], NULL);
    }

    //printCA();

    //printf("termina1\n");
    free(hilos);
    gettimeofday(&stop, NULL); // FIN CRONOMETRO---
    //printf("Time (s): %lf\n\n", 
        //((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0 );

//Verificacion del Covering Array  ----------------------------------------------


    C_Alfabeto();


    coeficiente = binomial(k, t);
    long f = pow(v, t);
    gtps = createMatrix(coeficiente);
    for (long i = 0; i < coeficiente; ++i)
        gtps[i] = inverseGTP(i, t);

    restantes = coeficiente % num_hilos;
    inicio=0;
    for (int i = 0; i < num_hilos; ++i)
    {
        tareas_hilos[i][0] = (i < restantes) ? coeficiente/num_hilos + 1 : coeficiente/num_hilos; //numero de tareas por hilo
        tareas_hilos[i][1] = inicio;
        tareas_hilos[i][2] = inicio + tareas_hilos[i][0];
        inicio += tareas_hilos[i][0];
        //printf("hilo %d = %ld\n", i, tareas_hilos[i][0]);
    }

    // Initialize barrier
    pthread_barrier_init(&barrier, NULL, num_hilos);
    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    gettimeofday(&start, NULL);// INICIO CRONOMETRO---


    hilos = (pthread_t*)malloc(sizeof(pthread_t) * num_hilos);

    for (long i = 0; i < num_hilos; ++i)
    {
        //printf("VCA\n");
        pthread_create(&hilos[i], NULL, Comparations, (void*)i);
    }
    //printf("aqui\n");

    for (int i = 0; i < num_hilos; ++i)
    {
        pthread_join(hilos[i], NULL);
    }

    //printf("Covering Array Correcto: %s \n", exist == 1 ? "si" : "no");

    //printCA();

    // Destroy mutex
    pthread_mutex_destroy(&mutex);
    // Destroy barrier
    pthread_barrier_destroy(&barrier);

    //printf("termina2\n");
    free(hilos);


    gettimeofday(&stop, NULL);// FIN CRONOMETRO---

    float time = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0;
    printf("Time (s): %f\n\n", time);

    char filename[100];

    sprintf(filename, "Tiempos/Paralelo/N%ldk%ldv%ld^%ldt%ld_%s_%ldH.txt", filas_ca, k, v, k, t, 
        exist == 1 ? "S" : "N", num_hilos);
    FILE * file = fopen(filename, "a");
    fprintf(file, "%f\n", time);
    fclose(file);

    free_memory();

    return 0;
}