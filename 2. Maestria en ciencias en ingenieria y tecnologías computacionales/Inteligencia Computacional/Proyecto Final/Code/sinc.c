#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void run_final(){

	char ins[20][200];

	printf("HOLAA\n");

	sprintf(ins[0], "ag_cmst.exe datasets/cm50r1.txt 200 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 1");
	sprintf(ins[1], "ag_cmst.exe datasets/cm50r1.txt 400 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 2");
	sprintf(ins[2], "ag_cmst.exe datasets/cm50r1.txt 800 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 3");
	sprintf(ins[3], "ag_cmst.exe datasets/cm50r1.txt 200 15 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 4");
	sprintf(ins[4], "ag_cmst.exe datasets/cm50r1.txt 400 15 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 5");
	sprintf(ins[5], "ag_cmst.exe datasets/cm50r1.txt 800 15 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 6");

	sprintf(ins[6], "ag_cmst.exe datasets/cm50r2.txt 200 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 7");
	sprintf(ins[7], "ag_cmst.exe datasets/cm50r2.txt 400 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 8");
	sprintf(ins[8], "ag_cmst.exe datasets/cm50r2.txt 800 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 9");
	sprintf(ins[9], "ag_cmst.exe datasets/cm50r2.txt 200 25 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 10");
	sprintf(ins[10], "ag_cmst.exe datasets/cm50r2.txt 400 25 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 11");
	sprintf(ins[11], "ag_cmst.exe datasets/cm50r2.txt 800 25 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 12");

	sprintf(ins[12], "ag_cmst.exe datasets/cm50r3.txt 200 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 13");
	sprintf(ins[13], "ag_cmst.exe datasets/cm50r3.txt 400 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 14");
	sprintf(ins[14], "ag_cmst.exe datasets/cm50r3.txt 800 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 15");
	sprintf(ins[15], "ag_cmst.exe datasets/cm50r3.txt 800 30 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 16");

	sprintf(ins[16], "ag_cmst.exe datasets/cm100r1.txt 200 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 17");
	sprintf(ins[17], "ag_cmst.exe datasets/cm100r1.txt 400 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 18");
	sprintf(ins[18], "ag_cmst.exe datasets/cm100r1.txt 800 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 19");
	sprintf(ins[19], "ag_cmst.exe datasets/cm100r2.txt 200 0 0.8 0.9 1 1000 3 1 3 1 1 0 0 5 20");

	
	for (int i = 0; i < 20; ++i)
	{
		
		//se recorren las ecuaciones diofanticas
		char f[100];
		sprintf(f, "R_FINAL2/run.txt", i+1);
		FILE *file = fopen(f, "a");
		for (int j = 0; j < 31; ++j){
			fprintf(file, "%s %d\n", ins[i], j+1);

		}
		fclose(file);
	}
	

}




int main(int argc, char const *argv[])
{	
	run_final();

	//run(ecuaciones);

	return 0;
}