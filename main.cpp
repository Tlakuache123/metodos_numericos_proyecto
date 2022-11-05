#include <iostream>

using namespace std;

#include "biseccion.h"
#include "falsaPos.h"
#include "newton.h"
#include "matrix.h"
#include "secante.h"
#include "system_matrix.h"

void print_metodos(){
    cout << "1- Falsa Posicion" << endl;
    cout << "2- Newton" << endl;
    return;
}

int main (int argc, char *argv[])
{
    vector<vector<double>> x_m ={
        {5, 8, 0, -3, -3},
        {0, 4, -3, 1, 3},
        {3, 2, 1, -1, -5},
        {0, 5, -4, 0, -4},
        {0, -3, 0, 8, -1}
    };

    vector<vector<double>> b_m = {
        {4},
        {-6.2832},
        {1.41421},
        {11},
        {8}
    };

    SystemMatrix system(x_m, b_m);

    system.gauss_partitions();
    system.inversion_partitions();
    system.intercambio();

    return 0;
}
