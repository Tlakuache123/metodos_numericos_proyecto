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
  cout << "Araujo Palestina Claudio Hassiel" << endl;
  cout << "Osorio Garcia Diego" << endl;
  cout << "[1]\t Solucion de Ecuaciones" << endl;
  cout << "[2]\t Sistemas de Ecuaciones Lineales" << endl;
  cout << "[3]\t Factorizacion LU" << endl;
  cout << "[0]\t Salir" << endl;
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
  cout << "[3]\t Crout" << endl;
  cout << "[+] => ";
  cin >> option;
  return option;
}

int main(int argc, char *argv[]) {
  int opt = 0;
  do{
    opt = get_sub_menu();
    // Solucion de Ecuaciones
    if (opt == 1) {
      if(opt > 4){
        cout << "[!]\t Ingresa una opcion valida" << endl;
        continue;
      }
      opt = get_metodo_ecuacion();
      switch (opt) {
      case 1:
        cout << "[Biseccion]" << endl;
        biseccion();
        break;

      case 2:
        cout << "[Falsa posicion]" << endl;
        falsa_posicion();
        break;

      case 3:
        cout << "[Newton]" << endl;
        newton();
        break;

      case 4:
        cout << "[Secante]" << endl;
        secante();
        break;
      }
    }
    // Solucion de Matrices
    else if (opt == 2) {
      opt = get_metodo_matriz();
      if(opt > 6){
        cout << "[!]\t Ingresa una opcion valida" << endl;
        continue;
      }
      SystemMatrix system = SystemMatrix();

      switch (opt) {
      case 1:
        cout << "[Inversion particionado]" << endl;
        system.inversion_partitions();
        break;

      case 2:
        cout << "[Guass particionado]" << endl;
        system.gauss_partitions();
        break;

      case 3:
        cout << "[Intercambio]" << endl;
        system.intercambio();
        break;

      case 4:
        cout << "[Jacobi]" << endl;
        system.jacobi();
        break;

      case 5:
        cout << "[Gauss Seidel]" << endl;
        system.gauss_seidel();
        break;

      case 6:
        cout << "[Relajacion]" << endl;
        system.relajacion();
        break;
      }
    }

    else if (opt == 3) {
      opt = get_metodo_factorizacion();
      if(opt > 3){
        cout << "[!]\t Ingresa una opcion valida" << endl;
        continue;
      }
      SystemMatrix system = SystemMatrix();

      switch (opt) {
      case 1:
        cout << "[Cholesky]" << endl;
        system.cholesky();
        break;

      case 2:
        cout << "[Doolittle]" << endl;
        system.doolittle();
        break;

      case 3:
        cout << "[Crout]" << endl;
        system.crout();
        break;
      }
    }

  } while(opt != 0);
  return 0;
}
