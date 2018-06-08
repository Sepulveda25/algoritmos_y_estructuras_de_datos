#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char pal[10]="hola pepe";
    char *direpal;
    int i;
    
    direpal=&pal[0];
    
    for (i=0;i<10;i++)//muestra el caracter y su posicion en la varible pal
    {
        cout<<i;
        cout<<*(direpal+i)<<"\n";
    }
    cout<<"\n\n";
    system("PAUSE");
    return EXIT_SUCCESS;
}
