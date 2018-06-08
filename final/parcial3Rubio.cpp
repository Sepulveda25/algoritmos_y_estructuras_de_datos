#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>
#include <cstdlib>
#include <string.h>
#define MAX 100
#define MAX1 2
 
using namespace std;
 
///////////////-------/////////-------------Grafo COMIENZO---------------///////-------//////////////////
 
///////////////--------------------Lista de Arrays COMIENZO--------------------------------
 
typedef int tipolista_de_array;
 
class Nodo
{
    protected:
        tipolista_de_array dato[MAX1];
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(tipolista_de_array d, tipolista_de_array p) {dato[0]=d;dato[1]=p; next=NULL;};
        void set_next(Nodo *n) {next=n; };
        tipolista_de_array *get_dato() {return dato; };
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
            void add(tipolista_de_array dest,tipolista_de_array peso);
            bool esvacia(void);
            tipolista_de_array *cabeza(void);
            Lista_de_arrays *resto(void);
            Nodo *get_czo(void){return czo;};
            //void toPrint_sec(Lista_de_arrays p2);
            void set_peso(int destino, int peso);
};
 
void Lista_de_arrays::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void Lista_de_arrays::add(tipolista_de_array dest,tipolista_de_array peso)
{  
     Nodo *nuevo=new Nodo(dest,peso);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista_de_arrays::esvacia(void) {     return czo->es_vacio(); }
 
tipolista_de_array *Lista_de_arrays::cabeza(void)
{
          if(esvacia())
          {
                        //~ cout<<" Error, Cabeza de lista vacia";
                        return NULL;
          }
          return czo->get_dato();
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
            void set_pesoAux(Lista_de_arrays p2, int destino, int peso);
            void set_peso(Lista p1, int origen, int destino, int peso, int iter);
            int get_pesoAux(Lista_de_arrays p2, int destino);
            int get_peso(Lista p1, int origen, int destino, int iter);
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
        if((p2.resto())->esvacia()){ cout<< "  Apunta a: " << *(p2.cabeza()) << " Con peso: " << *(p2.cabeza() + 1) << endl;	}
        else { cout<< "  Apunta a: " << *(p2.cabeza()) << " Con peso: " << *(p2.cabeza() + 1) << endl;toPrint_sec(*(p2.resto()));}
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

void Lista::set_pesoAux(Lista_de_arrays p2, int destino, int peso)
{
	if(p2.esvacia()) {cout<<"Error ese DESTINO es INVALIDO!!"<<endl; }
	else if(destino != *(p2.cabeza())) { set_pesoAux(*(p2.resto()), destino, peso); }
		 else
		 { 
			*(p2.cabeza() + 1) = peso;
			cout<<"Exito cambiando el peso "<<endl;
		 }
}

void Lista::set_peso(Lista p1, int origen, int destino, int peso, int iter)
{
	if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
	else if(iter == origen) { set_pesoAux(p1.cabeza(), destino, peso); }
		 else
		 {
			//~ cout<<count<<" "; 
			set_peso(*(p1.resto()), origen, destino, peso, --iter);
		 }
}

int Lista::get_pesoAux(Lista_de_arrays p2, int destino)
{
	if((p2.resto())->esvacia()) {/*cout<<"Error ese DESTINO es INVALIDO!!"<<endl;*/ return *(p2.cabeza() + 1); }
	else if(destino != *(p2.cabeza())) { return get_pesoAux(*(p2.resto()), destino); }
		 else
		 { 
			return *(p2.cabeza() + 1);
			//cout<<"Exito cambiando el peso "<<endl;
		 }
}

int Lista::get_peso(Lista p1, int origen, int destino, int iter)
{
	if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!";return -1; }
	else if(iter == origen) { return get_pesoAux(p1.cabeza(), destino); }
		 else
		 {
			//~ cout<<count<<" "; 
			return get_peso(*(p1.resto()), origen, destino,--iter);
		 }
}



///////////////--------------------Lista de listas FIN--------------------------------
 
 
///////////////-------/////////-------------Grafo FIN---------------///////-------//////////////////
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
/*
///////////////--------------------Cola COMIENZO--------------------------------
 
typedef int tipolista_c;
 
class Nodo
{
    protected:
        tipolista_c dato[MAX1];
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(tipolista_c a, tipolista_c b) {dato[0]=a;dato[1]=b; next=NULL;};
        void set_next(Nodo *n) {next=n; };
        tipolista_c *get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};    
};
 
class Lista
{
    protected: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            void del(void);
            void add(tipolista_c d,tipolista_c e);
            bool esvacia(void);
            tipolista_c *cabeza(void);
            Lista *resto(void);
            Nodo *get_czo(void){return czo;}
};
 
void Lista::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void Lista::add(tipolista_c d,tipolista_c e)
{  
     Nodo *nuevo=new Nodo(d,e);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void) {     return czo->es_vacio(); }
 
tipolista_c *Lista::cabeza(void)
{
          if(esvacia())
          {
                        //~ cout<<" Error, Cabeza de lista vacia";
                        return NULL;
          }
          return czo->get_dato();
}
 
Lista *Lista::resto(void)
{
      Lista *l=new Lista(czo->get_next());
      return (l);
}
 
///////--------------------------------------------------------------------
 
class Cola
{
      private:
              Lista *l;
              Nodo *czoq;
              void update_start(Lista *l,Nodo *p);
              void do_desencolar(Nodo *p,Nodo *s);
      public:
            Cola(void){l=new Lista();update_start(l,NULL);};
            ~Cola(void) {delete(l);};
            int *tope();
            int colavacia() { return l->esvacia();};
            void encolar(int a, int b) ;
            void desencolar();
};
 
int *Cola::tope()
{
           if (colavacia())
           {
                  //~ cout<<"Error: Cola vacia"<<endl;
                  return czoq->get_dato();
           }
           else   {     return czoq->get_dato(); }
}
 
void Cola::encolar(int a,int b)
{
     l->add(a,b);
     if (czoq==NULL) {  update_start(l,czoq); }
}
 
void Cola::desencolar()
{
           if (colavacia()) {  cout<<"Error: Cola vacia"<<endl; }
           else
           {
                  do_desencolar(l->get_czo(),NULL);
                  update_start(l,NULL);
           }
}
 
void Cola::do_desencolar(Nodo *p,Nodo *s)
{
     if (p->get_next()==NULL)
     {
         if (s!=NULL)  {  s->set_next(NULL); }
         delete(p);
     }
     else { this->do_desencolar(p->get_next(),p); }
}
 
void Cola::update_start(Lista *l,Nodo *p)
{
     if (l->esvacia()) {  czoq=p; }
     else { this->update_start(l->resto(),l->get_czo()); }
}
 
///////////----------------------------Cola FIN---------------------------------
*/
 
/*
///////////--------------------------Pila COMIENZO------------------------------
 
typedef Cola tipolista;
class Nodo_p
{
    private:
        tipolista *dato;
        int dato2[MAX1];
        Nodo_p *next;
    public:
        Nodo_p() {next=NULL;};
        Nodo_p(tipolista *a) {dato=a; next=NULL;};
        Nodo_p(int a, int b) {dato2[0]=a;dato2[1]=b; next=NULL;};      
        void set_next(Nodo_p *n) {next=n; };
        tipolista *get_dato() {return dato; };
        int *get_dato2(){return dato2;}
        Nodo_p *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};
 
class Lista_p:public Cola
{
    private: Nodo_p *czo;
    public:
            Lista_p() {czo=new Nodo_p();};
            Lista_p(Nodo_p *n) {czo=n;};
            void add(tipolista *d);
            void add2 (int a, int b);
            bool esvacia(void);
            tipolista *cabeza(void);
            int *cabeza2 (void);
            Lista_p *resto(void);
            Lista_p *resto2(void);  
            void del(void);
};
   
void Lista_p::add(tipolista *d)
{  
     Nodo_p *nuevo=new Nodo_p(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
void Lista_p::add2(int a, int b)
{  
         Nodo_p *nuevo=new Nodo_p(a, b);
         nuevo->set_next(czo);
         czo=nuevo;
}
bool Lista_p::esvacia(void) {  return czo->es_vacio(); }
 
tipolista *Lista_p::cabeza(void)
{
        if(esvacia())
        {
                //~ cout<<" Error, Cabeza de lista vacia";
                return czo->get_dato();
        }
        return czo->get_dato();
}
 
int *Lista_p::cabeza2(void)
{
          if(esvacia())
          {
                        //~ cout<<" Error, Cabeza de lista vacia";
                        return czo->get_dato2();
          }
          return czo->get_dato2();
}
 
Lista_p *Lista_p::resto2(void)
{
      Lista_p *l=new Lista_p(czo->get_next());
      return (l);
}
 
Lista_p *Lista_p::resto(void)
{
      Lista_p *l=new Lista_p(czo->get_next());
      return (l);
}
 
void Lista_p::del(void)
{
     Nodo_p *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
 
//------------------------------------------------------------------------------
 
class Pila:public Lista_p
{  
    public:
        Pila(){Lista_p();};
        void apilar(tipolista *x);
        void apilar2(int a, int b);
        tipolista *tope_p(void);
        int *tope_p2(void);
        void desapilar (void);
        bool pilavacia();
};
 
void Pila::apilar(tipolista *x) {  add(x); }
 
void Pila::apilar2(int a, int b) { add2(a,b); }
 
tipolista *Pila::tope_p(void) { return cabeza();  }
 
int *Pila::tope_p2(void) {  return cabeza2(); }
 
void Pila::desapilar(void) {  del(); }
 
bool Pila::pilavacia() {  return esvacia(); }
 
///////////-------------------------Pila FIN------------------------------------
*/
 
/*
///////////-------------------Pila de Colas COMIENZO----------------------------
 
Pila *armar (int f,int col)
{
    Pila *shoot=new Pila();
    Cola *ab=new Cola();Cola *arr=new Cola();Cola *der=new Cola();Cola *izq=new Cola();
    int coli = col,cold = col;
        int far = f, fab=f;
        int i = 0, d= 0,up=0,down=0;
        if (fab <9)
        {
                while (down !=3)                //----Cola ab
                {
                        if(fab <9) {    ab->encolar(++fab,col); }
                        else {  fab=fab-2;ab->encolar(fab,col); }
                        down++;
                }
                shoot->apilar(ab);
        }
        if (far >0)
        {
                while (up !=3)          //----Cola arr
                {                      
                        if (far >0) {   arr->encolar(--far,col); }
                        else {  far=far+2;arr->encolar(far,col); }
                        up++;
                }
                shoot->apilar(arr);
        }
        if (coli >0)
        {
                while (i !=3)           //----Cola Izq
                {
                        if (coli >0) {  izq->encolar(f,--coli); }
                        else {  coli=coli+2;izq->encolar(f,coli); }
                        i++;
                }
                shoot->apilar(izq);
        }
        if (cold <9)
        {
                while (d !=3)           //----Cola der
                {
                        if (cold <9) {  der->encolar(f,++cold); }
                        else {  cold=cold-2;der->encolar(f,cold); }
                        d++;
                }
                shoot->apilar(der);
        }
    return shoot;
}
 
///////////------------------------Pila de Colas FIN----------------------------
*/
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void mover_auto (Lista p1, int origen, int destino, int inter, int iter)
{
	//cout<<p1.get_peso(p1,origen,inter,iter)<<endl;
	p1.set_peso(p1, origen, inter, (p1.get_peso(p1,origen,inter,iter))-1, iter);
	p1.set_peso(p1, inter, destino, (p1.get_peso(p1,inter,destino,iter))+1, iter);
}

 
int main()
{
    Lista *Mapa = new Lista();     
    int texto; 
    
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
		ady->add(texto,1);
		}
    //Mapa->toPrint_pri(*Mapa, 81);
    
    Mapa->set_peso(*Mapa, 74, 75, 5, 81);
    Mapa->set_peso(*Mapa, 75, 74, 5, 81);
    Mapa->set_peso(*Mapa, 49, 48, 3, 81);
        
    //~ Mapa->toPrint_pri(*Mapa, 81);
	
	mover_auto(*Mapa,49,59,50,81);
	//Mapa->set_peso(*Mapa, 49, 50, 7, 81);
	//mover_auto(*Mapa,49,59,50,81);
	
	Mapa->toPrint_pri(*Mapa, 81);
}
