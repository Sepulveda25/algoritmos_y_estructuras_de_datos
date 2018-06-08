// constructing bitsets
#include <iostream>
#include <string>
#include <bitset>
using namespace std;
class xx{
      public:
      bitset<7> M[7];
      void impre();
      //definiendo and de conjuntos
      friend xx operator &(xx c1, xx c2);
};

xx operator &(xx c1, xx c2){ 
     xx c3;
     for(int i=0;i<7;i++)
            c3.M[i] = c1.M[i]&c2.M[i];
     return c3;
}
void xx::impre(){
     int i,j;
     for(i=0;i<7;i++){
                      cout<<endl;
                      for(j=0;j<7;j++)                 
                          cout<<this->M[i][j]<<"  ";
}
}
                     
int main ()
{  xx a,b,c;
   a.M[0][3]=1;
   b=a;
   b.M[1].set();
   c=a&b;
   c.impre();
   
  cout<<endl<<endl;
  system("PAUSE");
  return 0;
}
