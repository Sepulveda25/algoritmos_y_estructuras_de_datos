#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int *direc;
    int num;
    
    num=25;
    
    direc=&num;
    
    cout<<"La variable num tiene alamcenado el numero: "<<num<<"\n\n";
    cout<<"La variable direc contiene la direccion de la variable num y es: "
    <<direc<<"\n\n";
    
    cout<<"Usando el operador * en la variable direc (*direc) puedo ver lo \n"
    <<"que contiene la variable a la que apunta la direccion, en este caso\n"
    <<"apunta a la variable num que es: "<<*direc<<"\n\n";  
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
