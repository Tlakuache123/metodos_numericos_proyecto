#include "matrix.h"
#include <cmath>
#include <vector>


void print_row(vector<double> row){
    cout << "|";
    for(auto &i : row){
        cout << i << " ";
    }
    cout << "|" << endl;
}

// Constructor

Matrix::Matrix(){
    setSize();
    fillMatrix();
}

Matrix::Matrix(int s){
    setSize(s);
    fillMatrix();
}

Matrix::Matrix(int r, int c){
    setSize(r, c);
    fillMatrix();
}

Matrix::Matrix(int s, vector<vector<double>> m, vector<double> b_m){
    setSize(s);
    fillMatrix(m, b_m);
}

Matrix::Matrix(int s, vector<vector<double>> m){
    setSize(s);
    fillMatrix(m);
}

Matrix::Matrix(int r, int c, vector<vector<double>> m, vector<double> b_m){
    setSize(r, c);
    fillMatrix(m, b_m);
}

// Definiendo tamanio de la matriz

void Matrix::setSize(){
    int size = 0;
    cout << "Ingresa el tamanio de la matriz" << endl;
    cin >> size;

    rows = size;
    cols = size;
    rect_size = size;
}

void Matrix::setSize(int s){
    rows = s;
    cols = s;
    rect_size = s;
}

void Matrix::setSize(int r, int c){
    rows = r;
    cols = c;

    if(rows == cols){
        rect_size = rows;
    }
}

// Llenado de la matriz

void Matrix::fillMatrix(){
    double new_value = 0;

    cout << "Matrix" << endl;
    for(int i = 0; i < rows; i++){
        matrix.push_back( vector<double>() );

        for(int j = 0; j < cols; j++){
            cout << "[" << i + 1 << "][" << j + 1 <<"] => ";
            cin >> new_value;
            matrix.at(i).push_back(new_value);
        }
    }

    cout << "B_Matrix" << endl;

    for(int i = 0; i < rows; i++){
        cout << "B[" << i +1 << "] => ";
        cin >> new_value;
        b_matrix.push_back(new_value);
    }
}

void Matrix::fillMatrix(vector<vector<double>> m, vector<double> b_m){
    matrix = m;
    b_matrix = b_m;
}

void Matrix::fillMatrix(vector<vector<double>> m){
    matrix = m;
}

// Funciones auxiliares

void Matrix::print_matrix(){
    for(int i = 0; i < rows; i++){
        cout << "| ";
        for(int j = 0; j < cols; j++){
            cout << matrix.at(i).at(j) << ", ";
        }
        if(b_flag){
            cout << "| " << b_matrix.at(i);
        }

        cout << " |" << endl;
    }
}

void Matrix::print_matrix(vector<vector<double>> m){
    for(int i = 0; i < m.size(); i++){
        cout << "|\t";
        for(int j = 0; j < m.at(i).size(); j++){
            cout << m.at(i).at(j) << "\t";
        }
        cout << "|" << endl;
    }
}

void Matrix::clean(){
    matrix.clear();
    b_matrix.clear();
}

// Operaciones de matriz

void Matrix::sum(int row_to_sum, int row){
    for(int j = 0; j < cols; j++){
        matrix.at(row_to_sum).at(j) += matrix.at(row).at(j);
    }

    b_matrix.at(row_to_sum) += b_matrix.at(row);
}

void Matrix::sum(int row_to_sum, int row, double escalar){
    for(int j = 0; j < cols; j++){
        matrix.at(row_to_sum).at(j) += ( matrix.at(row).at(j) * escalar );
    }

    b_matrix.at(row_to_sum) += (b_matrix.at(row) * escalar);
}

void Matrix::product(int row_to_prd, double num){
    for(int j = 0; j < cols; j++){
        matrix.at(row_to_prd).at(j) *= num;
    }

    b_matrix.at(row_to_prd) *= num;
}

// Operaciones avanzadas
Matrix Matrix::copy(){
    return Matrix(rows, cols, matrix, b_matrix);
}

Matrix Matrix::smaller_copy(int row, int col){
    vector<vector<double>> proto_m = matrix;

    for(int i = 0; i < proto_m.size(); i++){
        proto_m.at(i).erase(proto_m.at(i).begin() + col);
    }
    proto_m.erase(proto_m.begin() + row);

    Matrix pm(rect_size - 1, proto_m);
    return Matrix(rect_size - 1, proto_m);
}

vector<vector<double>> Matrix::transp(){
    vector<vector<double>> aux_m (cols, vector<double> (rows));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            aux_m.at(j).at(i) = matrix.at(i).at(j);
        }
    }

    print_matrix(aux_m);
    return aux_m;
}

double Matrix::det(){
    double d = 0;
    int matrix_sign = -1;

    if(rect_size == 2){
        d = (matrix.at(0).at(0) * matrix.at(1).at(1)) - (matrix.at(0).at(1) * matrix.at(1).at(0));
    }else{
        for(int i = 0; i < rect_size; i++){
            d = d + pow(matrix_sign, i) * matrix.at(0).at(i) * smaller_copy(0, i).det();
        }
    }

    return d;
}

// Operaciones finales

vector<double> Matrix::gauss_jordan(){
    Matrix full_system (rect_size, matrix, b_matrix);

    int i, j = 0;
    
    for(int k = 0; k < full_system.matrix.size(); k++){
        double divisor = 1 / full_system.matrix.at(k).at(k);
        // Creating pivot
        full_system.product(k, divisor);

        for(i = 0; i < full_system.matrix.size(); i++){
            if(i == k){
                continue;
            }
            // Creating line of zeros
            double sub_escalar = full_system.matrix.at(i).at(k);
            full_system.sum(i, k, -sub_escalar);

        }
    }

    full_system.print_matrix();

    return full_system.b_matrix;
}



