#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

//numero de columnas del covering array
long k=0;
//fuerza
long t=0;
//se define el alfabeto
long v=0;
//numero del filas del covering array
long n=0;
//longitud del gtp
long m=0;
long **covering_array=NULL;
char *filename_c_array=NULL;
long **alfabeto=NULL;
long filas_ca = 0;
long num_c_array=0;

void free_memory(){
    for (int i = 0; i < filas_ca; ++i)
        free(covering_array[i]);
    free(covering_array);

    free(filename_c_array);
    long f = pow(v, t);
    for (int i = 0; i < f; ++i)
        free(alfabeto[i]);
    free(alfabeto);
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


void CoveringArray(){

    num_c_array = binomial(v, 2);
    //se crea el alfabeto para los CA
    long **c_array_alfabeto = createMatrix(num_c_array);
    for (long i = 0; i < num_c_array; ++i)
        c_array_alfabeto[i] = inverseGTP(i, 2);

    filas_ca = num_c_array * n;

    //printf("filas=%ld\n", filas_ca);

    covering_array = createMatrix(filas_ca);

    //printf("alfabeto=%ld\n", num_c_array);

    long fila = 0;
    for (long c = 0; c < num_c_array; ++c)
    {
        //printf("Alfabeto = %ld---%ld\n", c_array_alfabeto[c][0], c_array_alfabeto[c][1] );
        //se crea el covering array inicializado en ceros
        for (long i = fila; i < n*(c+1); ++i){
            covering_array[i] = createVector(k);
            for (long j = 0; j < k; ++j)
                covering_array[i][j] = c_array_alfabeto[c][0];
        }
        //se obtienen los gtp por columna
        for (long i = 0; i < k; i++){
            
            long *gtp = inverseGTP(i, m);

            for (long j = 0; j < m; j++){
                covering_array[gtp[j]+1 + n*c][i] = c_array_alfabeto[c][1];
            }
        }

        fila += n;
    }

    /*for (long i = 0; i < num_c_array; ++i)
        free(c_array_alfabeto[i]);
    free(c_array_alfabeto);*/


    /*for (long i = 0; i < k; i++){
            
        long *gtp = inverseGTP(i, m);

        //for (long j = 0; j < m; j++){
            //covering_array[gtp[j]+1 + n*c][i] = c_array_alfabeto[c][1];
        //}
    }*/
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
    //free(data);
    //free(filename);

    return filename;
}

void printCA(){
    printf("\nCovering Array:\n");
    for (long i = 0; i < filas_ca; i++){
        for (long j = 0; j < k; ++j)
            printf("%ld ", covering_array[i][j]);
        printf("\n");
    }
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
}

long ** leer_CoveringArray(char *filename, long n, long k, long v){
    
    long **covering_array = (long**)malloc(n*num_c_array *sizeof(long*));
    FILE *c_array_file = fopen(filename, "r");
    //printf("Leyendo Covering Array\n");

    char linea[2000];
    long f = 0;
    long num_linea = 0;
    while(fgets(linea, 2000, (FILE*)c_array_file)){
        if(num_linea >= 2){
            covering_array[f] = (long*)malloc(k * sizeof(long));
            for (long i = 0, j = 0; i < k*2-1; i+=2, j++)
                covering_array[f][j] = linea[i]-48;
            //printf("\n");
            f++;
        }      
        num_linea++;
    }
    fclose(c_array_file);
    return covering_array;
}

long Comparations(){
    long coeficiente = binomial(k, t);
    long f = pow(v, t);
    long **gtps = createMatrix(coeficiente);
    for (long i = 0; i < coeficiente; ++i){
        gtps[i] = inverseGTP(i, t);
        /*printf("gtp: ");
        for (int j = 0; j < t; ++j)
            printf("%ld", gtps[i][j]);
        printf("\n");*/
    }

    //printf("coef=%ld, f=%ld\n", coeficiente, f);

    //se recorren todas las comparaciones
    for (long i = 0; i < coeficiente; ++i){
        
        long existentes = 0;
        //printf("----------\n");
        for (long x = 0; x < f; ++x){
            long digito2 = 0;
            for (long y = t-1, p = 0; y >= 0; y--, p++)
                digito2 += alfabeto[x][y] * pow(10, p);

            //printf("digito2=%ld\n", digito2);

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
            return 0;
    }

    /*for (int i = 0; i < coeficiente; ++i)
        free(gtps[i]);
    free(gtps);*/

    return 1;
}

long main(long argc, char const *argv[])
{

    struct timeval stop, start;//taking time  
    
    //numero de columnas del covering array
    k = atoi(argv[1]);

    //fuerza
    t = atoi(argv[2]);

    //se define el alfabeto
    v = atoi(argv[3]);


    //numero del filas del covering array
    n = N_value(k);

    //longitud del gtp
    m = ceil((float)n/2);

    //printf("K=%ld, N=%ld, M=%ld\n", k,n,m );

    gettimeofday(&start, NULL);///---------------------------------

    CoveringArray();

    //printf("N=%ld\n", filas_ca);
    
    //printCA(); 

    filename_c_array = PrintCoveringArray(covering_array, n, k, t, v);

    //covering_array = leer_CoveringArray(filename_c_array, n, k, v);

    C_Alfabeto();

    long c_array_correct = Comparations();

    //printf("Covering Array Correcto: %s \n", c_array_correct == 1 ? "si" : "no");

    gettimeofday(&stop, NULL);///---------------------------------

    float time = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0;
    printf("Time (s): %f\n\n", time);

    char filename[100];

    sprintf(filename, "Tiempos/Secuencial/N%ldk%ldv%ld^%ldt%ld_%s.txt", filas_ca, k, v, k, t, 
        c_array_correct == 1 ? "S" : "N");
    FILE * file = fopen(filename, "a");
    fprintf(file, "%f\n", time);
    fclose(file);

    free_memory();

    return 0;
}