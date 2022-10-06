#include <cmath>
#include <iostream>

using namespace std;

// f(x) = Cos^2(x)Sen^2(x)
// f(x) = e^x(x^2-2x-15)
// f(x) = x^5 + 25/6x^4 - 197/6x^3 - 511/6x^2 + 395/6x + 175
// f(x) = Cos^2(x)(x^2-8x+10)
void imprimir_funciones(){
    cout << "Funciones:" << endl;
    cout << "1- f(x) = Cos^2(x)Sen^2(x)" << endl;
    cout << "2- f(x) = e^x(x^2-2x-15)" << endl;
    cout << "3- x^5 + 25/6x^4 - 197/6x^3 - 511/6x^2 + 395/6x + 175" << endl;
    cout << "4- f(x) = Cos^2(x)(x^2-8x+10)" << endl;
}

double eval_funcion(int index, double x)
{
    switch (index) {
        case 0:
            return pow(cos(x), 2) * pow(sin(x), 2);
        case 1:
            return exp(x) * (pow(x, 2) - 2 * x - 15);
        case 2:
            return pow(x, 5) + (25./6) * pow(x, 4) - (197./6) * pow(x, 3) - (511./6) * pow(x, 2) + (395./6) * x + 175;
        case 3:
            return pow(cos(x), 2) * (pow(x, 2) - 8 * x + 10);
        default:
            return -1;
    }
}

// -2Cos(x)Sin(X) (Sin^2(x) - Cos^2(x))
// (x^2 - 17)e^x
// (30x^4 + 100x^3 - 591x^2 - 1022x + 395)/6
// -2Cos(x) ((x^2 - 8x + 10) Sin(x) + (4 - x)Cos(x))
double eval_derivada_funcion(int index, double x)
{
    switch (index) {
        case 0:
            return -2 * cos(x) * sin(x) * (pow(sin(x), 2) - pow(cos(x), 2));
        case 1:
            return (pow(x, 2) - 17) * exp(x);
        case 2:
            return (30 * pow(x, 4) + 100 * pow(x, 3) - 591 * pow(x, 2) - 1022 * x + 395) / 6;
        case 3:
            return -2 * cos(x) * ((pow(x, 2) - 8 * x + 10) * sin(x) + (4 - x) * cos(x));
        default:
            return -1;
    }
}
