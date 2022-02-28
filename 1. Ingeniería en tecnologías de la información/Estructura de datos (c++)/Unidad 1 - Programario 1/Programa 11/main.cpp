#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
float* ecuacion123(float, float, int);
float* ecuacion45(float*, float*, int);
int* despeje (int *, int *);

int main()
{
    float x[3],y[3];
    x[0]=-4; y[0]=1;
    x[1]=4; y[1]=-4;
    x[2]=7; y[2]=9;
    cout << "A("<<x[0]<<","<<y[0]<<")  B("<<x[1]<<","<<y[1]<<")  C("<<x[2]<<","<<y[2]<<")"<<endl;
    cout << "\n(x - h)2 + (y - k)2 = r2"<<endl;
    cout << "\n x2 - 2xh + h2 + y2 - 2yk + k2 = r2"<<endl;
    float inc1[3],inc2[3],inc3[3],*inc, *ec;
    int ec4[3],ec5[3];
    int des1[2], des2[2], *des;
    inc = ecuacion123(x[0],y[0],1);
    inc1[0]=inc[0]; inc1[1]=inc[1]; inc1[2]=inc[2];

    inc = ecuacion123(x[1],y[1],2);
    inc2[0]=inc[0]; inc2[1]=inc[1]; inc2[2]=inc[2];

    inc = ecuacion123(x[2],y[2],3);
    inc3[0]=inc[0]; inc3[1]=inc[1]; inc3[2]=inc[2];
    cout<<inc2[2]<<endl;
    ec = ecuacion45(inc1,inc2,4);
    ec4[0]=ec[0]; ec4[1]=ec[1]; ec4[2]=ec[2];
    ec = ecuacion45(inc2,inc3,5);
    ec5[0]=ec[0]; ec5[1]=ec[1]; ec5[2]=ec[2];

    des = despeje(ec4,ec5);
    des1[0]=des[0]; des1[1]=des[1];
    des = despeje(ec4,ec5);
    des2[0]=des[0]; des2[1]=des[1];

    cout<<ec4[1]<<" "<<ec4[2]<<endl;

    return 0;
}
float* ecuacion123(float x, float y, int i){
    float inc[3];
    inc[0]=(x*x)+(y*y);
    inc[1]=-2*x;
    inc[2]=-2*y;
    cout <<"\nEc"<<i<<" = "<<inc[0]<<" "<<inc[1]<<"h + h2 "<<inc[2]<<"k + k2 = r2"<<endl;
    return inc;
}
float* ecuacion45(float *inc1, float *inc2, int i){
    float inc[3], n, h, k;
    n = inc1[0]-inc2[0];
    h = inc1[1]-inc2[1];
    k = inc1[2]-inc2[2];
    inc[0]=n;
    inc[1]=h;
    inc[2]=k;
    cout <<"\nEc"<<i<<" : "<<inc[1]<<"h "<<inc[2]<<"k = "<< -inc[0]<<endl;
    return inc;
}
int* despeje (int *ec1, int *ec2){
    int i=1, j, k=1;
    int num[2], aux;
    float n=0, N;
    if(ec1[1]>ec2[1]){
        aux=ec2[1];
        while(true){
            ec2[1] = aux*i;

            if(ec2[1]%ec1[1]==0){
                num[1]=i;
                break;
            }
            else{i++;}
        }
        j = ec2[1]/ec1[1];
        num[0]=j;
    }
    else if(ec1[1]<=ec2[1]){
        aux=ec2[1];
        while(true){
            ec1[1] = aux*i;

            if(ec1[1]%ec2[1]==0){
                num[1]=i;
                break;
            }
            else{i++;}
        }
        j = ec1[1]/ec2[1];
        num[0]=j;
    }
    return num;
}
