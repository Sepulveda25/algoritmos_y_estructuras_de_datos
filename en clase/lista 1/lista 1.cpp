#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class Lista{
      private:
              int d;
              Lista *next;
      public:
             Lista();
             void add(int x);
             void impre(void);
             bool empty(void);
};
Lista::Lista()
{     next=NULL;
}      
bool Lista::empty(void)
{  return next==NULL;
}
void Lista::add(int x)
{     Lista *aux;
      aux= new Lista;
      aux->d=x;
      aux->next=next;
      next=aux;
}
void Lista::impre(void)
{      Lista *aux;
       if(!this->empty()){
           aux=next;
           while(aux!=NULL){
                        cout<<endl<<setw(4)<<aux->d;
                        aux=aux->next;
                        }
       }   
       else cout<<"LISTA VACIA";              
}
int main(int argc, char *argv[])
{   Lista l;
    l.impre();
    l.add(5);
    l.add(9);
    l.add(-3);
    l.impre();
    cout<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
