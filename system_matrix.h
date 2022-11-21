#ifndef SYSTEMMATRIX_H
#define SYSTEMMATRIX_H

#include "matrix.h"

class SystemMatrix {
public:
  // Variables
  Matrix complete_x = vector<vector<double>>{{}};
  Matrix complete_b = vector<vector<double>>{{}};

  vector<Matrix> cmp_x_part;
  vector<Matrix> cmp_b_part;

  // Methods
  void printPartitions();

  // Constructors
  SystemMatrix();
  SystemMatrix(vector<vector<double>> cmp_x, vector<vector<double>> cmp_b);
  void gauss_partitions();
  void inversion_partitions();
  void intercambio();
  void jacobi();

private:
  int complete_rows;
  int complete_cols;

  void create_partitions();
  bool check_iteration_error(vector<double> vec1, vector<double> vec2,
                             double error);
  Matrix extract_partition(int row_init, int col_init, int row_final,
                           int col_final);
  Matrix b_extract_partition(int init, int final);
};

#endif // SYSTEMMATRIX_H
