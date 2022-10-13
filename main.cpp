#include <iostream>

using namespace std;

#include "falsaPos.h"
#include "newton.h"
#include "matrix.h"

void print_metodos(){
    cout << "1- Falsa Posicion" << endl;
    cout << "2- Newton" << endl;
    return;
}

int main (int argc, char *argv[])
{
    int size = 2;
    double m[2][10] = {
        {3, 3},
        {6, 3},
    };
    double bm[2] = {4, 5};

    Matrix x(size, m, bm);
    x.print_matrix();
    double d = x.det();
    cout << "Determinante: " << d << endl;
    Matrix sx = x.smaller_copy(-1, -1);
    sx.print_matrix();

    return 0;
}
