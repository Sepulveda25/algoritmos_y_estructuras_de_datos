#////////////////////////////////////////////////////////////////////////
//
//              Alumnos:
//                              - Sepulveda, Federico.
//                              - Gutierrez, Cristian Gabriel.
//                              - Barbiani, Gianfranco.
//
////////////////////////////////////////////////////////////////////////
 
 
#include <iostream>
#include <sstream>
#include <string.h>
#include <cstdlib>
#define MAX 100
#define MAX1 2
 
using namespace std;
 
///////////////----------Cola COMIENZO----------------------------------
 
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
 
//----------------------------------------------------------------------
 
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
           if (colavacia()) {  /*cout<<"Error: Cola vacia"<<endl; */}
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
 
///////////-----------------Cola FIN------------------------------------
 
///////////---------------Pila COMIENZO---------------------------------
 
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
            bool esvacia(void);
            tipolista *cabeza(void);
            Lista_p *resto(void);  
            void del(void);
            void add2 (int a, int b);
            int *cabeza2 (void);
            Lista_p *resto2(void);
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
 
//----------------------------------------------------------------------
 
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
 
///////////-------------------Pila FIN----------------------------------
 
///////////-----------Pila de Colas COMIENZO----------------------------
 
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
 
///////////-----------------Pila de Colas FIN---------------------------

///////////-----------------Imprimir por pantalla el tablero COMIENZO 
void imprimir (int *tablero)
{
    system("cls");
    
    for(int i = 0; i<10; i++)
        {
                cout<<" ___ ___ ___ ___ ___ ___ ___ ___ ___ ___"<<endl;
                for(int j = 0; j<10; j++)
                {
                        if(j==0) cout<<"| "<<*(tablero+(i*10)+j)<<" | ";
                        else cout<<*(tablero+(i*10)+j)<<" | ";
                }
                cout<<endl;
                if(i == 9) cout<<" ___ ___ ___ ___ ___ ___ ___ ___ ___ ___"<<endl;
        }
}
///////////-----------------Imprimir por pantalla el tablero FIN 

 
///////////------------------Main COMIENZO------------------------------
 
int main()
{
        //-----------Saludo de bienvenida-----------------------------------
        cout<<"Bienvenido al oponente virtual de batalla naval. A continuacion se mostraran por pantalla las cordenadas donde se van a efectuar los disparos; por favor responda con: "<<endl;
        cout<<endl<<"           - 'a'--> AGUA"<<endl; cout<<"           - 'v'--> AVERIADO"<<endl; cout<<"           - 'h'--> HUNDIDO"<<endl;
        cout<<endl<<"Recuerde ingresar valores logicos que se correspondan con su tablero."<<endl;
        cout<<endl<<"Al finalizar del juego se mostrara su tablero donde: "<<endl;
        cout<<endl<<"- '5'--> DISPARO ERRADO"<<endl; cout<<"- '1'--> DISPARO ACERTADO"<<endl; cout<<"- '0'--> NUNCA SE REALIZO UN DISPARO A ESE CASILLERO"<<endl;
       
        //-----------Declaracion e inicializacion variables-----------------
        Pila *shoot=new Pila();    
    Cola *aux =new Cola();
        Pila *f= new Pila();
        int tablero [10][10];
        int d = 0;
        int hu=0, exito = 0;
        char r;
        int barcos_hundidos = 0;
       
        //-----------Armado de tablero--------------------------------------
        for (int i = 0; i<10; i++)
        {
                for (int j = 0; j<10; j++){tablero[i][j] = 0;};
        }
       
        //------------Armado de las coordenadas generales-------------------
        for (int co = 8;co>=0;co=co-2)
        {
                for (int fi = 9;fi>=1;fi=fi-2)  {       f->apilar2(fi,co); }
        }
        for (int fi = 8; fi>=0;fi=fi-2)
        {
                for (int co = 8;co>=0;co=co-2)  {       f->apilar2(fi,co); }
        }
        for (int co = 9;co>=1;co=co-2)
        {
                for (int fi = 8;fi>=0;fi=fi-2)  {       f->apilar2(fi,co); }
        }      
        for (int fi = 9; fi>=1;fi=fi-2)
        {
                for (int co = 9;co>=1;co=co-2)  {       f->apilar2(fi,co); }
        }
       
        //---------------JUEGO!!--------------------------------------------
        while (barcos_hundidos != 10)
        {
                if (tablero [*(f->tope_p2())][*(f->tope_p2()+1)] != 0) {        f->desapilar(); }
                else
                {
                        cout<<endl<<"Nuestro proximo disparo es "<<"("<<*(f->tope_p2())<<","<<*(f->tope_p2()+1)<<")"<<endl;
                        cin>>r;
                        switch (r)
                        {
                                case 'a':  
                                                        tablero [*(f->tope_p2())][*(f->tope_p2()+1)] = 5;d++;f->desapilar(); imprimir(*tablero);
                                                        break;
                                case 'h':
                                                        tablero [*(f->tope_p2())][*(f->tope_p2()+1)] = 1;d++;barcos_hundidos++;f->desapilar();exito++;imprimir(*tablero);
                                                        break;
                                case 'v':       {
                                                                hu=0;tablero [*(f->tope_p2())][*(f->tope_p2()+1)] = 1;exito++;d++;shoot = armar(*(f->tope_p2()),*(f->tope_p2()+1));
                                                                while (hu!=1)
                                                                {
                                                                        aux=shoot->tope_p();
                                                                        if (tablero [*(aux->tope())][*(aux->tope()+1)] != 0)    {       shoot->desapilar(); }
                                                                        else
                                                                        {       imprimir(*tablero);
                                                                                cout<<endl<<"Nuestro proximo disparo es "<<"("<<*(aux->tope())<<","<<*(aux->tope()+1)<<")"<<endl;
                                                                                cin>>r;
                                                                                switch (r)
                                                                                {
                                                                                        case 'a':
                                                                                                                tablero [*(aux->tope())][*(aux->tope()+1)] = 5;shoot->desapilar();d++;imprimir(*tablero);
                                                                                                                break;
                                                                                        case 'h':
                                                                                                                tablero [*(aux->tope())][*(aux->tope()+1)] = 1;hu++;barcos_hundidos++;d++;exito++;imprimir(*tablero);
                                                                                                                break;
                                                                                        case 'v':
                                                                                                                tablero [*(aux->tope())][*(aux->tope()+1)] = 1;aux->desencolar();d++;exito++;imprimir(*tablero);
                                                                                                                break;
                                                                                        default :   cout<<endl<<"La respuesta ingresada no es valida, recuerde que los valores a ingresar son a, v, h (en minusculas). Por favor intentelo nuevamente."<<endl;
                                                                                                                break;
                                                                                }
                                                                        }
                                                                }
                                                                f->desapilar();
                                                                break;
                                                        }
                                default :   cout<<endl<<"La respuesta ingresada no es valida, recuerde que los valores a ingresar son a, v, h (en minusculas). Por favor intentelo nuevamente."<<endl;
                                                        break;
                        }                      
                }
        }
       
        //---------------Fin del Juego! --> ESTADISTICAS Y TABLERO-----------  
        for(int i = 0; i<10; i++)
        {
                cout<<" ___ ___ ___ ___ ___ ___ ___ ___ ___ ___"<<endl;
                for(int j = 0; j<10; j++)
                {
                        if(j==0) cout<<"| "<<tablero[i][j]<<" | ";
                        else cout<<tablero[i][j]<<" | ";
                }
                cout<<endl;
                if(i == 9) cout<<" ___ ___ ___ ___ ___ ___ ___ ___ ___ ___"<<endl;
        }
        cout<<endl<<"La cantidad de disparos realizados son "<<d<<" de los cuales "<<exito<<" fueron exitosos."<<endl;
        return 0;
}
 
////////////////-----------------Main FIN-------------------------------
