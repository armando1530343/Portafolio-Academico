#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

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

int procesos = 0;

int **covering_array = NULL;
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

int exist_all = 0;
int exist = 0;

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


void CoveringArray(int counts[], int displs[]){

    int id = omp_get_thread_num();
    int procesos = omp_get_num_threads();
    int tareas = counts[id];
    int inicio = displs[id];
    int fin = inicio + tareas;

    //int fila_global = inicio;
    int c = 0;

    //printf("proceso %d: inicio=%d, fin=%d\n", id, inicio, fin);

    for (int i = inicio; i < fin; ++i)
    {
        c=0;
        for (int j = 1; j <= num_c_array; ++j){
            if(i >= n * j)
                c++;
        }

        for (int j = 0; j < k; ++j){
            covering_array[i][j] = c_array_alfabeto[c][0];   

            int *gtp = inverseGTP(j, m);
            int f = i % n;
            //printf("f=%d\n", f);
            for (int x= 0; x < m; ++x)
            {
                if(gtp[x]+1 == f){
                    covering_array[ i ][j] = c_array_alfabeto[c][1];
                    break;
                }
            }
        }
        //fila_global++;
    }
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
    //free(data);
    //free(filename);

    return filename;
}

void printCA(){
    printf("\nCovering Array:\n");
    for (int i = 0; i < filas_ca; i++){
        for (int j = 0; j < k; ++j)
            printf("%d ", covering_array[i][j]);
        printf("\n");
    }
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
    //alfabeto = createMatrix(f);
    memory(&alfabeto, f, t);
    //printf("\nAlfabeto:\n");
    for (int i = 0; i < f; ++i){
        alfabeto[i] = Numero_Factoradico(i, v, t);

        /*for (int j = 0; j < t; ++j)
            printf("%d, ", alfabeto[i][j]);
        printf("\n");*/
    }
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

int Comparations(int counts[], int displs[]){
    
    int id = omp_get_thread_num();
    int procesos = omp_get_num_threads();
    int tareas = counts[id];
    int inicio = displs[id];
    int fin = inicio + tareas;
    
    int existentes = 0;
    int f = pow(v, t);

    for (int i = inicio; i < fin; ++i){
        existentes=0;    
        for (int x = 0; x < f; ++x){
            int digito2 = 0;
            for (int y = t-1, p = 0; y >= 0; y--, p++)
                digito2 += alfabeto[x][y] * pow(10, p);

            for (int j = 0; j < n * num_c_array; ++j){
                int digito = 0;
                for (int l = t-1, p = 0; l >= 0; l--, p++)
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
    return existentes;
}

int main(int argc, char const *argv[])
{

    struct timeval stop, start;//taking time  
    
    //numero de columnas del covering array
    k = atoi(argv[1]);

    //fuerza
    t = atoi(argv[2]);

    //se define el alfabeto
    v = atoi(argv[3]);

    procesos = atoi(argv[4]);

    //numero del filas del covering array
    n = N_value(k);

    //longitud del gtp
    m = ceil((float)n/2);

    gettimeofday(&start, NULL);///---------------------------------

    num_c_array = binomial(v, 2);
    filas_ca = num_c_array * n;
    memory(&c_array_alfabeto, num_c_array, 2);
    for (int i = 0; i < num_c_array; ++i){
        c_array_alfabeto[i] = inverseGTP(i, 2);
    }
    memory(&covering_array, filas_ca, k);        
    //se inicializa el CA global    
    //createMatrix(&covering_array, filas_ca);
    for (int i = 0; i < filas_ca; ++i){
        //createVector(&covering_array[i], k);
        for (int j = 0; j < k; ++j)
            covering_array[i][j] = -1;    
    }

    printf("FIlas=%d\n", filas_ca);

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

    #pragma omp parallel num_threads(procesos)
    CoveringArray(counts, displs);

    //printCA();
    //exit(0);

    C_Alfabeto();

    coeficiente = binomial(k, t);
    int f = pow(v, t);
    //createMatrix(&gtps, coeficiente);
    memory(&gtps, coeficiente, t);
    for (int i = 0; i < coeficiente; ++i){
        gtps[i] = inverseGTP(i, t);
        /*printf("gtp: ");
        for (int j = 0; j < t; ++j)
            printf("%d ", gtps[i][j]);
        printf("\n");*/
    }

    //exit(0);
    restantes = coeficiente % procesos;
    inicio=0;
    
    for (int i = 0; i < procesos; ++i){
        counts[i] = (i < restantes) ? coeficiente/procesos + 1 : coeficiente/procesos; //numero de tareas por hilo
        displs[i] = inicio;
        inicio += counts[i];
    }

    #pragma omp parallel num_threads( procesos ) \
      reduction(+: exist_all)
    exist_all += Comparations(counts, displs);    

    //printf("Covering Array Correcto: %s \n", exist_all == f * procesos ? "si" : "no");


    gettimeofday(&stop, NULL);///---------------------------------

    float time = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0;
    printf("Time (s): %f\n\n", time);

    char filename[100];
    sprintf(filename, "Tiempos/OPENMP/N%dk%dv%d^%dt%d_%s_%dH.txt", filas_ca, k, v, k, t, 
    exist_all == f * procesos ? "S" : "N", procesos);
    FILE * file = fopen(filename, "a");
    fprintf(file, "%f\n", time);
    fclose(file);

    /*sprintf(filename, "Tiempos/Secuencial/N%dk%dv%d^%dt%d_%s.txt", filas_ca, k, v, k, t, 
        c_array_correct == 1 ? "S" : "N");
    FILE * file = fopen(filename, "a");
    fprintf(file, "%f\n", time);
    fclose(file);*/

    free_m(&covering_array);
    free(filename_c_array);
    free_m(&alfabeto);
    free_m(&gtps);

    return 0;
}
