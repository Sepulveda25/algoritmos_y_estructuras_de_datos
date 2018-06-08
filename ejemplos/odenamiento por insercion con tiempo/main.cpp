#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

void impre(int *v)
{ int i;
  printf("\n");
  for(i=0;i<MAX;i++)
     printf("\n %3d   %3d",i,v[i]);
}

int main(int argc, char *argv[])
{int i,j,k,di;
 int a[MAX];//={50,40,30,20,10}; 
 
 
 for(i=0;i<MAX;i++)
 {
    a[i]=int(rand());
 }
 

 for(i=1;i<MAX;i++)
 {
   j=i-1; di=a[i];           
   while(di<a[j] && j>=0)
   {
      a[j+1]=a[j];            
      j--;
   }
   a[j+1]=di;     
 }
  impre(a);
  
  
  cout<<"ha\n\n";
  system("PAUSE");	
  return 0;
}


