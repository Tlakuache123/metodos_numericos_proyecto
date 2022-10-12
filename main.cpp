#include "falsaPos.h"
#include "newton.h"
#include <iostream>

using namespace std;

void print_metodos(){
    cout << "1- Falsa Posicion" << endl;
    cout << "2- Newton" << endl;
    return;
}

int main (int argc, char *argv[])
{
    int option = 0;

    print_metodos();
    cout << "[!] Ingresa el metodo que quieres usar" << endl;
    cin >> option;

    option -= 1;
    switch (option) {
        case 0:
            falsa_posicion();
        case 1:
            newton();
    }
    return 0;
}
