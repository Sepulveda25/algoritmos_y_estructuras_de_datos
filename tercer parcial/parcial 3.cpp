#include<iostream>
#include <list>
#include <stack>
 
using namespace std;
 
///////////////////////  Topologilal Sort //////////////////////////////
 
// Clase para representar el grafo
class Grafo
{
    int V;    // Numero de vertices
    list<int> *ady;   // Puntero a la lista de adyacencia
    void topologicalSortAux(int v, bool visitado[], stack<int> &Pila);   // Funcion auxiliar de la funcion TopologicalSort principal
   
public:
    Grafo(int V);   // Constructor
    void addArista(int v, int w);   // Funcion para crear un arista al grafo
    void topologicalSort();   // Imprime el topological sort total del grafo
};
 
Grafo::Grafo(int V)
{
    this->V = V;
    ady = new list<int>[V];
}
 
void Grafo::addArista(int v, int w)
{
    ady[v].push_back(w); // Agrega w a la lista de v
}
 
// Funcion recursiva usada por topologicalSort
void Grafo::topologicalSortAux(int v, bool visitado[], stack<int> &Pila)
{
    // Marcar el nodo actual como visitado
    visitado[v] = true;
 
    // Recursion de todos los vertices adjacentes a este vertice
    list<int>::iterator i;
    for (i = ady[v].begin(); i != ady[v].end(); ++i)
        if (!visitado[*i])
            topologicalSortAux(*i, visitado, Pila);
 
    // Apilar vertice actual a la pila que almacena resultados
    Pila.push(v);
}
 
// Esta es la funcion que hace el Topological Sort. Usa recursivamente topologicalSortAux()
void Grafo::topologicalSort()
{
    stack<int> Pila;
 
    // Marcar todos los vertices como no visitados
    bool *visitado = new bool[V];
    for (int i = 0; i < V; i++)
        visitado[i] = false;
 
    // Llamar recursivamente a la funcion auxiliar para hacer el topological sort
    // Empezando de todos los vertices uno por uno
    for (int i = 0; i < V; i++)
      if (visitado[i] == false)
        topologicalSortAux(i, visitado, Pila);
 
    // Imprime contenido de la pila
    while (Pila.empty() == false)
    {
        cout << Pila.top() << " ";
        Pila.pop();
    }
}
 
 
////////////////////////////   DFS    //////////////////////////////////
 
 
class Grafo_1
{
    int V;    // Numero de vertices
    list<int> *adj;    // Puntero a la lista de adyasencia
    void DFS_aux(int v, bool visitado[]);  // Funcion recursiva de DFS
public:
    Grafo_1(int V);   // Constructor
    void addArista(int v, int w);   // Funcion para crear un arista al grafo
    void DFS(int v);    // Funcion principal de DFS
};
 
Grafo_1::Grafo_1(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Grafo_1::addArista(int v, int w)
{
    adj[v].push_back(w); // Agrega a la lista de v a w
}
 
 // Funcion auxiliar de DFS
void Grafo_1::DFS_aux(int v, bool visitado[])
{
    // Marca el nodo actual como visitado y lo imprime
    visitado[v] = true;
    cout << v << " ";
 
    // Recorre todos los vertices adyacentes del vertice actual
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visitado[*i])
            DFS_aux(*i, visitado);
}
 
// Funcion principal de DFS
void Grafo_1::DFS(int v)
{
    // Marca todos los vertices como no visitados
    bool *visitado = new bool[V];
    for(int i = 0; i < V; i++)
        visitado[i] = false;
 
    // Llama a la funcion recursiva DFS aux
    DFS_aux(v, visitado);
}
 
 
////////////////////////////    BFS       //////////////////////////////
 
 
 
class Grafo_2
{
    int V;    // Numero de vertices
    list<int> *adj;    // Puntero a la lista de adyasencia
public:
    Grafo_2(int V);  // Constructor
    void addArista(int v, int w); // Funcion para crear un arista al grafo
    void BFS(int s);  // Imprime bfs para un s dado
};
 
Grafo_2::Grafo_2(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Grafo_2::addArista(int v, int w)
{
    adj[v].push_back(w); // Añadimos w a la lista
}
 
void Grafo_2::BFS(int s)
{
    // Marca todos los vertices como no visitados
    bool *visitado = new bool[V];
    for(int i = 0; i < V; i++)
        visitado[i] = false;
 
    // Crea una cola para BFS
    list<int> cola;
 
    // Marca el nodo actual como visitado y lo encola
    visitado[s] = true;
    cola.push_back(s);
 
    // Usamos "i" para ver todos los vertices adyasentes
    list<int>::iterator i;
 
    while(!cola.empty())
    {
        // Desencola un vertice de la cola y lo imprime
        s = cola.front();
        cout << s << " ";
        cola.pop_front();
 
        // Desencola el vertice s y btiene todos los vertices adyacentes
        // Si un vertice adyacente no fue visitado lo marcamos como visitado y lo encolamos
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visitado[*i])
            {
                visitado[*i] = true;
                cola.push_back(*i);
            }
        }
    }
}
 
int main()
{
       
///////////////////////  Topologilal Sort //////////////////////////////
 
        Grafo j(43);
    j.addArista(0, 3);j.addArista(0, 4);j.addArista(0, 7);j.addArista(0, 11);
    j.addArista(1, 9);
    j.addArista(2, 6);
    j.addArista(3, 8);j.addArista(3, 9);j.addArista(3, 10);
    j.addArista(4, 19);
    j.addArista(7, 12);j.addArista(7, 30);
    j.addArista(8, 13);j.addArista(8, 14);j.addArista(8, 15);j.addArista(8, 16);j.addArista(8, 21);
    j.addArista(9, 16);j.addArista(9, 19);
    j.addArista(11, 20);
    j.addArista(13, 17);j.addArista(13, 18);j.addArista(13, 19);
    j.addArista(14, 29);
    j.addArista(15, 24);
    j.addArista(16, 20);j.addArista(16, 22);
    j.addArista(17, 22);
    j.addArista(18, 28);
    j.addArista(19, 38);
    j.addArista(20, 23);
    j.addArista(21, 26);
    j.addArista(22, 27);j.addArista(22, 28);
    j.addArista(23, 30);
    j.addArista(24, 33);
    j.addArista(25, 34);
    j.addArista(27, 31);
    j.addArista(28, 37);j.addArista(28, 38);
    j.addArista(29, 32);
    j.addArista(30, 35);
    j.addArista(31, 36);
    j.addArista(32, 37);
    j.addArista(33, 41);
    j.addArista(34, 35);
    j.addArista(35, 39);
    j.addArista(36, 40);
    j.addArista(37, 40);j.addArista(37, 41);
    j.addArista(39, 42);
 
    cout << "El Topological Sort del grafo dado es: "<<endl;
    j.topologicalSort();
    cout<<endl<<endl;
       
       
////////////////////////////   DFS    //////////////////////////////////
               
 
    Grafo_1 g(40);
   
    g.addArista(0, 3);g.addArista(0, 4);g.addArista(0, 7);g.addArista(0, 11);
    g.addArista(1, 9);
    g.addArista(2, 6);
    g.addArista(3, 8);g.addArista(3, 9);g.addArista(3, 10);
    g.addArista(4, 19);
    g.addArista(7, 12);g.addArista(7, 30);
    g.addArista(8, 13);g.addArista(8, 14);g.addArista(8, 15);g.addArista(8, 16);g.addArista(8, 21);
    g.addArista(9, 16);g.addArista(9, 19);
    g.addArista(11, 20);
    g.addArista(16, 20);
   
    cout<<endl<<"Comienza la Busqueda por Profundidad"<<endl;
   
    cout<< "El DFS del grafo g empezando del vertice 1 es: "<<endl;
    g.DFS(1); cout<<endl<<"---------------------------------"<<endl;
    cout << "El DFS del grafo g empezando del vertice 0 es: "<<endl;
    g.DFS(0);cout<<endl<<"---------------------------------"<<endl;
    cout << "El DFS del grafo g empezando del vertice 7 es: "<<endl;
    g.DFS(7);cout<<endl<<"---------------------------------"<<endl;
    cout << "El DFS del grafo g empezando del vertice 12 es: "<<endl;
    g.DFS(12);cout<<endl<<"---------------------------------"<<endl;
    cout<<endl<<endl;
 
////////////////////////////    BFS       //////////////////////////////
 
 
        Grafo_2 b(40);
   
   b.addArista(0, 3);b.addArista(0, 4);b.addArista(0, 7);b.addArista(0, 11);
   b.addArista(1, 9);
   b.addArista(2, 6);
   b.addArista(3, 8);b.addArista(3, 9);b.addArista(3, 10);
   b.addArista(4, 19);
   b.addArista(7, 12);b.addArista(7, 30);
   b.addArista(8, 13);b.addArista(8, 14);b.addArista(8, 15);b.addArista(8, 16);b.addArista(8, 21);
   b.addArista(9, 16);b.addArista(9, 19);
   b.addArista(11, 20);
   b.addArista(16, 20);
   
   cout<<endl<<"Comienza la Busqueda por Amplitud"<<endl;
   
   cout << "El BFS del grafo b empezando del vertice 1 es: "<<endl;
   b.BFS(1);cout<<endl<<"---------------------------------"<<endl;
   cout << "El BFS del grafo b empezando del vertice 0 es: "<<endl;
   b.BFS(0);cout<<endl<<"---------------------------------"<<endl;
   cout << "El BFS del grafo b empezando del vertice 7 es: "<<endl;
   b.BFS(7);cout<<endl<<"---------------------------------"<<endl;
   cout << "El BFS del grafo b empezando del vertice 12 es: "<<endl;
   b.BFS(12);cout<<endl<<"---------------------------------"<<endl;
   cout<<endl<<endl;
    system ("pause");
        return 0;
}
