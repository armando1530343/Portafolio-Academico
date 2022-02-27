#include <iostream>

using namespace std;

int main()
{
    char *cad = new char;
    cin>>cad;
    int i=0, vocal=0;
    while(true){
        if(*(cad+i)!=NULL){
            switch(*(cad+i)){
                case 'a':vocal++;break;
                case 'e':vocal++;break;
                case 'i':vocal++;break;
                case 'o':vocal++;break;
                case 'u':vocal++;break;
            }
        }
        else{
            break;
        }
        i++;
    }
    cout<<"Vocales = "<<vocal;
}
