#include <stdio.h>
#include "fracciones.h"

int mcd(int a, int b) { //para simplificar
    int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

fraccion crear(int n, int d) {
    fraccion f;
    f.n = n;
    f.d =d;
    return f;
}

int numerador(fraccion f){
    return f.n;
}

int denominador(fraccion f) {
    return f.d;
}
fraccion sumar(fraccion f1, fraccion f2) {

    fraccion aux;

    aux.d = f1.d * f2.d;
    aux.n = f1.n * f2.d + f2.n * f1.d;

    aux = simplificar(aux);

    return aux;
}

fraccion simplificar(fraccion f) {

    int divisor = mcd(f.n,f.d);

    f.n /= divisor;
    f.d /= divisor;

    return f;
}

int iguales(fraccion f1, fraccion f2) {

    return (f1.n == f2.n && f1.d == f2.d) ? 1 : 0;

}










