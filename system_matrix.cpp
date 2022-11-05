#include "system_matrix.h"
#include <vector>
#include <cmath>

// Constructors

SystemMatrix::SystemMatrix(){
    complete_x = Matrix();
    complete_b = Matrix();
    create_partitions();
}

SystemMatrix::SystemMatrix(vector<vector<double>> cmp_x,vector<vector<double>> cmp_b){
    complete_x = Matrix(cmp_x);
    complete_b = Matrix(cmp_b);
    create_partitions();
}

void SystemMatrix::create_partitions(){
    int mat_size = complete_x.matrix.size();
    int sep_index = floor(mat_size / 2.0);

    cmp_x_part.push_back( extract_partition(0, 0, sep_index, sep_index) );
    cmp_x_part.push_back( extract_partition(0, sep_index, sep_index, mat_size) );
    cmp_x_part.push_back( extract_partition(sep_index, 0, mat_size, sep_index) );
    cmp_x_part.push_back( extract_partition(sep_index, sep_index, mat_size, mat_size) );

    cmp_b_part.push_back( b_extract_partition(0, sep_index) );
    cmp_b_part.push_back( b_extract_partition(sep_index, mat_size));
}

Matrix SystemMatrix::b_extract_partition(int init, int final){
    vector<vector<double>> sub_mat;
    int count_row = 0;

    for(int i = init; i < final; i++){
        sub_mat.push_back(vector<double> ());
        sub_mat.at(count_row).push_back(complete_b.matrix.at(i).at(0));
        count_row += 1;
    }

    return Matrix (sub_mat);
}

Matrix SystemMatrix::extract_partition(int row_init, int col_init, int row_final, int col_final){
    vector<vector<double>> sub_mat;
    int count_row = 0;

    for(int i = row_init; i < row_final; i++){
        sub_mat.push_back( vector<double> () );
        for(int j = col_init; j < col_final; j++){
            sub_mat.at(count_row).push_back(complete_x.matrix.at(i).at(j));
        }

        count_row += 1;
    }

    return Matrix(sub_mat);
}


void SystemMatrix::gauss_partitions(){
    // Diagonales cuadradas [0] && [3]
    // complete_x_partitions = [0] [1] [2] [3]
    // complete_b_partitions = [0] [1]
    SystemMatrix aux_sys = *this;

    aux_sys.cmp_x_part.at(1) = aux_sys.cmp_x_part.at(0).invers() * aux_sys.cmp_x_part.at(1);
    aux_sys.cmp_b_part.at(0) = aux_sys.cmp_x_part.at(0).invers() * aux_sys.cmp_b_part.at(0);
    aux_sys.cmp_x_part.at(3) = aux_sys.cmp_x_part.at(3) - (aux_sys.cmp_x_part.at(2) * aux_sys.cmp_x_part.at(1));
    aux_sys.cmp_b_part.at(1) = aux_sys.cmp_b_part.at(1) - (aux_sys.cmp_x_part.at(2) * aux_sys.cmp_b_part.at(0));

    aux_sys.cmp_b_part.at(1) = aux_sys.cmp_x_part.at(3).invers() * aux_sys.cmp_b_part.at(1);
    aux_sys.cmp_b_part.at(0) = aux_sys.cmp_b_part.at(0) - (aux_sys.cmp_x_part.at(1) * aux_sys.cmp_b_part.at(1));

    cout << "SOLUCION :" << endl;
    cout << aux_sys.cmp_b_part.at(0);
    cout << aux_sys.cmp_b_part.at(1);
}

void SystemMatrix::inversion_partitions(){
    // Diagonales cuadradas [0] && [3]
    // complete_x_partitions = [0] [1] [2] [3]
    // complete_b_partitions = [0] [1]

    Matrix C = cmp_x_part[0] - cmp_x_part[1] * ( cmp_x_part[3].invers() * cmp_x_part[2] );
    Matrix D = cmp_x_part[1] * cmp_x_part[3].invers();
    Matrix E = cmp_x_part[3].invers() * cmp_x_part[2];
    Matrix F = cmp_x_part[3].invers() + E * ( C.invers() * D );

    Matrix x1 = C.invers() * ( cmp_b_part.at(0) - D * cmp_b_part.at(1) );
    Matrix x2 = (E * -1) * ( C.invers() * cmp_b_part.at(0) ) + F * cmp_b_part.at(1);

    cout << "SOLUCION: " << endl;
    cout << x1;
    cout << x2;

}

void SystemMatrix::intercambio(){
    vector<int> from_change;
    vector<int> to_change;

    SystemMatrix aux_sys = *this;
    int sys_size = aux_sys.complete_x.matrix.size();
    bool aprox_flag = false;

    for(int k = 0; k < sys_size; k++){
        // Checar si el pivote es 0 -> Cambio de rows

        double pivot = aux_sys.complete_x.matrix.at(k).at(k);
        if(pivot == 0){
            pivot = 0.00001;
            aprox_flag = true;
        }

        // Toda la matriz menos row/col pivote
        for(int i = 0; i < sys_size; i++){
            for(int j = 0; j < sys_size; j++){
                if(i == k || j == k){
                    continue;
                }

                double new_num = aux_sys.complete_x.matrix.at(i).at(j);
                double row_pivot = aux_sys.complete_x.matrix.at(i).at(k);
                double col_pivot = aux_sys.complete_x.matrix.at(k).at(j);

                new_num = new_num - ((row_pivot * col_pivot) / pivot);
                aux_sys.complete_x.matrix.at(i).at(j) = new_num;
            }
        }

        // Col pivote
        for(int i = 0; i < sys_size; i++){
            aux_sys.complete_x.matrix.at(i).at(k) = aux_sys.complete_x.matrix.at(i).at(k) / pivot;
        }

        // Row pivote
        for(int i = 0; i < sys_size; i++){
            aux_sys.complete_x.matrix.at(k).at(i) = aux_sys.complete_x.matrix.at(k).at(i) / -pivot;
        }

        aux_sys.complete_x.matrix.at(k).at(k) = 1 / pivot;
    }

    // Regresar original matrix x
    for(int i = 0; i < from_change.size(); i++){
        aux_sys.complete_x.switch_row(from_change.at(i), to_change.at(i));
    }

    // SOLUCION
    Matrix sol_matrix = aux_sys.complete_x * aux_sys.complete_b;
    cout << "Solucion" << endl;
    if(aprox_flag){
        cout << "APROXIMADA" << endl;
    }
    cout << sol_matrix << endl;
}

void SystemMatrix::printPartitions(){
    cout << "[X] particiones: " << endl;
    for(auto &mat : cmp_x_part){
        cout << mat << endl;
    }
    cout << "[B] particiones: " << endl;
    for(auto &mat : cmp_b_part){
        cout << mat << endl;
    }
}
