#include <cstdlib>
#include <iostream>
#include <math.h> 
#define MAX 10000

using namespace std;

void armarHeap (int *v,int a,int lim)
{
    int aux;
    //--------------------------------Arma heap comiemzo   
   for (int n=2;n<=pow(2,lim);n=n*2)
    {
        for (int i=a;i>=n;i--)
        {
            if (*(v+i)>*(v+(i/2))){aux=*(v+i);*(v+i)=*(v+(i/2));*(v+(i/2))=aux;}
        }
    }
    
    
  //--------------------------------Arma heap fin  
    
}

void revHeap (int *v,int a,int lim)// Revisa que se siga cumpliendo la condiciones para heap y corrige sino se cumple
{
    int aux;
    
    for (int i=1;i<=(MAX/2);i++)//  con 10000 datos aca ya no se traba
    {
        
        if((*(v+(i*2))>*(v+i))&&(a>=(i*2))){aux=*(v+(i*2));*(v+(i*2))=*(v+i);*(v+i)=aux;}
        if((*(v+(i*2)+1)>*(v+i))&&(a>=((i*2)+1))){aux=*(v+(i*2)+1);*(v+(i*2)+1)=*(v+i);*(v+i)=aux;}
    }
    
}


int main(int argc, char *argv[])
{
    int v[MAX];//={0,7,12,5,38,25,9,15};
    int aux,altura;
    altura=int(log2 (MAX-1)); //Altura del Heap de 0, 1 , 2 .......
    
    
    
     for(int i=0;i<MAX;i++)
    {
            v[i]=int(rand());
    }
    
    
    armarHeap (v,MAX-1,altura);
    
    for (int i=MAX-1;i>=2;i--)
        {
            if (v[1]>v[i]){aux=v[i];v[i]=v[1];v[1]=aux;revHeap (v,i-1,altura);}
            
        }
    
    for (int i=1;i<=(MAX-1);i++)
    {
        cout<<*(v+i)<<endl;
    }
    
    //cout<<"Listo guacho!! ya ordene todo por vos!!\n\n";
    system("PAUSE");
    return EXIT_SUCCESS;
}
