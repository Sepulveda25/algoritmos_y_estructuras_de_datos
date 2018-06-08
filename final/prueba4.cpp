#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>
#include <cstdlib>
#include <string.h>
#include <list>
#define MAX 100
#define MAX1 2
#define MAX2 12
 
using namespace std;
class Nodo2{
    private: 
        //*** Variables privadas de la clase nodo
        int datos;
        Nodo2 *next;
    public:
        //*** Costructores
        Nodo2() {next=NULL;};//creo un objeto nodo con la variable dato vacia 
                            //y el puntero next apuntando a NULL
                            
        Nodo2(int a) {datos=a; next=NULL;};//creo un objeto nodo cargo el valor de a en 
                                        // dato y al puntero next le asigno NULL
                                        
        //*** Metodos 
        void set_dato(int a) {datos=a; };
        void set_next(Nodo2 *n) {next=n; };
        int get_dato() {return datos; };
        Nodo2 *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista2{
    private: Nodo2 *czo;// puntero tipo nodo o variable que apunta a un objeto tipo nodo
    public:
            //***Constructores
            Lista2() {czo=new Nodo2();};//creo un objeto nodo y guardo la diccion en el puntero czo
            Lista2(Nodo2 *n) {czo=n;};
            //~Lista(void);
            
            //***Metodos
            void add(int d);
            bool esvacia(void);
            int cabeza(void);
            Lista2 *resto(void);
            string toPrint(string p);   
            int suma(int i);
};
void Lista2::add(int d)
{  
     Nodo2 *nuevo=new Nodo2(d);//creo un objeto nodo y lo cargo con d, luego le paso
                            //la direccion al puntero nuevo
     nuevo->set_next(czo);//al objeto nodo al que apunta nuevo invoco su metodo
                         // set_next y le paso de parametro el putero czo 
     czo=nuevo;
}
bool Lista2::esvacia(void)
{   
    return czo->es_vacio();
}

int Lista2::cabeza(void)
{ 
  if(esvacia()){
                cout<<"Error, Cabeza de lista vacia";
                return -1; 
  }
  return czo->get_dato();
}

Lista2 *Lista2::resto(void)
{ 
      Lista2 *l=new Lista2(czo->get_next());
      return (l);
}

void toPrintArray (int *a)
{
    for (int n=0;n<MAX;n++)
    {
        cout<<*(a+n)<<", "<<endl;
    }
}

//~ string Lista2::toPrint(string p)
//~ { 
     //~ if (this->esvacia()) {
        //~ return p;
     //~ } else {
       //~ std::ostringstream stm;
       //~ stm <<this->cabeza()<<"-"<< this->resto()->toPrint(p) << endl;
      //~ 
       //~ return stm.str();
     //~ }
//~ }

class Vehiculos
{	
	private:
			struct vehiculo{int prioridad;
							Lista2 *recorrido;
							int origen;
							int destino;
							bool seMovio;	
			};
			vehiculo autos;
	
	public:
			Vehiculos(int pri);
			void set_origen (int orig){autos.origen=orig;};
			void set_destino(int dest){autos.destino=dest;};
			void set_recorrido(Lista2 *rec){autos.recorrido=rec;};
			int get_origen (void){return autos.origen;};
			int get_destino(void){return autos.destino;};
			int get_prioridad (void){return autos.prioridad;};
			Lista2 *get_recorrido(void){return autos.recorrido;};
}; 
 
 Vehiculos::Vehiculos(int pri)
 {
	autos.prioridad=pri; 
 }
 
 typedef Vehiculos tipolista;


class Cola
{
      private:
              Vehiculos *v [MAX2];
              tipolista *a[MAX2];
              int p;
      public:
             Cola();
             void encolar (Vehiculos *x);
             Vehiculos *tope(void);
             void desencolar (void);
             bool colaVacia();
             bool colaLlena();
             int cant_vehiculos(void){return p+1;};
             //~ void leerCola(tipolista v);
};

Cola::Cola()
{
            p=-1;
}

void Cola::encolar(Vehiculos *x)
{  
	p++;
	//~ cout<<p<<endl;
	if (colaLlena()){cout<<"La cola esta llena"<<endl;}
	else{		
			v[p]=x;
		}                                
}

Vehiculos *Cola::tope(void)
{
	    //~ cout<<"entre tope"<<endl;
        if (colaVacia()){cout<<"La cola esta vacia"<<"\n\n"; return v[0];}
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
		 //v[p-1]='\0';
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
///////////////-------/////////-------------Grafo COMIENZO---------------///////-------//////////////////
 
///////////////--------------------Lista de Arrays COMIENZO--------------------------------
 
//typedef int tipolista_de_array;
 
class Nodo
{
    protected:
		struct dato {
		int dest;
		Cola *autos;//=new Cola();
		} ;
		dato esquina;
        //~ Cola *dato[MAX1];
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(int d) {esquina.dest=d; next=NULL;esquina.autos=new Cola();};
        void set_next(Nodo *n) {next=n; };
        Cola *get_auto() {return esquina.autos; };
        int get_cant_vehiculos(){return esquina.autos->cant_vehiculos();}
        int get_dest(){return esquina.dest;};
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};
};
 
class Lista_de_arrays
{
    protected: Nodo *czo;
    public:
            Lista_de_arrays() {czo=new Nodo();};
            Lista_de_arrays(Nodo *n) {czo=n;};
            void del(void);
            void add(int d);
            bool esvacia(void);
            int cabeza_vehiculo(void);
            int cabeza_des(void);
            Cola *cabeza_auto (void);
            Lista_de_arrays *resto(void);
            Nodo *get_czo(void){return czo;};
            //void toPrint_sec(Lista_de_arrays p2);
            //~ void set_peso(int destino, int peso);
};
 
//~ void Lista_de_arrays::del(void)
//~ {    Nodo *aux;
     //~ aux=czo;
     //~ czo=czo->get_next();
     //~ delete aux;
//~ }

void Lista_de_arrays::add(int d)
{  
     Nodo *nuevo=new Nodo(d);
     nuevo->set_next(czo);
     czo=nuevo;
	
}
bool Lista_de_arrays::esvacia(void) 
{     
	return czo->es_vacio(); 
}
	
 
int Lista_de_arrays::cabeza_vehiculo(void)
{
          if(esvacia())
          {
                        cout<<" Error, Cabeza de lista vacia";
                        return 0;
          }
          return czo->get_cant_vehiculos();
}
 
 int Lista_de_arrays::cabeza_des(void)
{
          if(esvacia())
          {
                        cout<<" Error, Cabeza de lista vacia";
                        return 0;// NULL;
          }
          return czo->get_dest();
}

Cola *Lista_de_arrays::cabeza_auto (void)
{
	 if(esvacia())
          {
                        cout<<" Error, Cabeza de lista vacia";
                        return czo->get_auto();// NULL;
          }
          return czo->get_auto();	
}
Lista_de_arrays *Lista_de_arrays::resto(void)
{
      Lista_de_arrays *l=new Lista_de_arrays(czo->get_next());
      return (l);
}
 
///////////////--------------------Lista de Arrays FIN--------------------------------
 
 
///////////////--------------------Lista de listas COMIENZO--------------------------------
class Nodo_l{
    private:
        //*** Variables privadas de la clase nodo
        Lista_de_arrays listaDatos;
        Nodo_l *next;
    public:
        //*** Costructores
        Nodo_l() {next=NULL;};//creo un objeto nodo con la variable dato vacia
                            //y el puntero next apuntando a NULL
                           
        Nodo_l(Lista_de_arrays *a) {listaDatos=*a; next=NULL;};//creo un objeto nodo cargo el valor de a en
                                        // dato y al puntero next le asigno NULL
                                       
        //*** Metodos
        void set_dato(Lista_de_arrays d) {listaDatos=d; };
        void set_next(Nodo_l *n) {next=n; };
        Lista_de_arrays get_dato() {return listaDatos; };
        Nodo_l *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};
 
class Lista{
    private: Nodo_l *czo;// puntero tipo nodo o variable que apunta a un objeto tipo nodo
    public:
            //***Constructores
            Lista() {czo=new Nodo_l();};//creo un objeto nodo y guardo la diccion en el puntero czo
            Lista(Nodo_l *n) {czo=n;};
            //~Lista(void);
           
            //***Metodos
            void add(Lista_de_arrays *d);
            bool esvacia(void);
            Lista_de_arrays cabeza(void);
            Lista *resto(void);
            void toPrint_pri(Lista p1, int count);
            void toPrint_sec(Lista_de_arrays p2);
            void set_pesoAux(Lista_de_arrays p2, int destino, Vehiculos autom);
            void set_peso(Lista p1, int origen, int destino, Vehiculos autom, int iter);
            //~ int get_pesoAux(Lista_de_arrays p2, int destino);
            //~ int get_peso(Lista p1, int origen, int destino, int iter);
};
 
void Lista::add(Lista_de_arrays *d)
{  
     Nodo_l *nuevo=new Nodo_l(d);//creo un objeto nodo y lo cargo con d, luego le paso
                            //la direccion al puntero nuevo
     nuevo->set_next(czo);//al objeto nodo al que apunta nuevo invoco su metodo
                         // set_next y le paso de parametro el putero czo
     czo=nuevo;
}
bool Lista::esvacia(void)
{  
    return czo->es_vacio();
}
 
Lista_de_arrays Lista::cabeza(void)
{
  if(esvacia()){
                cout<<"Error, Cabeza de lista vacia";
                return czo->get_dato();
  }
  return czo->get_dato();
}
 
Lista *Lista::resto(void)
{
      Lista *l=new Lista(czo->get_next());
      return (l);
}
 
 void Lista::toPrint_sec(Lista_de_arrays p2)
{
        if((p2.resto())->esvacia()){ cout<< "  Apunta a: " << (p2.cabeza_des()) << " Con peso: " << (p2.cabeza_vehiculo() ) << endl;	}
        else { cout<< "  Apunta a: " << (p2.cabeza_des()) << " Con peso: " << (p2.cabeza_vehiculo() ) << endl;toPrint_sec(*(p2.resto()));}
}
 
void Lista::toPrint_pri(Lista p1, int count)
{
	cout<<endl;
        if((p1.resto())->esvacia()) {cout<<count<<" "; toPrint_sec(p1.cabeza()); }
        else
        {
			cout<<count<<" "; 
			toPrint_sec(p1.cabeza()); 
			toPrint_pri(*(p1.resto()), --count);
		}
}

//~ void Lista::set_pesoAux(Lista_de_arrays p2, int destino, Vehiculos autom)
//~ {
	//~ if(p2.esvacia()) {cout<<"Error ese DESTINO es INVALIDO!!"<<endl; }
	//~ else if(destino != (p2.cabeza_des())) { set_pesoAux(*(p2.resto()), destino, autom); }
		 //~ else
		 //~ { 
			//~ p2.cabeza_auto()->encolar(autom);// = autom;
			//~ cout<<"Exito cambiando el peso "<<" Con peso: " << (p2.cabeza_vehiculo() ) << endl;
		 //~ }
//~ }
//~ 
//~ void Lista::set_peso(Lista p1, int origen, int destino, Vehiculos autom, int iter)
//~ {
	//~ if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
	//~ else if(iter == origen) { set_pesoAux(p1.cabeza(), destino, autom); }
		 //~ else
		 //~ {
			//~ //cout<<count<<" "; 
			//~ set_peso(*(p1.resto()), origen, destino, autom, --iter);
		 //~ }
//~ }

//~ int Lista::get_pesoAux(Lista_de_arrays p2, int destino)
//~ {
	//~ if((p2.resto())->esvacia()) {/*cout<<"Error ese DESTINO es INVALIDO!!"<<endl;*/ return *(p2.cabeza() + 1); }
	//~ else if(destino != *(p2.cabeza())) { return get_pesoAux(*(p2.resto()), destino); }
		 //~ else
		 //~ { 
			//~ return *(p2.cabeza() + 1);
			//~ //cout<<"Exito cambiando el peso "<<endl;
		 //~ }
//~ }
//~ 
//~ int Lista::get_peso(Lista p1, int origen, int destino, int iter)
//~ {
	//~ if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!";return -1; }
	//~ else if(iter == origen) { return get_pesoAux(p1.cabeza(), destino); }
		 //~ else
		 //~ {
			//~ cout<<count<<" "; 
			//~ return get_peso(*(p1.resto()), origen, destino,--iter);
		 //~ }
//~ }



///////////////--------------------Lista de listas FIN--------------------------------
 
 

 
//~ void mover_auto (Lista p1, int origen, int destino, int inter, int iter)
//~ {
	//~ //cout<<p1.get_peso(p1,origen,inter,iter)<<endl;
	//~ p1.set_peso(p1, origen, inter, (p1.get_peso(p1,origen,inter,iter))-1, iter);
	//~ p1.set_peso(p1, inter, destino, (p1.get_peso(p1,inter,destino,iter))+1, iter);
//~ }

 
int main()
{
    Lista *Mapa = new Lista();     
    int texto; 
    //Vehiculos *automovil= new Vehiculos(1); 
    Vehiculos automovil(1);
    ifstream archivo_entr;
    archivo_entr.open("ADY.txt");
    
    if (archivo_entr.fail())
    {
		cout<<"El archivo no se abrio correctamente."<<endl;
		exit(1);
	}
	Lista_de_arrays *ady = new Lista_de_arrays();
	while(!archivo_entr.eof())
	{		
		archivo_entr>> texto;		
		if (texto == -1)
		{			
			archivo_entr>> texto;
			Mapa->add(ady);
			ady = new Lista_de_arrays();
			}
		ady->add(texto);
	}
   Mapa->toPrint_pri(*Mapa, 81);
    //Mapa->set_peso(*Mapa, 2, 3, automovil, 81);//mapa , origen, destino, auto, iter
    //~ Mapa->toPrint_pri(*Mapa, 81);
    //~ Mapa->set_peso(*Mapa, 75, 74, 5, 81);
    //~ Mapa->set_peso(*Mapa, 49, 48, 3, 81);
        //~ 
    //~ Mapa->toPrint_pri(*Mapa, 81);
	//~ 
	//~ mover_auto(*Mapa,49,59,50,81);
	//~ Mapa->set_peso(*Mapa, 49, 50, 7, 81);
	//~ mover_auto(*Mapa,49,59,50,81);
	//~ 
	//~ Mapa->toPrint_pri(*Mapa, 81);
}

