#include <cstdlib>
#include <iostream>
#include <sstream>
#define MAX 10
using namespace std;
class Nodo{
    private: 
        //*** Variables privadas de la clase nodo
        int dato[MAX];
        Nodo *next;
    public:
        //*** Costructores
        Nodo() {next=NULL;};//creo un objeto nodo con la variable dato vacia 
                            //y el puntero next apuntando a NULL
                            
        Nodo(int *a) {*dato=*a; next=NULL;};//creo un objeto nodo cargo el valor de a en 
                                        // dato y al puntero next le asigno NULL
                                        
        //*** Metodos 
        void set_dato(int a,int c) {dato[c]=a; };
        void set_next(Nodo *n) {next=n; };
        int get_dato() {return *dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista{
    private: Nodo *czo;// puntero tipo nodo o variable que apunta a un objeto tipo nodo
    public:
            //***Constructores
            Lista() {czo=new Nodo();};//creo un objeto nodo y guardo la diccion en el puntero czo
            Lista(Nodo *n) {czo=n;};
            //~Lista(void);
            
            //***Metodos
            void add(int *d);
            bool esvacia(void);
            int cabeza(void);
            Lista *resto(void);
            string toPrint(string p);   
            int suma(int i);
};
void Lista::add(int *d)
{  
     Nodo *nuevo=new Nodo(d);//creo un objeto nodo y lo cargo con d, luego le paso
                            //la direccion al puntero nuevo
     nuevo->set_next(czo);//al objeto nodo al que apunta nuevo invoco su metodo
                         // set_next y le paso de parametro el putero czo 
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}

int Lista::cabeza(void)
{ 
  if(esvacia()){
                cout<<"Error, Cabeza de lista vacia";
                return -1; 
  }
  return czo->get_dato();
}

Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}

void toPrintArray (int *a)
{
    for (int n=0;n<MAX;n++)
    {
        cout<<*(a+n)<<", "<<endl;
    }
}

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
    Lista *l=new Lista();
    int h[MAX]={8,0,0,0,0,0,0,0,00,0};
    int g[MAX]={9,0,0,0,0,0,0,0,00,0};
    l->add(h);
    l->add(g);
    //l->add(33);
    cout<< l->toPrint("fin") <<endl;
   
    system("PAUSE");
    return EXIT_SUCCESS;
    
}
