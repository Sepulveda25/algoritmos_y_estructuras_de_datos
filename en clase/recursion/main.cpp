#include <cstdlib>
#include <iostream>

using namespace std;
void imprevec (int *p,int n)
{
     if (n==0)
     {cout<<p[n]<<endl;}
     else 
     {imprevec (p,n-1);
     cout<<*(p+n)<<endl;
     }
 }
int suma (int *p,int n)
{
    int total;
    if (n==0)
     {return p[n];}
     else 
     {total=p[n]+suma (p,n-1);
     return total;}
}

int mayor (int *p,int n)
{
    int temp;
    
    if (n==0)
    {return p[n];}
    else
    {
        temp=mayor(p,n-1);
        if (temp<p[n])
        {temp=p[n];}
        return temp;
    }   
}

int multi (int i,int n)
{
    int total;
    if (n==0)
     {return 0;}
     else 
     {total=i+multi (i,n-1);
     return total;}
     
}

void impreD (char *p)
{
     if (*p!='\0'){
                   cout<<*p<<endl;
                   impreD (p+1);}

 }
    
    
void impreR (char *p)
{
     if (*p!='\0'){
                   impreR (p+1);
                   cout<<*p<<endl;
                   }

 }
        
int main(int argc, char *argv[])
{   
    int v[6]={17,11,-2,11,4,10};
    char nom[11]="juan perez";
    
    //imprevec(v,5);
    //cout<<suma(v,5)<<"\n\n";
    //cout<<mayor(v,5)<<"\n\n";
    //cout<<multi(7,5)<<"\n\n";
    
    //impreD (nom);
    impreR (nom);
    
    system("PAUSE");
    return EXIT_SUCCESS;
}


