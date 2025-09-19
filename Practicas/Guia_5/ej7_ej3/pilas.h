#ifndef PILAS_H_INCLUDED
#define PILAS_H_INCLUDED


#endif // PILAS_H_INCLUDED

#define MAX 50

typedef long int TElementoP;
typedef struct {
TElementoP datos[MAX];
int tope; } TPila;

void IniciaP (TPila * P);
void poneP (TPila * P, TElementoP x);
void sacaP (TPila * P, TElementoP * x);
TElementoP consultaP(TPila P);
int VaciaP (TPila P);

void muestraRec(TPila *P);

void muestraRecInverso(TPila *P);
