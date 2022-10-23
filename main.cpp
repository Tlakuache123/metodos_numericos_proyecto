#include <iostream>

using namespace std;

#include "falsaPos.h"
#include "newton.h"
#include "matrix.h"
#include "system_matrix.h"

void print_metodos(){
    cout << "1- Falsa Posicion" << endl;
    cout << "2- Newton" << endl;
    return;
}

int main (int argc, char *argv[])
{
    vector<vector<double>> m = {
        {4, 1, 1, 2, 3},
        {4, 2, 3, 1, 9},
        {5, 3, 3, -6, 2},
        {5, 4, -4, 7, 8},
        {1, 5, 2, 3, 4}
    };

    vector<vector<double>> b = {
        {1},
        {3},
        {5},
        {8},
        {8}
    };
    SystemMatrix sys_m(m, b );

    sys_m.gauss_partitions();
    return 0;
}
