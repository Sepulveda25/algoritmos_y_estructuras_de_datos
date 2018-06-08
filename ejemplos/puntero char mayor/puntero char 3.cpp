#include <cstdlib>
#include <iostream>

using namespace std;
char mayor (char *);

char mayor (char *dir)
{
    char m=*dir; //se guarda el primer caracter
    int i=1;
    
    while (*(dir+i)!='\0')
    {
        if (*(dir+i)>m)
        {m=*(dir+i);}
        i++;
    }
   return m; 
}


int main(int argc, char *argv[])
{
    char pal[10]="hola pepe";
    char *direpal;
    char max;
    
    direpal=&pal[0];
    
    max=mayor(direpal);
    cout<<"la mayor letra es: "<<max<<"\n\n";
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
