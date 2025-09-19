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
        muestraRec(P);      //Para mostrar el contenido como esta realmente en la Pila bastara con poner el printf antes del muestraRec()
        printf("%c\n",elem); //Dice mostrar el contenido de la pila, pero especifica de que forma.
    }
    poneP(P,elem);
}
