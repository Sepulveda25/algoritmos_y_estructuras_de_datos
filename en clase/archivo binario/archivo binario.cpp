// Este programa lee y graba un archivo binario con structs archivo
//
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <unistd.h>

using namespace std;
int fsize(FILE *p);
struct archivo{
                int   n;
                char  d[20];
                float r;
              };

int fsize(FILE *p)
{ long int l,i;
   i=ftell(p);    //lee pos actual
   fseek(p,0,2);  //se va al final
   l=ftell(p);    //lee cantidad total de bytes
   fseek(p,i,0);  //vuelve a la pos actual
   return l;
}


int main()
{ struct archivo dato;
  float f;
  FILE *arch;
  char ch;
  int nr,mx;
  system("cls");
  arch=fopen("datos1.dat","r+b");
   if (arch!=NULL)
   { mx=fsize(arch)/sizeof(dato); cout<<"\n Cantidad de registros= "<<mx<<endl;
     do{
        cout<<"\n desea leer o grabar (l/g) : ";cin>>ch;
      if (ch=='l')
          { mx=fsize(arch)/sizeof(dato);//cantidad de registros 
            cout<<"\n Cantidad de registros= "<<mx<<endl;
            cout<<"\n ingrese numero de registro a leer: ";
            scanf("%d",&nr);// guarda el numero de registro y la pasa por referencia
            cout<<"\n FSEEK= "<<fseek(arch,nr*sizeof(struct archivo),SEEK_SET)<<endl;
            fread(&dato,sizeof(struct archivo),1,arch);
            cout<<"\n numero: "<<dato.n<<" cadena: "<<dato.d<<" numero: "<<dato.r;
          }
      else{ cout<<"\n ingrese numero de registro a grabar: ";
            scanf("%d",&nr);//guarda el numero de registro y la pasa por referencia
            fseek(arch,nr*sizeof(struct archivo),SEEK_SET);//busca en arch  nr posiciones
            cout<<"\n\n ingrese un numero:  ";scanf("%d",&dato.n);
            cout<<"  \n ingrese una cadena: ";fflush(stdin);gets(dato.d);
            cout<<"  \n ingrese un numero:  ";scanf("%f",&dato.r);
            fwrite(&dato,sizeof(dato),1,arch);
            mx=fsize(arch)/sizeof(dato); cout<<"\n Cantidad de registros= "<<mx;
          }
      cout<<"\n\n desea realizar otra operacion (s/n): ";cin>>ch;
     }while(!(ch=='n'));
     fclose(arch);
   }
   system("PAUSE");
    return 0;
    
}


