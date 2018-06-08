#include <cstdlib>
#include <iostream>

using namespace std;

void invertir (char *,char*);
bool comparar (char*,char*);

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

bool comparar (char *pal,char *inv)
{
    int n=0,i=0;
    bool salir=true;
       
    while (((*(pal+i)!='\0')&&(*(inv+n)!='\0'))&&(salir))
    {
        
        while ((*(pal+i)!='\0')&&(*(pal+i)==' '))//ingnora los espacios
        {
            i++;
        }
        
        while ((*(inv+n)!='\0')&&(*(inv+n)==' '))//ingnora los espacios
        {
            n++;
        }
        
        if (*(pal+i)==*(inv+n))//compara los caracteres
        {
            i++;
            n++;
        }
        else
        {
            salir=false;
        }  
        
    } 

    if (salir)
    {return true;}
    else
    {return false;}
    
}

int main(int argc, char *argv[])
{
    
    char pal[20]="hola pepe";
    char *direpal,*direinv;
    char invpal[20];
    int n;
    direpal=&pal[0];
    direinv=&invpal[0];
    
    
    invertir(direpal,direinv);
    if (comparar(direpal,direinv))
    {
     cout<<"Es palindromo \n\n";
    }
    else
    {cout<<"No es palindromo\n\n";}
    //cout<<direinv<<"\n\n";
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
