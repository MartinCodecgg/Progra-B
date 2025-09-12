#include <stdio.h>
#include "pilas.h"

/*
6. Desarrollar subprogramas (con estructuras iterativas) que trabajando sobre una pila de
enteros:
a. cuente la cantidad de ceros que contiene.
b. obtenga el valor promedio (sin perder la información de la pila)
 UNMdP Ing. en Informática
 Facultad de Ingeniería Programación B
Práctica 5 – Pilas y Colas Página 2 / 2
c. calcule los valores máximo y mínimo de la pila (sin perder la información de la pila)
d. quite todos los valores mayores al último.
*/

int main() {

    TPila P;

    IniciaP(&P);
    cargaP(&P);
    //cuentaCeros(&P); //DESCOMENTAR PARA VER EJERCICIO a)
    promedio(&P);

    maxYmin(&P);

    quitaUlt(&P);

    return 0;
}
