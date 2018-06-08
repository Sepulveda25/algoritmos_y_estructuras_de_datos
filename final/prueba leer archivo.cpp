#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
 
using namespace std;
 
class Nodo{
    private:
        int esq;
        int peso;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(int e, int p) {esq=e; peso=p; next=NULL;};
        void set_esq(int e) {esq=e; };
        void set_peso(int p) {peso=p; };
        void set_next(Nodo *n) {next=n; };
        int get_esq() {return esq; };
        int get_peso() {return peso; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};
 
};
 
class Lista{
    private: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            void add(int e, int p);
            bool esvacia(void);
            int cabeza(void);
            Lista *resto(void);
            string toPrint(string p);  
};
void Lista::add(int e, int p)
{  
     Nodo *nuevo=new Nodo(e, p);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{  
    return czo->es_vacio();
}
 
int Lista::cabeza(void)
{
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return -1;
  }
  return czo->get_esq();
}
 
Lista *Lista::resto(void)
{
      Lista *l=new Lista(czo->get_next());
      return (l);
}
 
string Lista::toPrint(string p)
{
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<"-"<< this->resto()->toPrint(p) << endl;
       return stm.str();
     }
}
 
int main()
{
	cout<<"hola mundo";
    Lista *Ady=new Lista();
    ifstream fichero;
    int texto;
    fichero.open("ADY.txt", ios::in);
    if (fichero.is_open())
    {        
             while (!fichero.eof())      
             {
                   fichero >> texto;          
                   Ady->add(texto, 1);  
             }
    }
    fichero.close();
   
    cout<< Ady->toPrint("fin");
	return 0;
}
