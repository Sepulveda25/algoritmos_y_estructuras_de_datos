#include <cstdlib>
#include <iostream>

using namespace std;

char *concat2(char *uno, char *dos,char *tres,int n, int i)
{   
    if ((*(uno+n)=='\0')&&(*(dos+i)=='\0'))
    {
        return (dos+i); 
    }   else{    if (*(uno+n)!='\0')
                {                       
                        *(tres+n+1)=*concat2(uno,dos,tres,n+1,i);
                        return (uno+n);
                    
                } else {    if (*(dos+i)!='\0')
                            {
                                *(tres+n+i+1)= *concat2(uno,dos,tres,n,i+1);
                                return (dos+i);
                            }
                        }   
            }
}

char *concat (char *uno,char *dos)
{
    int i=0,n=0;
    
    while (*(dos+i)!='\0')//cuenta la cantidad de caracteres 
    {
        i++;
    } 
    while (*(uno+n)!='\0')//cuenta la cantidad de caracteres 
    {
        n++;
    } 
    char *tres = new char[i+n+1];
    *(tres)=*concat2(uno,dos,tres,0,0);
    return tres; 
}

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
    char pal2[]=" y chau!";
    char *pal3;
    char *pal4;
    
    pal3=concat(pal1,pal2);//llamada concatenacion recursiva
    pal4=concat_itvo(pal1,pal2);//llamada concatenacion iterativa
    
    cout<<"Concatenacion recusiva: "<<pal3<<"\n\n";
    cout<<"Concatenacion iterativa: "<<pal4<<"\n\n";
    
    delete [] pal3;
    delete [] pal4;
    system("PAUSE");
    return EXIT_SUCCESS;
}
