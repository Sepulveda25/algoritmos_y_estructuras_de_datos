/*  Alumno: Sepúlveda Federico
    Matricula: 35037929
    Carrera: ICOMP
*/
#include <cstdlib>
#include <iostream>

using namespace std;

void invertir (char *,char*);
bool comparar (char*,char*);
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
        
        while ((*(pal+i)!='\0')&&(*(pal+i)==' '))//ignora los espacios
        {
            i++;
        }
        
        while ((*(inv+n)!='\0')&&(*(inv+n)==' '))//ignora los espacios
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
    char max;
    char pal[20]="hola pepe";
    char *direpal,*direinv;
    char invpal[20];
    int n;
    direpal=&pal[0];
    direinv=&invpal[0];
    
    max=mayor(direpal);
    cout<<"la mayor letra es: "<<max<<"\n\n";
    
    invertir(direpal,direinv);
    cout<<"String invertido: "<<direinv<<"\n\n";
    
    if (comparar(direpal,direinv))
    {
     cout<<"Es palindromo \n\n";
    }
    else
    {cout<<"No es palindromo\n\n";}
    
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
