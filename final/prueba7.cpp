#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <queue>
 
#define MAX2 10005
#define MAX1 4
#define AUTO 80
#define MAX 10005 //maximo numero de vértices
#define Node pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas
 
 
using namespace std;
 
int semaforo[177][3];
 
void inicial1()
{      
        for(int i=1;i<178;i++)
        {
                for(int j=0;j<3;j++) {semaforo[i][j]=-1;}
        }
}
int Av[4];
int Ad[4];
void inicial(){ for(int i = 0;   i <4;   i++){Av[i]=0;} }
 
 
///////////////-------/////////------------Heapsort con Vehiculos COMIENZO-----------/////////--------/////////////////////
 
class Vehiculos
{      
        private:
                                struct vehiculo{                
                                                                        int prioridad;
                                                                        int recorrido[MAX2];
                                                                        int origen;
                                                                        int destino;
                                                                        bool seMovio;
                                                                        bool nuestro;  
                                                           };
                                vehiculo autos;
       
        public:
                                Vehiculos(int pri);
                                void set_origen (int orig){autos.origen=orig;};
                                void set_destino(int dest){autos.destino=dest;};
                                void set_recorrido(int rec,int i){autos.recorrido[i]=rec;};
                                void set_prioridad(int prior){autos.prioridad=prior;};
                                void set_esNuestro(void){autos.nuestro=true;};
                                void set_NoesNuestro(void){autos.nuestro=false;};
                                int get_origen (void){return autos.origen;};
                                int get_destino(void){return autos.destino;};
                                int get_prioridad (void){return autos.prioridad;};
                                int get_recorrido(int i){return autos.recorrido[i];};
                                bool get_nuestro(void) {return autos.nuestro;};
};
 
Vehiculos::Vehiculos(int pri)
{
        autos.prioridad=pri;
        for (int a=0; a<MAX2;a++){autos.recorrido[a]=-1;}
}
 
int cantidad (Vehiculos **v, bool av)
{
        int max = MAX1;
        int c=0;
   
        if (av){max=2*max;}
   
        for(int i = max; i >= 1; i--)  
        {
                if (v[i]->get_prioridad()==0){i=0; return c;}
                c++;
        }
        return c;
}
 
int congestion (Vehiculos **v, bool av)
{
        int max = MAX1;
        int c=0;
   
        if (av){max=2*max;}
   
        for(int i = max; i >= 1; i--)  
        {
                if (v[max]->get_prioridad()==0){if (av){c=0;};i=0; return c;}
                if (v[i]->get_prioridad()==0)
                {
                        if (av)
                        {
                                if (c%2==0){c=(c/2);}
                                else {c=(c/2)+1;}
                        }                      
                        i=0; return c;
                }
                c++;
        }
        if (av)
        {
                if (c%2==0){c=(c/2);}
                else {c=(c/2)+1;}
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
 
void comp_pad_hij(Vehiculos **v, int p, int altu, bool av)
{
        int max = MAX1;
        if(av){max = 2*max;}
    if ((p*2 >= altu) || (((p*2)+1) >= altu)) cout<<"";
    else if(v[p]->get_prioridad() < v[p*2]->get_prioridad())
        {
          swap(v,p,(p*2));
          comp_pad_hij(v, p, altu,av);
          comp_pad_hij(v, p*2, altu,av);
        }
        else if(v[p]->get_prioridad() < v[(p*2)+1]->get_prioridad())
                 {
                          swap(v,p,((p*2)+1));
                          comp_pad_hij(v, p, altu,av);
                          comp_pad_hij(v, ((p*2)+1), altu,av);
             }
             else comp_pad_hij(v, max, 0,av);
}
 
void heapsort (Vehiculos **vector, bool av)
{
//--------------------- Armado de la Heap-------------------------------
 
        int max = MAX1;
        if (av) {max = max * 2;}
 
        int u = max, v = u;
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
        for(int o = max; o > 1; o--)
        {
                        swap(vector,1,o);
                        comp_pad_hij(vector, 1, o,av);
        }
 
}
       
void impre(Vehiculos **v,bool av)
{
        int max=MAX1;
        if(av){max=max*2;}
        cout<<endl;
        for(int i = max; i >= 1; i--)  { cout<<v[i]->get_prioridad()<<endl; }
}
 
Vehiculos *pos_MiAuto(Vehiculos **v,bool av)
{
        int max=MAX1;
        if(av){max=max*2;}
        for(int i = max; i >= 1; i--)   {       if(v[i]->get_nuestro())         {return v[i];}       }
        return new Vehiculos(100);
}
 
Vehiculos *get_v(Vehiculos **v,bool av)
{  
        int max=MAX1;
        if(av){max=max*2;}
        return v[max];
}
 
void encolar (Vehiculos **vector, Vehiculos *aux,bool av)
{
   int max=MAX1;
        if(av){max=max*2;}  
   for (int c=max; c>0; c--)
   {
           if(vector[c]->get_prioridad() == 0)    {**(vector+c) = *aux; c=1;}
   }
   for (int c=1; c<max+1; c++)
   {
           if(vector[c]->get_prioridad() > 1)  {  heapsort(vector,av); c=max+1;  }
   }
}
       
void desencolar (Vehiculos **vector,bool av)
{      
        int max=MAX1;
        if(av){max=max*2;}
        if (vector[max]->get_prioridad() != 0)
                {
                                Vehiculos *v_aux[max+1];
                                for(int x=1; x<=max+1; x++){ v_aux[x] = new Vehiculos(0);}
                                Vehiculos *aux = new Vehiculos(0);
                                **(vector+max) = *aux;
                                for(int j=max; j>1; j--) { *v_aux[j] = **(vector + (j-1)); }
                                for(int j=max; j>1; j--) { **(vector + j) =*v_aux[j] ; }
                }
}
 
///////////////-------/////////------------Heapsort con Vehiculos FIN-----------/////////--------/////////////////////
 
 
 
///////////////-------/////////------------Heapsort con Semaforos COMIENZO-----------/////////--------/////////////////////
 
void swap_S (int uno ,int dos)
{
        int aux0 = semaforo[uno][0];
        int aux1 = semaforo[uno][1];
        int aux2 = semaforo[uno][2];
       
        semaforo[uno][0] = semaforo[dos][0];
        semaforo[uno][1] = semaforo[dos][1];
        semaforo[uno][2] = semaforo[dos][2];
       
        semaforo[dos][0] = aux0;
        semaforo[dos][1] = aux1;
        semaforo[dos][2] = aux2;
}
 
void comp_pad_hij_S(int p, int altu)
{
         int max = 177;
     if ((p*2 >= altu) || (((p*2)+1) >= altu)) cout<<"";
     else if(semaforo[p][2] < semaforo[p*2][2])
          {
              swap_S(p,(p*2));
              comp_pad_hij_S(p, altu);
              comp_pad_hij_S(p*2, altu);
          }
          else if (semaforo[p][2] < semaforo[(p*2)+1][2])
               {
                  swap_S(p,((p*2)+1));
                  comp_pad_hij_S(p, altu);
                  comp_pad_hij_S(((p*2)+1), altu);
               }
               else comp_pad_hij_S(max, 0);
}
 
void heapsort_S (void)
{
//--------------------- Armado de la Heap-------------------------------
        int max = 177;
 
        int u = max, v = u;
        while (v > 0)
        {
                bool house = true;
                u = v;
                while ((u > 1) && house)
                {                      
                        if (semaforo[u][2] > semaforo[u/2][2])
                        {
                                swap_S(u,u/2);                    
                                u = u/2;
                        }
                        else house = false;
                }
                v--;  
        }
 
       
//------------------------ Ordenar Heap---------------------------------
        for(int o = max; o > 1; o--)
        {
                        swap_S(1,o);
                        comp_pad_hij_S(1, o);
        }
 
}
 
///////////////-------/////////------------Heapsort con Semaforos FIN-----------/////////--------/////////////////////
 
 
///////////////-------/////////------------Dijkstra COMIENZO-----------/////////--------////////////////
 
//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};
 
vector< Node > ady1[ MAX ]; //lista de adyacencia
vector< Node > ady2[ MAX ]; //lista de adyacencia
int distancia[ MAX ];      //distancia[ u ] distancia de vértice inicial a vértice con ID = u
bool visitado[ MAX ];      //para vértices visitados
priority_queue< Node , vector<Node> , cmp > Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
priority_queue< Node , vector<Node> , cmp > Q2; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
int V=81;                     //numero de vertices
int previo[ MAX ];         //para la impresion de caminos
int path[MAX2];
 
//función de inicialización
void init()
{
    for( int i = 0 ; i <= MAX ; i++ )
    {
        distancia[ i ] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[ i ] = false; //inicializamos todos los vértices como no visitados
        previo[ i ] = -1;      //inicializamos el previo del vertice i con -1
    }
        for (int u=1; u<MAX2; u++) {path[u]=-1;}
}
 
//Paso de relajacion
void relajacion( int actual , int adyacente , int peso )
{
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] )
    {
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        Q.push( Node( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}
 
//Paso de relajacion
void relajacion2( int actual , int adyacente , int peso )
{
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] )
    {
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        Q2.push( Node( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}
 
//Impresion del camino mas corto desde el vertice inicial y final ingresados
void print( int destino )
{
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        print( previo[ destino ] );  //recursivamente sigo explorando
    printf("%d " , destino );        //terminada la recursion imprimo los vertices recorridos
}
 
void camino( int destino, int i )
{
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        camino( previo[ destino ] ,++i);  //recursivamente sigo explorando
   
    path[i]=destino;        //terminada la recursion imprimo los vertices recorridos
}
 
 
void dijkstra( int inicial, int destino)
{
    init(); //inicializamos nuestros arreglos
    Q.push( Node( inicial , 0 ) ); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q.empty()){                   //Mientras cola no este vacia
        actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q.pop();                         //Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         //Marco como visitado el vértice actual
 
        for( unsigned int i = 0 ; i < ady1[ actual ].size() ; ++i ){ //reviso sus adyacentes del vertice actual
            adyacente = ady1[ actual ][ i ].first;   //id del vertice adyacente
            peso = ady1[ actual ][ i ].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !visitado[ adyacente ] ){        //si el vertice adyacente no fue visitado
                relajacion( actual , adyacente , peso ); //realizamos el paso de relajacion
            }
        }
    }
}
 
void dijkstra2( int inicial, int destino)
{
    init(); //inicializamos nuestros arreglos
    Q2.push( Node( inicial , 0 ) ); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q2.empty()){                   //Mientras cola no este vacia
        actual = Q2.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q2.pop();                         //Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         //Marco como visitado el vértice actual
 
        for( unsigned int i = 0 ; i < ady2[ actual ].size() ; ++i ){ //reviso sus adyacentes del vertice actual
            adyacente = ady2[ actual ][ i ].first;   //id del vertice adyacente
            peso = ady2[ actual ][ i ].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !visitado[ adyacente ] ){        //si el vertice adyacente no fue visitado
                relajacion2( actual , adyacente , peso ); //realizamos el paso de relajacion
            }
        }
    }
}
 
///////////////-------/////////------------Dijkstra FIN-----------/////////--------/////////////////////
 
 
///////////////-------/////////-------------Grafo COMIENZO---------------///////-------//////////////////
 
///////////////--------------------Lista de Arrays COMIENZO--------------------------------
 
 
class Nodo
{
    protected:
                struct datos {
                                                                int esquina;
                                                                Vehiculos *cola_v[MAX1*2+1];
                                                                int esAvenida;                  
                             };
                datos dato;
                Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(int e, Vehiculos *p)
        {  
                        bool av=true;
                        dato.esquina = e;
                        for (int i = 0; i<(MAX1*2+1);i++){*((dato.cola_v)+(i+1)) = new Vehiculos(0);}
                        encolar(dato.cola_v, p,av);
                        next=NULL;
                        dato.esAvenida = 0;
        };
        void set_next(Nodo *n) {next=n; };
        int get_esquina() {return dato.esquina; };
        Vehiculos **get_cola_v(){return dato.cola_v;};
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};
        int  get_esAvenida(){return dato.esAvenida;};
        void set_esAvenida(int n){dato.esAvenida=n;};
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
            void set_peso(int destino, int peso);
            void set_Avenida(int n);
            int get_Avenida(void);
};
 
int Lista_de_arrays::get_Avenida(void) {return czo->get_esAvenida();}
 
void Lista_de_arrays::set_Avenida(int n) {czo->set_esAvenida(n);}
 
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
           
            //***Metodos
            void add(Lista_de_arrays *d);
            bool esvacia(void);
            Lista_de_arrays cabeza(void);
            Lista *resto(void);
            void toPrint_pri(Lista p1, int count, Lista p0,bool av);
            void toPrint_sec(Lista p0,Lista_de_arrays p2, int count,bool av);
            void add_vAux(Lista_de_arrays p2, int inter, Vehiculos *tutu,bool av);
            void add_v(Lista p1, int origen, int inter, Vehiculos *tutu, int iter,bool av);
            void print_heapAux(Lista_de_arrays p2, int destino,bool av);
            void print_heap(Lista p1, int origen, int destino, int iter,bool av);
            int cant_heapAux(Lista_de_arrays p2, int destino,bool av);
            int cant_heap(Lista p1, int origen, int destino, int iter,bool av);
            void desencolar_heap(Lista p1, int origen, int destino, int iter,bool av);
            void desencolar_heapAux(Lista_de_arrays p2, int destino,bool av);
            Vehiculos *get_vehiculoAux(Lista_de_arrays p2, int destino,bool av);
            Vehiculos *get_vehiculo(Lista p1, int origen, int destino, int iter,bool av);
            void Dijks_Aux(Lista_de_arrays p2, int count);
            void Dijks(Lista p1, int count);
            void llenarMapa(Lista p1);
            void avenidaAux2(Lista_de_arrays p3,int count,int ori,Lista_de_arrays p2_bis);
            void avenidaAux1(Lista p0,int cor, int count,Lista_de_arrays p2_bis, int c);
            void avenidaAux(Lista p0,Lista_de_arrays p2, int count);
            void avenida(Lista p1, int count, Lista p0);
            void get_avenidaAux(Lista_de_arrays p2, int count, int i);
            void get_avenida(Lista p1, int count,int o);
            int congestion_heapAux(Lista_de_arrays p2, int destino,bool av);
            int congestion_heap(Lista p1, int origen, int destino, int iter,bool av);
            void heap_semaforoAux(Lista p0,Lista_de_arrays p2, int count,int &i,bool av);
            void heap_semaforo(Lista p1, int count, Lista p0,int &i,bool av);
            Vehiculos *posicion_heapAux(Lista_de_arrays p2, int destino,bool av);
            Vehiculos *posicion_heap(Lista p1, int origen, int destino, int iter,bool av);
            Vehiculos *get_MiAutoAux(Lista p0,Lista_de_arrays p2, int count,bool av);
            Vehiculos *get_MiAuto(Lista p1, int count, Lista p0, int mi_origen,bool av);
            void get_adyacenciaAux(Lista_de_arrays p2, int count, int i);
            void get_adyacencia(Lista p1, int count,int o);
            void Dijks_miAutoAux(Lista p0, Lista p1, Lista_de_arrays p2, int count);
                        void Dijks_miAuto(Lista p0, Lista p1, int count);
};
 
void Lista::add(Lista_de_arrays *d)
{  
     Nodo_l *nuevo=new Nodo_l(d);//creo un objeto nodo y lo cargo con d, luego le paso
                            //la direccion al puntero nuevo
     nuevo->set_next(czo);//al objeto nodo al que apunta nuevo invoco su metodo
                         // set_next y le paso de parametro el putero czo
     czo=nuevo;
}
 
bool Lista::esvacia(void) {  return czo->es_vacio(); }
 
Lista_de_arrays Lista::cabeza(void)
{
    if(esvacia())
    {
           //~ cout<<"Error, Cabeza de lista vacia";
           return czo->get_dato();
    }
    return czo->get_dato();
}
 
Lista *Lista::resto(void)
{
        Lista *l=new Lista(czo->get_next());
        return (l);
}
 
void Lista::toPrint_sec(Lista p0,Lista_de_arrays p2, int count,bool av)
{
        inicial();
        av = false;
        p0.get_avenida(p0,81,count);
        for (int i = 0; i < 4; i++){if (Av[i] == p2.cabeza_esquina()){av = true;i=4;}}
        if((p2.resto())->esvacia())  {  cout<< "  Apunta a: " << p2.cabeza_esquina()<< " cantidad de autos: " << p0.cant_heap(p0, count, p2.cabeza_esquina(), 81,av)<< " congestion: " << p0.congestion_heap(p0, count, p2.cabeza_esquina(), 81,av)<<endl; }
        else
        {
                cout<< "  Apunta a: " << p2.cabeza_esquina()<< " cantidad de autos: " << p0.cant_heap(p0, count, p2.cabeza_esquina(), 81,av)<< " congestion: " << p0.congestion_heap(p0, count, p2.cabeza_esquina(), 81,av)<<endl;
                toPrint_sec(p0,*(p2.resto()), count,av);
        }
}
 
void Lista::toPrint_pri(Lista p1, int count, Lista p0,bool av)
{
        //~ cout<<endl;
        if((p1.resto())->esvacia()) {cout<<count<<" "; toPrint_sec(p0,p1.cabeza(), count,av); }
        else
        {
                cout<<count<<" ";
                toPrint_sec(p0,p1.cabeza(), count,av);
                toPrint_pri(*(p1.resto()), --count, p0,av);
        }
}
 
void Lista::add_vAux(Lista_de_arrays p2, int inter, Vehiculos *tutu,bool av)
{
        if(p2.esvacia()) {/*encolar(p2.cabeza_cola_v(), tutu,av);cout<<"Error ese DESTINO es INVALIDO!! add_vAux "<<endl;*/}
        else if(inter != (p2.cabeza_esquina())) { add_vAux(*(p2.resto()), inter, tutu,av); }
                 else
                 {
                         encolar(p2.cabeza_cola_v(), tutu,av);
                         //~ cout<<"Vehiculo agregado con exito "<<endl;
                 }
}
 
void Lista::add_v(Lista p1, int origen, int inter, Vehiculos *tutu, int iter,bool av)
{
        if(p1.esvacia()) {/*cout<<"Error ese ORIGEN es INVALIDO!! add_v"; add_vAux(p1.cabeza(), inter, tutu,av);*/}
        else if(iter == origen) { add_vAux(p1.cabeza(), inter, tutu,av); }
                  else   {   add_v(*(p1.resto()), origen, inter, tutu, --iter,av);   }
}
 
void Lista::print_heapAux(Lista_de_arrays p2, int destino,bool av)
{
        if((p2.resto())->esvacia())  {  impre(p2.cabeza_cola_v(),av);  }
        else if(destino != (p2.cabeza_esquina())) { print_heapAux(*(p2.resto()), destino,av); }
                 else  {  impre(p2.cabeza_cola_v(),av); }
}
 
void Lista::print_heap(Lista p1, int origen, int destino, int iter,bool av)
{
        av = false;
        p1.get_avenida(p1,81,origen);
        for (int i = 0; i < 4; i++){if (Av[i] == p1.cabeza().cabeza_esquina()){av = true;}}
        if((p1.resto())->esvacia()) {/*cout<<"Error ese ORIGEN es INVALIDO!! print_heap";*/print_heapAux(p1.cabeza(), destino,av); }
        else if(iter == origen) { print_heapAux(p1.cabeza(), destino,av); }
                 else  {  print_heap(*(p1.resto()), origen, destino,--iter,av); }
}
 
int Lista::cant_heapAux(Lista_de_arrays p2, int destino,bool av)
{
        if((p2.resto())->esvacia())  {  return cantidad(p2.cabeza_cola_v(),av);  }
        else if(destino != (p2.cabeza_esquina())) {return cant_heapAux(*(p2.resto()), destino,av); }
                 else   {   return cantidad(p2.cabeza_cola_v(),av);   }
}
 
int Lista::cant_heap(Lista p1, int origen, int destino, int iter,bool av)
{
        if((p1.resto())->esvacia()) {/*cout<<"Error ese ORIGEN es INVALIDO!! cant_heap";*/ return cant_heapAux(p1.cabeza(), destino,av);  }
        else if(iter == origen) { return cant_heapAux(p1.cabeza(), destino,av); }
                 else   {   return cant_heap(*(p1.resto()), origen, destino,--iter,av);  }
}
 
int Lista::congestion_heapAux(Lista_de_arrays p2, int destino,bool av)
{
        if((p2.resto())->esvacia())  {  return congestion(p2.cabeza_cola_v(),av);  }
        else if(destino != (p2.cabeza_esquina())) {return congestion_heapAux(*(p2.resto()), destino,av); }
                 else   {   return congestion(p2.cabeza_cola_v(),av);   }
}
 
int Lista::congestion_heap(Lista p1, int origen, int destino, int iter,bool av)
{
        if((p1.resto())->esvacia()) {/*cout<<"Error ese ORIGEN es INVALIDO!! cant_heap";*/ return congestion_heapAux(p1.cabeza(), destino,av);  }
        else if(iter == origen) { return congestion_heapAux(p1.cabeza(), destino,av); }
                 else   {   return congestion_heap(*(p1.resto()), origen, destino,--iter,av);  }
}
 
void Lista::desencolar_heapAux(Lista_de_arrays p2, int destino,bool av)
{
        if((p2.resto())->esvacia())  {  desencolar(p2.cabeza_cola_v(),av); }
        else if(destino != (p2.cabeza_esquina())) { desencolar_heapAux(*(p2.resto()), destino,av); }
                 else   {   desencolar(p2.cabeza_cola_v(),av);   }
}
 
void Lista::desencolar_heap(Lista p1, int origen, int destino, int iter,bool av)
{
        if(p1.esvacia()) {/*cout<<"Error ese ORIGEN es INVALIDO!! desencolar_heap";*/ }
        else if(iter == origen) { desencolar_heapAux(p1.cabeza(), destino,av); }
                 else   {   desencolar_heap(*(p1.resto()), origen, destino,--iter,av); }
}
 
Vehiculos *Lista::get_vehiculoAux(Lista_de_arrays p2, int destino,bool av)
{
        if((p2.resto())->esvacia())   {    return get_v(p2.cabeza_cola_v(),av); }
        else if(destino != (p2.cabeza_esquina())) { return get_vehiculoAux(*(p2.resto()), destino,av); }
                 else  {   return get_v(p2.cabeza_cola_v(),av);    }
}
 
Vehiculos *Lista::get_vehiculo(Lista p1, int origen, int destino, int iter,bool av)
{
        if(p1.esvacia()) {/*cout<<"Error ese ORIGEN es INVALIDO!! get_vehiculo";*/return new Vehiculos(0); }
        else if(iter == origen) { return get_vehiculoAux(p1.cabeza(), destino,av); }
                 else   {   return get_vehiculo(*(p1.resto()), origen, destino,--iter,av);  }
}
 
void Lista::avenidaAux2(Lista_de_arrays p3,int count,int cor,Lista_de_arrays p2_bis)
{      
        if(p3.cabeza_esquina() == count)  { p3.set_Avenida(count);}
        else if((p3.esvacia())) { /*cout<<endl<<count<<" NO! es avenida con "<<cor<<endl;*/ }
                  else   { avenidaAux2(*(p3.resto()), count,cor,p2_bis); }
}
 
void Lista::avenidaAux1(Lista p0,int cor, int count,Lista_de_arrays p2_bis, int c)
{
        if(c == cor)   { avenidaAux2(p0.cabeza(), count,cor,p2_bis); }
        else   {  avenidaAux1(*(p0.resto()),cor,count,p2_bis,--c);  }
}
 
 
void Lista::avenidaAux(Lista p0,Lista_de_arrays p2, int count)
{
   if((p2.resto())->esvacia()) { avenidaAux1(p0,p2.cabeza_esquina(),count,p2,81);}
   else
        {
                avenidaAux1(p0,p2.cabeza_esquina(),count,p2,81);
                avenidaAux(p0,*(p2.resto()), count);
        }
}
 
 
void Lista::avenida(Lista p1, int count, Lista p0)
{
        if((p1.resto())->esvacia()) { avenidaAux(p0,p1.cabeza(), count); }
        else
        {
                avenidaAux(p0,p1.cabeza(), count);
                avenida(*(p1.resto()), --count, p0);
        }
}
 
 
void Lista::get_avenidaAux(Lista_de_arrays p2, int count, int i)
{
        if((p2.resto())->esvacia())  {Av[i] = p2.get_Avenida();}
        else
        {
                Av[i] = p2.get_Avenida();
                get_avenidaAux(*(p2.resto()), count, ++i);
        }
}
 
 
void Lista::get_avenida(Lista p1, int count,int o)
{
        inicial();
        if(count == o) {  get_avenidaAux(p1.cabeza(), count, 0); }
        else    {   get_avenida(*(p1.resto()), --count,o);     }
}
 
void Lista::get_adyacenciaAux(Lista_de_arrays p2, int count, int i)
{
        if((p2.resto())->esvacia())  {Ad[i] = p2.cabeza_esquina();}
        else
        {
                Ad[i] = p2.cabeza_esquina();
                get_adyacenciaAux(*(p2.resto()), count, ++i);
        }
}
 
 
void Lista::get_adyacencia(Lista p1, int count,int o)
{
        for(int i = 0; i < 4; i++){Ad[i] = 0;}
        if(count == o) {  get_adyacenciaAux(p1.cabeza(), count, 0); }
        else       {   get_adyacencia(*(p1.resto()), --count,o);    }
}
 
 
void Lista::llenarMapa(Lista p1)
{
        bool av= false;
        int m, pi;
        srand(time(NULL));
        int vector[MAX];
        int vector1[MAX];
        for (m = 0; m<MAX;m++)  { vector[m]= int (rand() % (81)) + 1; }
        m=0;
        for (pi = 0; pi<MAX;pi++){ vector1[pi]= int (rand() % (100)); }
        pi=0;
        for (int pu = 0; pu<AUTO; pu++)
        {
                int p = vector1[pi];pi++;
                if(p <= 70){p = 1;}
                else if(p <= 90){p=2;}
                                else {p=3;}
                while (vector[m] == 9) {m++;}
                int o =vector[m];m++;
                while (o == vector[m] || vector[m] == 73) {m++;}
                int d = vector[m];m++;
                int inter;
                int h=1;
                int t=1;
               
                init();
                dijkstra(o,d);
                camino(d,0);              
                while(path[t] != -1) { inter = path[t]; t++;}
                if (inter == d)
                {
                        m++;
                        while (vector[m] == 9) {m++;}
                        o =vector[m];m++;
                        while (o == vector[m] || vector[m] == 73) {m++;}
                        int d = vector[m];m++;
                        init();
                        dijkstra(o,d);
                        camino(d,0);              
                        while(path[t] != -1) { inter = path[t]; t++;}
                }
                Vehiculos *patapata = new Vehiculos(p);
                (patapata)->set_origen(o);
                (patapata)->set_destino(d);
                while(path[h]!=-1)// cargo el recorrido
                {  
                        patapata->set_recorrido(path[h],h);
                        h++;
                }
                p1.get_avenida(p1,81,o);                
                for (int i = 0; i < 4; i++){if (Av[i] == inter){av = true;i=4;} }
                p1.add_v(p1, o, inter, patapata, 81,av);
                av = false;
        }
 
}
 
void Lista::heap_semaforoAux(Lista p0,Lista_de_arrays p2, int count,int &i, bool av)
{
        av = false;
        p0.get_avenida(p0,81,count);
        for (int m = 0; m < 4; m++){if (Av[m] == p2.cabeza_esquina()){av = true;m=4;}}
       
        if((p2.resto())->esvacia())
        {
                semaforo[i][0]=count;
                semaforo[i][1]=p2.cabeza_esquina();  
                semaforo[i][2]=p0.cant_heap(p0, count, p2.cabeza_esquina(), 81,av);i++;
               
        }
        else
        {
                semaforo[i][0]=count;
                semaforo[i][1]=p2.cabeza_esquina();  
                semaforo[i][2]=p0.cant_heap(p0, count, p2.cabeza_esquina(), 81,av);i++;
                heap_semaforoAux(p0,*(p2.resto()), count,i,av);
        }
}
 
void Lista::heap_semaforo(Lista p1, int count, Lista p0,int &i,bool av)
{
        if((p1.resto())->esvacia()) { heap_semaforoAux(p0,p1.cabeza(), count,i,av); }
        else
        {
                heap_semaforoAux(p0,p1.cabeza(), count,i,av);
                heap_semaforo(*(p1.resto()), --count, p0,i,av);
        }
}
 
///////////////--------------------Lista de listas FIN--------------------------------
 
 
///////////////-------/////////-------------Grafo FIN---------------///////-------//////////////////
 
 
void Lista::Dijks_Aux(Lista_de_arrays p2, int count)
{
        if((p2.resto())->esvacia())  { ady1[ count ].push_back( Node( p2.cabeza_esquina() , 1 ) );}
        else
        {
                ady1[ count ].push_back( Node( p2.cabeza_esquina() , 1 ) );
                Dijks_Aux(*(p2.resto()), count);
        }
}
 
void Lista::Dijks(Lista p1, int count)
{
        if((p1.resto())->esvacia()) { Dijks_Aux(p1.cabeza(), count); }
        else
        {
                Dijks_Aux(p1.cabeza(), count);
                Dijks(*(p1.resto()), --count);
        }
}
 
void Lista::Dijks_miAutoAux(Lista p0, Lista p1, Lista_de_arrays p2, int count)
{
        inicial();
        bool av = false;
        p0.get_avenida(p0,81,count);
        for (int i = 0; i < 4; i++){if (Av[i] == p2.cabeza_esquina()){av = true;i=4;}}
       
        if((p2.resto())->esvacia())
        { ady2[ count ].push_back( Node( p2.cabeza_esquina() , (p0.congestion_heap(p0, count, p2.cabeza_esquina(), 81, av) +1) ));}
        else
        {
                ady2[ count ].push_back( Node( p2.cabeza_esquina() , (p0.congestion_heap(p0, count, p2.cabeza_esquina(), 81, av)+1)));
                Dijks_miAutoAux(p0, p1,*(p2.resto()), count);
        }
        av=false;
}
 
void Lista::Dijks_miAuto(Lista p0, Lista p1, int count)
{
        if((p1.resto())->esvacia()) { Dijks_miAutoAux(p0, p1, p1.cabeza(), count); }
        else
        {
                Dijks_miAutoAux(p0, p1, p1.cabeza(), count);
                Dijks_miAuto(p0, *(p1.resto()), --count);
        }
}
 
Vehiculos *Lista::posicion_heapAux(Lista_de_arrays p2, int destino,bool av)
{
        if((p2.resto())->esvacia()){return pos_MiAuto(p2.cabeza_cola_v(),av);}
        else if(destino != (p2.cabeza_esquina())) {return posicion_heapAux(*(p2.resto()), destino,av); }
                         else   {   return pos_MiAuto(p2.cabeza_cola_v(),av);   }
}
 
Vehiculos *Lista::posicion_heap(Lista p1, int origen, int destino, int iter,bool av)
{
    if((p1.resto())->esvacia()) {/*cout<<"Error ese ORIGEN es INVALIDO!! cant_heap";*/ return posicion_heapAux(p1.cabeza(), destino,av);  }
    else if(posicion_heapAux(p1.cabeza(), destino,av)->get_prioridad() == 100) {return posicion_heap(*(p1.resto()), origen, destino,--iter,av);}
        else if(iter == origen) { return posicion_heapAux(p1.cabeza(), destino,av); }
                 else   {   return posicion_heap(*(p1.resto()), origen, destino,--iter,av);  }
}
 
Vehiculos *Lista::get_MiAutoAux(Lista p0,Lista_de_arrays p2, int count,bool av)
{
        av = false;
        p0.get_avenida(p0,81,count);
        for (int i = 0; i < 4; i++){if (Av[i] == p2.cabeza_esquina()){av = true;i=4;}}
        if((p2.resto())->esvacia())  { return p0.posicion_heap(p0, count, p2.cabeza_esquina(), 81,av); }
        else if(p0.posicion_heap(p0, count, p2.cabeza_esquina(), 81,av)->get_prioridad() == 100) {return get_MiAutoAux(p0,*(p2.resto()), count,av);}
        else
        {
                return p0.posicion_heap(p0, count, p2.cabeza_esquina(), 81,av);
                return get_MiAutoAux(p0,*(p2.resto()), count,av);
        }
}
 
Vehiculos *Lista::get_MiAuto(Lista p1, int count, Lista p0, int mi_origen, bool av)
{
    if(count > mi_origen){return get_MiAuto(*(p1.resto()), --count, p0, mi_origen, av);}
    else if((p1.resto())->esvacia()) {return get_MiAutoAux(p0,p1.cabeza(), count,av); }
         else if(get_MiAutoAux(p0,p1.cabeza(), count,av)->get_prioridad() == 100)       {return get_MiAuto(*(p1.resto()), --count, p0, mi_origen, av);}
                          else
                          {
                                                                return get_MiAutoAux(p0,p1.cabeza(), count,av);
                                                                return get_MiAuto(*(p1.resto()), --count, p0, mi_origen, av);
                          }
}
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void mover_auto (Lista *p1, int origen, int destino, int inter)
{
        bool av = false;
        bool av1 = false;
        int max = MAX1;int t=1, h =1, des = 0;
                p1->get_avenida(*p1,81,origen);
                for (int i = 0; i < 4; i++){if (Av[i] == inter){av = true;max = max * 2;i=4;}}
                init();
        if (p1->cant_heap(*p1, inter, destino, 81,av) < max)
        {                      
                        while(p1->get_vehiculo(*p1, origen, inter, 81,av)->get_recorrido(h+1)!=-1)
                        {  
                                des = p1->get_vehiculo(*p1, origen, inter, 81,av)->get_recorrido(h);
                                h++;
                        }
                       
                        if (destino != des)
                        {      
                                init();
                                if(p1->get_vehiculo(*p1, origen, inter, 81,av)->get_nuestro())
                                {
                                        init();
                                        p1->Dijks_miAuto(*p1,*p1, 81);
                                        dijkstra2(p1->get_vehiculo(*p1, origen, inter, 81,av)->get_origen(),p1->get_vehiculo(*p1, origen, inter, 81,av)->get_destino());
                                        camino(p1->get_vehiculo(*p1, origen, inter, 81,av)->get_destino(),0);
                                }
                                dijkstra(origen,p1->get_vehiculo(*p1, origen, inter, 81,av)->get_destino());
                                camino(p1->get_vehiculo(*p1, origen, inter, 81,av)->get_destino(),0);
                               
                                while(path[t+1]!=-1)// cargo el recorrido
                {
                                        destino = path[t];
                                        //~ cout<<t<<"  ----- "<<destino<<endl;
                                        p1->get_vehiculo(*p1, origen, inter, 81,av)->set_recorrido(path[t],t);
                                        t++;
                }              
                        }
                       
                        if (origen == 0){origen = p1->get_vehiculo(*p1, origen, inter, 81,av)->get_origen();}
                       
                        t=1;
                       
                        while(p1->get_vehiculo(*p1, origen, inter, 81,av)->get_recorrido(t+1)!=-1)              {       t++;    }
                       
                        p1->get_vehiculo(*p1, origen, inter, 81,av)->set_recorrido(-1,t);
                        p1->get_vehiculo(*p1, origen, inter, 81,av)->set_origen(inter);
                       
                        p1->get_avenida(*p1,81,inter);
                        for (int i = 0; i < 4; i++){if (Av[i] == destino){av1 = true;max = max * 2;i=4;}}
                       
                        //~ cout<<"Destino inter "<<destino<<"--- "<<p1->get_vehiculo(*p1, origen, inter, 81,av)->get_destino()<<endl;      
                        if(p1->get_vehiculo(*p1, origen, inter, 81,av)->get_destino() != destino)
                        {
                                p1->add_v(*p1, inter, destino, (p1->get_vehiculo(*p1, origen, inter, 81,av)),81,av1);
                        }
                        p1->desencolar_heap(*p1, origen, inter, 81,av);                                            
                        t=1;
            init();    
                                       
        }
        av = false;max = MAX1;av1= false;
}
 
void simulacion (Lista *p1)
{
        inicial1();
        bool av = false;
        int iter=1;
        int destino = 0;
        int t=1;
        int y=1;
        int aux[177][3];
        for(int k=177; k>0;k--){ for(int i=0;i<3;i++){ {aux[k][i] = 0;}}}
        p1->heap_semaforo(*p1,81,*p1,y,false);
                init();
        heapsort_S();heapsort_S();
       
                //~ cout<<"-----------------------------------------------------  "<<semaforo[177][2]<<endl;
                //~ cout<<"origen "<<semaforo[177][0]<<" inter "<<semaforo[177][1]<<endl;
       
        for(int i=177;i>0;i--)
        {
                        for(int k=0;k<3;k++){ {aux[i][k] = semaforo[i][k];}}
     
                        if (semaforo[i][2]>0)
                        {                                      
                                p1->get_avenida(*p1,81,aux[i][0]);
                               
                                t=1;
                               
                                for (int j = 0; j < 4; j++)
                                {
                                        if (Av[j] == aux[i][1])
                                        {      
                                                av = true;
                                                if(aux[i][2]%2==0){iter=iter*2;}
                                        }
                                }
                                if(aux[i][1] != 73 && aux[i][0] != 9 && aux[i][0] != 0 && aux[i][1] != 0)
                                {
                                        for(int n=0;n<iter;n++)
                                        {
                                                //~ cout<<endl<<semaforo[i][0]<<"---"<<semaforo[i][1];
                                                while((p1->get_vehiculo(*p1, aux[i][0], aux[i][1], 81,av))->get_recorrido(t+1) != -1)
                                                {
                                                         destino = (p1->get_vehiculo(*p1, aux[i][0], aux[i][1], 81,av))->get_recorrido(t);
                                                         //~ cout<<"----- "<<(p1->get_vehiculo(*p1, semaforo[i][0], semaforo[i][1], 81,av))->get_recorrido(t)<<endl;
                                                         t++;
                                                }                                                                      
                                               
                                                //~ cout<<"origen "<<aux[i][0]<<" inter "<<aux[i][1]<<"    "<<aux[i][2]<<endl;
                                                //~ cout<<"Destino: "<<(p1->get_vehiculo(*p1, aux[i][0], aux[i][1], 81,av))->get_destino()<<endl;
                                                //~ cout<<"petete "<<destino<<endl;
                                               
                                                mover_auto(p1, aux[i][0],destino,aux[i][1]);
                                               
                                                //~ cin>>t;
                                                t=1;
                                        }
                                }
                                av = false;     iter=1;
                        }
        }
}
 
void mover_mi_auto(Lista *p1)
{
        int origen=0,destino=0,t=1,inte=0,inter=0;
        bool av = false;
        Vehiculos *mi_auto= new Vehiculos(1);
        cout<<"Ingrese su origen: "<<endl;
        cin>>origen;
        mi_auto->set_origen(origen);
        cout<<"Ingrese su destino: "<<endl;
        cin>>destino;
        mi_auto->set_destino(destino);
        mi_auto->set_esNuestro();
                init();
                p1->Dijks_miAuto(*p1,*p1, 81);
        dijkstra2(mi_auto->get_origen(),mi_auto->get_destino());
        camino(mi_auto->get_destino(),0);
       
       
                while(path[t] != -1) { mi_auto->set_recorrido(path[t],t); t++;}// cargo el recorrido mi_auto
                t=1;
       
        while(mi_auto->get_recorrido(t) != -1) { inter=mi_auto->get_recorrido(t); t++;}//cout<<endl<<"Inter  "<<inter<<endl;
        t=1;
       
        while(mi_auto->get_recorrido(t) != -1) { inte = mi_auto->get_recorrido(t); t++;}
       
        p1->get_avenida(*p1,81,origen);                                
                for (int j = 0; j < 4; j++)  {  if (Av[j] == inter) {av = true;}  }
       
        p1->add_v(*p1,origen, inter, mi_auto, 81,av) ;
       
        Vehiculos *SillaDeRuedas = new Vehiculos(0);
        *SillaDeRuedas = *(p1->get_MiAuto(*p1, 81,*p1,origen, false));
        t=1;
       
        av=false;
       
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
         
         while(SillaDeRuedas->get_recorrido(t+1) != -1) { inte=SillaDeRuedas->get_recorrido(t+1);cout<<"<<--- "<<SillaDeRuedas->get_recorrido(t); t++;}
         int b = SillaDeRuedas->get_origen();
         cout<<endl<<"Origen    "<<b<<"  Inter  "<<inte<<endl;
                 cin>>t;
                 t=1;
             
         while (SillaDeRuedas->get_prioridad()!=100)
         {
                         simulacion(p1);
                         p1->toPrint_pri(*p1, 81,*p1,false);
                         b = SillaDeRuedas->get_origen();
                         p1->get_avenida(*p1,81,b);                                    
                         for (int j = 0; j < 4; j++)  {  if (Av[j] == inter) {av = true;}  }
                         *SillaDeRuedas = *(p1->get_MiAuto(*p1, 81,*p1,b, av));
                         b = SillaDeRuedas->get_origen();
                         while(SillaDeRuedas->get_recorrido(t+1) != -1) { inte=SillaDeRuedas->get_recorrido(t+1);cout<<"<<--- "<<SillaDeRuedas->get_recorrido(t); t++;}
                         if  (SillaDeRuedas->get_prioridad()!=100) {cout<<endl<<"Origen    "<<b<<"  Inter  "<<inte<<endl;cin>>t;}
                         t=1;av=false;
                         if  (SillaDeRuedas->get_prioridad()!=100)
                         {
                                 simulacion(p1);
                                 b = SillaDeRuedas->get_origen();
                                 p1->get_avenida(*p1,81,b);                                    
                                 for (int j = 0; j < 4; j++)  {  if (Av[j] == inter) {av = true;}  }
                                 *SillaDeRuedas = *(p1->get_MiAuto(*p1, 81,*p1,b, av));
                                 init();
                                 p1->Dijks_miAuto(*p1,*p1, 81);
                                 dijkstra2(mi_auto->get_origen(),mi_auto->get_destino());
                                 camino(mi_auto->get_destino(),0);
                                 *SillaDeRuedas = *(p1->get_MiAuto(*p1, 81,*p1,b, av));
                                 b = SillaDeRuedas->get_origen();
                                 while(SillaDeRuedas->get_recorrido(t+1) != -1) { inte=SillaDeRuedas->get_recorrido(t+1);cout<<"<<--- "<<SillaDeRuedas->get_recorrido(t); t++;}
                                 if  (SillaDeRuedas->get_prioridad()!=100) {cout<<endl<<"Origen    "<<b<<"  Inter  "<<inte<<endl;cin>>t;}
                                 t=1;av=false;
                          }
                  }
                  cout<<endl<<"Llegue che!! "<<endl<<endl;            
}
 
int main()
{
        Lista *Mapa = new Lista();    
    int texto, c=0;
    ifstream archivo_entr;
   
    archivo_entr.open("ADY.txt");
         
        Vehiculos *tutu = new Vehiculos(0);
   
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
                                        ady->add(texto,tutu);c++;
                                        tutu = new Vehiculos(0);
        }
        Mapa->Dijks(*Mapa, 81);
        Mapa->avenida(*Mapa, 81, *Mapa);
    Mapa->llenarMapa(*Mapa);
   
        Mapa->toPrint_pri(*Mapa, 81,*Mapa,false);
       
    mover_mi_auto(Mapa);
   
        return 0;
}
