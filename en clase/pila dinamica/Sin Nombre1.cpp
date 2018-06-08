#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;
typedef string tipolista;

class Nodo{
    private: 
        tipolista dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(tipolista a) {dato=a; next=NULL;};
        void set_dato(tipolista a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        tipolista get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista{
    private: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            //~Lista(void);
            void add(tipolista d);
            bool esvacia(void);
            tipolista cabeza(void);
            Lista *resto(void);
            //string toPrint(string p);   
            void borrarLista(void);
            void del(void);
};

void Lista::borrarLista(void)
{
    Lista();
    
}
  
void Lista::add(tipolista d)
{  
     Nodo *nuevo=new Nodo(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}

tipolista Lista::cabeza(void)
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

void Lista::del(void)
{
     Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}

class Pila:public Lista{
   
    public:
        Pila(){Lista();};
        void apilar(tipolista x);
        tipolista tope(void);
        void desapilar (void);
        bool pilavacia();
        void vaciarPila(void);
};

void Pila::vaciarPila(void)
{  
  borrarLista();                                 
}


/*
string Lista::toPrint(string p)
{ 
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<"-"<< this->resto()->toPrint(p) << endl;
      //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
       return stm.str();
     }
}*/
/*tipolista Lista::suma(tipolista i)
{    cout<<" i al entrar= "<<i<<endl;
     if (this->esvacia()) {
        return i;
     } else {
        
        cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i+this->cabeza());
     }
}*/

/*Pila::Pila()
{
            p=-1;
}*/

void Pila::apilar(tipolista x)
{  
   add(x);                                 
}

tipolista Pila::tope(void)
{
    return cabeza();    
}

void Pila::desapilar(void)
{
     del();
     
 }
bool Pila::pilavacia()
{
     return esvacia();     
} 

int main()
{
    
    Pila *p=new Pila();
    p->apilar ("primer");
    p->apilar ("segundo");
    p->apilar ("tercero");
    cout<<endl<<p->tope()<<endl;
    p->desapilar();
    p->vaciarPila();
    cout<<endl<<p->tope()<<endl;
    p->desapilar();
    cout<<endl<<p->tope()<<endl;
   
    system("PAUSE");
    return EXIT_SUCCESS;
    
}
