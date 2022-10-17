#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MATRIX_SIZE = 10;


class Matrix {
    public:
        int rows;
        int cols;
        int del_row = -1;
        int del_col = -1;
        int rect_size = 0;
        bool b_flag = true;
        vector<vector <double>> matrix;
        vector<double> b_matrix;


        void print_matrix();
        void print_matrix(vector<vector<double>> m);
        void clean();
    // Basic Operations
        void sum(int row_to_sum, int row);
        void sum(int row_to_sum, int row, double escalar);
        void product(int row_to_prd, double num);

    // Advance Operations
        vector<vector<double>> transp();
        Matrix copy();
        Matrix smaller_copy(int row, int col);
        double det();

    // Resolve Operations
        vector<double> gauss_jordan();

    // Constructors
        Matrix();
        Matrix(int s);
        Matrix(int r, int c);
        Matrix(int s, vector<vector<double>> m, vector<double> b_m);
        Matrix(int s, vector<vector<double>> m);
        Matrix(int r, int c, vector<vector<double>> , vector<double> b_m);
    private:
        void setSize();
        void setSize(int s);
        void setSize(int r, int c);
        void fillMatrix();
        void fillMatrix(vector<vector<double>> m, vector<double> b_m);
        void fillMatrix(vector<vector<double>> m);
};

#endif // MATRIX_H
