#include <cstdlib>
#include <iostream>
#define INFINITO  9000
#define MAXNODOS  5


void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS]);
void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS],int cf[][MAXNODOS]);
void caminoFloyd(int cf[][MAXNODOS], int s, int t);

using namespace std;

int main(int argc, char *argv[])
{   int peso[MAXNODOS][MAXNODOS]={9000, 9000,    4,   13, 9000,
                                  9000, 9000,    1, 9000, 9000,
                                  9000, 9000, 9000,    2,   11,
                                  9000, 9000, 9000, 9000,    2,
                                    10,   10, 9000,    1, 9000      
                                 };
    int caminos[MAXNODOS][MAXNODOS];
    int cf[MAXNODOS][MAXNODOS];
    int MatrizFloyd[MAXNODOS][MAXNODOS];
    int *pdist, i, j, precede[MAXNODOS],s,t;
    
    s=5;  // vertice de inicio
    t=2;  // vertice final
    
    cout<<endl<<"Matriz de pesos";   
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",peso[i][j]);                 
           }                 
    }
    s=s-1; t=t-1;
    warshall(peso,caminos);
    cout<<"\n\n";
    cout<<"\n WARSHALL ------------------------\n";
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",caminos[i][j]); 
           }//fin for j                 
    }//fin for i
    cout<<"\n\n";
    if(caminos[s][t]==1){
                         cout<<"\n HAY CAMINO ENTRE s= "<<s+1
                             <<" y t= "<<t+1<<endl;
                         Floyd(peso,MatrizFloyd,cf);
                         cout<<"\n costo para ir de "
                             <<s+1<<" a "<<t+1<<"= "
                             <<MatrizFloyd[s][t];
                         cout<<"\n\n camino:  "<<s+1;
                         caminoFloyd(cf,s,t);
                         cout<<"  "<<t+1;  
    }
    else{
          cout<<"\n NO HAY CAMINO POSIBLE ENTRE s= "
              <<s+1<<" y t= "<<t+1<<endl;
          
    }//fin if

    cout<<endl<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS])
{ int i,j,k;
//inicializo caminos haciendola igual a la adjunta impl??cita en peso  
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                if(peso[i][j]==INFINITO)caminos[i][j]=0;
                else                    caminos[i][j]=1;
         }//fin for j
  }//fin for i
  
  for(k=0;k<MAXNODOS;k++){
         for(i=0;i<MAXNODOS;i++){
                for(j=0;j<MAXNODOS;j++){                 
                                if(caminos[i][j]==0) 
                                   caminos[i][j]=caminos[i][k]&&caminos[k][j];
                }//fin for j
         }//fin for i
  }//fin for k
}//fin warshall     

void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS], int cf[][MAXNODOS])
{ int i,j,k;
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 A[i][j]=peso[i][j]; cf[i][j]=-1;
         }
  }
  for(i=0;i<MAXNODOS;i++) A[i][i]=0;
  
  for(k=0;k<MAXNODOS;k++){
      for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 if((A[i][k]+ A[k][j])< A[i][j]){
                                              A[i][j]= A[i][k]+ A[k][j];
                                              cf[i][j]=k;
                                 }
         }
      }
  }
    cout<<"\n FLOYD ------------------------\n";    
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",A[i][j]);                 
           }                 
    }
    cout<<endl;
    system("PAUSE");
     
}

void caminoFloyd(int cf[][MAXNODOS], int s, int t)
{ int k;

  k=cf[s][t];
  if (k!=-1){
            caminoFloyd(cf,s,k);
            cout<<"  "<<k+1;
            caminoFloyd(cf,k,t);
            }
}
