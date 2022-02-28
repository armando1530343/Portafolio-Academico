#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX_DATOS 100

struct Curp{
	char apellido_paterno[20];
	char apellido_materno[20];
	char mes[20];
	char nombres[50];
	/*Fecha*/
	char anio[4];
	char dia[2];
	
	char genero[20];
	char entidad_federativa[50];

	char CURP[16];	
};
//esta funcion obtiene la primer letra del apellido paterno
//recibe como parametro una cadena (apellido paterno)
//retorno de tipo char ya que se espera un solo caracter (letra)
char primer_letra_cadena(char *apellido){
	return apellido[0];
}
//esta funcion obtiene la primer vocal del apellido paterno
//recibe como parametro una cadena (apellido paterno)
//retorno de tipo char ya que se espera un solo caracter (letra)
char primer_vocal_apellido_paterno(char *apellido_paterno){
	int i;
	//ciclo que recorre la cadena de apellido de tamaño 20
	for (i = 0; i < 20; i++)
	{
		//si durante el recorrido de las posiciones se encuentra con alguna vocal entonces
		//la funcion retorna esa posicion (letra) y se sale del ciclo ya que las demas pocisiones 
		//ya o se ocuparan
		if (apellido_paterno[i] == 'a'||apellido_paterno[i] == 'e'||apellido_paterno[i] == 'i'||
			apellido_paterno[i] == 'o'||apellido_paterno[i] == 'u'||apellido_paterno[i] == 'A'||
			apellido_paterno[i] == 'E'||apellido_paterno[i] == 'I'||apellido_paterno[i] == 'O'||
			apellido_paterno[i] == 'U')
		{
			return apellido_paterno[i];
			break;
		}
	}
}
char consonante(char *cadena, int digito){
	int i, n = 0, v = 0;
	//ciclo que recorre la cadena de apellido de tamaño 20
	for (i = 0; i < 20; i++)
	{
		//si durante el recorrido de las posiciones se encuentra con alguna vocal entonces
		//la funcion retorna esa posicion (letra) y se sale del ciclo ya que las demas pocisiones 
		//ya o se ocuparan
		if (cadena[i] != 'a' && cadena[i] != 'e'&& cadena[i] != 'i'  &&
			cadena[i] !='o'  && cadena[i] != 'u'&& cadena[i]  !='A'  &&
			cadena[i] !='E'  && cadena[i] != 'I'&& cadena[i]  != 'O' &&			
			cadena[i] != 'U')
		{
			//n++;
			if(v == 1){
				return cadena[i];
				break;
			}
			/*else if(n == 2){
				return cadena[i];
				break;
			}*/
		}
		else
			v++;
	}
}
char* fecha_nac(char *fecha){
	char *digitos = malloc(6);

	char dia[2];
	char mes[20]; 
	char anio[4];
	int i, diagonales = 0, m = 0, a = 0;

	//TODO QUIERES
	//se rellenan las siguientes variables con valores nulos (0) para que no guarden valores basura
	for (i = 0; i < 20; ++i){mes[i] = 0;}
	for (i = 0; i < 2; ++i){dia[i] = 0;}
	
	for (i = 0; i < 40; ++i){
		if(fecha[i] == '/'){
			diagonales++;
			continue;
		}
		if(diagonales == 0)
			dia[i] = fecha[i];
		else if(diagonales == 1){
			mes[m] = fecha[i];
			m++;
		}
		else if(diagonales == 2){
			anio[a] = fecha[i];
			//printf("mes: %d %c\n", a, fecha[i]);	
			a++;
			if(a==4) break;
		}
	}
	//printf("mes: %s\n", mes);
	//digitos del anio (ultimos 2)
	digitos[0] = anio[2];
	digitos[1] = anio[3];
	//digitos del mes
	//strcmp() es una funcion que compara dos cadenas. Si el resultado es igual a 0 significa que las cadenas son iguales y si es 
	//diferente de 0 las cadenas son diferentes
	if(strcmp(mes, "enero") == 0){digitos[2] = '0';digitos[3] = '1';}
	if(strcmp(mes, "febrero") == 0){digitos[2] = '0';digitos[3] = '2';}
	if(strcmp(mes, "marzo") == 0){digitos[2] = '0';digitos[3] = '3';}
	if(strcmp(mes, "abril") == 0){digitos[2] = '0';digitos[3] = '4';}
	if(strcmp(mes, "mayo") == 0){digitos[2] = '0';digitos[3] = '5';}
	if(strcmp(mes, "junio") == 0){digitos[2] = '0';digitos[3] = '6';}
	if(strcmp(mes, "julio") == 0){digitos[2] = '0';digitos[3] = '7';}
	if(strcmp(mes, "agosto") == 0){digitos[2] = '0';digitos[3] = '8';}
	if(strcmp(mes, "septiembre") == 0){digitos[2] = '0';digitos[3] = '9';}
	if(strcmp(mes, "octubre") == 0){digitos[2] = '1';digitos[3] = '0';}
	if(strcmp(mes, "noviembre") == 0){digitos[2] = '1';digitos[3] = '1';}
	if(strcmp(mes, "diciembre") == 0){digitos[2] = '1';digitos[3] = '2';}

	//digitos del dia
	//si la variable 'dia' solo tiene ocupada la primera posicion, es decir que solo se a ingresado un digito,
	//entonces entra a la condicion del if para agregar un cero antes del digito. Si ocupa las dos posiciones
	//entonces se guardan normal en los dos digitos siguientes.
	if(dia[1] == 0){
		digitos[4] = '0';
		digitos[5] = dia[0];
	}
	else{
		digitos[4] = dia[0];
		digitos[5] = dia[1];	
	}

	return digitos;	
}
char* entidad_federativa(char *entidad){
	char *digito=malloc(2);

	char claves[32][2];
	int i = 0;

	FILE *archivo = fopen("claves.txt", "rt");
	for(i = 0; i < 32; i++){
		//fread(&(claves[i]), sizeof(char), 1, archivo);
		fscanf(archivo, "%s", claves[i]);
		//claves[i][0] = claves[i][0];
		//claves[i][1] = claves[i][1];
		//printf("%s\n", claves[i]);
		//fgets(claves[i],2,archivo);
		
	}
    if(strcmp(entidad, "aguascalientes") == 0){digito[0] = claves[0][0]; digito[1] = claves[0][1];}
    if(strcmp(entidad, "baja california") == 0){digito[0] = claves[1][0]; digito[1] = claves[1][1];}
    if(strcmp(entidad, "baja california sur") == 0){digito[0] = claves[2][0]; digito[1] = claves[2][1];}
    if(strcmp(entidad, "campeche") == 0){digito[0] = claves[3][0]; digito[1] = claves[3][1];}
    if(strcmp(entidad, "coahuila") == 0){digito[0] = claves[4][0]; digito[1] = claves[4][1];}
    if(strcmp(entidad, "colima") == 0){digito[0] = claves[5][0]; digito[1] = claves[5][1];}
    if(strcmp(entidad, "chiapas") == 0){digito[0] = claves[6][0]; digito[1] = claves[6][1];}
    if(strcmp(entidad, "chihuahua") == 0){digito[0] = claves[7][0]; digito[1] = claves[7][1];}
    if(strcmp(entidad, "distrito federal") == 0){digito[0] = claves[8][0]; digito[1] = claves[8][1];}
    if(strcmp(entidad, "durango") == 0){digito[0] = claves[9][0]; digito[1] = claves[9][1];}
    if(strcmp(entidad, "guanajuato") == 0){digito[0] = claves[10][0]; digito[1] = claves[10][1];}
    if(strcmp(entidad, "guerrero") == 0){digito[0] = claves[11][0]; digito[1] = claves[11][1];}
    if(strcmp(entidad, "hidalgo") == 0){digito[0] = claves[12][0]; digito[1] = claves[12][1];}
    if(strcmp(entidad, "jalisco") == 0){digito[0] = claves[13][0]; digito[1] = claves[13][1];}
    if(strcmp(entidad, "mexico") == 0){digito[0] = claves[14][0]; digito[1] = claves[14][1];}
    if(strcmp(entidad, "michoacan") == 0){digito[0] = claves[15][0]; digito[1] = claves[15][1];}
    if(strcmp(entidad, "morelos") == 0){digito[0] = claves[16][0]; digito[1] = claves[16][1];}
    if(strcmp(entidad, "nayarit") == 0){digito[0] = claves[17][0]; digito[1] = claves[17][1];}
    if(strcmp(entidad, "nuevo leon") == 0){digito[0] = claves[18][0]; digito[1] = claves[18][1];}
    if(strcmp(entidad, "oaxaca") == 0){digito[0] = claves[19][0]; digito[1] = claves[19][1];}
    if(strcmp(entidad, "puebla") == 0){digito[0] = claves[20][0]; digito[1] = claves[20][1];}
    if(strcmp(entidad, "queretaro") == 0){digito[0] = claves[21][0]; digito[1] = claves[21][1];}
    if(strcmp(entidad, "quintana roo") == 0){digito[0] = claves[22][0]; digito[1] = claves[22][1];}
    if(strcmp(entidad, "san luis potosi") == 0){digito[0] = claves[23][0]; digito[1] = claves[23][1];}
    if(strcmp(entidad, "sinaloa") == 0){digito[0] = claves[24][0]; digito[1] = claves[24][1];}
    if(strcmp(entidad, "sonora") == 0){digito[0] = claves[25][0]; digito[1] = claves[25][1];}
    if(strcmp(entidad, "tabasco") == 0){digito[0] = claves[26][0]; digito[1] = claves[26][1];}
    if(strcmp(entidad, "tamaulipas") == 0){digito[0] = claves[27][0]; digito[1] = claves[27][1];}
    if(strcmp(entidad, "tlaxcala") == 0){digito[0] = claves[28][0]; digito[1] = claves[28][1];}
    if(strcmp(entidad, "veracruz") == 0){digito[0] = claves[29][0]; digito[1] = claves[29][1];}
    if(strcmp(entidad, "yucatan") == 0){digito[0] = claves[30][0]; digito[1] = claves[30][1];}
    if(strcmp(entidad, "zacatecas") == 0){digito[0] = claves[31][0]; digito[1] = claves[31][1];}

    fclose(archivo);


   	return digito ;

}

int main(int argc, char const *argv[]){
	int opc, opc2, i, diagonales, m, a;
	int cont = 0;
	char *digitos_fecha, *entidad;

	char fecha[40], dia[2], mes[15], anio[4];

	char b_curp[20], b_apellido[20], b_fecha[20], b_entidad[20];

	char dato1[20], dato2[20], dato3[20], dato4[50], dato5[20], dato6[20], dato7[20];

	char cifra[4];

	for(i = 0; i < 20; i++){
		dato2[i] = 0;
		dato5[i] = 0;
		dato7[i] = 0;
		b_apellido[i]=0, b_fecha[i]=0, b_entidad[i]=0;
	}
	for(i = 0; i < 16; i++){
		b_curp[i] = 0;
		dato1[i] = 0;
	}

	struct Curp datos[MAX_DATOS];

	FILE *archivo_datos, *palabras;
	char palabras_inconvenientes[81][4];

	do{
		system("cls");
		printf("<<-- CURP -->>\n\n");
		printf("1.Registrar CURP\n");
		printf("2.Busqueda\n");
		printf("3.Salir\n");
		printf("Elige Opcion: "); scanf("%d", &opc);

		switch(opc){
			case 1: 
				system("cls");
			    printf("<<-- CURP -->>\n\n");
			    printf("-- Obtener curp --\n");
			    printf("Apellido Paterno: "); scanf(" %[^\n]", datos[cont].apellido_paterno);
			    printf("Apellido Materno: "); scanf(" %[^\n]", datos[cont].apellido_materno);
			    printf("Nombre(s) (Separar con '-'): "); scanf(" %[^\n]", datos[cont].nombres);
			    
			    printf("Fecha: "); scanf(" %[^\n]", fecha);
			    //printf("(Fecha Nacimiento) Dia: "); scanf(" %[^\n]", datos[cont].dia);
			    //printf("(Fecha Nacimiento) Mes: "); scanf(" %[^\n]", datos[cont].mes);			    
			    //printf("(Fecha Nacimiento) Anio: "); scanf(" %[^\n]", datos[cont].anio);
			    printf("Genero: "); scanf(" %[^\n]", datos[cont].genero);
			    printf("Entidad: "); scanf(" %[^\n]", datos[cont].entidad_federativa);
			    //printf("mes:%s\n", datos[cont].dia);
			    digitos_fecha = fecha_nac(fecha);
			    //printf("fecha:%s\n", digitos_fecha);

			    //obtencion del primer digito de la CURP
			    datos[cont].CURP[0] = primer_letra_cadena(datos[cont].apellido_paterno);
		        datos[cont].CURP[1] = primer_vocal_apellido_paterno(datos[cont].apellido_paterno);
			    datos[cont].CURP[2] = primer_letra_cadena(datos[cont].apellido_materno);
			    datos[cont].CURP[3] = primer_letra_cadena(datos[cont].nombres);

			    datos[cont].CURP[4] = digitos_fecha[0];
			    datos[cont].CURP[5] = digitos_fecha[1];
			    datos[cont].CURP[6] = digitos_fecha[2];
			    datos[cont].CURP[7] = digitos_fecha[3];
			    datos[cont].CURP[8] = digitos_fecha[4];
			    datos[cont].CURP[9] = digitos_fecha[5];
			   
			    //seleccion del genero
			    if (strcmp(datos[cont].genero,"masculino")==0) {datos[cont].CURP[10]='H';}
                if (strcmp(datos[cont].genero,"femenino")==0) {datos[cont].CURP[10]='M';}

                entidad=entidad_federativa(datos[cont].entidad_federativa);
                //printf("entidad:%s\n", entidad);
                datos[cont].CURP[11]=entidad[0];
                datos[cont].CURP[12]=entidad[1];
                datos[cont].CURP[13]=consonante(datos[cont].apellido_paterno, 2);
                datos[cont].CURP[14]=consonante(datos[cont].apellido_materno, 2);
                datos[cont].CURP[15]=consonante(datos[cont].nombres, 1);
                //transforma minusculas a
			    for (i = 0; i < 16; ++i){
			    	if(datos[cont].CURP[i] >= 97 && datos[cont].CURP[i] <= 122)
			    		datos[cont].CURP[i] -= 32;
			    }

                cifra[0] = datos[cont].CURP[0];
                cifra[1] = datos[cont].CURP[1];
                cifra[2] = datos[cont].CURP[2];
                cifra[3] = datos[cont].CURP[3];

                palabras = fopen("palabras_inconvenientes.txt", "rt");
                for(i = 0; i < 81; i++){
                	fscanf(palabras, "%s", palabras_inconvenientes[i]);
                	//printf("%s\n", palabras_inconvenientes[i]);
                	if (strcmp(cifra, palabras_inconvenientes[i])==0){
                		datos[cont].CURP[1] = 'X';
                		break;
                	}

                }    

                fclose(palabras);

        		printf("CURP: ");
        		for (i = 0; i < 16; ++i)
        		{
        			printf("%c", datos[cont].CURP[i]);
        			/* code */
        		}
        		printf("\n");

                archivo_datos = fopen("archivo_datos.txt", "a");
                fprintf(archivo_datos, "%d %s %s %s %s %s %s %s\n",0,datos[cont].CURP, datos[cont].apellido_paterno, datos[cont].apellido_materno,
                datos[cont].nombres, fecha, datos[cont].genero, datos[cont].entidad_federativa );
                fclose(archivo_datos);
			    //printf("mes:%s\n", datos[cont].mes);
			    //if(strcmp(datos[cont].mes, "enero") == 0){}

			    //printf("	primara letra: %c\n", datos[cont].CURP[2]);
			    system("pause");
			    cont ++;

			    break;
			case 2:	
				system("cls");
			    printf("<<-- BUSCAR PERSONA POR -->>\n\n");
			    printf("1.CURP\n");
			    printf("2.Apellido Paterno\n");
			    printf("3.Fecha de Nacimiento\n");
			    printf("4.Entidad Federativa\n"); 
			    printf("Elige Opcion: "); scanf("%d", &opc2);

			    archivo_datos = fopen("archivo_datos.txt", "r");
			    if(archivo_datos == NULL) break;
			    char x[2];

			    switch(opc2){
			    	case 1:
			    		system("cls");
			    		printf("<<-- BUSCAR PERSONA POR -->>\n\n");
			    		printf("Ingresa CURP: "); scanf(" %[^\n]", b_curp);
			    		printf("\n");
			    		while(!feof(archivo_datos)){
			    			fscanf(archivo_datos, "%s %s %s %s %s %s %s %s\n",x, dato1, dato2, dato3, dato4, dato5, dato6, dato7);
			    			//printf("CURP: %s\n", b_curp);
			    			if(strcmp(b_curp, dato1) == 0){
			    				printf("-------------------------------------------------\n");
			    				printf("CURP: %s\n", dato1);
			    				printf("Apellido Paterno: %s\n", dato2);
			    				printf("Apellido Materno: %s\n", dato3);
			    				printf("Nombre(s): %s\n", dato4);
			    				printf("Fecha de Nacimiento: %s\n", dato5);
			    				printf("Genero: %s\n", dato6);
			    				printf("Entidad Federativa: %s\n", dato7);
			    			}
			    		}
			    		system("pause");
			    		break;
			    	case 2:
			    		system("cls");
			    		printf("<<-- BUSCAR PERSONA POR -->>\n\n");
			    		printf("Ingresa Apellido Paterno: "); scanf(" %[^\n]", b_apellido);
			    		printf("\n");
			    		while(!feof(archivo_datos)){
			    			fscanf(archivo_datos, "%s %s %s %s %s %s %s %s\n",x, dato1, dato2, dato3, dato4, dato5, dato6, dato7);
			    			//printf("CURP: %s\n", b_curp);
			    			if(strcmp(b_apellido, dato2) == 0){
			    				printf("-------------------------------------------------\n");
			    				printf("CURP: %s\n", dato1);
			    				printf("Apellido Paterno: %s\n", dato2);
			    				printf("Apellido Materno: %s\n", dato3);
			    				printf("Nombre(s): %s\n", dato4);
			    				printf("Fecha de Nacimiento: %s\n", dato5);
			    				printf("Genero: %s\n", dato6);
			    				printf("Entidad Federativa: %s\n", dato7);
			    			}
			    		}
			    		system("pause");
			    		break;
			    	case 3:
			    		system("cls");
			    		printf("<<-- BUSCAR PERSONA POR -->>\n\n");
			    		printf("Ingresa Fecha de Nacimiento: "); scanf(" %[^\n]", b_fecha);
			    		printf("\n");
			    		//printf("FECHA: %s\n", b_fecha);
			    		while(!feof(archivo_datos)){
			    			fscanf(archivo_datos, "%s %s %s %s %s %s %s %s\n",x, dato1, dato2, dato3, dato4, dato5, dato6, dato7);
			    			//printf("FECHA: %s\n", dato5);
			    			if(strcmp(b_fecha, dato5) == 0){
			    				printf("-------------------------------------------------\n");
			    				printf("CURP: %s\n", dato1);
			    				printf("Apellido Paterno: %s\n", dato2);
			    				printf("Apellido Materno: %s\n", dato3);
			    				printf("Nombre(s): %s\n", dato4);
			    				printf("Fecha de Nacimiento: %s\n", dato5);
			    				printf("Genero: %s\n", dato6);
			    				printf("Entidad Federativa: %s\n", dato7);
			    			}
			    		}
			    		system("pause");
			    		break;
			    	case 4:
			    		system("cls");
			    		printf("<<-- BUSCAR PERSONA POR -->>\n\n");
			    		printf("Ingresa Entidad Federativa: "); scanf(" %[^\n]", b_entidad);

			    		printf("\n");
			    		while(!feof(archivo_datos)){
			    			fscanf(archivo_datos, "%s %s %s %s %s %s %s %s\n",x, dato1, dato2, dato3, dato4, dato5, dato6, dato7);
			    			
			    			if(strcmp(b_entidad, dato7) == 0){
			    				printf("-------------------------------------------------\n");
			    				printf("CURP: %s\n", dato1);
			    				printf("Apellido Paterno: %s\n", dato2);
			    				printf("Apellido Materno: %s\n", dato3);
			    				printf("Nombre(s): %s\n", dato4);
			    				printf("Fecha de Nacimiento: %s\n", dato5);
			    				printf("Genero: %s\n", dato6);
			    				printf("Entidad Federativa: %s\n", dato7);
			    			}
			    		}
			    		system("pause");
			    		break;
			    }
			    fclose(archivo_datos);

			    break;
			default: opc = 3; break;
		}
	}
	while(opc != 3);
	return 0;
}
