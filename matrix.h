#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

const int MATRIX_SIZE = 10;

class Matrix {
    public:
        int rows;
        int cols;
        int del_row = -1;
        int del_col = -1;
        int rect_size = 0;
        double matrix[MATRIX_SIZE][MATRIX_SIZE];
        double b_matrix[MATRIX_SIZE];


        void print_matrix();
        void clean();
    // Basic Operations
        void sum(int row_to_sum, int row);
        void sum(int row_to_sum, int row, double escalar);
        void product(int row_to_prd, double num);

    // Advance Operations
        Matrix copy();
        Matrix smaller_copy(int row, int col);
        double det();

    // Constructors
        Matrix();
        Matrix(int s);
        Matrix(int r, int c);
        //Matrix(int s, double **m, double *b_m);
        Matrix(int s, double m[][MATRIX_SIZE], double b_m[]);
        Matrix(int s, double m[][MATRIX_SIZE]);
        Matrix(int r, int c, double m[][MATRIX_SIZE], double b_m[]);
    private:
        void setSize();
        void setSize(int s);
        void setSize(int r, int c);
        void fillMatrix();
        //void fillMatrix(double **m, double *b_m);
        void fillMatrix(double m[][MATRIX_SIZE], double b_m[]);
        void fillMatrix(double m[][MATRIX_SIZE]);
};

#endif // MATRIX_H
