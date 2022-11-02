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
    vector<vector<double>> mx = {
        {4, 1, 1, 1, 4},
        {9, 2, 3, 2, 5},
        {1, -6, 3, 1, 0},
        {2, 4, -4, 2, 3},
        {3, 2, 5, 3, 1}
    };
    vector<vector<double>> mb = {
        {5},
        {1},
        {1},
        {3},
        {4}
    };

    SystemMatrix new_system (mx, mb);
    cout << "Gauss particionado" << endl;
    new_system.gauss_partitions();
    cout << "Inversion particionado" << endl;
    new_system.inversion_partitions();
    return 0;
}
