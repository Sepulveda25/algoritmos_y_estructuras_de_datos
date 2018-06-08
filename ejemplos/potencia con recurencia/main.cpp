#include <cstdlib>
#include <iostream>

using namespace std;

int pot(int x ,int y)
{
    int t;
    if (y==0){return 1;}
    else{t=x*pot(x,y-1);
        return t;}
}


int main(int argc, char *argv[])
{
    cout<<pot(2,5)<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
