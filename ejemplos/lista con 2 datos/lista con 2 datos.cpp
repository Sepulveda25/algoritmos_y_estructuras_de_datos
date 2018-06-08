#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;
class Nodo{
    private: 
        //*** Variables privadas de la clase nodo
        int dato;
        char *pal;
        Nodo *next;
    public:
        //*** Costructores
        Nodo() {next=NULL;};//creo un objeto nodo con la variable dato vacia 
                            //y el puntero next apuntando a NULL
                            
        Nodo(int a,char *b) {dato=a; pal=b; next=NULL;};//creo un objeto nodo cargo el valor de a en 
                                                // dato y al puntero next le asigno NULL
                                        
        //*** Metodos 
        void set_dato(char *b, int a) {dato=a; pal=b; };
        void set_next(Nodo *n) {next=n; };
        int get_dato() {return dato; };
        char *get_pal() {return pal;};
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
            void add(char *c,int d);
            bool esvacia(void);
            string cabeza(void);
            Lista *resto(void);
            string toPrint(void);   
            int suma(int i);
};
void Lista::add(char *c,int d)
{  
     Nodo *nuevo=new Nodo(d,c);//creo un objeto nodo y lo cargo con d, luego le paso
                            //la direccion al puntero nuevo
     nuevo->set_next(czo);//al objeto nodo al que apunta nuevo invoco su metodo
                         // set_next y le paso de parametro el putero czo 
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}

string Lista::cabeza(void)
{ 
  if(esvacia()){
                cout<<"Error, Cabeza de lista vacia";
                return ""; 
  }
  std::ostringstream datos;
  datos<<czo->get_pal()<<", "<<czo->get_dato();
  return datos.str();
}

Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}

string Lista::toPrint(void)
{ 
     if (this->esvacia()) {
        return "";
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<"\n"<< this->resto()->toPrint() << endl;
       return stm.str();
     }
}
/*int Lista::suma(int i)
{    cout<<" i al entrar= "<<i<<endl;
     if (this->esvacia()) {
        return i;
     } else {
        
        cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i+this->cabeza());
     }
}*/

int main()
{
    Lista *l=new Lista();
    char pal[]="pepe";
    char pal1[]="juan";
    
    l->add(pal,12);
    l->add(pal1,20);
    cout<< l->toPrint() <<endl;
    //cout<< "suma:"<<l->suma(0)<<endl;
   
    system("PAUSE");
    return EXIT_SUCCESS;
    
}
