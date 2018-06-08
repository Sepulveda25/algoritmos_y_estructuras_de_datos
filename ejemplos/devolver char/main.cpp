#include <cstdlib>
#include <iostream>

using namespace std;
char *concat(char *, char *);

char *concat (char *uno,char *dos)
{
    char *m;
    int n=0;
    char jop[10]="hola";
    m=&jop[0];
    
    while(*(dos+n)!='\0')
    {*(dos+n)=jop[n];
        n++;
    }
       
    
    cout<<dos<<"\n\n";
   
   return dos; 
}
/*char concat2(char *uno, char *dos,char *tres, int n, int i)
{
    if ((*(uno+n)!='\0')||(*(dos+i)!='\0'))
    {
        
    }
    else
    {
        return *tres;
    }
}*/

int main(int argc, char *argv[])
{
    char pal[10]="hola pepe";
    char pal2[12]="jajaja";
    int n=0;
    char *r;
    //r=(char*) malloc(sizeof (char)*10);
    
    
    r=concat(&pal[0],&pal2[0]);
    cout<<pal2[0]<<"\n\n";
    /*while(*(r+n)!='\0')
    {cout<<*(r+n)<<"\n\n";
        n++;
    }*/
    //free(r);
    system("PAUSE");
    return EXIT_SUCCESS;
}
