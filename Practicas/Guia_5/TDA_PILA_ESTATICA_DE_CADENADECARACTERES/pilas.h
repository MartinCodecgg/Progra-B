#ifndef PILAS_H_INCLUDED
#define PILAS_H_INCLUDED

#endif // PILAS_H_INCLUDED

#define MAX 50
#define MAX_CADENA

typedef char TElementoP[MAX_CADENA];

typedef struct TPila{
TElementoP datos[MAX];
int tope;
} TPila;

void IniciaP (TPila * P);
void poneP (TPila * P, TElementoP x);
void sacaP (TPila * P, TElementoP * x);
//TElementoP consultaP(TPila P); En C no se puede retornar un array, pero si podria modificar un array definiendo como parametro de salida.
