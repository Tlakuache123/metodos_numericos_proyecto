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
    int size = 3;
    vector<vector<double>> m = {
        {2, -1, 1},
        {3, 1, -2},
        {-1, 2, 5}
    };
    vector<double> bm = {2, 9, -5};

    Matrix x(size, m, bm);
    x.print_matrix();
    cout << "Guass-Jordan" << endl;
    x.gauss_jordan();

    cout << "Determinante: " << x.det() << endl;
    return 0;
}
