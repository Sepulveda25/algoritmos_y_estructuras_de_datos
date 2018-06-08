#include <cstdlib>
#include <iostream>
#include <sstream>
#define MAX1 2
using namespace std;

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
            Nodo *get_czo(void){return czo;}
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
 
//------------------------------------------

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
            string toPrint(string p);   
            int suma(int i);
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
//~ 
//~ void toPrintArray (int *a)
//~ {
    //~ for (int n=0;n<MAX1;n++)
    //~ {
        //~ cout<<*(a+n)<<", "<<endl;
    //~ }
//}

string Lista::toPrint(string p)
{ 
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm <<this->cabeza()<<"-"<< this->resto()->toPrint(p) << endl;
      
       return stm.str();
     }
}




int main()
{
	
    return EXIT_SUCCESS;

}
