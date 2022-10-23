#include "matrix.h"
#include <vector>

// Constructor

Matrix::Matrix(){
    fillMatrix();
}

Matrix::Matrix(vector<vector<double>> m){
    matrix = m;
    rows = matrix.size();
    cols = matrix.at(0).size();
}

// Llenado de la matriz

void Matrix::fillMatrix(){
    cout << "Numero de filas (rows): ";
    cin >> rows;
    cout << "Numero de columnas (cols): ";
    cin >> cols;

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
}

// Operaciones de matriz
ostream& operator<<(ostream &out, const Matrix& mt){
    for(auto row : mt.matrix){
        out << "|\t";
        for(auto col : row){
            out << col << "\t";
        }
        out << "|\n";
    }
    return out;
}

Matrix Matrix::operator+(const Matrix& mt2){
    vector<vector<double>> f_mt (matrix.size(), vector<double> (matrix.at(0).size() ));
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.at(0).size(); j++){
            f_mt.at(i).at(j) = matrix.at(i).at(j) + mt2.matrix.at(i).at(j);
        }
    }

    return Matrix (f_mt);
}


Matrix Matrix::operator-(const Matrix& mt2){
    vector<vector<double>> f_mt (matrix.size(), vector<double> (matrix.at(0).size() ));
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.at(0).size(); j++){
            f_mt.at(i).at(j) = matrix.at(i).at(j) - mt2.matrix.at(i).at(j);
        }
    }

    return Matrix (f_mt);
}

Matrix Matrix::operator*(const Matrix &mt2){
    int n_rows_sz = matrix.size();
    int n_cols_sz = mt2.matrix.at(0).size();

    vector<vector<double>> f_mt (n_rows_sz, vector<double> (n_cols_sz) );

    for(int i = 0; i < n_rows_sz; i++){

        for(int j = 0; j < n_cols_sz; j++){
            for(int k = 0; k < mt2.matrix.size(); k++){

                f_mt.at(i).at(j) += matrix.at(i).at(k) * mt2.matrix.at(k).at(j);
            }
        }
    }

    return Matrix(f_mt);
}

void Matrix::set_row(int row_index, vector<double> new_row){
    if(matrix.at(row_index).size() == new_row.size()){
        matrix.at(row_index) = new_row;
    }
}

vector<double> Matrix::sum_row(int row_to_sum, int row){
    vector<double> row_sum = matrix.at(row_to_sum);

    for(int j = 0; j < cols; j++){
        row_sum.at(j) += matrix.at(row).at(j);
    }

    return row_sum;
}

vector<double> Matrix::sum_row(int row_to_sum, int row, double escalar){
    vector<double> row_sum = matrix.at(row_to_sum);

    for(int j = 0; j < cols; j++){
        row_sum.at(j) += ( matrix.at(row).at(j) * escalar );
    }

    return row_sum;
}

vector<double> Matrix::product_row(int row_to_prd, double num){
    vector<double> row_prd = matrix.at(row_to_prd);

    for(int j = 0; j < cols; j++){
        row_prd.at(j) *= num;
    }

    return row_prd;
}

// Operaciones avanzadas
Matrix Matrix::get_ident(){
    vector<vector<double>> idn (rows, vector<double> (cols, 0));
    
    for(int i = 0; i < idn.size(); i++){
        for(int j = 0; j < idn.at(0).size(); j++){
            if(i == j){
                idn.at(i).at(j) = 1;
            }
        }
    }

    return Matrix (idn);
}

Matrix Matrix::smaller_copy(int row, int col){
    vector<vector<double>> proto_m = matrix;

    for(int i = 0; i < proto_m.size(); i++){
        proto_m.at(i).erase(proto_m.at(i).begin() + col);
    }
    proto_m.erase(proto_m.begin() + row);

    return Matrix (proto_m);
}

Matrix Matrix::transp(){
    vector<vector<double>> aux_m (cols, vector<double> (rows));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            aux_m.at(j).at(i) = matrix.at(i).at(j);
        }
    }

    return Matrix (aux_m);
}

double Matrix::det(){
    double d = 0;
    int matrix_sign = -1;

    if(rows != cols){
        return -1;
    }

    if(rows == 2 && cols == 2){
        d = (matrix.at(0).at(0) * matrix.at(1).at(1)) - (matrix.at(0).at(1) * matrix.at(1).at(0));
    }else{
        for(int i = 0; i < rows; i++){
            d = d + pow(matrix_sign, i) * matrix.at(0).at(i) * smaller_copy(0, i).det();
        }
    }

    return d;
}

Matrix Matrix::invers(){
    Matrix m_inv(get_ident());
    Matrix m_copy (matrix);

    for(int k = 0; k < m_copy.matrix.size(); k++){
        double divider = 1 / m_copy.matrix.at(k).at(k);

        m_inv.set_row(k, m_inv.product_row(k, divider));
        m_copy.set_row(k, m_copy.product_row(k, divider)) ;

        for(int i = 0; i < m_copy.matrix.size(); i++){
            if(i == k){
                continue;
            }
            m_inv.set_row(i, m_inv.sum_row(i, k, -m_copy.matrix.at(i).at(k)) );
            m_copy.set_row(i, m_copy.sum_row(i, k, -m_copy.matrix.at(i).at(k)) );
        }
    }

    return m_inv;
}
