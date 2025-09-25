#ifndef PILAS_H_INCLUDED
#define PILAS_H_INCLUDED

#endif // PILAS_H_INCLUDED

#define MAX 50

typedef int TElementoP[MAX];

typedef struct nodop {
TElementoP dato;
struct nodop *sig; } nodop;

typedef nodop *TPila;

void poneP(TPila *P, TElementoP x); //TElementoP ya es un tipo array, por ello x ya es array y no es valido x[]

void sacaP(TPila *P, TElementoP x);

//TElementoP consultaP(TPila P); una funcion no puede devolver un array, pero si lo podriamos modificar como parametro de salida

int VaciaP(TPila P);

void IniciaP(TPila *P);
