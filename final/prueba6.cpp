#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>
 
#include <stdio.h>
#include <vector>
#include <queue>
 
//~ #define MAX 100
#define MAX1 12
 
#define MAX 10005 //maximo numero de vértices
#define Node pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas
 
 
using namespace std;
 
 
 
 
///////////////-------/////////------------Heapsort con Vehiculos COMIENZO-----------/////////--------/////////////////////
 
class Vehiculos
{      
        private:
                        struct vehiculo{                int prioridad;
                                                        int recorrido[MAX];
                                                        int origen;
                                                        int destino;
                                                        bool seMovio;  
                        };
                        vehiculo autos;
       
        public:
                        Vehiculos(int pri);
                        void set_origen (int orig){autos.origen=orig;};
                        void set_destino(int dest){autos.destino=dest;};
                        void set_recorrido(int rec,int i){autos.recorrido[i]=rec;};
                        int get_origen (void){return autos.origen;};
                        int get_destino(void){return autos.destino;};
                        int get_prioridad (void){return autos.prioridad;};
                        int get_recorrido(int i){return autos.recorrido[i];};
};
 
 Vehiculos::Vehiculos(int pri)
 {
        autos.prioridad=pri;
        for (int a=0; a<MAX;a++){autos.recorrido[a]=-1;}
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
 
Vehiculos *get_v(Vehiculos **v) {  return v[MAX1]; }
 
void encolar (Vehiculos **vector, Vehiculos *aux)
{
       
   for (int c=MAX1; c>1; c--)
   {
                   if(vector[c]->get_prioridad() == 0)    {**(vector+c) = *aux; c=1;}
   }
   for (int c=1; c<MAX1+1; c++)
   {
           if(vector[c]->get_prioridad() > 1)  {  heapsort(vector); c=MAX1+1;  }
   }
   //~ impre (vector);
}
       
void desencolar (Vehiculos **vector)
{
        //~ for(int i = MAX1; i>MAX1-4; i--)
        //~ {
                        if (vector[MAX1]->get_prioridad() != 0)
                        {
                                Vehiculos *v_aux[MAX1+1];
                                for(int x=1; x<=MAX1+1; x++){ v_aux[x] = new Vehiculos(0);}
                                Vehiculos *aux = new Vehiculos(0);
                                **(vector+MAX1) = *aux;
                                for(int j=MAX1; j>1; j--) { *v_aux[j] = **(vector + (j-1)); }
                                for(int j=MAX1; j>1; j--) { **(vector + j) =*v_aux[j] ; }
                        }
        //~ }  
 
        //~ impre (vector);
}
 
///////////////-------/////////------------Heapsort con Vehiculos FIN-----------/////////--------/////////////////////
 
 
///////////////-------/////////------------Dijkstra COMIENZO-----------/////////--------////////////////
 
//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};
vector< Node > ady1[ MAX ]; //lista de adyacencia
int distancia[ MAX ];      //distancia[ u ] distancia de vértice inicial a vértice con ID = u
bool visitado[ MAX ];      //para vértices visitados
priority_queue< Node , vector<Node> , cmp > Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
int V;                     //numero de vertices
int previo[ MAX ];         //para la impresion de caminos
int path[MAX];
 
//función de inicialización
void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[ i ] = false; //inicializamos todos los vértices como no visitados
        previo[ i ] = -1;      //inicializamos el previo del vertice i con -1
    }
        for (int u=1; u<MAX; u++) {path[u]=-1;}
}
 
//Paso de relajacion
void relajacion( int actual , int adyacente , int peso ){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        Q.push( Node( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}
 
//Impresion del camino mas corto desde el vertice inicial y final ingresados
void print( int destino ){
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        print( previo[ destino ] );  //recursivamente sigo explorando
    printf("%d " , destino );        //terminada la recursion imprimo los vertices recorridos
}
 
void camino( int destino, int i ){
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        camino( previo[ destino ] ,++i);  //recursivamente sigo explorando
   
    path[i]=destino;        //terminada la recursion imprimo los vertices recorridos
}
 
 
void dijkstra( int inicial ){
    init(); //inicializamos nuestros arreglos
    Q.push( Node( inicial , 0 ) ); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q.empty() ){                   //Mientras cola no este vacia
        actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q.pop();                           //Sacamos el elemento de la cola
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
 
 
    //~ printf( "Distancias mas cortas iniciando en vertice %d\n" , inicial );
    //~ for( int i = 1 ; i <= V ; ++i ){
        //~ printf("Vertice %d , distancia mas corta = %d\n" , i , distancia[ i ] );
    //~ }
 
    //~ puts("\n**************Impresion de camino mas corto**************");
    printf("Ingrese vertice destino: ");
    int destino;
    scanf("%d" , &destino );
    print( destino );
    printf("\n");
}
 
///////////////-------/////////------------Dijkstra FIN-----------/////////--------/////////////////////
 
 
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
            void set_peso(int destino, int peso);
};
 
 
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
            Vehiculos *get_vehiculo(Lista p1, int origen, int destino, int iter);
            void Dijks_Aux(Lista_de_arrays p2, int count);
            void Dijks(Lista p1, int count);
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
        if((p2.resto())->esvacia())  {  cout<< "  Apunta a: " << p2.cabeza_esquina()<<endl;  }
        else
        {
                        cout<< "  Apunta a: " << p2.cabeza_esquina()<<endl;
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
                                         encolar(p2.cabeza_cola_v(), tutu);
                                         cout<<"Vehiculo agregado con exito "<<endl;
                 }
}
 
void Lista::add_v(Lista p1, int origen, int destino, Vehiculos *tutu, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
        else if(iter == origen) { add_vAux(p1.cabeza(), destino, tutu); }
                 else   {   add_v(*(p1.resto()), origen, destino, tutu, --iter);   }
}
 
void Lista::print_heapAux(Lista_de_arrays p2, int destino)
{
        if((p2.resto())->esvacia())  {  impre(p2.cabeza_cola_v());  }
        else if(destino != (p2.cabeza_esquina())) { print_heapAux(*(p2.resto()), destino); }
                 else  {  impre(p2.cabeza_cola_v()); }
}
 
void Lista::print_heap(Lista p1, int origen, int destino, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
        else if(iter == origen) { print_heapAux(p1.cabeza(), destino); }
                 else  {  print_heap(*(p1.resto()), origen, destino,--iter); }
}
 
int Lista::cant_heapAux(Lista_de_arrays p2, int destino)
{
        if((p2.resto())->esvacia())  {  return cantidad(p2.cabeza_cola_v());  }
        else if(destino != (p2.cabeza_esquina())) {return cant_heapAux(*(p2.resto()), destino); }
                 else   {   return cantidad(p2.cabeza_cola_v());   }
}
 
int Lista::cant_heap(Lista p1, int origen, int destino, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; return -1;}
        else if(iter == origen) { return cant_heapAux(p1.cabeza(), destino); }
                 else   {   return cant_heap(*(p1.resto()), origen, destino,--iter);  }
}
 
void Lista::desencolar_heapAux(Lista_de_arrays p2, int destino)
{
        if((p2.resto())->esvacia())  {  desencolar(p2.cabeza_cola_v()); }
        else if(destino != (p2.cabeza_esquina())) { desencolar_heapAux(*(p2.resto()), destino); }
                 else   {   desencolar(p2.cabeza_cola_v());   }
}
 
void Lista::desencolar_heap(Lista p1, int origen, int destino, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!"; }
        else if(iter == origen) { desencolar_heapAux(p1.cabeza(), destino); }
                 else   {   desencolar_heap(*(p1.resto()), origen, destino,--iter); }
}
 
Vehiculos *Lista::get_vehiculoAux(Lista_de_arrays p2, int destino)
{
        if((p2.resto())->esvacia())   {    return get_v(p2.cabeza_cola_v()); }
        else if(destino != (p2.cabeza_esquina())) { return get_vehiculoAux(*(p2.resto()), destino); }
                 else  {   return get_v(p2.cabeza_cola_v());    }
}
 
Vehiculos *Lista::get_vehiculo(Lista p1, int origen, int destino, int iter)
{
        if((p1.resto())->esvacia()) {cout<<"Error ese ORIGEN es INVALIDO!!";return new Vehiculos(0); }
        else if(iter == origen) { return get_vehiculoAux(p1.cabeza(), destino); }
                 else   {   return get_vehiculo(*(p1.resto()), origen, destino,--iter);  }
}
///////////////--------------------Lista de listas FIN--------------------------------
 
 
///////////////-------/////////-------------Grafo FIN---------------///////-------//////////////////
 
 
void Lista::Dijks_Aux(Lista_de_arrays p2, int count)
{
        if((p2.resto())->esvacia())  { /* cout<< "  Apunta a: " << p2.cabeza_esquina()<<endl; */ ady1[ count ].push_back( Node( p2.cabeza_esquina() , 1 ) );}
        else
        {
                        //~ cout<< "  Apunta a: " << p2.cabeza_esquina()<<endl;
                        ady1[ count ].push_back( Node( p2.cabeza_esquina() , 1 ) );
            Dijks_Aux(*(p2.resto()), count);
        }
}
 
void Lista::Dijks(Lista p1, int count)
{
        //~ cout<<endl;
        if((p1.resto())->esvacia()) {/*cout<<count<<" "; */Dijks_Aux(p1.cabeza(), count); }
        else
        {
                        //~ cout<<count<<" ";
                        Dijks_Aux(p1.cabeza(), count);
                        Dijks(*(p1.resto()), --count);
        }
}
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void mover_auto (Lista *p1, int origen, int destino, int inter)
{
        //cout<<p1.get_peso(p1,origen,inter,iter)<<endl;
        if (p1->cant_heap(*p1, inter, destino, 81) < MAX1)
        {
                p1->add_v(*p1, inter, destino, (p1->get_vehiculo(*p1, origen, inter, 81)),81);
                p1->desencolar_heap(*p1, origen, inter, 81);
        }
}
 
int main()
{
    Lista *Mapa = new Lista();    
    int texto, c=0,i=1;
   
    ifstream archivo_entr;
   
    archivo_entr.open("ADY.txt");
         
        Vehiculos *tutu = new Vehiculos(0);
        //~ Vehiculos *tutu2 = new Vehiculos(4);
        //~ Vehiculos *tutu3 = new Vehiculos(3);
   tutu->set_origen(11);
   tutu->set_destino(72);
   
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
                        tutu->set_origen(11);
                        tutu->set_destino(72);
        }
       
       
        //~ int E , origen, destino , peso ,
        //~ int inicial;
    //~ scanf("%d %d" , &V , &E );
    V=81;
    //~ while( E-- ){
        //~ scanf("%d %d %d" , &origen , &destino , &peso );
        //~ ady1[ origen ].push_back( Node( destino , peso ) ); //consideremos grafo dirigido
        //~ //ady[ destino ].push_back( Node( origen , peso ) ); //grafo no dirigido
    //~ }
    Mapa->Dijks(*Mapa, 81);
    //~ printf("Ingrese el esquina inicial: ");
    //~ scanf("%d" , &inicial );
    dijkstra( Mapa->get_vehiculo(*Mapa, 11, 20, 81)->get_origen() );
    camino(Mapa->get_vehiculo(*Mapa, 11, 20, 81)->get_destino(),0);
    i=1;
    cout<<endl;
    while(path[i]!=-1)
    {  
                cout<<path[i]<<endl;
                Mapa->get_vehiculo(*Mapa, 11, 20, 81)->set_recorrido(path[i],i);
                i++;
        }
        i=1;
        cout<<endl<<"////////////////-------------------------////////////////"<<endl;
        while(path[i]!=-1)
    {  
                cout<<Mapa->get_vehiculo(*Mapa, 11, 20, 81)->get_recorrido(i)<<endl;
               
                i++;
        }
       
        //~ cout<<Mapa->get_vehiculo(*Mapa, 11, 20, 81)->get_origen();
        //~ for (int i=1;path[i]!=Mapa->get_vehiculo(*Mapa, 11, 20, 81)->get_origen();i++)
                        //~ {cout<<path[i]<<endl;       }      
 
       
        //~ Mapa->get_vehiculo(*Mapa, 74, 75, 81)->get_destino()
       
       
    //~ cout<<"aristas  "<<c<<endl;
        //~ cout<<endl<<"Cantidad = "<<Mapa->cant_heap(*Mapa, 74, 75, 81)<<endl;
        //~ Mapa->print_heap(*Mapa, 74, 75, 81);
        //~ Mapa->add_v(*Mapa, 74, 75, tutu2, 81);
        //~ Mapa->print_heap(*Mapa, 74, 75, 81);
        //~ cout<<endl<<"--------     "<<(Mapa->get_vehiculo(*Mapa, 74, 75, 81))->get_prioridad()<<endl;
        //~ Mapa->add_v(*Mapa, 74, 75, tutu3, 81);
        //~ Mapa->print_heap(*Mapa, 74, 75, 81);
       
        //~ Mapa->desencolar_heap(*Mapa, 74, 75, 81);
        //~ Mapa->print_heap(*Mapa, 74, 75, 81);
        //~
        //~ mover_auto(Mapa, 74, 66, 75);
        //~ Mapa->print_heap(*Mapa, 74, 75, 81);
        //~ Mapa->print_heap(*Mapa, 75, 66, 81);
        //~
        //~ cout<<endl<<"--------     "<<(Mapa->get_vehiculo(*Mapa, 74, 75, 81))->get_prioridad()<<endl;
        //~ cout<<endl<<"Cantidad = "<<Mapa->cant_heap(*Mapa, 74, 75, 81)<<endl;
       
       
                 
        return 0;
}
