#ifndef PILAS_H_INCLUDED
#define PILAS_H_INCLUDED



#endif // PILAS_H_INCLUDED

typedef char TElementoP;

typedef struct nodop {
TElementoP dato;
struct nodop *sig; } nodop;

typedef nodop *TPila;

void poneP(TPila *P, TElementoP x);

void sacaP(TPila *P, TElementoP * x);

TElementoP consultaP(TPila P);

int VaciaP(TPila P);

void IniciaP(TPila *P);
