#include <stdio.h>
#include "pilas.h"
#define TOP 50;

int main() {

    TPila P1,P2;
    IniciaP(&P1);
    IniciaP(&P2);
    cargaP(&P1,"entero.txt");
    cargaP(&P2,"entero2.txt");

    sumaP(&P1,&P2);

    return 0;
}
