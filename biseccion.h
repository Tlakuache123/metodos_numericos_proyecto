#include "aux_functions.h"
#include <iostream>

using namespace std;

// index -> funcion a evaluar
// iteraciones -> maximo de iteraciones
// a -> inicio de intervalo
// b -> fin del intervalo
// error -> error a cumplir en la raiz
void biseccion() {
  // Ingreso de datos
  int index, iteraciones, count = 0;
  double a, b, error = 0;
  imprimir_funciones();
  cout << "[+] Funcion a evaluar => ";
  cin >> index;
  cout << "[+] a => ";
  cin >> a;
  cout << "[+] b => ";
  cin >> b;
  cout << "[+] maximo num. de iteraciones => ";
  cin >> iteraciones;
  cout << "[+] error => ";
  cin >> error;

  // Indice, Iteraciones, From_x, To_x, Error
  index -= 1;
  double raiz = 1;
  double f_a = eval_funcion(index, a);
  double f_b = eval_funcion(index, b);
  double f_raiz = 99;

  if (f_a * f_b > 0) {
    cout << "[!] Se necesita un cambio de signo para operar" << endl;
    return;
  }

  while (iteraciones > 0) {

    // Evaluamo funciones
    f_a = eval_funcion(index, a);
    f_b = eval_funcion(index, b);

    // Obtenemos falso punto
    raiz = (a + b) / 2;
    f_raiz = eval_funcion(index, raiz);

    cout << "Iteracion [" << count << "]" << endl;
    cout << "x: " << raiz << endl;
    cout << "f(x): " << f_raiz << endl;

    // Checamos si se cumple el error
    if (abs(f_raiz) <= error) {
      cout << "Raiz encontrada = " << raiz << endl;
      return;
    }

    // Acotamos el intervalo
    if (f_raiz * f_a < 0) {
      b = raiz;
    } else {
      a = raiz;
    }

    iteraciones -= 1;
    count += 1;
  }

  cout << "[!] Numero maximo de iteraciones, raiz aproximada = " << raiz
       << endl;
  return;
}
