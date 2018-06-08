#include <cstdlib>
#include <iostream>

using namespace std;

char *concat_itvo (char *uno,char *dos)
{
    int i=0, n=0;
    while (*(uno+i)!='\0')
    {
        i++;
    }
    while (*(dos+n)!='\0')
    {
        n++;
    }
    
    char *tres =new char[n+i];
    *(tres+n+i)='\0';
    n=0;
    i=0;
    while (*(uno+i)!='\0')
    {
        *(tres+i)=*(uno+i);
        i++;
    }
    while (*(dos+n)!='\0')
    {
        *(tres+i+n)=*(dos+n);
        n++;
    }
    return tres;
}

int main()
{
    char pal1[]="hola pepe";
    char pal2[]=" y chau pepe";
    char *pal3;
    
    pal3=concat_itvo(pal1,pal2);
    cout<<pal3<<"\n\n";
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
