#include <stdio.h>
#include <iostream>
#include <conio.h>

using namespace std;

typedef int tarbol;
struct nodo{
      tarbol info;
      nodo *der,*izq;
};
typedef nodo * pnodo;
class arbol{		//metodos privados de clase arbol
    pnodo raiz, q; //raiz y q tipo puntero nodo
    void ArbolBusq(tarbol x, pnodo &nuevo);
    void rid(pnodo aux);
    void ird(pnodo aux);
    void idr(pnodo aux);
    void ih(pnodo aux,int n);
    void show(pnodo aux, int n);
    void borrar(pnodo &p, tarbol x);
    void bor(pnodo &d);
    int max (pnodo aux);
    
 
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
    
};

void arbol::borrar(pnodo &p, tarbol x)
{ if(p==NULL) cout<<"\n El dato NO esta\n\n";
  else if(x>p->info) borrar(p->der,x);
  else if(x<p->info) borrar(p->izq,x);
  else {// lo encontre en el nodo p
        q=p;
        if (q->der==NULL) p=q->izq;
        else if (q->izq==NULL) p=q->der;
        else bor(q->izq);//busca en el sub arbol izq
        delete q;
  }
}
void arbol::bor(pnodo &d)
{ if(d->der!=NULL) bor(d->der);//busca el elemento mas a la derecha
  else{ q->info = d->info;
        q=d;
        d=d->izq;
  }
}
void arbol::CreaArbolBus(tarbol x)
{ ArbolBusq(x,raiz);
}
void arbol::ArbolBusq(tarbol x, pnodo &nuevo)
{
  if(nuevo==NULL){
      nuevo= new nodo;
      nuevo->info=x; nuevo->der=nuevo->izq=NULL;
  }
  if(x > nuevo->info) ArbolBusq(x, nuevo->der);
  if(x < nuevo->info) ArbolBusq(x, nuevo->izq);
}
void arbol::ird(pnodo aux)
{  if(aux!=NULL){
        ird(aux->izq);
        cout<<"\n"<<aux->info;
        ird(aux->der);
   }
}
void arbol::rid(pnodo aux)
{  if(aux!=NULL){
        cout<<"\n"<<aux->info;
        rid(aux->izq);
        rid(aux->der);
   }
}
void arbol::idr(pnodo aux)
{  if(aux!=NULL){
        idr(aux->izq);
        idr(aux->der);
        cout<<"\n"<<aux->info;
   }
}
void arbol::show(pnodo aux, int n)
{ int i;
   if(aux!=NULL){                      //OjO este es un recorrido dri
       show(aux->der, n+1);
       for(i=1; i<=n; i++) cout<<"     ";
       cout<<aux->info<<"\n";
       show(aux->izq, n+1);
   }
}

void arbol::ih(pnodo aux,int n)
{  if(aux!=NULL){
        ih(aux->izq,n+1);
        if (aux->izq==NULL && aux->der==NULL)
                              cout<<"\n"<<aux->info<<" nivel: "<<n;
        ih(aux->der,n+1);
   }
}

tarbol arbol::max(pnodo aux)
{  if(aux->der!=NULL){
        return (max(aux->der));
        } return aux->info;
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
   int vec[10]={50,12,18,240,222,45,410,325,38,95};
   for(i=0;i<10;i++){ 
                      T.CreaArbolBus(vec[i]);
                      T.VerArbol();
                      cout<<"-------------------------------------\n";
                      //system("PAUSE");
   } 
                     
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
