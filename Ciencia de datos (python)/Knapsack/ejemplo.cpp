#include <stdio.h>
#include <string.h>

using namespace std;

class animal{

	animal(){

	}

	int correr(string a){
		cout<<"Corriendo: "<< a <<endl;
	}
	int dormir(){

	}
	int comer(){

	}
};


int main(){

	int a;
	char b;

	animal an1 = animal();
	an1.correr("perro");
	return 0;
}