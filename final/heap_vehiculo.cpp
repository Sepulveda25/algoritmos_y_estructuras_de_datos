#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define max 10
 
using namespace std;
 
class Vehiculos
{      
        private:
                        struct vehiculo{int prioridad;
                                                        //Lista2 *recorrido;
                                                        int origen;
                                                        int destino;
                                                        bool seMovio;  
                        };
                        vehiculo autos;
       
        public:
                        Vehiculos(int pri);
                        void set_origen (int orig){autos.origen=orig;};
                        void set_destino(int dest){autos.destino=dest;};
                        //~ void set_recorrido(Lista2 *rec){autos.recorrido=rec;};
                        //~ int get_origen (void){return autos.origen;};
                        //~ int get_destino(void){return autos.destino;};
                        int get_prioridad (void){return autos.prioridad;};
                        //~ Lista2 *get_recorrido(void){return autos.recorrido;};
};
 
 Vehiculos::Vehiculos(int pri)
 {
        autos.prioridad=pri;
 }
 

void swap (Vehiculos *v,int uno ,int dos)
{
        Vehiculos *aux1 = new Vehiculos(0);
        *aux1 = *(v+uno);
        *(v+uno) = *(v+dos);
        *(v+dos) = *aux1;
}
 
void comp_pad_hij(Vehiculos *v, int p, int altu)
{
     if ((p*2 >= altu) || (((p*2)+1) >= altu)) cout<<"";
     else if((v+p)->get_prioridad() < (v+(p*2))->get_prioridad())
          {
              //~ swap((v+p), (v+(p*2)));
              swap(v,p,(p*2));
              comp_pad_hij(v, p, altu);
              comp_pad_hij(v, p*2, altu);
          }
          else if((v+p)->get_prioridad() < (v+((p*2)+1))->get_prioridad())
               {
                  //~ swap((v+p), (v+((p*2)+1)));
                  swap(v,p,((p*2)+1));
                  comp_pad_hij(v, p, altu);
                  comp_pad_hij(v, ((p*2)+1), altu);
               }
               else comp_pad_hij(v, max, 0);
}
 
 
void heapsort (Vehiculos *vector)
{
//--------------------- Armado de la Heap-------------------------------
        int u = max, v = u;
        while (v > 0)
        {
                bool house = true;
                u = v;
                while ((u > 1) && house)
                {                      
                                if ((vector+u)->get_prioridad() > (vector+(u/2))->get_prioridad())
                                {
                                        swap(vector,u,u/2);
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
    swap(vector,1,o);
    comp_pad_hij(vector, 1, o);
}
 
}
       
void impre(Vehiculos *v)
{
  cout<<endl;
  Vehiculos *aux = new Vehiculos(0);
  aux=v+1;
  for(int i = max-1; i >= 0; i--)  {cout<<aux->get_prioridad()<<endl; /*cout<<(v+i)->get_prioridad()<<endl; */}
}
 
void encolar (Vehiculos *vector, Vehiculos *aux)
{
            for (int c=0;c<10;c++)
           {
                   if ((vector+c)->get_prioridad() == 0)
                   {*(vector+c) = *aux; c=10;}
                }
                heapsort(vector);
                //~ impre (vector);
        }
       
void desencolar (Vehiculos *vector)
{
        for(int i = max; i>max-4; i--)
        {
                if ((vector+i)->get_prioridad() != 0)
                {
                        Vehiculos *aux = new Vehiculos(0);
                        *(vector+i) = *aux;
                }
        }  
        heapsort(vector);
        //~ impre (vector);
        }
 
int main()
{
        //~ Vehiculos *tutu = new Vehiculos(15);
        //~ cout<<tutu->get_prioridad()<<endl;
        Vehiculos *vector[max];
        for (int i = 0; i<=max;i++){(vector[i+1]) = new Vehiculos(0);}
        //~ impre(vector);
        Vehiculos *aux = new Vehiculos(0);
        impre((*vector));
        //~ for (int i = 0; i<max;i++){cout<<vector[i+1]->get_prioridad()<<endl;;}
        
           for (int j=0;j<6;j++)
           {
                   int pri;
                   cout<<endl<<"Ingrese el proximo valor al heap: ";
                   cin>>pri;
                   cout<<endl;
                   aux = new Vehiculos(pri);
                   encolar(*vector, aux);
           }
                //~ impre(*vector);
        //~
        //~ cout<<endl<<"Desencolamos los 4 primeros."<<endl;
        //~ desencolar(*vector);
       
        return 0;
}
