// Este programa lee y graba un archivo binario con structs archivo
//
#include <stdio.h>
#include <iostream>
//#include <conio.h>
//#include <unistd.h>

using namespace std;
int fsize(FILE *p);
struct archivo{
                //int  *p[5];
                //int  d[4];
                int *d;
                int *p;
              };

int fsize(FILE *p)
{ long int l,i;
   i=ftell(p);    //lee pos actual
   fseek(p,0,2);  //se va al final
   l=ftell(p);    //lee cantidad total de bytes
   fseek(p,i,0);  //vuelve a la pos actual
   return l;
}

void escribir_Archivo(int *v,int *p,int nr,FILE *arch)
{
    int mx; struct archivo dato;
    dato.d=v;
    dato.p=p;
    //cout<<*(dato.d)<<endl;
            scanf("%d",&nr);//guarda el numero de registro y la pasa por referencia
            fseek(arch,nr*sizeof(struct archivo),SEEK_SET);//busca en arch  nr posiciones
            //cout<<"\n\n ingrese un numero:  ";scanf("%d",&dato.d);
           // cout<<"  \n ingrese un numero:  ";scanf("%d",&dato.p);
            fwrite(&dato,sizeof(dato),1,arch);
            mx=fsize(arch)/sizeof(dato); cout<<"\n Cantidad de registros= "<<mx;    
}

void leer_Archivo (int nr,FILE *arch)
{
            struct archivo dato;
            int mx=fsize(arch)/sizeof(dato);//cantidad de registros 
            cout<<"\n Cantidad de registros= "<<mx<<endl;
            
            //scanf("%d",&nr);// guarda el numero de registro y la pasa por referencia
            cout<<"\n FSEEK= "<<fseek(arch,nr*sizeof(struct archivo),SEEK_SET)<<endl;
            fread(&dato,sizeof(struct archivo),1,arch);
            for (int n=0;n<4;n++){cout<<"\n numero pos arreglo: "<<n<<" dato= "<<*(dato.d+n)<<endl;}
            for (int n=0;n<4;n++){cout<<"\n direccion pos arreglo: "<<n<<" direccion= "<<*(dato.p+n)<<endl;}
            //cout<<"\n numeros: "<<*(dato.d)<<" numero: "<<dato.p;
}

int main()
{ struct archivo dato;
  FILE *arch;
  char ch;
  int nr,mx, v[4];
  int *p[4];
  system("cls");
  arch=fopen("datos1.dat","r+b");
  //for (int n=0;n<4;n++){v[n]=n*2;}
  //for (int n=0;n<4;n++){cout<<v[n]<<endl;}
  p[0]=v;
   if (arch!=NULL)
   { mx=fsize(arch)/sizeof(dato); cout<<"\n Cantidad de registros= "<<mx<<endl;
     do{
        cout<<"\n desea leer o grabar (l/g) : ";cin>>ch;
      if (ch=='l')
          {
                cout<<"\n ingrese numero de registro a leer: ";//posicion del  registro
                cin>>nr;
                leer_Archivo(nr,arch); 
          }
      else{ 
                cout<<"\n ingrese numero de registro a grabar: ";
                escribir_Archivo( v, *p, nr,arch);
          }
      cout<<"\n\n desea realizar otra operacion (s/n): ";cin>>ch;
     }while(!(ch=='n'));
     fclose(arch);
   }
   system("PAUSE");
    return 0;
    
}


