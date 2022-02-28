#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "randfunc.h"
//#include "barrier.h"
#include "Tree3.h"
#include <time.h>
#include <sys/time.h>

const char *instancia = NULL;
double crossover_p = 0;
double mutation_p = 0;
int N_POBLACION = 0;
int GMAX = 0;
int gen = 0;
int torneo = 0;
int elitista = 0;
double cruce[3], mutacion[3];
int id = 0;
double semilla = 0;

int **POBLACION = NULL;
int **_POBLACION = NULL;
int *FITNESS = NULL;
int *_FITNESS = NULL;

void init_param(){
}


void getDATA(const char *argv[]){

	instancia = argv[1];	

	//printf("aqui\n");
	Q = atoi(argv[2]);
	CENTER_NODE = atoi(argv[3]);
	crossover_p = atof(argv[4]);
	mutation_p = atof(argv[5]);
	//N_POBLACION = atoi(argv[6]) * N;
	GMAX = atoi(argv[7]);
	torneo = atoi(argv[8]);
	elitista = atoi(argv[9]);
	cruce[0] = atof(argv[10]) * 200.0;
	cruce[1] = atof(argv[11]) * 200.0;
	cruce[2] = atof(argv[12]) * 200.0;
	mutacion[0] = atof(argv[13]) * 200.0;
	mutacion[1] = atof(argv[14]) * 200.0;
	mutacion[2] = atof(argv[15]) * 200.0;

	//printf("mutaciones: %f %f %f\n", mutacion[0], mutacion[1], mutacion[2]);
	//fila_ca = atoi(argv[16]);
	id = atoi(argv[16]);
	semilla = atof(argv[17]);
	//printf("id=%d semilla=%f\n", id, semilla);
	//GMAX = (mutacion[2] > 0.0) ? 200 : GMAX;

	randomizef(semilla * .01);
	initrandomnormaldeviate();

	read_dataset((char*)instancia);

	N_POBLACION = atoi(argv[6]) * N;

}

void poblacion_inicial(){
	createMatrix(&POBLACION, N_POBLACION, N-2);
	createVector(&FITNESS, N_POBLACION);

	createMatrix(&_POBLACION, N_POBLACION, N-2);
	createVector(&_FITNESS, N_POBLACION);
	
	for (int i = 0; i < N_POBLACION; ++i){
		POBLACION[i] = random_secuence();
		FITNESS[i] = 0;
	}
}
void print_poblacion(int **P){
	printf("\nPOBLACION:\n");
	for (int i = 0; i < N_POBLACION; ++i){
		printf("s%d ",i );
		print_secuence(P[i]);
	}
	printf("\n");
}
void print_fitness(int *f){
	printf("\nFITNESS:\n");
	for (int i = 0; i < N_POBLACION; ++i)
		printf("%d\n", f[i]);
	printf("\n");
}
int **evaluar_poblacion(int **P, int **F){
	//printf("FITNESS:\n");
	//printf("F=%d\n",P[0][47]);
	
	for (int i = 0; i < N_POBLACION; ++i){
		(*F)[i] = evaluation(P[i]);
		//printf("F%d=%d\n",i, (*F)[i]);
	}
	//printf("hola\n");


	for (int i = 0; i < N_POBLACION; ++i){
		for (int j = 0; j < N_POBLACION-1; ++j){
			if((*F)[j] > (*F)[j+1]){
				int f = (*F)[j];
				(*F)[j] = (*F)[j+1];
				(*F)[j+1] = f;

				int *sec = P[j];
				P[j] = P[j+1];
				P[j+1] = sec;
			}
		}
	}
	return P;
}

void seleccion(int **padre1, int **padre2){
	//printf("SELECCION\n");
	int rand1 = rnd(0, N_POBLACION-1), rand2;
	do{rand2 = rnd(0, N_POBLACION-1);}while(rand2 == rand1);

	//printf("padre1=%d, padre2=%d\n", rand1, rand2);

	//seleccion por torneo
	for (int i = 0; i < torneo-1; ++i){

		int rand1_2 = rnd(0, N_POBLACION-1);
		if(rand1_2 < rand1)
			rand1 = rand1_2;

		int rand2_2 = rnd(0, N_POBLACION-1);
		if(rand2_2 < rand2)
			rand2 = rand2_2;

		//printf("padre1=%d, padre2=%d\n", rand1, rand2);
	}

	/*int *a = createVector(N-2);
	int *b = createVector(N-2);

	for (int i = 0; i < N-2; ++i)
	{
		a[i] = POBLACION[rand1][i];
		b[i] = POBLACION[rand2][i];
	}*/

	//(*padre1) = a;// random_secuence(); //POBLACION[rand1];
	//(*padre2) = b;//random_secuence(); //POBLACION[rand2];

	copySequence(padre1, POBLACION[rand1]);
	copySequence(padre2, POBLACION[rand2]);
	//print_secuence(padres[0]);
	//print_secuence(padres[1]);
	//free(a);
	//free(b);

}
void crossover(int **padre1, int **padre2){
	//printf("CROSSOVER:\n");
	//se verifica si se realiza la cruza
	if(rndreal(0.0,1.0) < crossover_p){
		int prob = rnd(0,1000);
		if(prob < cruce[0]){
			//printf("cruza1\n");
			crossover1(padre1, padre2);
		}
		else if(prob < cruce[0] + cruce[1]){
			//printf("cruza2\n");
			crossover2(padre1, padre2);
		}
		else if(prob < cruce[0] + cruce[1] + cruce[2]){
			//printf("cruza3\n");
			crossover3(padre1, padre2, crossover_p);
		}
	}	
}
void mutation(int **padre1, int **padre2, int fit_global){
	//se verifica si se realiza la mutacion
	if(rndreal(0.0,1.0) < mutation_p){

		int prob = rnd(0,1000);
		if(prob < mutacion[0]){
			//printf("mutacion1\n");
			mutation1(padre1);
			mutation1(padre2);
		}
		else if(prob < mutacion[0] + mutacion[1]){
			//printf("mutacion2\n");
			mutation2(padre1);
			mutation2(padre2);
		}
		else if(prob < mutacion[0] + mutacion[1] + mutacion[2]){
			//printf("mutacion3\n");
			mutation3(padre1, fit_global);
			mutation3(padre2, fit_global);
		}

	}
}

void elitism(){
	//printf("elitista = %d\n", elitista);
	if(elitista == 1){//es elitista
		for (int i = N_POBLACION-2; i >= 0; i--){
			_POBLACION[i+1] = _POBLACION[i];
		}

		_POBLACION[0] = POBLACION[0];
	}

	POBLACION = _POBLACION;	//nueva poblacion
}


void generation(){
    for (int j = 0; j < N_POBLACION; j+=2)
	{
		seleccion(&_POBLACION[j], &_POBLACION[j+1]);
		crossover(&_POBLACION[j], &_POBLACION[j+1]);
		mutation(&_POBLACION[j], &_POBLACION[j+1], FITNESS[0]);
	}

	_POBLACION = evaluar_poblacion(_POBLACION, &_FITNESS);
	elitism();
	POBLACION = evaluar_poblacion(POBLACION, &FITNESS);
}

int main(int argc, char const *argv[])
{
	struct timeval stop, start;//taking time

	
	getDATA(argv);

	maximum_tree = get_maximum_tree();
	cost_maximum_tree = get_tree_cost(maximum_tree);

	gettimeofday(&start, NULL);///---------------------------------

	poblacion_inicial();
	
	POBLACION = evaluar_poblacion(POBLACION, &FITNESS);

	printf("N=%d\n", N_POBLACION);
	printf("\nINIT=%d\n", FITNESS[0]);
	int F = FITNESS[0];

	char filename[100];
	char filename2[100];
	int ins = (CENTER_NODE == 0) ? 1 :
					(CENTER_NODE == 15) ? 2 :
					(CENTER_NODE == 25) ? 3 : 4;

	sprintf(filename, "R_FINAL2\\instancia%d_%d.txt", id, (int)semilla);

	printf("%s\tGMAX=%d\n", filename, GMAX);
	//exit(0);

	//printf("GMAX=%d\n", GMAX);
	FILE *file = fopen(filename, "w");
	fclose(file);

	for (int i = 0; i < GMAX; ++i)
	{
		generation();
		//printf("i=%d\tBEST=%d\n", i, FITNESS[0]);
		if(FITNESS[0] < F){
			printf("i=%d\tBEST=%d\n", i, FITNESS[0]);
			file = fopen(filename, "a");
			fprintf(file, "%d %d\n", i, FITNESS[0]);
			fclose(file);
			F = FITNESS[0];
		}
	}
	gettimeofday(&stop, NULL);///---------------------------------
	float time = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0;
    printf("Time (s): %f\n\n", time);

    for (int i = 0; i < N; ++i){
		free(cost_matrix[i]);
		free(nodes_[i]);
		free(adyacent_matrix[i]);
		free(new_cost_matrix[i]);
		if(i < N-1){
			free(maximum_tree[i]);
			free(tree[i]);
		}
	}

	free(cost_matrix);
	free(demandas);
	free(nodes);


    
    printf("FINN\n\n");
	return 0;
}