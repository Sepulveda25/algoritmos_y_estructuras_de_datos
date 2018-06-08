#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

typedef int tipolista;

class Nodo{
    protected: 
        tipolista dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(tipolista a) {dato=a; next=NULL;};
        void set_dato(tipolista a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        tipolista get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};
        
};

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            void del(void);
            void add(tipolista d);
            bool esvacia(void);
            tipolista cabeza(void);
            Lista *resto(void);
            string toPrint(tipolista p);   
            Nodo *get_czo(void){return czo;}
};

void Lista::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
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
                return -1; 
  }
  return czo->get_dato();
}

Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}

string Lista::toPrint(tipolista p)
{ 
     if (this->esvacia()) {
        return "";
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<"-"<< this->resto()->toPrint(p) << endl;
       return stm.str();
     }
}

//------------------------------------------------------------------------

class Cola{
      private:
              Lista *l;
              Nodo *czoq;
              void update_start(Lista *l,Nodo *p);
              void do_desencolar(Nodo *p,Nodo *s);
      public:
      Cola(void){l=new Lista();update_start(l,NULL);};
      ~Cola(void) {delete(l);};
      int tope();
      int colavacia() { return l->esvacia();};
      void encolar(int a) ;
      void desencolar();
};
int Cola::tope() {
           if (colavacia()){
              cout<<"Error: Cola vacia"<<endl;
              return -1;
           } 
           else
              return czoq->get_dato();
}

void Cola::encolar(int a) {
     l->add(a);
     if (czoq==NULL) {
        update_start(l,czoq);
     }
}

void Cola::desencolar() {
           if (colavacia())
              cout<<"Error: Cola vacia"<<endl;
           else {
              do_desencolar(l->get_czo(),NULL);
              update_start(l,NULL);
           }
}

void Cola::do_desencolar(Nodo *p,Nodo *s){
     if (p->get_next()==NULL) {
         if (s!=NULL) {
            s->set_next(NULL);
         }
         delete(p);
     }else {
         this->do_desencolar(p->get_next(),p);
     }
}
void Cola::update_start(Lista *l,Nodo *p){
     if (l->esvacia()) {
          czoq=p;
     }else {
          this->update_start(l->resto(),l->get_czo());
     }
}

//------------------------------------------------Lista
class Nodo_l{
    private: 
        Cola *dato;
        Nodo_l *next;
    public:
        Nodo_l() {next=NULL;};
        Nodo_l(Cola *a) {*dato=*a; next=NULL;};
        //void set_dato(Cola a) {dato=a; };
        void set_next(Nodo_l *n) {next=n; };
        Cola *get_dato() {return dato; };
        Nodo_l *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista_c{
    private: Nodo_l *czo;
    public:
            Lista_c() {czo=new Nodo_l();};
            Lista_c(Nodo_l *n) {czo=n;};
            //~Lista(void);
            void add(Cola *d);
            bool esvacia(void);
            Cola *cabeza(void);
            Lista_c *resto(void);
            string toPrint(string p);   
            int suma(int i);
};
void Lista_c::add(Cola *d)
{  
     Nodo_l *nuevo=new Nodo_l(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista_c::esvacia(void)
{   
    return czo->es_vacio();
}

Cola *Lista_c::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return NULL; 
  }
  return czo->get_dato();
}

Lista_c *Lista_c::resto(void)
{ 
      Lista_c *l=new Lista_c(czo->get_next());
      return (l);
}

string Lista_c::toPrint(string p)
{ 
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<"-"<< this->resto()->toPrint(p) << endl;
      //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
       return stm.str();
     }
}

//------------------------------------------------Lista Fin

int main(){
    Cola *c=new Cola();
    Lista_c *l=new Lista_c();
    //if (c->colavacia()) cout<<endl<<"La cola esta VACIA"<<endl;
    c->encolar(15);
    c->encolar(2);
    c->encolar(3);
    
    l->add(c);
    //l->add(22);
    //cout<< l->toPrint("fin") <<endl;
    
    
    /*cout<<"en cola:"<<c->tope()<<endl;
    c->desencolar();

    cout<<"en cola:"<<c->tope()<<endl;
    c->desencolar();

    cout<<"en cola:"<<c->tope()<<endl;
    c->desencolar();

    cout<<"en cola:"<<c->tope()<<endl;
    c->desencolar();

    c->encolar(44);
    cout<<"en cola:"<<c->tope()<<endl;
    c->desencolar();
    cout<<"en cola:"<<c->tope()<<endl;
    c->desencolar();*/
      
    system("PAUSE");
    return EXIT_SUCCESS;
    
}
