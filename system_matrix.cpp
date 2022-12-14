#include "system_matrix.h"
#include "matrix.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
// Constructors

SystemMatrix::SystemMatrix() {
  complete_x = Matrix();
  cout << "B Matrix" << endl;
  complete_b = Matrix(complete_x.rows, 1);
  create_partitions();
}

SystemMatrix::SystemMatrix(vector<vector<double>> cmp_x,
                           vector<vector<double>> cmp_b) {
  complete_x = Matrix(cmp_x);
  complete_b = Matrix(cmp_b);
  create_partitions();
}

void SystemMatrix::create_partitions() {
  int mat_size = complete_x.matrix.size();
  int sep_index = floor(mat_size / 2.0);

  cmp_x_part.push_back(extract_partition(0, 0, sep_index, sep_index));
  cmp_x_part.push_back(extract_partition(0, sep_index, sep_index, mat_size));
  cmp_x_part.push_back(extract_partition(sep_index, 0, mat_size, sep_index));
  cmp_x_part.push_back(
      extract_partition(sep_index, sep_index, mat_size, mat_size));

  cmp_b_part.push_back(b_extract_partition(0, sep_index));
  cmp_b_part.push_back(b_extract_partition(sep_index, mat_size));
}

Matrix SystemMatrix::b_extract_partition(int init, int final) {
  vector<vector<double>> sub_mat;
  int count_row = 0;

  for (int i = init; i < final; i++) {
    sub_mat.push_back(vector<double>());
    sub_mat.at(count_row).push_back(complete_b.matrix.at(i).at(0));
    count_row += 1;
  }

  return Matrix(sub_mat);
}

Matrix SystemMatrix::extract_partition(int row_init, int col_init,
                                       int row_final, int col_final) {
  vector<vector<double>> sub_mat;
  int count_row = 0;

  for (int i = row_init; i < row_final; i++) {
    sub_mat.push_back(vector<double>());
    for (int j = col_init; j < col_final; j++) {
      sub_mat.at(count_row).push_back(complete_x.matrix.at(i).at(j));
    }

    count_row += 1;
  }

  return Matrix(sub_mat);
}

void SystemMatrix::printPartitions() {
  cout << "[X] particiones: " << endl;
  for (auto &mat : cmp_x_part) {
    cout << mat << endl;
  }
  cout << "[B] particiones: " << endl;
  for (auto &mat : cmp_b_part) {
    cout << mat << endl;
  }
}

void SystemMatrix::gauss_partitions() {
  // Diagonales cuadradas [0] && [3]
  // complete_x_partitions = [0] [1] [2] [3]
  // complete_b_partitions = [0] [1]

  if (complete_x.det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Determinante igual a cero" << endl;
    return;
  }

  if (cmp_x_part[0].det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] No existe inversa en A11" << endl;
    return;
  }

  SystemMatrix aux_sys = *this;

  aux_sys.cmp_x_part.at(1) =
      aux_sys.cmp_x_part.at(0).invers() * aux_sys.cmp_x_part.at(1);
  aux_sys.cmp_b_part.at(0) =
      aux_sys.cmp_x_part.at(0).invers() * aux_sys.cmp_b_part.at(0);
  aux_sys.cmp_x_part.at(3) =
      aux_sys.cmp_x_part.at(3) -
      (aux_sys.cmp_x_part.at(2) * aux_sys.cmp_x_part.at(1));
  aux_sys.cmp_b_part.at(1) =
      aux_sys.cmp_b_part.at(1) -
      (aux_sys.cmp_x_part.at(2) * aux_sys.cmp_b_part.at(0));

  aux_sys.cmp_b_part.at(1) =
      aux_sys.cmp_x_part.at(3).invers() * aux_sys.cmp_b_part.at(1);
  aux_sys.cmp_b_part.at(0) =
      aux_sys.cmp_b_part.at(0) -
      (aux_sys.cmp_x_part.at(1) * aux_sys.cmp_b_part.at(1));

  cout << "SOLUCION :" << endl;
  cout << aux_sys.cmp_b_part.at(0);
  cout << aux_sys.cmp_b_part.at(1);
}

void SystemMatrix::inversion_partitions() {
  // Diagonales cuadradas [0] && [3]
  // complete_x_partitions = [0] [1] [2] [3]
  // complete_b_partitions = [0] [1]
  if (complete_x.det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Determinante igual a cero" << endl;
    return;
  }

  if (cmp_x_part[3].det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] No existe inversa en la submatrix A22" << endl;
    return;
  }

  printPartitions();
  cout << cmp_x_part[3].invers() << endl;

  Matrix C =
      cmp_x_part[0] - (cmp_x_part[1] * (cmp_x_part[3].invers() * cmp_x_part[2]));
  Matrix D = cmp_x_part[1] * cmp_x_part[3].invers();
  Matrix E = cmp_x_part[3].invers() * cmp_x_part[2];
  Matrix F = cmp_x_part[3].invers() + E * (C.invers() * D);

  Matrix x1 = C.invers() * (cmp_b_part.at(0) - D * cmp_b_part.at(1));
  Matrix x2 = (E * -1) * (C.invers() * cmp_b_part.at(0)) + F * cmp_b_part.at(1);

  cout << "SOLUCION: " << endl;
  cout << x1;
  cout << x2;
}

void SystemMatrix::intercambio() {

  if (complete_x.rows != complete_x.cols) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] El sistema no tiene N variables con N incognitas" << endl;
    return;
  }

  vector<int> from_change;
  vector<int> to_change;

  SystemMatrix aux_sys = *this;
  int sys_size = aux_sys.complete_x.matrix.size();

  for (int k = 0; k < sys_size; k++) {
    // Checar si el pivote es 0 -> Cambio de rows

    double pivot = aux_sys.complete_x.matrix.at(k).at(k);
    if (pivot == 0) {
      int pivot_index = k;
      vector<double> row_pivot = aux_sys.complete_x.matrix.at(k);
      for (int i = k; i < sys_size; i++) {
        if (aux_sys.complete_x.matrix.at(i).at(k) != 0) {
          pivot_index = i;
          break;
        }
      }
      aux_sys.complete_x.matrix.at(k) =
          aux_sys.complete_x.matrix.at(pivot_index);
      aux_sys.complete_x.matrix.at(pivot_index) = row_pivot;

      double pivot = aux_sys.complete_x.matrix.at(k).at(k);
    }

    // Toda la matriz menos row/col pivote
    for (int i = 0; i < sys_size; i++) {
      for (int j = 0; j < sys_size; j++) {
        if (i == k || j == k) {
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
    for (int i = 0; i < sys_size; i++) {
      aux_sys.complete_x.matrix.at(i).at(k) =
          aux_sys.complete_x.matrix.at(i).at(k) / pivot;
    }

    // Row pivote
    for (int i = 0; i < sys_size; i++) {
      aux_sys.complete_x.matrix.at(k).at(i) =
          aux_sys.complete_x.matrix.at(k).at(i) / -pivot;
    }

    aux_sys.complete_x.matrix.at(k).at(k) = 1 / pivot;
  }

  // Regresar original matrix x
  for (int i = 0; i < from_change.size(); i++) {
    aux_sys.complete_x.switch_row(from_change.at(i), to_change.at(i));
  }

  // SOLUCION
  Matrix sol_matrix = aux_sys.complete_x * aux_sys.complete_b;
  cout << "Solucion" << endl;
  cout << sol_matrix << endl;
}

bool SystemMatrix::check_iteration_error(vector<double> vec1,
                                         vector<double> vec2, double error) {
  if (vec1.size() != vec2.size()) {
    cout << "[!][check_iteration_error]VECTORES DE DIFERENTE TAMA??O" << endl;
    return false;
  }

  for (int i = 0; i < vec1.size(); i++) {
    if (abs(vec2.at(i) - vec1.at(i)) > error) {
      return false;
    }
  }

  return true;
}

void SystemMatrix::jacobi() {

  if (complete_x.rows != complete_x.cols) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] El sistema no tiene N variables con N incognitas" << endl;
    return;
  }

  if (!complete_x.diagonal_dominante()) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Matriz no diagonalmente dominante" << endl;
    return;
  }

  vector<double> vec_solucion(complete_x.rows, 0);
  vector<double> aux_vec(complete_x.rows, 0);
  double error = 0.1;
  int iteracion = 0;

  cout << "[!] Ingresa la toleracia de error" << endl;
  cout << "[+] => ";
  cin >> error;

  // Ecuacion recursiva
  do {
    // Copy vec
    for (int i = 0; i < vec_solucion.size(); i++) {
      aux_vec.at(i) = vec_solucion.at(i);
    }
    for (int i = 0; i < complete_x.matrix.size(); i++) {
      double acomulation = 0;

      for (int j = 0; j < complete_x.matrix.at(0).size(); j++) {
        if (i == j) {
          continue;
        }

        acomulation += complete_x.matrix.at(i).at(j) * aux_vec.at(j);
      }

      vec_solucion.at(i) = (1 / complete_x.matrix.at(i).at(i)) *
                           (complete_b.matrix.at(i).at(0) - acomulation);
    }

    // Imprimir iteracion
    cout << "\t Iteracion [" << iteracion << "]" << endl;
    iteracion += 1;
    for (auto vc : vec_solucion) {
      cout << vc << endl;
    }
  } while (!check_iteration_error(vec_solucion, aux_vec, error));
  cout << "SOLUCION" << endl;
  for (auto sol : vec_solucion) {
    cout << "|\t " << sol << " \t|" << endl;
  }
}

void SystemMatrix::gauss_seidel() {

  if (complete_x.rows != complete_x.cols) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] El sistema no tiene N variables con N incognitas" << endl;
    return;
  }

  if (complete_x.det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Determinante igual a cero" << endl;
    return;
  }

  if (complete_x.diagonal_dominante() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Diagonalmente no dominante" << endl;
    return;
  }

  vector<double> vec_solucion(complete_x.rows, 0);
  vector<double> aux_vec(complete_x.rows, 0);
  double error = 0.1;
  int iteracion = 0;

  cout << "[!] Ingresa la toleracia de error" << endl;
  cout << "[+] => ";
  cin >> error;

  // Ecuacion recursiva
  do {
    // Copy vec
    for (int i = 0; i < vec_solucion.size(); i++) {
      aux_vec.at(i) = vec_solucion.at(i);
    }
    for (int i = 0; i < complete_x.matrix.size(); i++) {
      double acomulation = 0;

      for (int j = 0; j < complete_x.matrix.at(0).size(); j++) {
        if (i == j) {
          continue;
        }
        if (i < j) {
          acomulation += complete_x.matrix.at(i).at(j) * aux_vec.at(j);
        } else {
          acomulation += complete_x.matrix.at(i).at(j) * vec_solucion.at(j);
        }
      }

      vec_solucion.at(i) = (1 / complete_x.matrix.at(i).at(i)) *
                           (complete_b.matrix.at(i).at(0) - acomulation);
    }

    // Imprimir iteracion
    cout << "\t Iteracion [" << iteracion << "]" << endl;
    iteracion += 1;
    for (auto vc : vec_solucion) {
      cout << vc << endl;
    }
  } while (!check_iteration_error(vec_solucion, aux_vec, error));
  cout << "SOLUCION" << endl;
  for (auto sol : vec_solucion) {
    cout << "|\t " << sol << " \t|" << endl;
  }
}

void SystemMatrix::relajacion() {

  if (complete_x.rows != complete_x.cols) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] El sistema no tiene N variables con N incognitas" << endl;
    return;
  }

  if (complete_x.det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Determinante igual a cero" << endl;
    return;
  }

  if (complete_x.diagonal_dominante() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Diagonalmente no dominante" << endl;
    return;
  }
  Matrix aux_mat_x = complete_x;
  Matrix aux_mat_b = complete_b;
  vector<double> vec_solucion(aux_mat_x.rows, 0);
  vector<double> aux_vec(aux_mat_x.rows, 0);
  vector<double> vec_residuo(aux_mat_x.rows, 0);
  double error = 0.0001;
  int iteracion = 0;

  cout << "[!] Ingresa la toleracia de error" << endl;
  cout << "[+] => ";
  cin >> error;

  for (int i = 0; i < aux_mat_x.rows; i++) {
    double pivot = -aux_mat_x.matrix.at(i).at(i);
    for (int j = 0; j < aux_mat_x.cols; j++) {
      aux_mat_x.matrix.at(i).at(j) /= pivot;
    }
    aux_mat_b.matrix.at(i).at(0) /= pivot;
  }

  do {
    cout << "\tITERACION " << iteracion << endl;
    iteracion += 1;
    aux_vec = vec_solucion;
    // Crear reciduos
    for (int i = 0; i < aux_mat_x.rows; i++) {
      double acomulation = 0;
      for (int j = 0; j < aux_mat_x.cols; j++) {
        acomulation += vec_solucion.at(j) * aux_mat_x.matrix.at(i).at(j);
      }
      vec_residuo.at(i) = acomulation - aux_mat_b.matrix.at(i).at(0);
    }

    // Maximo residuo
    double max_r = 0;
    for (auto vr : vec_residuo) {
      if (abs(vr) > abs(max_r))
        max_r = vr;
    }
    // Index max residuo
    int index_max_r = 0;
    for (int i = 0; i < vec_residuo.size(); i++) {
      if (abs(vec_residuo.at(i)) == abs(max_r))
        index_max_r = i;
    }

    vec_solucion.at(index_max_r) = max_r + aux_vec.at(index_max_r);
    for (auto vs : vec_solucion) {
      cout << vs << endl;
    }
  } while (!check_iteration_error(vec_solucion, aux_vec, error));
  cout << "SOLUCION" << endl;
  for (auto sol : vec_solucion) {
    cout << "|\t " << sol << " \t|" << endl;
  }
}

void SystemMatrix::cholesky() {
  if (complete_x.rows != complete_x.cols) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] La matriz no es cuadrada" << endl;
    return;
  }

  if (complete_x.det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] No tiene solucion unica" << endl;
    return;
  }

  if (!complete_x.symmetrical()) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] La matriz no es simetrica" << endl;
    return;
  }

  if (!complete_x.definida_positiva()) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] La matriz no esta definida positiva" << endl;
    return;
  }

  int m_size = complete_x.rows;
  Matrix mat_l(vector<vector<double>>(complete_x.rows,
                                      vector<double>(complete_x.cols, 0)));
  // Creating L
  for (int i = 0; i < m_size; i++) {
    for (int j = 0; j <= i; j++) {
      double acomulation = 0;

      // Diagonal -> raiz
      if (i == j) {
        for (int h = 0; h < j; h++)
          acomulation += pow(mat_l.matrix.at(j).at(h), 2);
        mat_l.matrix.at(j).at(j) =
            sqrt(complete_x.matrix.at(j).at(j) - acomulation);
      } else {
        // Elementos no diagonales
        for (int h = 0; h < j; h++)
          acomulation += mat_l.matrix.at(i).at(h) * mat_l.matrix.at(j).at(h);
        mat_l.matrix.at(i).at(j) =
            (complete_x.matrix.at(i).at(j) - acomulation) /
            mat_l.matrix.at(j).at(j);
      }
    }
  }
  // Creating U
  Matrix mat_u = mat_l.transp();
  cout << "\t[L]" << endl;
  cout << mat_l << endl;
  cout << "\t[U]" << endl;
  cout << mat_u << endl;

  vector<double> vec_solucion;

  // Creando el vector C
  for (int i = 0; i < m_size; i++) {
    double acomulation = 0;
    for (int j = 0; j < i; j++) {
      acomulation -= mat_l.matrix.at(i).at(j) * vec_solucion.at(j);
    }
    acomulation += complete_b.matrix.at(i).at(0);
    vec_solucion.push_back(1 / mat_l.matrix.at(i).at(i) * acomulation);
  }

  cout << "\t[Vector C]" << endl;
  for (auto vs : vec_solucion) {
    cout << vs << endl;
  }

  // Creando vector solucion X
  for (int i = m_size - 1; i >= 0; i--) {
    double acomulation = 0;
    for (int j = m_size - 1; j > i; j--) {
      acomulation -= mat_u.matrix.at(i).at(j) * vec_solucion.at(j);
    }
    acomulation += vec_solucion.at(i);
    vec_solucion.at(i) = (1 / mat_u.matrix.at(i).at(i)) * acomulation;
  }

  cout << "\t[Solucion X]" << endl;
  for (auto vs : vec_solucion) {
    cout << vs << endl;
  }
}

void SystemMatrix::doolittle() {
  if (complete_x.rows != complete_x.cols) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] La matriz no es cuadrada" << endl;
    return;
  }

  if (complete_x.det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] No tiene solucion unica" << endl;
    return;
  }

  int m_size = complete_x.rows;
  double acomulation = 0;
  Matrix mat_l(vector<vector<double>>(complete_x.rows,
                                      vector<double>(complete_x.cols, 0)));
  Matrix mat_u(vector<vector<double>>(complete_x.rows,
                                      vector<double>(complete_x.cols, 0)));

  vector<double> vec_solucion;
  // Inicializamos diagonal L
  for (int i = 0; i < m_size; i++) {
    mat_l.matrix.at(i).at(i) = 1;
  }
  // Inicializamos primer renglon U
  for (int i = 0; i < m_size; i++) {
    mat_u.matrix.at(0).at(i) = complete_x.matrix.at(0).at(i);
  }
  // Inicializamos primera columna L
  for (int i = 1; i < m_size; i++) {
    mat_l.matrix.at(i).at(0) =
        complete_x.matrix.at(i).at(0) / mat_u.matrix.at(0).at(0);
  }

  // Loop de tama??o - 1 de la matriz
  for (int i = 0; i < m_size; i++) {
    // Renglon U
    for (int k = i; k < m_size; k++) {
      acomulation = 0;
      for (int j = 0; j < i; j++) {
        acomulation += mat_l.matrix.at(i).at(j) * mat_u.matrix.at(j).at(k);
      }

      mat_u.matrix.at(i).at(k) = complete_x.matrix.at(i).at(k) - acomulation;
    }
    // Columna L
    for (int k = i; k < m_size; k++) {
      if (i == k)
        continue;
      acomulation = 0;
      for (int j = 0; j < i; j++) {
        acomulation += mat_l.matrix.at(k).at(j) * mat_u.matrix.at(j).at(i);
      }

      mat_l.matrix.at(k).at(i) = (complete_x.matrix.at(k).at(i) - acomulation) /
                                 mat_u.matrix.at(i).at(i);
    }
  }

  cout << "\t[L]" << endl;
  cout << mat_l << endl;
  cout << "\t[U]" << endl;
  cout << mat_u << endl;

  for (int i = 0; i < m_size; i++) {
    double acomulation = 0;
    for (int j = 0; j < i; j++) {
      acomulation -= mat_l.matrix.at(i).at(j) * vec_solucion.at(j);
    }
    acomulation += complete_b.matrix.at(i).at(0);
    vec_solucion.push_back(1 / mat_l.matrix.at(i).at(i) * acomulation);
  }

  cout << "\t[Vector C]" << endl;
  for (auto vs : vec_solucion) {
    cout << vs << endl;
  }

  // Creando vector solucion X
  for (int i = m_size - 1; i >= 0; i--) {
    double acomulation = 0;
    for (int j = m_size - 1; j > i; j--) {
      acomulation -= mat_u.matrix.at(i).at(j) * vec_solucion.at(j);
    }
    acomulation += vec_solucion.at(i);
    vec_solucion.at(i) = (1 / mat_u.matrix.at(i).at(i)) * acomulation;
  }

  cout << "\t[Vector X]" << endl;
  for (auto vs : vec_solucion) {
    cout << vs << endl;
  }
}

void SystemMatrix::crout(){
  if (complete_x.rows != complete_x.cols) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] La matriz no es cuadrada" << endl;
    return;
  }

  if (complete_x.det() == 0) {
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] No tiene solucion unica" << endl;
    return;
  }

  if (!complete_x.tridiagonal()){
    cout << "[!] Supuesto de aplicacion no cumplido" << endl;
    cout << "[-] Matriz no tridiagonal" << endl;
    return;
  }

  int m_size = complete_x.rows;
  double acomulation = 0;
  Matrix mat_l(vector<vector<double>>(complete_x.rows,
                                      vector<double>(complete_x.cols, 0)));
  Matrix mat_u(vector<vector<double>>(complete_x.rows,
                                      vector<double>(complete_x.cols, 0)));
  vector<double> vec_solucion;
  
  // U fija
  for(int i = 0; i < m_size; i++){
    mat_u.matrix.at(i).at(i) = 1;
  }
  // L11 = A11
  mat_l.matrix.at(0).at(0) = complete_x.matrix.at(0).at(0);

  //L fija
  for(int i = 1 ; i < m_size; i++){
    mat_l.matrix.at(i).at(i - 1) = complete_x.matrix.at(i).at(i - 1);
  }

  for(int i = 1; i < m_size; i++){
    mat_u.matrix.at(i - 1).at(i) = complete_x.matrix.at(i - 1).at(i) / mat_l.matrix.at(i - 1).at(i - 1);
    mat_l.matrix.at(i).at(i) = complete_x.matrix.at(i).at(i) - mat_l.matrix.at(i).at(i - 1) * mat_u.matrix.at(i - 1).at(i);
  }

  cout << "\t[L]" << endl;
  cout << mat_l << endl;
  cout << "\t[U]" << endl;
  cout << mat_u << endl;

  for (int i = 0; i < m_size; i++) {
    double acomulation = 0;
    for (int j = 0; j < i; j++) {
      acomulation -= mat_l.matrix.at(i).at(j) * vec_solucion.at(j);
    }
    acomulation += complete_b.matrix.at(i).at(0);
    vec_solucion.push_back(1 / mat_l.matrix.at(i).at(i) * acomulation);
  }

  cout << "\t[Vector C]" << endl;
  for (auto vs : vec_solucion) {
    cout << vs << endl;
  }

  // Creando vector solucion X
  for (int i = m_size - 1; i >= 0; i--) {
    double acomulation = 0;
    for (int j = m_size - 1; j > i; j--) {
      acomulation -= mat_u.matrix.at(i).at(j) * vec_solucion.at(j);
    }
    acomulation += vec_solucion.at(i);
    vec_solucion.at(i) = (1 / mat_u.matrix.at(i).at(i)) * acomulation;
  }

  cout << "\t[Vector X]" << endl;
  for (auto vs : vec_solucion) {
    cout << vs << endl;
  }
}
