#include <cstdlib>
#include <iostream>
#define MAX 4
using namespace std;


class Vehiculos
{	
	private:
			struct vehiculo{int prioridad;
							int origen;
							int destino;	
			};
			vehiculo autos;
	
	public:
			Vehiculos(int pri);
			void set_origen (int orig){autos.origen=orig;};
			void set_destino(int dest){autos.destino=dest;};
			int get_origen (void){return autos.origen;};
			int get_destino(void){return autos.destino;};
			int get_prioridad (void){return autos.prioridad;};
}; 
 
 Vehiculos::Vehiculos(int pri)
 {
	autos.prioridad=pri; 
 }

typedef Vehiculos tipolista;
class Cola
{
      private:
              tipolista v [MAX];
              tipolista a[MAX];
              int p;
      public:
             Cola();
             void encolar (tipolista x);
             tipolista tope(void);
             void desencolar (void);
             bool colaVacia();
             bool colaLlena();
             int tamanio(void){return p+1;};
             //~ void leerCola(tipolista v);
};

Cola::Cola()
{
            p=-1;
}

void Cola::encolar(tipolista x)
{  
	p++;
	//~ cout<<p<<endl;
	if (colaLlena()){cout<<"La cola esta llena"<<endl;}
	else{		
			v[p]=x;
		}                                
}

tipolista Cola::tope(void)
{
	    //~ cout<<"entre tope"<<endl;
        if (colaVacia()){cout<<"La cola esta vacia"<<"\n\n"; return 0;}
        else{return v[0];}
}

void Cola::desencolar(void)
{;
     if (colaVacia()){cout<<"La cola esta vacia"<<"\n\n";}
     else
     {
		 for (int i = 0; i+1 < p; i++)
		 {
			v[i]=v[i+1];		
			}	
		 //~ v[p-1]='\0';
		 //~ if (v[0] == v[1]) {p = 0;}	
		 p--;
		 }
     
 }
bool Cola::colaVacia()
{
     if (p==-1)
     {return true;}
     else{return false;}
} 

bool Cola::colaLlena()
{
     if (p==MAX){return true;}
     else{return false;}
} 
//~ int Cola::leerCola()
//~ {
	 //~ for (int i = 0; i <=p; i++)
		 //~ {
			 //~ if(!colaVacia()){
			//~ cout<<v[i]<<endl;}		
		//~ }
	//~ return *v;
//~ }

int main(int argc, char *argv[])
{
    Cola *p=new Cola();
    Cola *j=new Cola();
    Cola *ac[2];
    p->encolar (1);
    p->encolar (2);
    //~ p->encolar (3);
    j->encolar (4);
    j->encolar (5);
    j->encolar (6);
    ac[0]=p;
    ac[1]=j;
    
    cout<< p->tamanio()<<endl;
    //~ cout<<endl<<ac[0]->tope()<<endl;
    //~ ac[0]->desencolar();
    //~ 
    //~ cout<<endl<<ac[1]->tope()<<endl;
    //~ ac[1]->desencolar();
    //~ 
    //~ cout<<endl<<ac[0]->tope()<<endl;
    //~ ac[0]->desencolar();
    //~ 
    //~ cout<<endl<<ac[1]->tope()<<endl;
    //~ ac[1]->desencolar();
    //~ cout<<endl<<ac[0]->tope()<<endl;
    //~ ac[0]->desencolar();
    //~ cout<<endl<<ac[1]->tope()<<endl;
    //~ ac[1]->desencolar();
    //~ cout<<endl<<p->tope()<<endl;
    //~ p->leerCola();
    system("PAUSE");
    return EXIT_SUCCESS;
}
