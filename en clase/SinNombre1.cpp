#include <iostream>
#include <stdlib.h>
#include <stdio.h>

const int MAX = 4 ;
const int MIN = 2 ;

using namespace std;

int fsize(FILE *p);
struct archivo{
                //int  *p[5];
                //int  d[4];
                int *d;
                int *p;
                FILE *arch;
                int nr,mx;
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
            for (int n=0;n<4;n++){cout<<"\n direccion pos arreglo: "<<n<<" direccion= "<<dato.p+n<<endl;}
            //cout<<"\n numeros: "<<*(dato.d)<<" numero: "<<dato.p;
}



//-------------------------------------------------------------------------------
struct nodo
{
	int count ;
	int dato[MAX + 1] ;
	nodo *hijo[MAX + 1] ;
} ;
class arbol:archivo
{
	private :
		nodo *raiz ;
	public :
		arbol( ) ;
		void insertar ( int val ) ;
		int setdato ( int val, nodo *n, int *p, nodo **c, FILE *arch) ;
		static nodo * buscar ( int val, nodo *raiz, int *pos ) ;
		static int buscarnodo ( int val, nodo *n, int *pos ) ;
		void llenarnodo ( int val, nodo *c, nodo *n, int k ) ;
		void explota ( int val, nodo *c, nodo *n,	int k, int *y, nodo **newnodo ) ;
		void del ( int val ) ;
		int delhelp ( int val, nodo *raiz ) ;
		void clear ( nodo *raiz, int k ) ;
		void copysucc ( nodo *raiz, int i ) ;
		void restore ( nodo *raiz, int i ) ;
		void rightshift ( int k ) ;
		void leftshift ( int k ) ;
		void merge ( int k ) ;
		void show() ;
		static void display ( nodo *raiz ) ;
		static void deltree ( nodo *raiz ) ;
		~arbol( ) ;
} ;
 
arbol :: arbol( )
{
	raiz = NULL ;
}
void arbol :: insertar ( int val )
{
	int i ;
	FILE *arch=fopen("datos1.dat","r+b");
	nodo *c, *n ;
	int flag ;
	flag = setdato ( val, raiz, &i, &c, arch) ;
	if ( flag )
	{
		n = new nodo ;
		n -> count = 1 ;
		n -> dato[1] = i ;
		n -> hijo[0] = raiz ;
		n -> hijo[1] = c ;
		raiz = n ;
	}
}
int arbol :: setdato ( int val, nodo *n, int *p, nodo **c, FILE *arch )
{
	int k ;
	if ( n == NULL )
	{
		*p = val ;
		*c = NULL ;
		return 1 ;
	}
	else
	{
		if ( buscarnodo ( val, n, &k ) )
			cout << endl << "Key dato already exists." << endl ;
		if ( setdato ( val, n -> hijo[k], p, c, arch ) )
		{
			if ( n -> count < MAX )
			{
				llenarnodo ( *p, *c, n, k ) ;
				return 0 ;
			}
			else
			{
				explota ( *p, *c, n, k, p, c ) ;
				return 1 ;
			}
		}
		return 0 ;
	}
}
nodo * arbol :: buscar ( int val, nodo *raiz, int *pos )
{
	if ( raiz == NULL )
		return NULL ;
	else
	{
		if ( buscarnodo ( val, raiz, pos ) )
			return raiz ;
		else
			return buscar ( val, raiz -> hijo[*pos], pos ) ;
	}
}
int arbol :: buscarnodo ( int val, nodo *n, int *pos )
{
	if ( val < n -> dato[1] )
	{
		*pos = 0 ;
		return 0 ;
	}
	else
	{
		*pos = n -> count ;
		while ( ( val < n -> dato[*pos] ) && *pos > 1 )
			( *pos )-- ;
		if ( val == n -> dato[*pos] )
			return 1 ;
		else
			return 0 ;
	}
}
void arbol :: llenarnodo ( int val, nodo *c, nodo *n, int k )
{
	int i ;
	for ( i = n -> count ; i > k ; i-- )
	{
		n -> dato[i + 1] = n -> dato[i] ;
		n -> hijo[i + 1] = n -> hijo[i] ;
	}
	n -> dato[k + 1] = val ;
	n -> hijo[k + 1] = c ;
	n -> count++ ;
}
void arbol :: explota ( int val, nodo *c, nodo *n,	int k, int *y, nodo **newnodo )
{
	int i, mid ;
 
	if ( k <= MIN )
		mid = MIN ;
	else
		mid = MIN + 1 ;
 
	*newnodo = new nodo ;
 
	for ( i = mid + 1 ; i <= MAX ; i++ )
	{
		( *newnodo ) -> dato[i - mid] = n -> dato[i] ;
		( *newnodo ) -> hijo[i - mid] = n -> hijo[i] ;
	}
 
	( *newnodo ) -> count = MAX - mid ;
	n -> count = mid ;
 
	if ( k <= MIN )
		llenarnodo ( val, c, n, k ) ;
	else
		llenarnodo ( val, c, *newnodo, k - mid ) ;
 
	*y = n -> dato[n -> count] ;
	( *newnodo ) -> hijo[0] = n -> hijo[n -> count] ;
	n -> count-- ;
}
void arbol :: del ( int val )
{
	nodo * temp ;
 
	if ( ! delhelp ( val, raiz ) )
		cout << endl << "Value " << val << " not found." ;
	else
	{
		if ( raiz -> count == 0 )
		{
			temp = raiz ;
			raiz = raiz -> hijo[0] ;
			delete temp ;
		}
	}
}
int arbol :: delhelp ( int val, nodo *raiz )
{
	int i ;
	int flag ;
 
	if ( raiz == NULL )
		return 0 ;
	else
	{
		flag = buscarnodo ( val, raiz, &i ) ;
		if ( flag )
		{
			if ( raiz -> hijo[i - 1] )
			{
				copysucc ( raiz, i ) ;
				flag = delhelp ( raiz -> dato[i], raiz -> hijo[i] ) ;
				if ( !flag )
					cout << endl << "Value " << val << " not found." ;
			}
			else
				clear ( raiz, i ) ;
		}
		else
			flag = delhelp ( val, raiz -> hijo[i] ) ;
		if ( raiz -> hijo[i] != NULL )
		{
			if ( raiz -> hijo[i] -> count < MIN )
				restore ( raiz, i ) ;
		}
		return flag ;
	}
}
void arbol :: clear ( nodo *raiz, int k )
{
	int i ;
	for ( i = k + 1 ; i <= raiz -> count ; i++ )
	{
		raiz -> dato[i - 1] = raiz -> dato[i] ;
		raiz -> hijo[i - 1] = raiz -> hijo[i] ;
	}
	raiz -> count-- ;
}
void arbol :: copysucc ( nodo *raiz, int i )
{
	nodo *temp = raiz -> hijo[i] ;
 
	while ( temp -> hijo[0] )
		temp = temp -> hijo[0] ;
 
	raiz -> dato[i] = temp -> dato[1] ;
}
void arbol :: restore ( nodo *raiz, int i )
{
	if ( i == 0 )
	{
		if ( raiz -> hijo [1] -> count > MIN )
			leftshift ( 1 ) ;
		else
			merge ( 1 ) ;
	}
	else
	{
		if ( i == raiz -> count )
		{
			if ( raiz -> hijo[i - 1] -> count > MIN )
				rightshift ( i ) ;
			else
				merge ( i ) ;
		}
		else
		{
			if ( raiz -> hijo[i - 1] -> count > MIN )
				rightshift ( i ) ;
			else
			{
				if ( raiz -> hijo[i + 1] -> count > MIN )
					leftshift ( i + 1 ) ;
				else
					merge ( i ) ;
			}
		}
	}
}
void arbol :: rightshift ( int k )
{
	int i ;
	nodo *temp ;
 
	temp = raiz -> hijo[k] ;
 
	for ( i = temp -> count ; i > 0 ; i-- )
	{
		temp -> dato[i + 1] = temp -> dato[i] ;
		temp -> hijo[i + 1] = temp -> hijo[i] ;
	}
 
	temp -> hijo[1] = temp -> hijo[0] ;
	temp -> count++ ;
	temp -> dato[1] = raiz -> dato[k] ;
	temp = raiz -> hijo[k - 1] ;
	raiz -> dato[k] = temp -> dato[temp -> count] ;
	raiz -> hijo[k] -> hijo [0] = temp -> hijo[temp -> count] ;
	temp -> count-- ;
}
void arbol :: leftshift ( int k )
{
	nodo *temp ;
 
	temp = raiz -> hijo[k - 1] ;
	temp -> count++ ;
	temp -> dato[temp -> count] = raiz -> dato[k] ;
	temp -> hijo[temp -> count] = raiz -> hijo[k] -> hijo[0] ;
	temp = raiz -> hijo[k] ;
	raiz -> dato[k] = temp -> dato[1] ;
	temp -> hijo[0] = temp -> hijo[1] ;
	temp -> count-- ;
	for ( int i = 1 ; i <= temp -> count ; i++ )
	{
		temp -> dato[i] = temp -> dato[i + 1] ;
		temp -> hijo[i] = temp -> hijo[i + 1] ;
	}
}
void arbol :: merge ( int k )
{
	nodo *temp1, *temp2 ;
	temp1 = raiz -> hijo[k] ;
	temp2 = raiz -> hijo[k - 1] ;
	temp2 -> count++ ;
	temp2 -> dato[temp2 -> count] = raiz -> dato[k] ;
	temp2 -> hijo[temp2 -> count] = raiz -> hijo[0] ;
	for ( int i = 1 ; i <= temp1 -> count ; i++ )
	{
		temp2 -> count++ ;
		temp2 -> dato[temp2 -> count] = temp1 -> dato[i] ;
		temp2 -> hijo[temp2 -> count] = temp1 -> hijo[i] ;
	}
	for ( int i = k ; i < raiz -> count ; i++ )
	{
		raiz -> dato[i] = raiz -> dato[i + 1] ;
		raiz -> hijo[i] = raiz -> hijo[i + 1] ;
	}
	raiz -> count-- ;
	delete temp1 ;
}
void arbol :: show( )
{
	display ( raiz ) ;
}
void arbol :: display ( nodo *raiz )
{
	int i;
	if ( raiz != NULL )
	{		
		for ( i = 0 ; i < raiz -> count ; i++ )
		{
			display ( raiz -> hijo[i] ) ;
			cout << raiz -> dato[i + 1] << "\t" ;
		}
		display ( raiz -> hijo[i] ) ;
	}
}

void arbol :: deltree ( nodo *raiz )
{
	int i;
	if ( raiz != NULL )
	{
		for ( i = 0 ; i < raiz -> count ; i++ )
		{
			deltree ( raiz -> hijo[i] ) ;
			delete ( raiz -> hijo[i] ) ;
		}
		deltree ( raiz -> hijo[i] ) ;
		delete ( raiz -> hijo[i] ) ;
	}
}
 
arbol :: ~arbol( )
{
	deltree ( raiz ) ;
}
 
int main( )
{
    struct archivo dato;
    FILE *arch;
    char ch;
    int nr,mx, v[4];
    int *p[4];
    system("cls");
    arch=fopen("datos1.dat","r+b");
	arbol b ;
	int arr[ ] = { 27, 42, 22, 47, 32, 2, 51, 40, 13 } ;
	int sz = sizeof ( arr ) / sizeof ( int ) ;
	for ( int i = 0 ; i < sz ; i++ )
		b.insertar ( arr[i] ) ;
	cout << "B-tree of order 5:" << endl ;
	b.show( ) ;
	b.del ( 22 ) ;
	b.del ( 11 ) ;
	cout << "\n\nB-tree after deletion of datos:" << endl ;
	b.show( ) ;
	system("pause");
    return 0;
}
