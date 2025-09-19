#include <stdio.h>
#include "pilas.h"
#define TOP 50;

int main() {

    TPila P1,P2;
    IniciaP(&P1);
    IniciaP(&P2);
    cargaP1(&P1);
    cargaP2(&P2);

    sumaP(&P1,&P2);

    return 0;
}
