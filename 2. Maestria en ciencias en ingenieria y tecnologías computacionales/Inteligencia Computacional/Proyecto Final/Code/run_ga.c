#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if(argc != 4){
		printf("Falta nombre del archivo\n");
		exit(0);
	}

	int inf = atoi(argv[2]);
	int sup = atoi(argv[3]);

	FILE *file = fopen(argv[1], "r");
	char linea[500];
	int i = 1;
	while(fgets(linea, 500, (FILE*)file)){

		if(i >= inf && i <= sup){
			printf("%s\tlinea:%d\n", linea,i);
			system(linea);
		}
		if(i > sup) break;		
		i++;
		//if(i==2)return 0;
	}

	fclose(file);

	return 0;
}