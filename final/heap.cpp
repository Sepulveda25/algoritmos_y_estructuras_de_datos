#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define max 10
 
using namespace std;
 
void swap (int &uno, int &dos)
{
        int aux;
        aux = uno;
        uno = dos;
        dos = aux;
        }
 
void comp_pad_hij(int *v, int p, int altu)
{
     if ((p*2 >= altu) || (((p*2)+1) >= altu)) cout<<"";
     else if(v[p] < v[p*2])
          {
              swap(v[p], v[p*2]);
              comp_pad_hij(v, p, altu);
              comp_pad_hij(v, p*2, altu);
          }
          else if(v[p] < v[(p*2)+1])
               {
                  swap(v[p], v[(p*2)+1]);
                  comp_pad_hij(v, p, altu);
                  comp_pad_hij(v, (p*2)+1, altu);
               }
               else comp_pad_hij(v, max, 0);
}
 
 
void heapsort (int *vector)
{
//--------------------- Armado de la Heap-------------------------------
        int u = max, v = u;
        while (v > 0)
        {
                bool house = true;
                u = v;
                while ((u > 1) && house)
                {                      
                                if (vector[u] > vector[u/2])
                                {
                                        int q = u;
                                        swap(vector[u],vector[u/2]);
                                        if (vector[u] < vector[u*2])
                                        {
                                                 while ((u*2) <= max)
                                                 {
                                                         if (vector[u] < vector[u*2]) { swap(vector[u],vector[u*2]); }
                                                         else {u = max;}
                                                         u = u*2;
                                                 }
                                        }
                                        u = q;
                                        if (vector[u] <= vector[(u*2)+1])
                                        {
                                                 while ((u*2)+1 <= max)
                                                 {
                                                         if (vector[u] <= vector[(u*2)+1]) { swap(vector[u],vector[(u*2)+1]); }
                                                         else {u = max;}
                                                         u = (u*2);
                                                 }
                                        }
                                               
                                        u = u/2;
                                }
                                else house = false;
                }
                v--;  
        }
 
       
//------------------------ Ordenar Heap---------------------------------
//cout<<endl<<"-------------------------------------------"<<endl;
for(int o = max; o > 1; o--)
{
    swap(vector[1], vector[o]);
    comp_pad_hij(vector, 1, o);
}
 
}
       
void impre(int *v)
{
  cout<<endl;
  for(int i = max; i >= 1; i--)   cout<<v[i]<<endl;
}
 
void encolar (int *vector, int aux)
{
            for (int c=0;c<10;c++)
           {
                   if (vector[c]==-1) {vector[c] = aux;c=10;}
                }
                heapsort(vector);
                impre (vector);
        }
       
void desencolar (int *vector)
{
        for(int i = max; i>max-4; i--)
        {
                if (vector[i] != -1){vector[i]=-1;}
        }  
        heapsort(vector);
        impre (vector);
        }
 
int main()
{
        //~ int Vector[max] = {15,48,47,55,6,27,87,37,37,43};
        int vector[max];
        for (int i = 0; i<max;i++){vector[i+1]=-1;/*Vector[i];*/}
       
           for (int j=0;j<6;j++)
           {
                   
                   int aux;
                   cout<<endl<<"Ingrese el proximo valor al heap: ";
                   cin>>aux;
                   cout<<endl;
                   encolar(vector, aux);
                }
       
        cout<<endl<<"Desencolamos los 4 primeros."<<endl;
        desencolar(vector);
       
        return 0;
}

