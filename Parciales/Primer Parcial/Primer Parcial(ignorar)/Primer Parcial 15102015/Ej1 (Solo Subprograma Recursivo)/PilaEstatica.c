#include <stdio.h>
#include <stdlib.h>
#include "PilaEstatica.h"
#define MAXELEM 100

void iniciaP(TPila *P){
    (*P).tope = -1;
}

void poneP(TPila *P, TElementoP x){
    if((*P).tope != MAXELEM - 1)
        (*P).datos[++(*P).tope] = x;
}

void sacaP(TPila *P, TElementoP *x){
    if((*P).tope != -1)
        *x = (*P).datos[(*P).tope--];
}

TElementoP consultaP(TPila P){
    if(P.tope != -1)
        return P.datos[P.tope];
}

int vaciaP(TPila P){
    return P.tope == -1;
}
