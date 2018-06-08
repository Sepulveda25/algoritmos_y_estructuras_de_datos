#include <iostream>
#include <stdlib.h>
#include <stdio.h>

const int MAX = 4 ;
const int MIN = 2 ;

using namespace std;

int fsize(FILE *p);
struct archivo{           
                int  d[4];
                int p[5];
              };
 
int fsize(FILE *p)
{ long int l,i;
   i=ftell(p);    //lee pos actual
   fseek(p,0,2);  //se va al final
   l=ftell(p);    //lee cantidad total de bytes
   fseek(p,i,0);  //vuelve a la pos actual
   return l;
}

void escribir_Archivo(int *v,int *p,int nr,FILE *arch, int cant)
{
    int mx; struct archivo dato;
   for (int n=0;n<cant;n++){dato.d[n]=*(v+n);}
   for (int n=0;n<cant;n++){dato.p[n]=*(p+n);}
    //cout<<*(dato.d)<<endl;
            //scanf("%d",&nr);//guarda el numero de registro y la pasa por referencia
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
            //for (int n=0;n<4;n++){cout<<"\n numero pos arreglo: "<<n<<" dato= "<<dato.d[n]<<endl;}
            //for (int n=0;n<4;n++){cout<<"\n direccion pos arreglo: "<<n<<" direccion= "<<dato.p[n]<<endl;}
            //cout<<"\n numeros: "<<*(dato.d)<<" numero: "<<dato.p;
}

void imprimir_Archivo (int nr,FILE *arch)
{
            struct archivo dato;
            int mx=fsize(arch)/sizeof(dato);//cantidad de registros
            cout<<"\n Cantidad de registros= "<<mx<<endl;
           
            //scanf("%d",&nr);// guarda el numero de registro y la pasa por referencia
            cout<<"\n FSEEK= "<<fseek(arch,nr*sizeof(struct archivo),SEEK_SET)<<endl;
            fread(&dato,sizeof(struct archivo),1,arch);
            for (int n=0;n<4;n++){cout<<"\n numero pos arreglo: "<<n<<" dato= "<<dato.d[n]<<endl;}
            for (int n=0;n<4;n++){cout<<"\n direccion pos arreglo: "<<n<<" direccion= "<<dato.p[n]<<endl;}
            //cout<<"\n numeros: "<<*(dato.d)<<" numero: "<<dato.p;
}

int largo_d(FILE *arch, int nr)
{
	struct archivo dato;
	arch=fopen("datos1.dat","r+b");
    int largo, i=0;
    while(dato.d[i] != '\0')
    {
		largo++;
		i++;
	}
	return largo;
}

int largo_p(FILE *arch, int nr)
{
	struct archivo dato;
	arch=fopen("datos1.dat","r+b");
    int largo, i=0;
    while(dato.p[i] != '\0')
    {
		largo++;
		i++;
	}
	return largo;
}

////////////////////////////////////////////////////////////////////////
//////////////////////////////B-TREE
////////////////////////////////////////////////////////////////////////
struct nodo
{
	int tamanio ;
	int dato[MAX + 1] ;
	nodo *hijo[MAX + 1] ;
} ;
class arbol:archivo
{
	private :
		nodo *raiz ;
	public :
		arbol( ) ;
		void insertar ( int val, FILE *arch) ;
		int crearArbolBusqueda ( int val, int mx, int *p, nodo **c, FILE *arch) ;
		static nodo * buscar ( int val, nodo *raiz, int *pos ) ;
		static int buscarnodo ( int val, int nr, int *pos, FILE *arch) ;
		void llenarnodo ( int *val,int *c, int nr, int k, FILE *arch) ;
		void explota ( int val, nodo *hijo,	int k, int *nuevo_padre, nodo **nuevo_hijo, FILE *arch, int &mx) ;
		void borrar ( int val ) ;
		int borrar_aux ( int val, nodo *raiz ) ;
		void limpiar ( nodo *raiz, int k ) ;
		void copiar_exito ( nodo *raiz, int i ) ;
		void restaurar ( nodo *raiz, int i ) ;
		void derecha ( int k ) ;
		void izquierda ( int k ) ;
		void unir ( int k ) ;
		void Show() ;
		static void show ( nodo *raiz ) ;
		static void borrarArbol ( nodo *raiz ) ;
		//~ ~arbol( ) ;
} ;
 
arbol :: arbol( )
{
	raiz = NULL ;
}

void arbol :: insertar ( int val, FILE *arch)
{
	int i ;
	struct archivo dato;
	arch=fopen("datos1.dat","r+b");
	imprimir_Archivo(1,arch);
	int mx=fsize(arch)/sizeof(dato);
	nodo *c, *n ;
	int flag ;
	flag = crearArbolBusqueda ( val, mx, &i, &c, arch) ;
	if ( flag )
	{
		n = new nodo ;
		n -> tamanio = 1 ;
		//n -> dato[1] = i ;
		dato.d[1]=i;
		dato.p [0] = 0 ;
		dato.p [1] = 0 ;
		raiz = n ;
		escribir_Archivo( dato.d, dato.p, mx,arch,raiz->tamanio);
	}
	fclose(arch);
}
int arbol :: crearArbolBusqueda ( int val, int mx, int *padre, nodo **hijo, FILE *arch)
{
	
	cout<<"Putilin 2º vuelta.."<<endl;
	int k ;
	struct archivo dato;
	arch=fopen("datos1.dat","r+b");
	cout<<"heyyyyyy "<<mx;
	if ( mx == 0 )
	{
		*padre = val ;
		*hijo = NULL ;
		cout<<"pas true";
		return 1 ;
	}
	else
	{	cout<<"pas else";
		if ( buscarnodo ( val, 1, &k, arch) ) {	cout << endl << "El Valor a ingresar ya existe" << endl ;}
		cout<<"	PASO BUSCARNODO!!!!!"<<	endl;
		if ( crearArbolBusqueda ( val, (mx+1), padre, hijo, arch ) )
		{
			cout<<"HOLA!!!!"<<endl;
			if ( mx < MAX )
			{
				llenarnodo ( dato.d, dato.p, mx, k, arch) ;
				return 0 ;
			}
			else
			{
				explota ( *padre, *hijo, k, padre, hijo, arch, mx) ;
				return 1 ;
			}
		}
		cout<<"CAB es false??"<<endl;
		return 0 ;
	}
	fclose(arch);
}
nodo * arbol :: buscar ( int val, nodo *raiz, int *pos )
{
	if ( raiz == NULL )
		return NULL ;
	else
	{
		//~ if ( buscarnodo ( val, raiz, pos ) )
			return raiz ;
		//~ else
			return buscar ( val, raiz -> hijo[*pos], pos ) ;
	}
}
int arbol :: buscarnodo ( int val,int nr, int *pos, FILE *arch)
{
	struct archivo dato;
	arch=fopen("datos1.dat","r+b");
	cout<<endl<<"Buscarnodo INICIO              "<<endl;
	leer_Archivo(nr,arch);cout<<"Paso el leer.  "<<endl;
	if ( val < dato.d[1] )
	{
		cout<<"Entro al if.."<<endl;
		pos = 0 ;
	cout<<"Buscarnodo FIN              "<<endl;
		return 0 ;
	}
	else
	{
		cout<<"Entro al else.."<<endl;
		*pos = largo_d(arch, nr);
		while ( ( val < dato.d[*pos] ) && *pos > 1 )
			pos-- ;
		if ( val == dato.d[*pos] )
			return 1 ;
		else
			return 0 ;
	}
	cout<<"Buscarnodo FIN              "<<endl;

	fclose(arch);
}

void arbol :: llenarnodo ( int *val,int *c, int nr, int k, FILE *arch)
{
	struct archivo dato;
	arch=fopen("datos1.dat","r+b");
	leer_Archivo(nr,arch);
	int i ;
	for ( i = raiz->tamanio ; i > k ; i-- )
	{
		dato.d[i + 1] = dato.d[i] ;
		dato.p[i + 1] = dato.p[i] ;
	}
	dato.d[k + 1] = *val ;
	dato.p[k + 1] = *c ;
	raiz->tamanio++ ;
	escribir_Archivo(dato.d, dato.p, nr,arch, raiz->tamanio);
	fclose(arch);
}

void arbol :: explota ( int val, nodo *hijo, int k, int *nuevo_padre, nodo **nuevo_hijo, FILE *arch, int &mx)
{
	struct archivo dato;
	int i, mid ;
	int large_d,large_p;
	int dato_aux[4];
	int punt_aux[5];
 
	if ( k <= MIN )
		mid = MIN ;
	else
		mid = MIN + 1 ;
 
	//~ *nuevo_hijo = new nodo ;
 
	for ( i = mid + 1 ; i <= MAX ; i++ )
	{
		dato_aux[i - mid] = dato.d[i] ;
		punt_aux[i - mid] = dato.p[i] ;
	}
 
	large_p = MAX - mid ;
	large_d = mid ;
 
	if ( k <= MIN )
		llenarnodo ( dato_aux, punt_aux, mx, k, arch) ;
	else
		llenarnodo (dato_aux, punt_aux, mx, k - mid, arch) ;
 
	dato.d[0] = dato.d[large_d] ;
	dato.p[0] = dato.p[large_p] ;
	large_d-- ;
	large_p-- ;
}
/*
void arbol :: borrar ( int val )
{
	nodo * temp ;
 
	if ( ! borrar_aux ( val, raiz ) )
		cout << endl << "Valor " << val << " no encontrado." ;
	else
	{
		if ( raiz -> tamanio == 0 )
		{
			temp = raiz ;
			raiz = raiz -> hijo[0] ;
			delete temp ;
		}
	}
}
int arbol :: borrar_aux ( int val, nodo *raiz )
{
	int i ;
	int flag ;
 
	if ( raiz == NULL )
		return 0 ;
	else
	{
		//~ flag = buscarnodo ( val, raiz, &i ) ;
		if ( flag )
		{
			if ( raiz -> hijo[i - 1] )
			{
				copiar_exito ( raiz, i ) ;
				flag = borrar_aux ( raiz -> dato[i], raiz -> hijo[i] ) ;
				if ( !flag )
					cout << endl << "Valor " << val << " no encontrado." ;
			}
			else
				limpiar ( raiz, i ) ;
		}
		else
			flag = borrar_aux ( val, raiz -> hijo[i] ) ;
		if ( raiz -> hijo[i] != NULL )
		{
			if ( raiz -> hijo[i] -> tamanio < MIN )
				restaurar ( raiz, i ) ;
		}
		return flag ;
	}
}
void arbol :: limpiar ( nodo *raiz, int k )
{
	int i ;
	for ( i = k + 1 ; i <= raiz -> tamanio ; i++ )
	{
		raiz -> dato[i - 1] = raiz -> dato[i] ;
		raiz -> hijo[i - 1] = raiz -> hijo[i] ;
	}
	raiz -> tamanio-- ;
}
void arbol :: copiar_exito ( nodo *raiz, int i )
{
	nodo *temp = raiz -> hijo[i] ;
 
	while ( temp -> hijo[0] )
		temp = temp -> hijo[0] ;
 
	raiz -> dato[i] = temp -> dato[1] ;
}
void arbol :: restaurar ( nodo *raiz, int i )
{
	if ( i == 0 )
	{
		if ( raiz -> hijo [1] -> tamanio > MIN )
			izquierda ( 1 ) ;
		else
			unir ( 1 ) ;
	}
	else
	{
		if ( i == raiz -> tamanio )
		{
			if ( raiz -> hijo[i - 1] -> tamanio > MIN )
				derecha ( i ) ;
			else
				unir ( i ) ;
		}
		else
		{
			if ( raiz -> hijo[i - 1] -> tamanio > MIN )
				derecha ( i ) ;
			else
			{
				if ( raiz -> hijo[i + 1] -> tamanio > MIN )
					izquierda ( i + 1 ) ;
				else
					unir ( i ) ;
			}
		}
	}
}
void arbol :: derecha ( int k )
{
	int i ;
	nodo *temp ;
 
	temp = raiz -> hijo[k] ;
 
	for ( i = temp -> tamanio ; i > 0 ; i-- )
	{
		temp -> dato[i + 1] = temp -> dato[i] ;
		temp -> hijo[i + 1] = temp -> hijo[i] ;
	}
 
	temp -> hijo[1] = temp -> hijo[0] ;
	temp -> tamanio++ ;
	temp -> dato[1] = raiz -> dato[k] ;
	temp = raiz -> hijo[k - 1] ;
	raiz -> dato[k] = temp -> dato[temp -> tamanio] ;
	raiz -> hijo[k] -> hijo [0] = temp -> hijo[temp -> tamanio] ;
	temp -> tamanio-- ;
}
void arbol :: izquierda ( int k )
{
	nodo *temp ;
 
	temp = raiz -> hijo[k - 1] ;
	temp -> tamanio++ ;
	temp -> dato[temp -> tamanio] = raiz -> dato[k] ;
	temp -> hijo[temp -> tamanio] = raiz -> hijo[k] -> hijo[0] ;
	temp = raiz -> hijo[k] ;
	raiz -> dato[k] = temp -> dato[1] ;
	temp -> hijo[0] = temp -> hijo[1] ;
	temp -> tamanio-- ;
	for ( int i = 1 ; i <= temp -> tamanio ; i++ )
	{
		temp -> dato[i] = temp -> dato[i + 1] ;
		temp -> hijo[i] = temp -> hijo[i + 1] ;
	}
}
void arbol :: unir ( int k )
{
	nodo *temp1, *temp2 ;
	temp1 = raiz -> hijo[k] ;
	temp2 = raiz -> hijo[k - 1] ;
	temp2 -> tamanio++ ;
	temp2 -> dato[temp2 -> tamanio] = raiz -> dato[k] ;
	temp2 -> hijo[temp2 -> tamanio] = raiz -> hijo[0] ;
	for ( int i = 1 ; i <= temp1 -> tamanio ; i++ )
	{
		temp2 -> tamanio++ ;
		temp2 -> dato[temp2 -> tamanio] = temp1 -> dato[i] ;
		temp2 -> hijo[temp2 -> tamanio] = temp1 -> hijo[i] ;
	}
	for ( int i = k ; i < raiz -> tamanio ; i++ )
	{
		raiz -> dato[i] = raiz -> dato[i + 1] ;
		raiz -> hijo[i] = raiz -> hijo[i + 1] ;
	}
	raiz -> tamanio-- ;
	delete temp1 ;
}
void arbol :: Show( )
{
	show ( raiz ) ;
}
void arbol :: show ( nodo *raiz )
{
	int i;
	if ( raiz != NULL )
	{		
		for ( i = 0 ; i < raiz -> tamanio ; i++ )
		{
			show ( raiz -> hijo[i] ) ;
			cout << raiz -> dato[i+1] << "\t" ;
		}
		show ( raiz -> hijo[i] ) ;
	}
}

void arbol :: borrarArbol ( nodo *raiz )
{
	int i;
	if ( raiz != NULL )
	{
		for ( i = 0 ; i < raiz -> tamanio ; i++ )
		{
			borrarArbol ( raiz -> hijo[i] ) ;
			delete ( raiz -> hijo[i] ) ;
		}
		borrarArbol ( raiz -> hijo[i] ) ;
		delete ( raiz -> hijo[i] ) ;
	}
}
 
arbol :: ~arbol( )
{
	borrarArbol ( raiz ) ;
}
 */
int main( )
{
	arbol T ;
	FILE *arch;
	 arch=fopen("datos1.dat","r+b");
	int vector[ ] = {6,2,8,3,222,45,410,325,38,95} ;
	int largo = sizeof ( vector ) / sizeof ( int ) ;
	
	for ( int i = 0 ; i < largo ; i++ ){	T.insertar ( vector[i], arch) ;	cout<<i<<endl;}//T.Show( ) ;
	
	imprimir_Archivo(1,arch);
	//~ T.borrar ( 22 ) ;
	//~ T.borrar ( 325 ) ;
	
	//~ cout <<endl<< "Despues del borrado: " << "325"<<endl ;
	//~ T.Show( ) ;
	fclose(arch);
	
	return 0;
}
