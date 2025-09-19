#include <stdio.h>
#include <stdlib.h>
#include "pilas_dinamica.h"


void poneP(TPila *P, TElementoP x) {
 TPila N;

 N = (TPila)malloc(sizeof(nodop));
 N->dato = x;
 N->sig = *P;
 *P=N;
}

void sacaP(TPila *P, TElementoP * x) {
 TPila N;
 if (*P) { // if (*P != NULL)
	 N = *P;
 *x = (*P)->dato;
 *P = (*P)->sig;
 free(N);
 }
}

TElementoP consultaP(TPila P) {
	if (P) // if (P != NULL)
	 return P->dato;
}

int VaciaP(TPila P) {
	return (P == NULL);
}

void IniciaP(TPila *P) {
	*P =NULL;
}

void muestraRec(TPila *P) {
    TElementoP elem;
    if(!VaciaP(*P)) {
        sacaP(P,&elem);
        muestraRec(P);      //Para mostrar el contenido como esta en el txt bastara con poner el printf despues del muestraRec()
        printf("%c\n",elem); //Dice mostrar el contenido de la pila, cosa que de por si mostrara alreves
    }
    poneP(P,elem);
}
