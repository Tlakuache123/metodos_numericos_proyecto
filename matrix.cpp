#include "matrix.h"

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

Matrix::Matrix(int s, double m[][MATRIX_SIZE], double b_m[]){
    setSize(s);
    fillMatrix(m, b_m);
}

Matrix::Matrix(int s, double m[][MATRIX_SIZE]){
    setSize(s);
    fillMatrix(m);
}

Matrix::Matrix(int r, int c, double m[][MATRIX_SIZE], double b_m[]){
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
    cout << "Matrix" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << "[" << i + 1 << "][" << j + 1 <<"] => ";
            cin >> matrix[i][j];
        }
    }

    cout << "B_Matrix" << endl;
    for(int i = 0; i < rows; i++){
        cout << "B[" << i +1 << "] => ";
        cin >> b_matrix[i];
    }
}

void Matrix::fillMatrix(double m[][MATRIX_SIZE], double b_m[]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = m[i][j];
        }
    }

    for(int i = 0; i < rows; i++){
        b_matrix[i] = b_m[i];
    }
}

void Matrix::fillMatrix(double m[][MATRIX_SIZE]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = m[i][j];
        }
    }
}

// Funciones auxiliares

void Matrix::print_matrix(){
    for(int i = 0; i < rows; i++){
        if(i == del_row){
            i += 1;
        }

        cout << "| ";
        for(int j = 0; j < cols; j++){
            if(j == del_col){
                j += 1;
            }

            cout << matrix[i][j] << ", ";
        }
        cout << "| " << b_matrix[i];

        cout << " |" << endl;
    }
}

void Matrix::clean(){
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            matrix[i][j] = 0;
        }
    }
}

// Operaciones de matriz

void Matrix::sum(int row_to_sum, int row){
    for(int j = 0; j < cols; j++){
        matrix[row_to_sum][j] += matrix[row][j];
    }

    b_matrix[row_to_sum] *= b_matrix[row];
}

void Matrix::sum(int row_to_sum, int row, double escalar){
    for(int j = 0; j < cols; j++){
        matrix[row_to_sum][j] += ( matrix[row][j] * escalar );
    }

    b_matrix[row_to_sum] *= b_matrix[row];
}

void Matrix::product(int row_to_prd, double num){
    for(int j = 0; j < cols; j++){
        matrix[row_to_prd][j] *= num;
    }

    b_matrix[row_to_prd] *= num;
}

// Operaciones avanzadas
Matrix Matrix::copy(){
    return Matrix(rows, cols, matrix, b_matrix);
}

Matrix Matrix::smaller_copy(int row, int col){
    double proto_m[MATRIX_SIZE][MATRIX_SIZE];
    for(int i = 0; i < rect_size; i++){
        for(int j = 0; j < rect_size; j++){
            if(i == row || j == col){
                continue;
            }
            proto_m[i][j] = matrix[i][j];
        }
    }
    Matrix pm(rect_size - 1, proto_m);
    pm.del_row = row;
    pm.del_col = col;
    return Matrix(rect_size - 1, proto_m);
}

double Matrix::det(){
    double d = 0;
    if(rect_size == 2){
        d = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }else{

    }

    return d;
}
