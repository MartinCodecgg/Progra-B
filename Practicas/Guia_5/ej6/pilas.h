#ifndef PILAS_H_INCLUDED
#define PILAS_H_INCLUDED

#endif // PILAS_H_INCLUDED

#define MAX 50
typedef int TElementoP;

typedef struct {
TElementoP datos[MAX];
int tope; } TPila;

void IniciaP (TPila * P);
void poneP (TPila * P, TElementoP x);
void sacaP (TPila * P, TElementoP * x);
TElementoP consultaP(TPila P);
int VaciaP (TPila P);

void cargaP(TPila *P);
void cuentaCeros (TPila *P);
void promedio(TPila *P);
void maxYmin(TPila*P);
void quitaUlt(TPila *P);
