#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>
#include <cstdlib>
#include <string.h>
#define MAX 100
#define MAX1 12
 
using namespace std;
 
///////////////-------/////////------------Heapsort con Vehiculos COMIENZO-----------/////////--------/////////////////////
 
class Vehiculos
{      
        private:
                        struct vehiculo{                                int prioridad;
                                                        //Lista2 *recorrido;
                                                        int origen;
                                                        int destino;
                                                        bool seMovio;  
                        };
                        vehiculo autos;
       
        public:
                        Vehiculos(int pri);
                        void set_origen (int orig){autos.origen=orig;};
                        void set_destino(int dest){autos.destino=dest;};
                        //~ void set_recorrido(Lista2 *rec){autos.recorrido=rec;};
                        //~ int get_origen (void){return autos.origen;};
                        //~ int get_destino(void){return autos.destino;};
                        int get_prioridad (void){return autos.prioridad;};
                        //~ Lista2 *get_recorrido(void){return autos.recorrido;};
};
 
 Vehiculos::Vehiculos(int pri)
 {
        autos.prioridad=pri;
 }
 
int cantidad (Vehiculos **v)
{
        int c=0;
        for(int i = MAX1; i >= 1; i--)  
        {
                if (v[i]->get_prioridad()==0){i=0; return c;}
                c++;
        }
        return c;
}
 
void swap (Vehiculos **v,int uno ,int dos)
{
        Vehiculos *aux1 = new Vehiculos(0);
        aux1 = v[uno];
        v[uno] = v[dos];
        v[dos] = aux1;
}
 
void comp_pad_hij(Vehiculos **v, int p, int altu)
{
     if ((p*2 >= altu) || (((p*2)+1) >= altu)) cout<<"";
     else if(v[p]->get_prioridad() < v[p*2]->get_prioridad())
          {
              //~ swap((v+p), (v+(p*2)));
              swap(v,p,(p*2));
              comp_pad_hij(v, p, altu);
              comp_pad_hij(v, p*2, altu);
          }
          else if(v[p]->get_prioridad() < v[(p*2)+1]->get_prioridad())
               {
                  //~ swap((v+p), (v+((p*2)+1)));
                  swap(v,p,((p*2)+1));
                  comp_pad_hij(v, p, altu);
                  comp_pad_hij(v, ((p*2)+1), altu);
               }
               else comp_pad_hij(v, MAX1, 0);
}
 
void heapsort (Vehiculos **vector)
{
//--------------------- Armado de la Heap-------------------------------
        int u = MAX1, v = u;
        while (v > 0)
        {
                bool house = true;
                u = v;
                while ((u > 1) && house)
                {                      
                                if (vector[u]->get_prioridad() > vector[u/2]->get_prioridad())
                                {
                                        swap(vector,u,u/2);                    
                                        u = u/2;
                                }
                                else house = false;
                }
                v--;  
        }
 
       
//------------------------ Ordenar Heap---------------------------------
for(int o = MAX1; o > 1; o--)
{
    swap(vector,1,o);
    comp_pad_hij(vector, 1, o);
}
 
}
       
void impre(Vehiculos **v)
{
  cout<<endl;
  for(int i = MAX1; i >= 1; i--)  { cout<<v[i]->get_prioridad()<<endl; }
}
 
void encolar (Vehiculos **vector, Vehiculos *aux)
{
       
            for (int c=1;c<13;c++)
           {
                   if (vector[c]->get_prioridad() == 0)
                   {**(vector+c) = *aux; c=12;}
                }
                heapsort(vector);
                //~ impre (vector);
}
       
void desencolar (Vehiculos **vector)
{
        //~ for(int i = MAX1; i>MAX1-4; i--)
        //~ {
                if (vector[MAX1]->get_prioridad() != 0)
                {
                        Vehiculos *aux = new Vehiculos(0);
                        **(vector+MAX1) = *aux;
                }
        //~ }  
        heapsort(vector);
        //~ impre (vector);
}
 
///////////////-------/////////------------Heapsort con Vehiculos FIN-----------/////////--------/////////////////////
 
///////////////-------/////////-------------Grafo COMIENZO---------------///////-------//////////////////
 
///////////////--------------------Lista de Arrays COMIENZO--------------------------------
 
 
class Nodo
{
    protected:
                struct datos {
                                                int esquina;
                                                Vehiculos *cola_v[MAX1+1];                     
                                         };
                datos dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(int e, Vehiculos *p)
        {
                        dato.esquina = e;
                        for (int i = 0; i<MAX1;i++){*((dato.cola_v)+(i+1)) = new Vehiculos(0);}
                        encolar(dato.cola_v, p);
                        next=NULL;
                };
        void set_next(Nodo *n) {next=n; };
        int get_esquina() {return dato.esquina; };
        Vehiculos **get_cola_v(){return dato.cola_v;};
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
            void add(int esq,Vehiculos *tutu);
            bool esvacia(void);
                        int cabeza_esquina(void);
                        Vehiculos **cabeza_cola_v(void);
            Lista_de_arrays *resto(void);
            Nodo *get_czo(void){return czo;};
            //void toPrint_sec(Lista_de_arrays p2);
            void set_peso(int destino, int peso);
            int cant (void);
};
 
//~ int Lista_de_arrays::cant(void)
//~ {
        //~ return cantidad((czo->get_cola_v()));
//~ }
 
void Lista_de_arrays::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
 
void Lista_de_arrays::add(int esq,Vehiculos *tutu)
{  
     Nodo *nuevo=new Nodo(esq,tutu);
     nuevo->set_next(czo);
     czo=nuevo;
}
 
bool Lista_de_arrays::esvacia(void) {     return czo->es_vacio(); }
 
int Lista_de_arrays::cabeza_esquina(void)
{
          if(esvacia())
          {
                        //~ cout<<" Error, Cabeza de lista vacia";
                        return 0;
          }
          return czo->get_esquina();
}
 
Vehiculos **Lista_de_arrays::cabeza_cola_v(void)
{
          if(esvacia())
          {
                        //~ cout<<" Error, Cabeza de lista vacia";
                        return czo->get_cola_v();
          }
          return czo->get_cola_v();
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
            void add_vAux(Lista_de_arrays p2, int destino, Vehiculos *tutu);
            void add_v(Lista p1, int origen, int destino, Vehiculos *tutu, int iter);
            void print_heapAux(Lista_de_arrays p2, int destino);
            void print_heap(Lista p1, int origen, int destino, int iter);
            int cant_heapAux(Lista_de_arrays p2, int destino);
            int cant_heap(Lista p1, int origen, int destino, int iter);
            void desencolar_heap(Lista p1, int origen, int destino, int iter);
            void desencolar_heapAux(Lista_de_arrays p2, int destino);
            Vehiculos *get_vehiculoAux(Lista_de_arrays p2, int destino);
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
        if((p2.resto())->esvacia())
        {
                        cout<< "  Apunta a: " << p2.cabeza_esquina()<<endl;
                        //cout<< " Con peso: " << cantidad((**p2.cabeza_cola_v())) << endl;
                }
        else { cout<< "  Apunta a: " << p2.cabeza_esquina()<<endl;
                        //<< " Con peso: " << cantidad(p2.cabeza_cola_v()) << endl;
                        toPrint_sec(*(p2.resto()));
                        }
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
 
void Lista::add_vAux(Lista_de_arrays p2, int destino, Vehiculos *tutu)
{
        if(p2.esvacia()) {cout<<"Error ese DESTINO es INVALIDO!!"<<endl; }
        else if(destino != (p2.cabeza_esquina())) { add_vAux(*(p2.resto()), destino, tutu); }
                 else
                 {
                        //~ Vehiculos *caca[MAX1];
                        //~ *caca = *(*p2.cabeza_cola_v());
                        encolar(p2.cabeza_cola_v(), tutu);
                        //~ cout<<(*(p2.cabeza_cola_v())+2)->get_prioridad();
                        cout<<"Vehiculo agregado con exito "<<endl;
                 }
}
 
void Lista::add_v(Lista p1, int origen, int destino, Vehiculos *tutu, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
        else if(iter == origen) { add_vAux(p1.cabeza(), destino, tutu); }
                 else
                 {
                        // cout<<count<<" ";
                        add_v(*(p1.resto()), origen, destino, tutu, --iter);
                 }
}
 
void Lista::print_heapAux(Lista_de_arrays p2, int destino)
{
        if((p2.resto())->esvacia())
        {/*cout<<"Error ese DESTINO es INVALIDO!!"<<endl;*/
                 impre(p2.cabeza_cola_v());
                 /*(p2.cabeza_cola_v()).get_prioridad()*/; }
        else if(destino != (p2.cabeza_esquina())) { print_heapAux(*(p2.resto()), destino); }
                 else
                 {
                         impre(p2.cabeza_cola_v());
                        /*p2.get_prioridad()*/;
                        //cout<<"Exito cambiando el peso "<<endl;
                 }
}
 
void Lista::print_heap(Lista p1, int origen, int destino, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
        else if(iter == origen) { print_heapAux(p1.cabeza(), destino); }
                 else
                 {
                        print_heap(*(p1.resto()), origen, destino,--iter);
                 }
}
 
int Lista::cant_heapAux(Lista_de_arrays p2, int destino)
{
        if((p2.resto())->esvacia())
        {/*cout<<"Error ese DESTINO es INVALIDO!!"<<endl;*/
                 return cantidad(p2.cabeza_cola_v());
                 /*(p2.cabeza_cola_v()).get_prioridad()*/; }
        else if(destino != (p2.cabeza_esquina())) {return cant_heapAux(*(p2.resto()), destino); }
                 else
                 {
                         return cantidad(p2.cabeza_cola_v());
                        /*p2.get_prioridad()*/;
                        //cout<<"Exito cambiando el peso "<<endl;
                 }
}
 
int Lista::cant_heap(Lista p1, int origen, int destino, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; return -1;}
        else if(iter == origen) { return cant_heapAux(p1.cabeza(), destino); }
                 else
                 {
                        return cant_heap(*(p1.resto()), origen, destino,--iter);
                 }
}
 
void Lista::desencolar_heapAux(Lista_de_arrays p2, int destino)
{
        if((p2.resto())->esvacia())
        {/*cout<<"Error ese DESTINO es INVALIDO!!"<<endl;*/
                 desencolar(p2.cabeza_cola_v());
                 /*(p2.cabeza_cola_v()).get_prioridad()*/; }
        else if(destino != (p2.cabeza_esquina())) { desencolar_heapAux(*(p2.resto()), destino); }
                 else
                 {
                         desencolar(p2.cabeza_cola_v());
                        /*p2.get_prioridad()*/;
                        //cout<<"Exito cambiando el peso "<<endl;
                 }
}
 
void Lista::desencolar_heap(Lista p1, int origen, int destino, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
        else if(iter == origen) { desencolar_heapAux(p1.cabeza(), destino); }
                 else
                 {
                        desencolar_heap(*(p1.resto()), origen, destino,--iter);
                 }
}
 
//~ Vehiculos *Lista::get_vehiculoAux(Lista_de_arrays p2, int destino)
//~ {
        //~ if((p2.resto())->esvacia())
        //~ {/*cout<<"Error ese DESTINO es INVALIDO!!"<<endl;*/
                 //~ return (*p2.cabeza_cola_v()+MAX1);
                 //~ /*(p2.cabeza_cola_v()).get_prioridad()*/; }
        //~ else if(destino != (p2.cabeza_esquina())) { return get_vehiculoAux(*(p2.resto()), destino); }
                 //~ else
                 //~ {
                        //~ return (*p2.cabeza_cola_v()+MAX1);
                        //~ /*p2.get_prioridad()*/;
                        //~ //cout<<"Exito cambiando el peso "<<endl;
                 //~ }
//~ }
 //~ 
//~ Vehiculos Lista::get_vehiculo(Lista p1, int origen, int destino, int iter)
//~ {
        //~ if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
        //~ else if(iter == origen) { return get_vehiculoAux(p1.cabeza(), destino); }
                 //~ else
                 //~ {
                        //~ return get_vehiculo(*(p1.resto()), origen, destino,--iter);
                 //~ }
//~ }
///////////////--------------------Lista de listas FIN--------------------------------
 
 
///////////////-------/////////-------------Grafo FIN---------------///////-------//////////////////
 
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
//~ void mover_auto (Lista p1, int origen, int destino, int inter)
//~ {
        //~ //cout<<p1.get_peso(p1,origen,inter,iter)<<endl;
        //~ if (p1->cant_heap(*p1, inter, destino, 81)<12)
        //~ {
                //~ p1->add_v(*p1, inter, destino, ,81);
               //~ 
                //~ }
        //~ p1.set_peso(p1, origen, inter, (p1.get_peso(p1,origen,inter,iter))-1, iter);
        //~ p1.set_peso(p1, inter, destino, (p1.get_peso(p1,inter,destino,iter))+1, iter);
//~ }
 
 
int main()
{
    Lista *Mapa = new Lista();    
    int texto;
   
    ifstream archivo_entr;
   
    archivo_entr.open("ADY.txt");
   
    // Vehiculos *vector[MAX1];
        // for (int i = 0; i<MAX1;i++){*(vector+(i+1)) = new Vehiculos(0);}
       
        Vehiculos *tutu = new Vehiculos(0);
        Vehiculos *tutu2 = new Vehiculos(4);
        Vehiculos *tutu3 = new Vehiculos(3);
   
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
                ady->add(texto,tutu);
                tutu = new Vehiculos(0);
        }
       
        
        Mapa->print_heap(*Mapa, 74, 75, 81);
        Mapa->add_v(*Mapa, 74, 75, tutu2, 81);
        Mapa->add_v(*Mapa, 74, 75, tutu3, 81);
        Mapa->print_heap(*Mapa, 74, 75, 81);
        cout<<endl<<"Cantidad = "<<Mapa->cant_heap(*Mapa, 74, 75, 81)<<endl;
        Mapa->desencolar_heap(*Mapa, 74, 75, 81);
        Mapa->print_heap(*Mapa, 74, 75, 81);
        cout<<endl<<"Cantidad = "<<Mapa->cant_heap(*Mapa, 74, 75, 81)<<endl;
       
    //~ Mapa->toPrint_pri(*Mapa, 81);
    //~ cout<<endl<<(ady->cabeza_cola_v() + 1)->get_prioridad()<<endl;
   
    //~ Vehiculos *tutu[MAX1] = ady->cabeza_cola_v();
    //~ impre(tutu);
    //~ cout<<endl<<tutu[0]->get_prioridad()<<endl;
    //~ impre(ady->cabeza_cola_v());
   
    //~ Mapa->set_peso(*Mapa, 74, 75, 5, 81);
    //~ Mapa->set_peso(*Mapa, 75, 74, 5, 81);
    //~ Mapa->set_peso(*Mapa, 49, 48, 3, 81);
       
    //~ Mapa->toPrint_pri(*Mapa, 81);
       
        //~ mover_auto(*Mapa,49,59,50,81);
        //Mapa->set_peso(*Mapa, 49, 50, 7, 81);
        //mover_auto(*Mapa,49,59,50,81);
       
        //~ Mapa->toPrint_pri(*Mapa, 81);
       
        ////////////////////////////////////////////
       
        //~ int Vector[max] = {15,48,47,55,6,27,87,37,37,43};
        //~ Vehiculos *tutu = new Vehiculos(15);
        //~ cout<<tutu->get_prioridad()<<endl;
       
        //~ impre(vector);
        //~ Vehiculos *aux = new Vehiculos(0);
       
           //~ for (int j=0;j<6;j++)
           //~ {
                   //~ int pri;
                   //~ cout<<endl<<"Ingrese el proximo valor al heap: ";
                   //~ cin>>pri;
                   //~ cout<<endl;
                   //~ aux = new Vehiculos(pri);
                   //~ encolar(vector, aux);
                //~ }
                //~ impre(vector);
       
        //~ cout<<endl<<"Desencolamos los 4 primeros."<<endl;
        //~ desencolar(vector);
       
        return 0;
}
