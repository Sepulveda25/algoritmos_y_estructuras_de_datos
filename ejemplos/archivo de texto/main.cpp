#include <cstdlib>
#include <iostream>
#include <fstream.h>
#include <string>

using namespace std;


int main(int argc, char *argv[])
{
    
    char linea[10];
    ifstream archivo;
    archivo.open("d:\\datos.txt");

    if (archivo.fail()) {
    cerr << "No pudo leerse el archivo";
    exit(1);   // parar
    }
    
    while (!archivo.eof() )
    {
      archivo.getline(linea,sizeof(linea));
      cout << linea << endl;
    }

    archivo.close();
    system("PAUSE");
    return EXIT_SUCCESS;
}
