#include <stdio.h>
#include <string.h>
#include "pilas.h"

void poneP(TPila *P, TElementoP x[]) {
 if ( ((*P).tope)!= MAX-1)
 ++((*P).tope);
 strcpy((*P).datos[((*P).tope),x);
}

void sacaP(TPila *P, TElementoP* x) {
 if (((*P).tope) != -1) //if (P->tope != 1)
 *x = (*P).datos[(*P).tope--]; // *x = P->datos[P->tope--]
}

/*
TElementoP consultaP(TPila P) {
 if (P.tope != -1)
    return P.datos[P.tope];
 else
    return -1;
}
*/

int VaciaP(TPila P) {
 return (P.tope == -1);
}

void IniciaP (TPila *P) {
(*P).tope=-1;
}

