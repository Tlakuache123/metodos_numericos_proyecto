#include "aux.h"
#include <iostream>

using namespace std;

// index -> funcion a evaluar
// iteraciones -> maximo de iteraciones
// a -> inicio de intervalo
// b -> fin del intervalo
// error -> error a cumplir en la raiz
void secante()
{
    // Ingreso de datos
    int index, iteraciones, count = 0;
    double a, b, error = 0;
    
    imprimir_funciones();
    cout << "[+] Funcion a evaluar => ";
    cin >> index;
    cout << "[+] x_n => ";
    cin >> a;
    cout << "[+] x_n-1 => ";
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

    while(iteraciones > 0){
        
        // Evaluamo funciones
        f_a = eval_funcion(index, a);
        f_b = eval_funcion(index, b);

        // Obtenemos falso punto
        raiz = a - ((f_a * (b - a))/(f_b - f_a));
        f_raiz = eval_funcion(index, raiz);

        cout << "Iteracion [" << count << "]" << endl;
        cout << "x: " << raiz << endl;
        cout << "f(x): " << f_raiz << endl;

        // Checamos si se cumple el error
        if(f_b - f_a == 0){
            cout << "[!] Error al dividir entre 0 (F(a) - F(b) = 0)" << endl;
            return;
        }
        if(abs(f_raiz) <= error){
            cout << "Raiz encontrada = " << raiz << endl;
            return;
        }

        // Acotamos el intervalo
        b = a;
        a = raiz;


        iteraciones -= 1;
        count += 1;

    }

    cout << "[!] Numero maximo de iteraciones, raiz aproximada = " << raiz << endl;
    return;
}

