#include <cstdlib>
#include <iostream>

using namespace std;

#include "biseccion.h"
#include "falsaPos.h"
#include "matrix.h"
#include "newton.h"
#include "secante.h"
#include "system_matrix.h"

int get_sub_menu() {
  int option = 0;
  cout << "==\t\t [MENU] \t\t==" << endl;
  cout << "[1]\t Solucion de Ecuaciones" << endl;
  cout << "[2]\t Sistemas de Ecuaciones Lineales" << endl;
  cout << "[3]\t Factorizacion LU" << endl;
  cout << "[+] => ";
  cin >> option;
  return option;
}

int get_metodo_ecuacion() {
  int option = 0;
  cout << "=\t\t[Sol. de Ecuaciones]\t\t=" << endl;
  cout << "[1]\t Biseccion" << endl;
  cout << "[2]\t Falsa Posicion" << endl;
  cout << "[3]\t Newton" << endl;
  cout << "[4]\t Secante" << endl;
  cout << "[+] => ";
  cin >> option;
  return option;
}

int get_metodo_matriz() {
  int option = 0;
  cout << "=\t\t[Sol. de Matrices]\t\t=" << endl;
  cout << "[1]\t Inversion particionado" << endl;
  cout << "[2]\t Guass-Jordan particionado" << endl;
  cout << "[3]\t Intercambio" << endl;
  cout << "[4]\t Jacobi" << endl;
  cout << "[5]\t Gauss Seidel" << endl;
  cout << "[6]\t Relajacion" << endl;
  cout << "[+] => ";
  cin >> option;
  return option;
}

int get_metodo_factorizacion() {
  int option = 0;
  cout << "=\t\t[Factorizacion LU]\t\t=" << endl;
  cout << "[1]\t Cholesky" << endl;
  cout << "[2]\t Doolittle" << endl;
  cout << "[+] => ";
  cin >> option;
  return option;
}

int main(int argc, char *argv[]) {
  int opt = get_sub_menu();
  // Solucion de Ecuaciones
  if (opt == 1) {
    opt = get_metodo_ecuacion();
    switch (opt) {
    case 1:
      biseccion();
      break;

    case 2:
      falsa_posicion();
      break;

    case 3:
      newton();
      break;

    case 4:
      secante();
      break;

    default:
      cout << "[!]\t Ingresa una opcion valida" << endl;
      break;
    }
  }
  // Solucion de Matrices
  if (opt == 2) {
    opt = get_metodo_matriz();
    SystemMatrix system = SystemMatrix();

    switch (opt) {
    case 1:
      system.inversion_partitions();
      break;

    case 2:
      system.gauss_partitions();
      break;

    case 3:
      system.intercambio();
      break;

    case 4:
      system.jacobi();
      break;

    case 5:
      system.gauss_seidel();
      break;

    case 6:
      system.relajacion();
      break;

    case 7:
      system.cholesky();
      break;

    default:
      cout << "[!]\t Ingresa una opcion valida" << endl;
      break;
    }
  }

  if (opt == 3) {
    opt = get_metodo_factorizacion();
    SystemMatrix system = SystemMatrix();

    switch (opt) {
    case 1:
      system.cholesky();
      break;

    case 2:
      system.doolittle();
      break;

    default:
      cout << "[!]\t Ingresa una opcion valida" << endl;
      break;
    }
  }
  return 0;
}
