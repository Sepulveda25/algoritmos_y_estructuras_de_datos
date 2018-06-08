#include <cstdlib>
#include <iostream>

using namespace std;

void invertir (char *,char*);

void invertir (char *dir,char *dirinv)
{
    int i=0;
    int n;
    
    while (*(dir+i)!='\0')//cuenta la cantidad de caracteres 
    {
        i++;
    } 
      *(dirinv+i)='\0';  
    for (n=0;n<i;n++)
    {
        *(dirinv+n)=*(dir+i-n-1);
         
    }
    
}


int main(int argc, char *argv[])
{
    char pal[10]="hola pepe";
    char *direpal,*direinv;
    char invpal[10];
    int n;
    direpal=&pal[0];
    direinv=&invpal[0];
    
    
    invertir(direpal,direinv);
    
    cout<<direinv<<"\n\n";
   
    

    system("PAUSE");
    return EXIT_SUCCESS;
}
