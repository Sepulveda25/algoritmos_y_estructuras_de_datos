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

  
        

int main()
{
    char pal[]="hola pepe";
    char pal2[]=" y chau!";
    char *pal3;
    
    
    pal3=concat(pal,pal2);
    
    cout<<"Concatenacion con funcion recursiva: "<<pal3<<"\n\n";
    
    delete [] pal3;
    system("PAUSE");
    return EXIT_SUCCESS;
}
