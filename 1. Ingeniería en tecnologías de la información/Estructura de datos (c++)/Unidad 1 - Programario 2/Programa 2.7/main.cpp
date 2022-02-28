#include <iostream>

using namespace std;

int main()
{
    int votos[5][4];
    int total=0, i, j, candidatos[4]={0,0,0,0};
    votos[0][0]=194; votos[0][1]=48; votos[0][2]=206; votos[0][3]=45;
    votos[1][0]=180; votos[1][1]=20; votos[1][2]=320; votos[1][3]=16;
    votos[2][0]=221; votos[2][1]=90; votos[2][2]=140; votos[2][3]=20;
    votos[3][0]=432; votos[3][1]=50; votos[3][2]=821; votos[3][3]=14;
    votos[4][0]=820; votos[4][1]=61; votos[4][2]=946; votos[4][3]=18;
    for(i=0;i<5;i++){
        for(j=0;j<4;j++){
            total+=votos[i][j];
            candidatos[j]+=votos[i][j];
        }
    }
    double porciento[4],porciento2[4];
    cout<<"Total de Votos = "<<total<<endl;
    porciento[0]=(100*candidatos[0])/total;
    porciento2[0]=porciento[0];
    cout<<"Candidato A: "<<candidatos[0]<<" = "<<porciento[0]<<"%"<<endl;
    porciento[1]=(100*candidatos[1])/total;
    porciento2[1]=porciento[1];
    cout<<"Candidato B: "<<candidatos[1]<<" = "<<porciento[1]<<"%"<<endl;
    porciento[2]=(100*candidatos[2])/total;
    porciento2[2]=porciento[2];
    cout<<"Candidato C: "<<candidatos[2]<<" = "<<porciento[2]<<"%"<<endl;
    porciento[3]=(100*candidatos[3])/total;
    porciento2[3]=porciento[3];
    cout<<"Candidato D: "<<candidatos[3]<<" = "<<porciento[3]<<"%"<<endl;

    int aux;
    for(i=0;i<4;i++){
        for(j=0;j<3;j++){
            if(porciento2[j]>porciento2[j+1]){
                aux=porciento2[j+1];
                porciento2[j+1]=porciento2[j];
                porciento2[j]=aux;
            }
        }
    }
    for(i=0;i<4;i++){
        if(porciento[i]==porciento2[3]){
            break;
        }
    }
    for(j=0;j<4;j++){
        if(porciento[j]==porciento2[2]){
            break;
        }
    }
    char letra, letra2;
        switch(i){
            case 0:letra='A'; break;
            case 1:letra='B'; break;
            case 2:letra='C'; break;
            case 3:letra='D'; break;
        }
        switch(j){
            case 0:letra2='A'; break;
            case 1:letra2='B'; break;
            case 2:letra2='C'; break;
            case 3:letra2='D'; break;
        }
    if(porciento[i]>=50){
        cout<<"Ganador: Candidato "<<letra<<endl;
    }
    else{
        cout<<"Candidatos a la Segunda Ronda: Candidato "<<letra<<" y Candidato "<<letra2<<endl;
    }
    return 0;
}
