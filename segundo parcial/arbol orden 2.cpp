#include <stdio.h>
#include <iostream>
#include <conio.h>
#define MAX 5

using namespace std;

typedef int tarbol;
struct nodo{
      tarbol dato[MAX-1]; //datos
      nodo *punteros[MAX];//punteros (para binario der izq)
};
typedef nodo * pnodo;
class arbol{
    pnodo raiz, q;
    void ArbolBusq(tarbol x, pnodo &nuevo);
    void rid(pnodo aux);
    void ird(pnodo aux);
    void idr(pnodo aux);
    void ih(pnodo aux,int n);
    void show(pnodo aux, int n);
    void borrar(pnodo &p, tarbol x);
    void bor(pnodo &d);
    int max (pnodo aux);
    int cantDatos (int *v);
    bool hoja (pnodo pun);
    
 
public:
    arbol(){raiz=NULL;};
    ~arbol(){};
    void CreaArbolBus(tarbol x);
    void RID(){ rid(raiz); }
    void IRD(){ ird(raiz); }
    void IDR(){ idr(raiz); }
    void IH() {ih (raiz,0);}
    void VerArbol(){ show(raiz,0); }
    void Borrar(tarbol x){ borrar(raiz,x);}
    //void ImpreHojas(){ih(raiz,0);}
    tarbol BuscarMayor(){return max(raiz); }
   int numDatos(int *v){return cantDatos(v);}
   bool Es_hoja (nodo *punteros){return hoja(punteros);}
    
};

bool arbol::hoja (pnodo pun)
{
    if (pun==NULL){return true;}
    else{return false;}
}

int arbol::cantDatos (int *v)
{
    int i=0;
    while(*(v+i)!=-1){ i++;}
    return i;
}

void arbol::borrar(pnodo &p, tarbol x)
{ if(p==NULL) cout<<"\n El dato NO esta\n\n";
  else if(x>p->dato[0]) borrar(p->punteros[1],x);
  else if(x<p->dato[0]) borrar(p->punteros[0],x);
  else {// lo encontre en el nodo p
        q=p;
        if (q->punteros[1]==NULL) p=q->punteros[0];
        else if (q->punteros[0]==NULL) p=q->punteros[1];
        else bor(q->punteros[0]);//busca en el sub arbol izq
        delete q;
  }
}
void arbol::bor(pnodo &d)
{ if(d->punteros[1]!=NULL) bor(d->punteros[1]);//busca el elemento mas a la derecha
  else{ q->dato[0]= d->dato[0];
        q=d;
        d=d->punteros[0];
  }
}
void arbol::CreaArbolBus(tarbol x)
{ ArbolBusq(x,raiz);
}
void arbol::ArbolBusq(tarbol x, pnodo &nuevo)
{
  int largo;
  if(nuevo==NULL){
      nuevo= new nodo;
      for (int i = 0; i< MAX-1;i++){nuevo->dato[i]=-1;}
      nuevo->dato[0]=x;for (int i=0;i<=MAX;i++){nuevo->punteros[i]=NULL;};
  }
  if (Es_hoja(*(nuevo->punteros)))
  {
        largo=numDatos(nuevo->dato) - 1; 
        while((largo<=4)&&(largo>=0))
        {
            if (largo = 0){nuevo->dato[largo]= x;}
            else
            {
                if (nuevo->dato[largo] !=-1)
                {
                    if (nuevo->dato[largo]>x){ nuevo->dato[largo + 1] = nuevo->dato[largo];/* nuevo->dato[largo] = -2;*/ --largo; }
                    else {nuevo->dato[largo + 1]=x;largo = -2;}
                }
                else { largo = -2;}
            }

        }
    }
   // for(int i =0; i<numDatos(nuevo->dato); i++){ cout<<nuevo->dato[i]<<endl;}
  //if(x > nuevo->dato[0]) ArbolBusq(x, nuevo->punteros[1]);
 //if(x < nuevo->dato[0]) ArbolBusq(x, nuevo->punteros[0]);
}
void arbol::ird(pnodo aux)
{  if(aux!=NULL){
        ird(aux->punteros[0]);
        cout<<"\n"<<aux->dato[0];
        ird(aux->punteros[1]);
   }
}
void arbol::rid(pnodo aux)
{  if(aux!=NULL){
        cout<<"\n"<<aux->dato[0];
        rid(aux->punteros[0]);
        rid(aux->punteros[1]);
   }
}
void arbol::idr(pnodo aux)
{  if(aux!=NULL){
        idr(aux->punteros[0]);
        idr(aux->punteros[1]);
        cout<<"\n"<<aux->dato[0];
   }
}
void arbol::show(pnodo aux, int n)
{ int i;
   if(aux!=NULL){                      //OjO este es un recorrido dri
       show(aux->punteros[1], n+1);
       for(i=1; i<=n; i++) cout<<"     ";
       for(int j =0; i<4; i++){ cout<<aux->dato[i]<<endl;}
       cout<<aux->dato[0]<<"\n";
       show(aux->punteros[0], n+1);
   }
}

void arbol::ih(pnodo aux,int n)
{  if(aux!=NULL){
        ih(aux->punteros[0],n+1);
        if (aux->punteros[0]==NULL && aux->punteros[1]==NULL)
                              cout<<"\n"<<aux->dato[0]<<" nivel: "<<n;
        ih(aux->punteros[1],n+1);
   }
}

tarbol arbol::max(pnodo aux)
{  if(aux->punteros[1]!=NULL){
        return (max(aux->punteros[1]));
        } return aux->dato[0];
}
/*
int arbol::altura(tarbol a,int n)
{  if(aux!=NULL){
        int ad=altura(aux->der,n+1);
        int ai=altura(aux->izq,n+1);
        if (ad>ai) return ad;
        return ai;
                              cout<<"\n"<<aux->info<<" nivel: "<<n;
        ih(aux->der,n+1);
   }
}*/
//-------------------------------------------------------
int main (int argc, char *argv[])
{  int i; tarbol x;
   arbol T;
   int vec[4]={50,12,18,240};//,222,45,410,325,38,95};
   
   for(i=0;i<4;i++){ 
                      T.CreaArbolBus(vec[i]);
                      T.VerArbol();
                      cout<<"-------------------------------------\n";
                      //system("PAUSE");
   } 
   /*                  
   T.VerArbol();
   cout<<"IRD--------------------------------\n";
   T.IRD();
   cout<<"\n--------------------------------";
   cout<<"RID--------------------------------\n";
   T.RID();
   cout<<"\n--------------------------------";
   cout<<"IDR--------------------------------\n";
   T.IDR();  
   cout<<"\n--------------------------------";
   cout<<"IH--------------------------------\n";   
   T.IH();
   cout<<"\n--------------------------------";
   cout<<"Mayor--------------------------------\n"; 
   cout<<T.BuscarMayor();
/*
   for(i=1;i<5;i++){
     cout<<"\n -------------------------------- Ing dato a borrar= "; cin>>x;
     T.Borrar(x);
     T.VerArbol();
   }
  */
  
  
  
   cout<<endl;
   system("PAUSE");
   return EXIT_SUCCESS;
}
