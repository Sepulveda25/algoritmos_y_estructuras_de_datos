#include <cstdlib>
#include <iostream>
#define MAX 10
using namespace std;
typedef string tipolista;


class Pila
{
      private:
              tipolista v [MAX];
              int p;
      public:
             Pila();
             void apilar (tipolista x);
             tipolista tope(void);
             void desapilar (void);
             bool pilavacia();
      
};

Pila::Pila()
{
            p=-1;
}

void Pila::apilar(tipolista x)
{  
   p++;
   v[p]=x;                                
}

tipolista Pila::tope(void)
{
        if (pilavacia()){cout<<"La pila esta vacia"<<"\n\n";
        return "";}
        else{return v[p];}    
}

void Pila::desapilar(void)
{
     if (pilavacia()){cout<<"La pila esta vacia"<<"\n\n";}
     else{p--;}
     
 }
bool Pila::pilavacia()
{
     if (p==-1)
     {return true;}
     else{return false;}
} 

int main(int argc, char *argv[])
{
    Pila *p=new Pila();
    p->apilar ("primer");
    p->apilar ("segundo");
    p->apilar ("tercero");
    cout<<endl<<p->tope()<<endl;
    p->desapilar();
    cout<<endl<<p->tope()<<endl;
    p->desapilar();
    cout<<endl<<p->tope()<<endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
