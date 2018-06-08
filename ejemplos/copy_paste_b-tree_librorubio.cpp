#include <iostream>
#define MAX 5

using namespace std;


struct Nodo{
      int tamanio;
      int dato[MAX-1];
      Nodo *hijo[MAX];
      Nodo(){
                for(int i = 0; i < MAX; i++)
                {
                    if(i < MAX - 1) { dato[i] = int();}
                    hijo[i] = NULL;
                }
            }   
};

class arbol{
    Nodo* raiz_local;
    bool crearArbolBusqueda(Nodo *raiz_local, const int &x, int &nuevo_padre, Nodo *&nuevo_hijo);
    void explota(Nodo *nodo, int indice, const int &x, Nodo *hijo, int &nuevo_padre, Nodo *&nuevo_hijo);
    void insertar(Nodo *nodo, int indice, const int &x, Nodo *hijo);
    int busqueda_binaria (int *a, int imax, int x);
    void show(Nodo *aux, int n);
    //void borrar(Nodo &raiz_local, int x);
    
 public:
        arbol ();
        void ArbolBusqueda(int x);
        void Show() { show(raiz_local,0); }
        //void Borrar(int x) { borrar(raiz_local, x); }
        int Buscar(int x);  
};
arbol::arbol()
{
    raiz_local=NULL;
}
void arbol::insertar(Nodo *nodo, int indice, const int &x, Nodo *hijo)
{
    for(int i = nodo->tamanio; i > indice; i--)
    {
        nodo->dato[i] = nodo->dato[i-1];
        nodo->hijo[i+1] = nodo->hijo[i];
    }
    nodo->dato[indice] = x;
    nodo->hijo[indice+1] = hijo;
    nodo->tamanio++;
}

int arbol::busqueda_binaria (int *a, int imax, int x)
{
   // Prueba si el array está vacío
   if (imax < 0)
   {
     // Set está vacío, por lo que devolver el valor que muestra que no se encuentra
     return imax+1;
   }
   else
   {
       // Calcular punto medio para cortar situado en medio
       int imid = imax/2;

       if (*(a+imid) > x)
       {
         // La clave está en la parte baja subconjunto
         return busqueda_binaria (a, imid-1, x);
       }
       else if (*(a+imid) < x)
            {
                 // La clave está en subgrupo superior
                 return busqueda_binaria (a+imid+1, imax, x);
            }
            else
            {
                // Se ha encontrado la clave
                return imid;
            }
    }
}

/*void arbol::insertar(Nodo *nodo, int indice, const int &x, Nodo *nuevo_hijo)
{
}*/

void arbol::explota(Nodo *nodo, int indice, const int &x, Nodo *hijo, int &nuevo_padre, Nodo *&nuevo_hijo)
{
    nuevo_hijo = new Nodo;//crea nuevo hijo
    //determina el numero de elemntos q van a ser movidos (caso general) 
    int cant_a_mover = (MAX - 1) - (MAX - 1)/2;
    //si crearArbolBusqueda se encuentra en la mitad derecha => moverlo un elemento menos
    if(indice > (MAX-1)/2) { cant_a_mover--; }
    //mover elementos
    std::copy(nodo->dato + (MAX - 1) - cant_a_mover, nodo->dato + (MAX - 1), nuevo_hijo->dato);
    std::copy(nodo->hijo + MAX - cant_a_mover, nodo->hijo + MAX, nuevo_hijo->hijo+1);
    nodo->tamanio = (MAX - 1) - cant_a_mover;
    nuevo_hijo->tamanio = cant_a_mover;
    //insertar el nuevo elemento
    if(indice == (MAX - 1)/2)
    {
        //insertar en el medio
        nuevo_padre = x;
        nuevo_hijo->hijo[0] = hijo;
    }
    else
    {
        //insertar en el lado izquierdo
        if(indice < (MAX - 1)/2) { insertar(nodo, indice, x, hijo); }
        else
        {
            //insertar en el lado derecho
            insertar(nuevo_hijo, indice - (MAX - 1)/2, x, hijo);
        }
         //el elemento del extremo derecho del nodo se convierte en el nuevo padre
         nuevo_padre = nodo->dato[nodo->tamanio - 1];
         //su hijo es ahora el hijo izquierdo que surgio de la division
         nuevo_hijo->hijo[0] = nodo->hijo[nodo->tamanio];
         nodo->tamanio--;
    }
}

bool arbol::crearArbolBusqueda(Nodo *raiz_local, const int &x, int &nuevo_padre, Nodo *&nuevo_hijo)
{
    int aux = *(raiz_local->dato + raiz_local->tamanio);
    int puntero = busqueda_binaria(raiz_local->dato, aux, x);
    int indice = puntero - *raiz_local->dato;
    if((indice != raiz_local->tamanio) && !(x < raiz_local->dato[indice])) { return false;} //el elemento ya esta en el arbol
    //vemos si la raiz local es una hoja
    if(raiz_local->hijo[indice] == NULL)
    {
        if(raiz_local->tamanio < MAX - 1)//si no esta lleno el vector => inserto el dato
        {
            insertar(raiz_local, indice, x, NULL);
            nuevo_hijo = NULL;
        } 
        else { explota(raiz_local, indice, x, NULL, nuevo_padre, nuevo_hijo); }
        return true;
    }
    else
    {
        bool resultado = crearArbolBusqueda(raiz_local->hijo[indice], x, nuevo_padre, nuevo_hijo);
        if(nuevo_hijo != NULL)
        {
            if(raiz_local->tamanio < MAX - 1)
            {
                insertar(raiz_local, indice, nuevo_padre, nuevo_hijo);
                nuevo_hijo = NULL;
            }
            else { explota(raiz_local, indice, nuevo_padre, nuevo_hijo, nuevo_padre, nuevo_hijo); }
        }
        return resultado;
    }
}

void arbol::show(Nodo *aux, int n)
{ 
   int i;
   if(aux!=NULL)
   {                      //OjO este es un recorrido dri
       show(aux->hijo[1], n+1);
       for(i=0; i<n; i++) cout<<"     ";
       for(int j =3; j>=0; j--)
       {
            if (aux->dato[j] != -1){ cout<<aux->dato[j]<<endl;}
            else {cout<<endl;}
        }
       //cout<<aux->dato[0]<<"\n";
       show(aux->hijo[0], n+1);
   }
}

/*int arbol::Buscar(int x)
{ 
    
} */

void arbol::ArbolBusqueda(int x)
{
    int i;
    Nodo *c, *n ;
    if(crearArbolBusqueda(raiz_local, x, i, c))
    {
        n = new Nodo ;
        n -> tamanio = 1 ;
        n -> dato[1] = i ;
        n -> hijo[0] = raiz_local ;
        n -> hijo[1] = c ;
        raiz_local = n ;
    }
}

int main()
{
        arbol T;
    int vec[10]={6,2,8,3,222,45,410,325,38,95};
    
    for(int i = 0; i < 10; i++)
    {
    T.ArbolBusqueda(vec[i]);
    //~ cout<<endl;
    T.Show();
    cout<<endl<<"-------------------------------------\n"<<endl;
    }   
    system("pause");
    return 0;
}
