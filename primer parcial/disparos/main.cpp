#include <cstdlib>
#include <iostream>
#include <sstream>
#define MAX1 2
using namespace std;
//-------------------------------------------------------cola comeinzo

typedef int tipolista_c;

class Nodo{
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

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            void del(void);
            void add(tipolista_c d,tipolista_c e);
            bool esvacia(void);
            tipolista_c *cabeza(void);
            Lista *resto(void);
            string toPrint(tipolista_c p);   
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
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}

tipolista_c *Lista::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return NULL; 
  }
  return czo->get_dato();
}

Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}

string Lista::toPrint(tipolista_c p)
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
            int *tope();
            int colavacia() { return l->esvacia();};
            void encolar(int a, int b) ;
            void desencolar();
};
int *Cola::tope() {
           if (colavacia()){
              cout<<"Error: Cola vacia"<<endl;
              return czoq->get_dato();
           } 
           else
              return czoq->get_dato();
}

void Cola::encolar(int a,int b) {
     l->add(a,b);
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

//---------------------------------------------------------cola fin

typedef Cola tipolista;

class Nodo_p{
    private: 
        tipolista *dato;
        int dato2;
        Nodo_p *next;
    public:
        Nodo_p() {next=NULL;};
        Nodo_p(tipolista *a) {dato=a; next=NULL;};
        Nodo_p(int b) {dato2=b; next=NULL;};
        
        void set_next(Nodo_p *n) {next=n; };
        tipolista *get_dato() {return dato; };
        int get_dato2() {return dato2; };
        Nodo_p *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista_p{
    private: Nodo_p *czo;
    public:
            Lista_p() {czo=new Nodo_p();};
            Lista_p(Nodo_p *n) {czo=n;};
            void add(tipolista *d);
            bool esvacia(void);
            tipolista *cabeza(void);
            Lista_p *resto(void);  
            void del(void);
            
            void add2(int a);
            int cabeza2(void);
            Lista_p *resto2(void); 
};
   
void Lista_p::add2(int d)
{  
     Nodo_p *nuevo=new Nodo_p(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
   
void Lista_p::add(tipolista *d)
{  
     Nodo_p *nuevo=new Nodo_p(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista_p::esvacia(void)
{   
    return czo->es_vacio();
}

int Lista_p::cabeza2(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return -1; 
  }
  return czo->get_dato2();
}

tipolista *Lista_p::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return czo->get_dato(); 
  }
  return czo->get_dato();
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
//-------------------------------------------PILA
class Pila:public Lista_p{
   
    public:
        Pila(){Lista_p();};
        void apilar(tipolista *x);
        tipolista *tope_p(void);
        void desapilar (void);
        bool pilavacia();
        
        void apilar2(int x);
        int tope_p2(void);
};

void Pila::apilar2(int x)
{  
   add2(x);                                 
}

void Pila::apilar(tipolista *x)
{  
   add(x);                                 
}

int Pila::tope_p2(void)
{
    return cabeza2();    
}

tipolista *Pila::tope_p(void)
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

Pila *ProxDisparos (int i,int j)
{
    Pila *p=new Pila();
    Cola *c=new Cola();
    Cola *k=new Cola();
    int iaux,jaux;
    
    for (iaux=i-1;iaux>=i-3;iaux--)
    {
        c->encolar(iaux,j);
    }
    p->apilar (c);
    
    for (iaux=i+1;iaux<=i+3;iaux++)
    {
        c->encolar(iaux,j);
    }
    p->apilar (c);
    
    for (jaux=j-1;jaux>=j-3;jaux--)
    {
        c->encolar(i,jaux);
    }
    p->apilar (c);
    
    for (jaux=j+1;jaux<=j+3;jaux++)
    {
        c->encolar(i,jaux);
    }
    p->apilar (c);
    
    return p;
}

int main(int argc, char *argv[])
{
    Pila *p=new Pila();
    Pila *r=new Pila();
    Cola *a=new Cola();
    Cola *k=new Cola();
    
    Pila *c=new Pila();
    Pila *f=new Pila();
    
    int tablero [10][10];
    int i,d=0,n=0;
    int bh;
    char q;
    
    
    
    for (int i = 0; i<10; i++)
        {
                for (int j = 0; j<10; j++){tablero[i][j] = 0;}; 
                }
    
    ////////  Armado de las coordenadas /////////////////
        for (int co = 9;co>=0;co=co-2)
        {
                for (int fi = 9;fi>=0;fi--)
                {
                        f->apilar2(fi);c->apilar2(co);
                        }
                }
        for (int fi = 9; fi>=0;fi--)
        {
                for (int co = 8;co>=0;co=co-2)
                {
                        f->apilar2(fi);c->apilar2(co);
                        }
                }
    
    ///////////////////////////////////////////////////
     while (bh != 10)
        {
                if (tablero [f->tope_p2()][c->tope_p2()] != 0)
                {
                        f->desapilar();c->desapilar();
                }
                else
                {       //cout<<*(r->tope())<<endl;
                        cout<< "El proximo disparo es: "<<f->tope_p2()<<","<<c->tope_p2()<<endl;
                        cin>>q;
                        switch (q)
                        {
                                case 'a':  
                                                        tablero [f->tope_p2()][c->tope_p2()] = 5;d++;f->desapilar();c->desapilar();
                                                        break;
                                case 'h':
                                                        tablero [f->tope_p2()][c->tope_p2()] = 1;d++;bh++;f->desapilar();c->desapilar();
                                                        break;
                                case 'v':                
                                                        tablero [f->tope_p2()][c->tope_p2()] = 2;d++;
                                                        r=ProxDisparos(f->tope_p2(),c->tope_p2());//Se cargan los disparos cercanos al punto de averiado en una cola de pilas
                                                        
                                                        
                                                        for(i=0;i<3;i++) 
                                                        {
                                                            k=r->tope_p();
                                                            for (n=0;n<3;n++)
                                                            {    if (((*(k->tope())>(-1))&&(*(k->tope())<10))&&((*((k->tope())+1)>(-1))&&(*((k->tope())+1)<10)))
                                                                    {if(tablero [*(k->tope())][*((k->tope())+1)] != 0){ cout<< "El proximo disparo es: "<<*(k->tope())<<","<<*((k->tope())+1)<<endl;
                                                                        cin>>q;
                                                                    switch (q)
                                                                    {
                                                                        case 'a':   n=3;tablero [f->tope_p2()][c->tope_p2()] = 5;d++;;break;
                                                                        case 'h':    
                                                                        
                                                                    } 
                                                                    
                                                                    }
                                                                    }else{k->desencolar();}
                                                            }
                                                            r->desapilar();
                                                        }
                                                        
                                                        f->desapilar();c->desapilar();
                                                        break;               
                                    
                                default :    cout<<"La respuesta ingresada no es valida, recuerde que los valores a ingresar son a, v, h (en minusculas). Por favor intentelo nuevamente."<<endl;
                                                        break;
                        }
                }
        }
        
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
