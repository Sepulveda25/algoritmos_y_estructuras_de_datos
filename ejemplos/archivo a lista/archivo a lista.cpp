#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream.h>
#include <string>

using namespace std;
class Nodo{
    private: 
        string dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(string a) {dato=a; next=NULL;};
        void set_dato(string a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        string get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista{
    private: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            //~Lista(void);
            void add(string d);
            bool esvacia(void);
            string cabeza(void);
            Lista *resto(void);
            string toPrint(void);   
            //int suma(int i);
};
void Lista::add(string d)
{  
     Nodo *nuevo=new Nodo(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}

string Lista::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return ""; 
  }
  return czo->get_dato();
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

int main()
{
    char linea[10];
    Lista *l=new Lista();
    ifstream archivo;
    archivo.open("d:\\datos.txt");
    if (archivo.fail()) {
    cerr << "No pudo leerse el archivo";
    exit(1);   // parar
    }
    
  
    while (!archivo.eof() )
    {
      archivo.getline(linea,sizeof(linea));
      l->add(linea);
    }
    
    cout<< l->toPrint()<<endl;


    archivo.close();
   
    system("PAUSE");
    return EXIT_SUCCESS;
    
}
