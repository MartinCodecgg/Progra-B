#include "pilas.h"
#include <stdio.h>

void poneP(TPila *P, TElementoP x) {
 if ( ((*P).tope)!= MAX-1)
 (*P).datos[++((*P).tope)] = x;
}

void sacaP(TPila *P, TElementoP* x) {
 if (((*P).tope) != -1) //if (P->tope != 1)
 *x = (*P).datos[(*P).tope--]; // *x = P->datos[P->tope--]
}

TElementoP consultaP(TPila P) {
 if (P.tope != -1)
 return P.datos[P.tope];
}

int VaciaP(TPila P) {
 return (P.tope == -1);
}

void IniciaP (TPila *P) {
(*P).tope=-1;
}

void muestraRec(TPila *P) {
    TElementoP elem;
    if(!VaciaP(*P)) {
        sacaP(P,&elem);
        printf("%ld\n",elem);
        muestraRec(P);
        poneP(P,elem); //recordar de solo poner si saque algun dato, es decir el pone va dentro del if.
    }
}

void muestraRecInverso(TPila *P) {
    TElementoP elem;
    if(!VaciaP(*P)) {
        sacaP(P,&elem);
        muestraRec(P);
        printf("%ld\n",elem);
        poneP(P,elem);
    }
}
