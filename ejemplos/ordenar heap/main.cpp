#include <cstdlib>
#include <iostream>

using namespace std;

void armarHeap (int *v,int a)
{
    int aux;
    //--------------------------------Arma heap comiemzo   
   for (int n=2;n<=4;n=n*2)
    {
        for (int i=a;i>=n;i--)
        {
            if (*(v+i)>*(v+(i/2))){aux=*(v+i);*(v+i)=*(v+(i/2));*(v+(i/2))=aux;}
        }
    }
    
    
  //--------------------------------Arma heap fin  
    
}

void revHeap (int *v,int a)
{
    int aux;
    
    for (int i=1;i<=3;i++)
    {
        if((*(v+(i*2))>*(v+i))&&(a>=(i*2))){aux=*(v+(i*2));*(v+(i*2))=*(v+i);*(v+i)=aux;}
        if((*(v+(i*2)+1)>*(v+i))&&(a>=(i*2)+1)){aux=*(v+(i*2)+1);*(v+(i*2)+1)=*(v+i);*(v+i)=aux;}
    }
}

//void niveles (int *v,)

int main(int argc, char *argv[])
{
    int v[8]={0,7,12,5,38,25,9,15};
    int aux;
    
    armarHeap (v,7);
    for (int i=7;i>=2;i--)
        {
            if (v[1]>v[i]){aux=v[i];v[i]=v[1];v[1]=aux;revHeap (v,i-1);}
            
        }
    
    for (int i=1;i<=7;i++)
    {
        cout<<*(v+i)<<endl;
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
