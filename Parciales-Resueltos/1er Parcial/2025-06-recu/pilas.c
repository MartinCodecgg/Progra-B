#include <stdio.h>
#include <stdlib.h>
#include "pilas.h"

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
/*
TElementoP consultaP(TPila P) {
if (P) // if (P != NULL)
return P->dato;
else
return -1;
}
*/

int VaciaP(TPila P) {
	return (P == NULL);
}

void IniciaP(TPila *P) {
	*P =NULL;
}
