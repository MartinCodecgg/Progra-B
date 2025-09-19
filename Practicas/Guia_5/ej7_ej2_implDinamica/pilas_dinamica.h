#ifndef PILAS_DINAMICA_H_INCLUDED
#define PILAS_DINAMICA_H_INCLUDED

#endif // PILAS_DINAMICA_H_INCLUDED

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

//Funciones propias del ejercicio

void muestraRec(TPila* P);
