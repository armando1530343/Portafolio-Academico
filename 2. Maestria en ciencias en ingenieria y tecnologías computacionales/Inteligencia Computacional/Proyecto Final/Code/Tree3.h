#include <stdio.h>
#include <float.h>
#include <stdlib.h>

int **cost_matrix = NULL;		//matriz de costos de los nodos
int *demandas = NULL;			//matriz de demandas de los nodos (longitud N-1)
int N;						//numero de nodos
int Q;						//capacidad maxima de flujo de demandas
int *nodes = NULL;
int **nodes_ = NULL;
int num_subroots;
int CENTER_NODE;

int **maximum_tree = NULL;
int cost_maximum_tree = 0;

int *sequence = NULL;
int **tree = NULL;
int **adyacent_matrix = NULL;
int **new_cost_matrix = NULL;
int **padres = NULL;


int evaluation(int *);

void free_memory(){	

	/*for (int i = 0; i < N; ++i){
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
	free(nodes);*/
}

void createVector(int **vector, int size){
    (*vector) = (int*)malloc(sizeof(int)*size);
    //return vector;
}
void createMatrix(int ***matrix, int f, int c){
    (*matrix) = (int**)malloc(sizeof(int*) * f);
    for (int i = 0; i < f; ++i)
    	(*matrix)[i] = (int*)malloc(sizeof(int) * c);
    //return matrix;
}
void copySequence(int **a, int *b){
	createVector(a, N-2);
	for (int i = 0; i < N-2; ++i){
		(*a)[i] = b[i];
	}

}

void init(){

	createMatrix(&cost_matrix, N, N);
	createVector(&demandas, N);
	createVector(&nodes, N);
	createMatrix(&nodes_, N, 3);
	createMatrix(&maximum_tree, N-1, 2);
	createVector(&sequence, N-2);
	createMatrix(&tree, N-1, 2);
	createMatrix(&adyacent_matrix, N, N+1);
	createMatrix(&new_cost_matrix, N, N);
	//createMatrix(&padres)


}

void read_dataset(char *filename){

	FILE *dataset = fopen(filename, "r");
	char linea[2000];
	int f = 0;
	int num_linea = 0;
	int columna = 0;
	int fila = 0;

	
	
	while(fgets(linea, 2000, (FILE*)dataset)){
		char digit[5] = {0,0,0,0,0};
		int c = 0;
		int col = 0;
		if(num_linea == 0){
			N = atoi(linea);
			N = N;			
			init();
			//se inicializa los vectores
			//createVector(&demandas,N);
			//CENTER_NODE = rnd(0, N-1); //se selecciona el nodo concentrador
			demandas[CENTER_NODE] = 0;
			//createMatrix(&cost_matrix, N, N);

			printf("CENTER: %d\n", CENTER_NODE);
			
			//for (int i = 0; i < N; ++i)
			//	createVector(&cost_matrix[i], N);
		}
		else if(num_linea == 1){
			int i = 0;
			while(linea[i] != '\n'){
				if(linea[i] != ' '){
					digit[c] = linea[i];
					c++;
				}
				else{
					col += (col == CENTER_NODE) ? 1: 0;
					demandas[col] = atoi(digit);
					digit[0] = 0; digit[1] = 0; digit[2] = 0; digit[3] = 0;	digit[4] = 0;
					col ++;
					c = 0;
				}

				i++;
			}
			demandas[col] = atoi(digit);
		}
		else{
			

			int i = 0;
			while(linea[i] != '\n'){
				if(linea[i] != ' '){
					digit[c] = linea[i];
					c++;
				}
				else{
					cost_matrix[fila][columna] = atoi(digit);
					//printf("%d, %d = %d\n", fila, columna, cost_matrix[fila][columna]);
					columna ++;
					c = 0;
					digit[0] = 0; digit[1] = 0; digit[2] = 0; digit[3] = 0;	digit[4] = 0;
				}

				if(N > 50 && columna == N){
					fila++;
					columna = 0;

				}

				i++;
			}

			if(N == 50 && columna == N){
				fila++;
				columna = 0;

			}

		}
		num_linea ++;
	}

	//createVector(&nodes, N);
    for (int i = 0; i < N; ++i)
    	nodes[i] = 1;

	demandas[CENTER_NODE] = 0;
}

/*-----------------------------------------------------------
--------------Secuencia Aleatoria----------------
-------------------------------------------------------------*/

int* random_secuence(){
	//if(sequence == NULL)
	//	createVector(&sequence, N-2);
	//num_hilos = N-2;
	for (int i = 0; i < N-2; ++i){
		//los valores de la secuence toma valores aleatorios
		//desde 0 hasta N-1 nodos del arbol
		sequence[i] = rnd(0, N-1);
	}

	return sequence;
}

/*-----------------------------------------------------------
--------------codificacion de secuencia-arbol----------------
-------------------------------------------------------------*/

int **get_tree(int *secuence){
	//se declara el vector de los enlaces que se obtiene a partir de la secuencia
	/*if(tree == NULL){
		createMatrix(&tree, N-1, 2);
		//for (int i = 0; i < N-1; ++i)
		//	createVector(&tree[i], 2);
	}*/
	

	//se crea un vector con un indice para cada nodo del arbol
	//if(nodes == NULL)
	//createMatrix(&nodes_, N, 3);
	//se inicializa el vector con ceros
	for (int i = 0; i < N; ++i){
		//createVector(&nodes_[i], 3);
		
		nodes_[i][0] = i;//etiqueta del nodo
		nodes_[i][1] = 0;//repeticiones
		nodes_[i][2] = 0;// 0=sin auxiliar.  1=auxiliar1.  2=auxiliar2
		for (int j = 0; j < N-2; ++j){
			if(secuence[j] == i)
				nodes_[i][1] ++;
		}
		if(nodes_[i][1] == 0)
			nodes_[i][2] = 1;
	}

	int vec_aux = 1;
	for (int i = 0; i < N-2; ++i){
		int existe_aux = 0;
		//se verifica en que auxiliar se guarda
		for (int j = 0; j < N; ++j){
			if(nodes_[j][2] == vec_aux){
				existe_aux = 1;
				break;
			}
		}
		//incrementa el indice auxiliar
		vec_aux = (existe_aux == 0) ? vec_aux+1: vec_aux;
		//se decrementa las repeticiones de la etiqueta de la secuencia
		nodes_[secuence[i]][1]--;
		if(nodes_[secuence[i]][1] == 0)
			nodes_[secuence[i]][2] = vec_aux + 1;

		//se verifican con los nodos auxiliares
		int aux = 0;
		for (aux = 0; aux < N; ++aux){
			if(nodes_[aux][2] == vec_aux){
				nodes_[aux][2] = 0;
				break;
			}
		}
		tree[i][0] = secuence[i];
		tree[i][1] = nodes_[aux][0];
	}

    int c = 0;
	for (int i = 0; i < N; ++i){
		if(nodes_[i][2] > 0){
			tree[N-2][c] = i;
			c++;
		}
		if(c == 2)
			break;
	}

	/*for (int j = 0; j < N-1; j++){
		//printf("j=%d\n", j);
		free(nodes_[j]);
		//printf("j=%d\n", j);
	}
	free(nodes_);*/

	return tree;
}

/*-----------------------------------------------------------
-------actualiza los grados de la matriz de adyacencia-------
-------------------------------------------------------------*/
void *update_degree_p(void *t){
	int *works = (int*)t;
	for (int i = works[2]; i < works[3]; ++i)
	{
		int degree=0;
		for (int j = 0; j < N; ++j)
		{
			if(adyacent_matrix[i][j] == 1)
				degree++;
		}

		adyacent_matrix[i][N] = degree;
	}
	return NULL;
}
int **update_degree(int **adyacent){
	
	adyacent_matrix = adyacent;
	
	for (int i = 0; i < N; ++i)
	{
		int degree=0;
		for (int j = 0; j < N; ++j)
		{
			if(adyacent_matrix[i][j] == 1)
				degree++;
		}

		adyacent_matrix[i][N] = degree;
	}

	return adyacent_matrix;
}

//codificacion de arbol-secuencia
int *get_secuence(int **tree){
	
	//se recorren las filas de la matriz
	for (int i = 0; i < N; ++i)
	{
		//createVector(&adyacent_matrix[i], N+1);
		//primero se llena cada fila con ceros
		for (int j = 0; j < N+1; ++j)
			adyacent_matrix[i][j] = 0;
	}

	for (int i = 0; i < N-1; ++i)
	{
		//se enciende el nodo de acuerdo al enlace
		adyacent_matrix [ tree[i][0] ] [ tree[i][1] ] = 1;
		adyacent_matrix [ tree[i][1] ] [ tree[i][0] ] = 1;
		adyacent_matrix [ tree[i][0] ][N] ++;
		adyacent_matrix [ tree[i][1] ][N] ++;
	}

	//print_adyacent_matrix(adyacent_matrix, long_tree);

	int sec = 0;
	//se empieza a generar la secuencia
	do{
		adyacent_matrix = update_degree(adyacent_matrix);

		for (int i = 0; i < N; ++i)
		{
			if(adyacent_matrix[i][N] == 1){
				for (int j = 0; j < N; ++j)
				{
					if(adyacent_matrix[i][j] == 1){
						adyacent_matrix[i][j] = 0;
						adyacent_matrix[j][i] = 0;
						adyacent_matrix[i][N]--;
						sequence[sec] = j;
						sec++;
						if(sec == N-2)
							i = N;
						break;
					}
				}
			}
		}
		
	}
	while(sec < N-2);

	/*for (int i = 0; i < N; ++i)
		free(adyacent_matrix[i]);
	free(adyacent_matrix);*/
	//adyacent_matrix = NULL;
	
	return sequence;

}


int **get_cost_matrix(int **tree){

	/*for (int i = 0; i < N+1; ++i)
    	free(new_cost_matrix[i]);
    free(new_cost_matrix);*/
    //new_cost_matrix=NULL;

	//se crea una nueva matriz de adyacencia
	//if(new_cost_matrix == NULL)
	//	createMatrix(&new_cost_matrix, N, N);

	//se inicializa con ceros
	for (int i = 0; i < N; ++i){
		//createVector(&new_cost_matrix[i], N);
		//printf("%d: ", i);
		for (int j = 0; j < N; ++j){
			new_cost_matrix[i][j] = 0;
			//printf("%d ", new_cost_matrix[i][j]);
		}
		//printf("\n");

	}
	//printf("matrix\n");

	//se recorre el vector de enlaces y se asignan los costos
	for (int i = 0; i < N-1; ++i){
		int ci = tree[i][0];
		int cj = tree[i][1];
		new_cost_matrix[ci][cj] = cost_matrix[ci][cj];
		new_cost_matrix[cj][ci] = cost_matrix[cj][ci];
	}

	return new_cost_matrix;
}

int *get_subroots(int **tree){
	int *subrootss = NULL;
	createVector(&subrootss, N); //(int*)malloc(0);

	//subrootss = (int*)realloc(subrootss, 5);
	
	num_subroots = 1;
	
	//printf("subroots (conect with node 0) = ");
	for (int i = 0; i < N-1; ++i)
	{
		if(tree[i][0] == CENTER_NODE || tree[i][1] == CENTER_NODE){
			
			//subrootss = (int*) realloc(subrootss, 1);
			
			subrootss[num_subroots-1] = tree[i][0] == CENTER_NODE ? tree[i][1] : tree[i][0];
			//printf("[%d]", subroots_nodes[num_subroots-1]);
			num_subroots++;

		}
	}
	num_subroots--;

	return subrootss;
}

int *number_to_secuence(int number, int base){
	//createVector(&sequence, base-2);
	for (int i = base-3; i >= 0; i--)
	{
		int mod = number%base;
		number = number / base;
		sequence[i] = mod;
	}
	return sequence;
}

/*-----------------------------------------------------------
--------------------Operadores Geneticos---------------------
-------------------------------------------------------------*/
void crossover1(int **hijo1, int **hijo2){
	int punto_cruza = rnd(0, N-3);
	//printf("Punto cruza: %d\n", punto_cruza);
	
	for (int i = punto_cruza; i < N-2; ++i){
		int h = (*hijo1)[i];
		(*hijo1)[i] = (*hijo2)[i];
		(*hijo2)[i] = h;
	}

}
void crossover2(int **hijo1, int **hijo2){
	int punto1 = rnd(0,N-4), punto2;
	do{punto2 = rnd(1,N-3);}while(punto2<=punto1);

	
	//printf("p1=%d, p2=%d\n", punto1, punto2);
	for (int i = punto1; i < punto2; ++i){
		int h = (*hijo1)[i];
		(*hijo1)[i] = (*hijo2)[i];
		(*hijo2)[i] = h;
	}
	
}
void crossover3(int **hijo1, int **hijo2, double cruza_p){
	//printf("puntos cruza: ");
	for (int i = 0; i < N-2; ++i)
	{
		double r = rndreal(0.0, 1.0);
		if(r < cruza_p){
			//printf("%d, ", i);
			int h = (*hijo1)[i];
			(*hijo1)[i] = (*hijo2)[i];
			(*hijo2)[i] = h;
		}
	}
	
}

void mutation1(int **secuence/*secuencia del arbol*/){
	//se selecciona la posicion aleatoria de la secuencia a mutar
	int random_index = rnd(0, N-3);
	//printf("mut1=%d\n",random_index );
	//printf("random_index=%d, ",random_index);

	//se asigna un valor de secuencia en el rango de 0 a N-1
	//en la posicion seleccionada
	(*secuence)[random_index] = rnd(0, N-1);

	//printf("mutation=%d\n",tree_secuence[random_index]);
}
void mutation2(int **secuence){
	//se selecciona la posicion aleatoria de la secuencia a mutar
	int random_index1 = rnd(0, N-3), random_index2;

	do{random_index2 = rnd(0,N-3);}while(random_index2 == random_index1);
	//printf("mut1=%d, mut2=%d\n",random_index1, random_index2 );

	(*secuence)[random_index1] = rnd(0, N-1);
	(*secuence)[random_index2] = rnd(0, N-1);

}
void mutation3(int **secuence, int fit_global){
	//se selecciona la posicion aleatoria de la secuencia a mutar
	int random_index1 = rnd(0, N-3), random_index2;
	
	//print_secuence(secuence);
	//do{random_index2 = rnd(0,N-3);}while(random_index2 == random_index1);
	int x = (*secuence)[random_index1];
	//printf("aqui\n");
	//int y = tree_secuence[random_index2];
	long fit_local = 999999999;
	//print_secuence(secuence);
	int loc_i=x;
	int rompe = 0;

	for (int i = 0; i < N; ++i)
	{

		if(i != x){
			(*secuence)[random_index1] = i;


			int fit = evaluation((*secuence));
			if(fit < fit_local){
				loc_i = i;
				fit_local = (long)fit;
			}

			if(fit < fit_global){
				return;
				//print_secuence(secuence);
				//return secuence;
			}
		}

		
	}

	//print_secuence(secuence);
	(*secuence)[random_index1] = loc_i;
	//printf("aqui\n");
}

//-------------------EVALUATION--------------------
int sum_subtree_demands(int subroot, int **matrix){
	int sum = demandas[subroot];
	//printf("-->subroot: %d = %d", subroosum);
	nodes[subroot] = 0;
	for (int i = 0; i < N; ++i)
	{
		if(matrix[i][subroot] > 0 && nodes[i] == 1 && i != CENTER_NODE){
			
			sum += sum_subtree_demands(i, matrix);
		}
	}

	return sum;
}
int **get_maximum_tree(){
	//maximum_tree = (int**)malloc(sizeof(int*)*(N-1));
	for (int i = 0; i < N-1; ++i){
		//maximum_tree[i] = (int*)malloc(sizeof(int)*2);
		maximum_tree[i][0] = i;

		int max = 0;
		int max_node = 0;
		for (int j = i+1; j < N; ++j){
			if(cost_matrix[i][j] > max){
				max = cost_matrix[i][j];
				max_node = j;
			}
		}
		maximum_tree[i][1] = max_node;
	}
	return maximum_tree;
}
int get_tree_cost(int **tree){
	int cost = 0;
	for (int i = 0; i < N-1; ++i)
	{
		int ci = tree[i][0];
		int cj = tree[i][1];
		
		cost += cost_matrix[ci][cj];
	}

	return cost;
}
int get_violation(int **tree){
	//se obtienen todas las subraices (nodos adyacentes al nodo 0)
	
	int *subroots = get_subroots(tree);


    new_cost_matrix = get_cost_matrix(tree);
    for (int i = 0; i < N; ++i)
    	nodes[i] = 1;

    //printf("violation\n");

    //se calculan el total de demandas por cada subarbol
	int demands_subroots[num_subroots];
	int violation = 0;



	//printf("--------------------------------------------------------------\n");
    for (int i = 0; i < num_subroots; ++i){
    	demands_subroots[i] = sum_subtree_demands(subroots[i], new_cost_matrix);
    	//printf("Total demand of subroot node(%d) = %d of %d\n", subroots_nodes[i], demands_subroots[i], Q);

    	if(demands_subroots[i] > Q /*&& demands_subroots[i] > max_violation*/){
    		//max_violation = demands_subroots[i];
    		violation += (demands_subroots[i] - Q);
    	}
    }
    //------liberacion de memoria----
    free(subroots); subroots = NULL;
    /*for (int i = 0; i < N-1; ++i)
    	free(new_cost_matrix[i]);
    free(new_cost_matrix);
    new_cost_matrix=NULL;*/

    return violation;

}
void print_tree(int**);
int evaluation(int *secuence){

	tree = get_tree(secuence);
	//get_tree(secuence);

    //print_maximum_tree(maximum_tree);
    //print_tree(tree_links, N-1);

    //int *secuence_maximum_tree = get_secuence(maximum_tree, N-1);

    //print_secuence(secuence_maximum_tree, N-2);

	//printf("ERROR 2\n");

    int cost_tree = get_tree_cost(tree);



    //printf("Cost Tree = %d\t", cost_tree);
    //printf("Cost Maximum Tree = %d\n", cost_maximum_tree);
    //print_tree(tree);
    int violation = get_violation(tree);

    //printf("evalua\n");
    //printf("Violation = %d\n", violation);

    //printf("Evaluation = %d\n", cost_tree + violation*cost_maximum_tree);

	//print_secuence(tree_secuence, long_secuence);
	//print_tree(tree_links, long_secuence+1);

	//for (int i = 0; i < N-1; ++i)
	//	free(tree[i]);
	//free(tree);	tree=NULL; 

	/*for (int i = 0; i < N-1; ++i)
		free(maximum_tree[i]);
	free(maximum_tree);	maximum_tree=NULL;*/


	return cost_tree + (violation*cost_maximum_tree);
}

//-------------------MUTACION SELECCION---------------
int **get_best_padres_union_hijos(int **PADRES_HIJOS, int p, int h){

	//se declara el vector que almacena los mejores padres

	if(padres == NULL)
		createMatrix(&padres, p, N-2);

	int *fitness = NULL;
	createVector(&fitness, p+h);
	
	for (int i = 0; i < p+h; ++i)
		fitness[i] = evaluation(PADRES_HIJOS[i]);
	
	for (int i = 0; i < (p+h); ++i)
	{
		for (int j = 0; j < (p+h)-1; ++j)
		{
			if(fitness[j] > fitness[j+1]){
				int aux = fitness[j];
				fitness[j] = fitness[j+1];
				fitness[j+1] = aux;

				int *sec = PADRES_HIJOS[j];
				PADRES_HIJOS[j] = PADRES_HIJOS[j+1];
				PADRES_HIJOS[j+1] = sec;
			}
		}
	}

	free(fitness);
	fitness=NULL;

	//se almacenan los mejores p padres
	for (int i = 0; i < p; ++i){
		padres[i] = PADRES_HIJOS[i];
		//printf("%f, %d\n",evaluation(padres[i]), get_tree_cost(get_tree(padres[i])));
	}

	return padres;

}

int **get_best_hijos(int **HIJOS, int p, int h){
	//se declara el vector que almacena los mejores padres
	if(padres == NULL)
		createMatrix(&padres, p, N-2);

	int *fitness = NULL;
	createVector(&fitness, h);
	
	for (int i = 0; i < h; ++i)
		fitness[i] = evaluation(HIJOS[i]);
	
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < h-1; ++j)
		{
			if(fitness[j] > fitness[j+1]){
				int aux = fitness[j];
				fitness[j] = fitness[j+1];
				fitness[j+1] = aux;

				int *sec = HIJOS[j];
				HIJOS[j] = HIJOS[j+1];
				HIJOS[j+1] = sec;
			}
		}
	}
	free(fitness);
	fitness = NULL;

	//se almacenan los mejores p padres
	for (int i = 0; i < p; ++i){
		padres[i] = HIJOS[i];
		//printf("%f, %d\n",evaluation(padres[i]), get_tree_cost(get_tree(padres[i])));
	}

	return padres;
}

int Torneo(int **padres, int N_PADRES, int n){

    //-----Torneo t------
    int p1 = rnd(0, N_PADRES-1), p2; //se selecciona un padre aleatorio de la poblacion

    for (int i = 0; i < n-1; ++i)
    {
        //int p2;
        do{
            p2 = rnd(0, N_PADRES-1); //se selecciona un padre aleatorio de la poblacion
        }while(p2 == p1);

        //printf("p1=%d p2=%d\n", p1,p2);
        int fev_p1 = evaluation(padres[p1]);
        int fev_p2 = evaluation(padres[p2]);

        //printf("p1=%d ev=%f, p2=%d ev=%f\n",p1, fev_p1, p2, fev_p2 );

        if(fev_p2 < fev_p1){
            p1 = p2;
            //printf("best=%d\n", p1);
        }
    }

    return p1;

}

//-----------PRINTS-------------

//imprime los enlaces de un arbol dado
void print_tree (int **tree){
	printf("Links of Tree:\n");
	for (int i = 0; i < N-1; ++i)
		printf("(%d, %d)", tree[i][0], tree[i][1] );
	printf("\n\n");
}

//imprime una secuencia de arbol
void print_secuence(int *secuence){
	printf("Secuence: ");
	for (int i = 0; i < N-2; ++i)
		printf("%d,", secuence[i]);
	printf("\n");
}

void print_subroots(int *subroots){
	printf("Subroots: ");
	for (int i = 0; i < num_subroots; ++i)
		printf("%d, ", subroots[i]);
	printf("\n");
}
void print_demands(){
	printf("Demands: ");
	for (int i = 0; i < N; ++i)
		printf("%d, ", demandas[i]);
	printf("\n");
}
void print_adyacent_cost(){
	printf("Adyacent Cost:\n");
	for (int i = 0; i < N; ++i){
		printf("FILA %d: ", i);
		for (int j = 0; j < N; ++j)
			printf("%d,", cost_matrix[i][j]);
		printf("\n");
	}
}
//------------------