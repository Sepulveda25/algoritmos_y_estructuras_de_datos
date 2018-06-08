#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char pal[10]="hola pepe";
    char *direpal;
    direpal=(char *)malloc(sizeof(char)*20);
    direpal=&pal[0];
        
    cout<<"La variable pal contiene: "<<pal<<"\n\n";
    cout<<"La variable direpal contiene la direccion de la variable pal y es: "
    <<direpal<<"\n\n";
    cout<<"Si uso el operador * para la variable direpal (*dirapal) tengo: "
    <<*direpal<<"\n\n";
    
    free (direpal);
    system("PAUSE");
    return EXIT_SUCCESS;
}
