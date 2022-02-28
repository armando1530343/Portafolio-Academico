#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//calculo de coeficiente binomial
int binomial(int k, int r){
    if(k < r)
        return 0;
    int b = 1;
    for (int i = 1; i <= r; i++)
        b = b * (k-i+1) / i;
    return b;    
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

    int *vector = (int*)malloc(m * sizeof(int));

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


int **CoveringArray(int n/*filas*/, int k/*columnas*/, int m/*long GTP*/, int v/*alfabeto*/){

    int num_c_array = binomial(v, 2);
    //se crea el alfabeto para los CA
    int **c_array_alfabeto = (int **)malloc(num_c_array * sizeof(int*));
    for (int i = 0; i < num_c_array; ++i)
        c_array_alfabeto[i] = inverseGTP(i, 2);

    int **c_array = (int **)malloc(n * num_c_array * sizeof(int*));

    int fila = 0;
    for (int c = 0; c < num_c_array; ++c)
    {
        //printf("Alfabeto = %d---%d\n", c_array_alfabeto[c][0], c_array_alfabeto[c][1] );
        //se crea el covering array inicializado en ceros
        for (int i = fila; i < n*(c+1); ++i){
            c_array[i] = (int*)malloc(k * sizeof(int));
            for (int j = 0; j < k; ++j)
                c_array[i][j] = c_array_alfabeto[c][0];
        }
        //se obtienen los gtp por columna
        for (int i = 0; i < k; i++){
            
            int *gtp = inverseGTP(i, m);

            for (int j = 0; j < m; j++)
                c_array[gtp[j]+1 + n*c][i] = c_array_alfabeto[c][1];
        }

        fila += n;
    }

    return c_array;
}

char* PrintCoveringArray(int **CA, int n, int k, int t, int v){
    printf("\nCovering Array:\n");

    char *filename = (char*)malloc(100*sizeof(char));

    int num_c_array = binomial(v, 2);

    sprintf(filename, "N%dk%dv%d^%dt%d.ca", n, k, v, k, t);

    FILE *data = fopen(filename, "w");

    fprintf(data, "C Covering array with N=%d k=%d v=%d^%d t=%d\n", n, k, v, k, t);
    fprintf(data, "%d %d %d^%d %d\n", n, k, v, k, t);  

    for (int i = 0; i < n*num_c_array; i++){
        for (int j = 0; j < k; ++j){
            printf("%d ", CA[i][j]);
            fprintf(data, "%d ", CA[i][j]);
        }
        fprintf(data, "\n");
        printf("\n");
    }

    fclose(data);

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

int **C_Alfabeto(int v, int t){

    //total de combinaciones
    //v = alfabeto
    //t = fuerza (2 para este caso)
    int f = pow(v, t);

    //se crean todas las filas de la matriz de combinaciones
    int **vector = (int **)malloc(f * sizeof(int*));
    printf("\nAlfabeto:\n");
    for (int i = 0; i < f; ++i){
        vector[i] = Numero_Factoradico(i, v, t);

        for (int j = 0; j < t; ++j)
            printf("%d, ", vector[i][j]);
        printf("\n");
    }

    return vector;
}

int ** leer_CoveringArray(char *filename, int n, int k, int v){
    
    int num_c_array = binomial(v, 2);
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

int Comparations(int **covering_array, int k, int n, int t, int **alfabeto, int v){
    int coeficiente = binomial(k, t);
    int f = pow(v, t);
    int **gtps = (int**)malloc(coeficiente * sizeof(int*));
    for (int i = 0; i < coeficiente; ++i)
        gtps[i] = inverseGTP(i, t);

    int num_c_array = binomial(v, 2);

    //se recorren todas las comparaciones
    for (int i = 0; i < coeficiente; ++i){
        
        int existentes = 0;
    
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
            return 0;
    }

    return 1;
}

int main(int argc, char const *argv[])
{
    
    //numero de columnas del covering array
    int k = atoi(argv[1]);

    //fuerza
    int t = atoi(argv[2]);

    //se define el alfabeto
    int v = atoi(argv[3]);

    //numero del filas del covering array
    int n = N_value(k);

    //longitud del gtp
    int m = ceil((float)n/2);

    int **covering_array = CoveringArray(n, k, m, v);

    printf("K=%d\nN=%d\nM=%d\n", k,n,m );

    char *filename_c_array = PrintCoveringArray(covering_array, n, k, t, v);

    //covering_array = leer_CoveringArray(filename_c_array, n, k, v);

    int **alfabeto = C_Alfabeto(v, t);

    int c_array_correct = Comparations(covering_array, k, n, t, alfabeto, v);

    printf("Covering Array Correcto: %s \n", c_array_correct == 1 ? "si" : "no");

    return 0;
}