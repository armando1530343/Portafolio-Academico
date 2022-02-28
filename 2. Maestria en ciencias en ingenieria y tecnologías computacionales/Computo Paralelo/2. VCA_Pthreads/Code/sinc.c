#include <stdio.h>
#include <stdlib.h>

int k[5] = {500, 800, 1000, 1500, 2000};
int t = 2;
int v[5] = {5, 6, 7, 8 ,9};
int hilos[8] = {1,2,4,8,16,32,64,128};

int main(int argc, char const *argv[])
{

	FILE *file = fopen("Tiempos/run_parallel.txt", "w");

	for (int i = 0; i < 5; ++i)//instancias
	{
		for (int j = 0; j < 8; ++j)//numero de hilos
		{
			for (int z = 0; z < 10; ++z)
			{
				fprintf(file, "./VCA_parallel %d 2 %d %d\n", k[i], v[i], hilos[j]);
			}
		}

	}	
	fclose(file);

	file = fopen("Tiempos/run_serial.txt", "w");
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			fprintf(file, "./VCA_serial %d 2 %d\n", k[i], v[i]);
		}
	}

	fclose(file);


	/* code */
	return 0;
}