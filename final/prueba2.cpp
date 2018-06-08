#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
 
using namespace std;
 
///////////////////////  Topologilal Sort //////////////////////////////
 
// Clase para representar el grafo
class Grafo
{
    int V;    // Numero de vertices
    list<int> *ady;   // Puntero a la lista de adyacencia
 
public:
    Grafo(int V);   // Constructor
    void addArista(int v, int d,int p);   // Funcion para crear un arista al grafo
    void showListAdy();   //Funcion que muestra lista de ady. del grafo "m"
};

class Datos
{
    int dato;    
    int peso;
 
public:
	Datos ();
    void setDato (int d){dato=d;};
    void setPeso (int p){peso=p;};
    int getDato(){return dato;};
    int getPeso(){return peso;};
};
  
 Datos::Datos ()
{
		
}
 
Grafo::Grafo(int V)
{
    this->V = V;
    ady = new list<int>[V];
}
 
void Grafo::addArista(int v, int d, int p)
{
	Datos datos;
	datos.setDato(d);
	datos.setPeso(p);
    ady[v].push_back(datos); // Agrega w a la lista de v
}
 
void Grafo::showListAdy()
{
         for (int i=0; i<81;i++)
         {
                cout <<i+1<<")  ";
                while (!(ady+i)->empty())
                {
                        std::cout<<"-"<< (ady+i)->front();                     
                        (ady+i)->pop_front();
                }
                cout<<endl;
        }
}
 
int main()
{
        Grafo mapa(81);
    ifstream fichero;
    int texto;
    fichero.open("ADY.txt", ios::in);
    int ady_ext[81][4];
    int i=0, j=0;
    if (fichero.is_open())
    {        
             while (!fichero.eof())      
             {
                   fichero >> texto;
                   if(texto > -1) {/*cout<<texto<<"-";*/ ady_ext[j][i]=texto; mapa.addArista(j, texto,1); i++;}
                   else {j++; i=0; cout<<endl;}
             }
    }
    fichero.close();
    mapa.showListAdy();
    cout<<"fin de la lectura"<<endl;
   
}
