#include "aux.h"
#include <iostream>

using namespace std;

void newton()
{
    // Ingreso de datos
    int index, iteraciones, count = 0;
    double x, error = 0;

    imprimir_funciones();
    cout << "[+] Funcion a evaluar => ";
    cin >> index;
    cout << "[+] x => ";
    cin >> x;
    cout << "[+] maximo num. de iteraciones => ";
    cin >> iteraciones;
    cout << "[+] error => ";
    cin >> error;
    
    index -= 1;
    cout << "Funcion = " << index << endl;
    double f_x = eval_funcion(index, x);
    double df_x = eval_derivada_funcion(index, x);

    while(iteraciones > 0){
        
        cout << "Iteracion [" << count + 1 << "]" << endl;
        cout << "x = " << x << endl;
        cout << "f(x) = " << f_x << endl;
        cout << "df(x) = " << df_x << endl;

        if(abs(f_x) <= error){
            cout << "Raiz = " << x << endl;
            return;
        }

        if(df_x == 0){
            cout << "[!] Derivada = 0, imposible iterar, raiz = " << x << endl;
            return;
        }

        x = x - (f_x / df_x);
        f_x = eval_funcion(index, x);
        df_x = eval_derivada_funcion(index, x);

        count += 1;
        iteraciones -= 1;
    }

    cout << "[!] Numero maximo de iteraciones, raiz aproximada = " << x << endl;
    return;
}
