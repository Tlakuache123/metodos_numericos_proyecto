#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

class Matrix {
public:
  int rows;
  int cols;
  vector<vector<double>> matrix;

  // Basic Operations
  void set_row(int row_index, vector<double> new_row);

  vector<double> sum_row(int row_to_sum, int row);
  vector<double> sum_row(int row_to_sum, int row, double escalar);
  vector<double> product_row(int row_to_prd, double num);

  void switch_row(int row1, int row2);

  friend ostream &operator<<(ostream &out, const Matrix &mt);
  Matrix operator+(Matrix const &mt2);
  Matrix operator-(Matrix const &mt2);
  Matrix operator*(Matrix const &mt2);
  Matrix operator*(const double &escalar);
  Matrix operator/(Matrix const &mt2);
  Matrix operator/(const double &escalar);
  bool operator==(Matrix const &mt2);

  // Advance Operations
  Matrix transp();
  Matrix smaller_copy(int row, int col);
  Matrix invers();
  Matrix get_ident();
  Matrix adjunta();
  double det();
  bool symmetrical();
  bool diagonal_dominante();
  bool definida_positiva();
  bool tridiagonal();

  // Constructors
  Matrix();
  Matrix(int rows, int cols);
  Matrix(vector<vector<double>> m);

private:
  void fillMatrix();
  void fillMatrix(int rows, int cols);
};

#endif // MATRIX_H
