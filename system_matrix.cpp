#include "system_matrix.h"
#include <vector>
#include <cmath>

// Constructors

SystemMatrix::SystemMatrix(){
    complete_x = Matrix();
    complete_b = Matrix();
}

SystemMatrix::SystemMatrix(vector<vector<double>> cmp_x,vector<vector<double>> cmp_b){
    complete_x = Matrix(cmp_x);
    complete_b = Matrix(cmp_b);
    cout << complete_x << endl;
    create_partitions();
}

void SystemMatrix::create_partitions(){
    int mat_size = complete_x.matrix.size();
    int sep_index = floor(mat_size / 2.0);

    complete_x_partitions.push_back( extract_partition(0, 0, sep_index, sep_index) );
    complete_x_partitions.push_back( extract_partition(0, sep_index, sep_index, mat_size) );
    complete_x_partitions.push_back( extract_partition(sep_index, 0, mat_size, sep_index) );
    complete_x_partitions.push_back( extract_partition(sep_index, sep_index, mat_size, mat_size) );

    complete_b_partitions.push_back( b_extract_partition(0, sep_index) );
    complete_b_partitions.push_back( b_extract_partition(sep_index, mat_size));
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

    complete_x_partitions.at(1) = complete_x_partitions.at(0).invers() * complete_x_partitions.at(1);
    complete_b_partitions.at(0) = complete_x_partitions.at(0).invers() * complete_b_partitions.at(0);
    complete_x_partitions.at(3) = complete_x_partitions.at(3) - (complete_x_partitions.at(2) * complete_x_partitions.at(1));
    complete_b_partitions.at(1) = complete_b_partitions.at(1) - (complete_x_partitions.at(2) * complete_b_partitions.at(0));

    complete_b_partitions.at(1) = complete_x_partitions.at(3).invers() * complete_b_partitions.at(1);
    complete_b_partitions.at(0) = complete_b_partitions.at(0) - (complete_x_partitions.at(1) * complete_b_partitions.at(1));

    cout << "SOLUCION :" << endl;
    cout << complete_b_partitions.at(0);
    cout << complete_b_partitions.at(1);
}

void SystemMatrix::inversion_partitions(){
    // Diagonales cuadradas [0] && [3]
    // complete_x_partitions = [0] [1] [2] [3]
    // complete_b_partitions = [0] [1]

    Matrix C = complete_x_partitions[0] - complete_x_partitions[1] * ( complete_x_partitions[3].invers() * complete_x_partitions[2] );
    Matrix D = complete_x_partitions[1] * complete_x_partitions[3].invers();
    Matrix E = complete_x_partitions[3].invers() * complete_x_partitions[2];
    Matrix F = complete_x_partitions[3].invers() + E * ( C.invers() * D );

    Matrix x1 = C.invers() * ( complete_b_partitions.at(0) - D * complete_b_partitions.at(1) );
    Matrix x2 = (E * -1) * ( C.invers() * complete_b_partitions.at(0) ) + F * complete_b_partitions.at(1);

    cout << "SOLUCION: " << endl;
    cout << x1;
    cout << x2;

}

void SystemMatrix::printPartitions(){
    cout << "[X] particiones: " << endl;
    for(auto &mat : complete_x_partitions){
        cout << mat << endl;
    }
    cout << "[B] particiones: " << endl;
    for(auto &mat : complete_b_partitions){
        cout << mat << endl;
    }
}
