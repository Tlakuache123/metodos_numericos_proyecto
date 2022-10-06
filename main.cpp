#include "falsaPos.h"
#include <iostream>

using namespace std;

void print_metodos(){
    cout << "1- Falsa Posicion" << endl;
    return;
}

int main (int argc, char *argv[])
{
    int option = 0;

    print_metodos();
    cout << "[!] Ingresa el metodo que quieres usar" << endl;
    cin >> option;

    switch (option) {
        case 0:
            falsa_posicion();
    }
    return 0;
}
