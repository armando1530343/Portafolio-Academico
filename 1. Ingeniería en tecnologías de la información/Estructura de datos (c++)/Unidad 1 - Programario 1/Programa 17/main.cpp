#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    time_t tiempo;
    struct tm *t;
    tiempo = time(NULL);
    t=localtime(&tiempo);
    int day = t->tm_mday;
    int month = t->tm_mon+1;
    int year = t->tm_year+1900;

    int dia, mes, anio;

    cout<<"Fecha de Actual: "<<day<<"/"<<month<<"/"<<year<<endl;
    cout<<"Fecha de Nacimiento"<<endl;
    do{
        cout<<"Dia: ";cin>>dia;
    }
    while(dia<1||dia>31);
    do{
        cout<<"Mes: ";cin>>mes;
    }
    while(mes<1||mes>12);
    do{
        cout<<"Anio: ";cin>>anio;
    }
    while(anio<1900||anio>2017);

    int i, dias;
    int totalDias=0, a = anio;

    for(i=anio;i<=2017;i++){
        int meses[12]={31,59,90,120,151,181,212,243,273,304,334,365};
        if(anio%4==0){
            if(anio%100==0){
                if(anio%400==0){
                    dias = 366;
                }
                else{
                    dias = 365;
                }
            }
            else{
                dias = 366;
            }
        }
        else{
            dias = 365;
        }
        int j;
        if (dias == 366){
            for(j=2;j<=12;j++){
                meses[j]++;
            }
        }
        if(i==a){
            if(a==year){
                totalDias = totalDias + (day-dia);
            }
            else{
                totalDias = totalDias + (dias-(meses[mes-2]+dia));
            }
        }
        else if(i>a&&i<2017){
            totalDias = totalDias + dias;
        }
        else{
            totalDias = totalDias + meses[month-2] + day;
        }
        anio++;
    }
    cout<<"Edad en dias: "<<totalDias<<endl;

    return 0;
}
