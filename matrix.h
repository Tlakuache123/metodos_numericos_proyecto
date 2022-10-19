#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <ostream>
#include <vector>
#include <cmath>

using namespace std;

class Matrix {
    public:
        int rows;
        int cols;
        vector<vector <double>> matrix;

    // Basic Operations
        void set_row(int row_index, vector<double> new_row);

        vector<double> sum_row(int row_to_sum, int row);
        vector<double> sum_row(int row_to_sum, int row, double escalar);
        vector<double> product_row(int row_to_prd, double num);

        friend ostream& operator<<(ostream &out, const Matrix& mt);
        Matrix operator+(Matrix const &mt2);
        Matrix operator*(Matrix const &mt2);

    // Advance Operations
        Matrix transp();
        Matrix smaller_copy(int row, int col);
        Matrix invers();
        Matrix get_ident();
        double det();

    // Constructors
        Matrix();
        Matrix(vector<vector<double>> m);
    private:
        void fillMatrix();
};

#endif // MATRIX_H
