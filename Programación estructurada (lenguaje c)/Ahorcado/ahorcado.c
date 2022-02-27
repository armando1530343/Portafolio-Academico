#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void agrega_palabras(){

	FILE * nivel = NULL;

	system("cls");
	char palabra[20];
	printf("Nueva palabra: ");
	scanf(" %[^\n]", palabra);
    int contador=0;
	for (int i=0; i<20; ++i){
		if(palabra[i] == 0)
   			break;
   	else
   		contador++;
	}

	if (contador <=4)
		nivel = fopen("nivel1.txt","a");
	else if (contador >=5 && contador<=10)
        nivel = fopen("nivel2.txt","a");   
    else 
     	nivel = fopen("nivel3.txt","a");

    fprintf(nivel, "%s\n", palabra );
    fclose(nivel);

	system("pause");
}
void juego(int nivel){
	
	FILE * archivo = NULL;
	
	

	int numero_palabras = 0;
	

	if(nivel == 1)
		archivo = fopen("nivel1.txt", "r");	
	else if(nivel == 2)
		archivo = fopen("nivel2.txt", "r");	
	else
		archivo = fopen("nivel3.txt", "r");	

	char palabra_escogida[20];

	while(!feof(archivo)){
		fscanf(archivo, "%s", palabra_escogida);//esta linea no sirve para nada, pero no se debe borrar porque se cicla
		numero_palabras++;
	}

	int indice = rand() % numero_palabras + 1;	

	int linea = 1;
	while(!feof(archivo)){
		if(linea == indice){
			fscanf(archivo, "%s", palabra_escogida);
			break;
		}
		linea++;
	}

	char palabra_oculta[40];
	int numero_letras = 0;
	int j = 0;
	for (int i = 0; i < 20; ++i)
	{
		if(palabra_escogida[i] == 0)
			break;

		numero_letras ++;
		palabra_oculta[j] = '_';
		palabra_oculta[j+1] = ' ';

		j += 2;
	}


	int numero_errores = 0;
	int numero = numero_letras;
	int salir = 0;
	
	do{

		system("cls");
		printf("---- AHORCADOS-----\n\n");
		
		printf("%s\n\n", palabra_oculta);
		if(numero_letras == 0 || numero_errores == 6)
			salir = 1;

		if(salir == 0){
			char letra;
			printf("Adivina una letra: "); scanf(" %c", &letra);

			//printf("numero: %d\n", numero);

			//printf("letra: %c", letra);
			
			int existe = 0;

			for (int i = 0; i < numero; ++i)
			{
				//printf("%c", palabra_escogida[i]);
				if(palabra_escogida[i] == letra){

					palabra_oculta[i*2] = letra;
					numero_letras --;
					existe = 1;
				}
				if(i == numero-1 && existe == 0){
					numero_errores ++;
					
				}
				//if(numero_errores == 6)
					//break;
			}
			printf("Errores: %d/6\n", numero_errores );
		}
	}
	while(salir == 0);

	if(numero_letras == 0)
		printf("\nHAZ GANADO !!!\n");
	else
		printf("\nHAZ PERDIDO !!!\n");

	system("pause");
	
}

void interfaz(){

	system("cls");
	int opc;
	do{
		printf("1.Nivel 1\n2.Nivel 2\n3. Nivel 3\n4.Salir\nElige:");
		scanf("%d", &opc);


		switch(opc){
			case 1:
				juego(1);
				break;
			case 2:
				juego(2);
				break;
			case 3:
				juego(3);
				break;

			default:break;

		}

	}
	while(opc != 4);
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	
	FILE * palabras = fopen("palabras.txt", "a");

	int opc;

	do{
		printf("1.Añadir palabra\n2.Jugar\n3.Salir\nELige:");
		scanf("%d", &opc);

		switch(opc){
			case 1:
				agrega_palabras();
				break;
			case 2:
				interfaz();
				break;
			default: break;
		}
	}
	while(opc != 3);	

	return 0;
}
 


