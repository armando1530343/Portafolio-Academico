#include <iostream>

using namespace std;

template<typename Tipo>
Tipo* copiarArray(Tipo *vec1, Tipo *vec2, int tam){
    Tipo *aux=new Tipo(tam);
    int i, j=0;
    for(i=0;i<tam;i++){
        *(aux+i)=*(vec1+i);
    }
    vec1=new Tipo(tam*2);
    for(i=0;i<tam*2;i++){
        if(i<tam){
            *(vec1+i)=*(aux+i);
        }
        else{
            *(vec1+i)=*(vec2+j);
            j++;
        }
    }
    return vec1;
}
int main()
{
    int vec1[]={1,2,3}, i;
    int vec2[]={4,5,6};
    int *nuevoVec;
    cout<<"Vec1 = ["<<vec1[0]<<","<<vec1[1]<<","<<vec1[2]<<"]"<<endl;
    cout<<"Vec2 = ["<<vec2[0]<<","<<vec2[1]<<","<<vec2[2]<<"]"<<endl;
    nuevoVec=copiarArray(vec1,vec2,3);
    cout<<"Nuevo Vec1 = ["<<nuevoVec[0]<<","<<nuevoVec[1]<<","<<nuevoVec[2]<<","<<nuevoVec[3]<<","<<nuevoVec[4]<<","<<nuevoVec[5]<<"]"<<endl;
}
