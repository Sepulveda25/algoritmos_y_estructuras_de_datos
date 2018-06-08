#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    int v[8]={0,7,12,5,38,25,9,15};
    int aux;
    
   for (int n=2;n<=4;n=n*2)
    {
        for (int i=7;i>=n;i--)
        {
            if (v[i]>v[i/2]){aux=v[i];v[i]=v[i/2];v[i/2]=aux;}
        }
    }
    
     
    
    for (int i=1;i<=7;i++)
    {
        cout<<v[i]<<endl;
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
