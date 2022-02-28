#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main()
{
    int canibal_orilla1=3, misionero_orilla1=3, canibal_orilla2=0, misionero_orilla2=0;
    int orilla1=misionero_orilla1+canibal_orilla1, orilla2=misionero_orilla2+canibal_orilla2;
    int bote = 0, v=2, i;
    int opc;
    char per[2]={'-','-'};
    int aux;

    while(misionero_orilla2<3&&canibal_orilla2<3){

        system("cls");
        if(misionero_orilla2==3&&canibal_orilla2==3){cout<<"Has Ganado"<<endl;break;}

        cout<<"Orilla 1: Canibales = "<<canibal_orilla1<<"   Misioneros = "<<misionero_orilla1<<endl;
        cout<<"Orilla 2: Canibales = "<<canibal_orilla2<<"   Misioneros = "<<misionero_orilla2<<endl;
        if(v%2==0){i=1;}else{i=2;}
        cout<<"\nEstas en la orilla "<<i<<endl;
        cout<<"\nBote: "<<bote<<" ("<<per[0]<<","<<per[1]<<")"<<endl;
        if(i==1 && misionero_orilla2<canibal_orilla2 || i==2 && misionero_orilla1<canibal_orilla1){
                cout<<"\nPerdiste"<<endl;
                break;
            }
        if(bote==0){
            cout<<"\n1.Subir Canibal   2.Subir Misionero\nElige: ";
        }
        else if(bote<2&&bote>0){
            cout<<"\n1.Subir Canibal   2.Subir Misionero   3.Bajar Canibal   4.Bajar Misionero   5.Go\nElige: ";
        }
        else{
            cout<<"\n1.Bajar Canibal   2.Bajar Misionero   3.Go\nElige: ";
        }
        cin>>opc;

        if(opc==3 && bote==2 || opc==5){
            v++;

            continue;
        }
        if(opc==1 && bote<2){
            if(i==1){
                if(canibal_orilla1>0){
                    canibal_orilla1--;
                }
                else{continue;}
            }
            else{
                if(canibal_orilla1>0){
                    canibal_orilla1--;
                }
                else{continue;}
            }
            bote++;
            if(per[0]=='-'){
                per[0]='C';
            }
            else if(per[1]=='-'){
                per[1]='C';
            }
            //per[bote-1]='C';
            continue;
        }
        if(opc==2 && bote<2){
            if(i==1){
                if(misionero_orilla1>0){
                    misionero_orilla1--;
                }
                else{continue;}
            }
            else{
                if(misionero_orilla2>0){
                    misionero_orilla2--;
                }
                else{continue;}
            }
            bote++;
            if(per[0]=='-'){
                per[0]='M';
            }
            else if(per[1]=='-'){
                per[1]='M';
            }
            //per[bote-1]='M';
            continue;
        }
        if(opc==3||opc==1&&bote==2){
            if(i==1){
                if(canibal_orilla1<3){
                    canibal_orilla1++;
                }
                else{continue;}

            }
            else{
                if(canibal_orilla2<3){
                    canibal_orilla2++;
                }
                else{continue;}
            }
            bote--;
            if(per[0]=='C'){
                per[0]='-';
            }
            else if(per[1]=='C'){
                per[1]='-';
            }
            //per[bote]='-';
            continue;
        }
        if(opc==4||opc==2&&bote==2){
            if(i==1){
                if(misionero_orilla1<3){
                    misionero_orilla1++;
                }
                else{continue;}
            }
            else{
                if(misionero_orilla2<3){
                    misionero_orilla2++;
                }
                else{continue;}
            }
            bote--;
            //aux=per[bote];
            if(per[0]=='M'){
                per[0]='-';
            }
            else if(per[1]=='M'){
                per[1]='-';
            }
            //per[bote]='-';
            continue;
        }

        system("pause");
    }

    return 0;
}
