#ifndef COLAS_H_INCLUDED
#define COLAS_H_INCLUDED

#endif // COLAS_H_INCLUDED

#define MAX 50

typedef char TElementoC;

typedef struct TCola{
TElementoC datos[MAX];
int pri, ult;
} TCola;

void poneC (TCola *C, TElementoC X);

void sacaC (TCola *C, TElementoC *X);

void IniciaC (TCola *C);

int VaciaC(TCola C);

TElementoC consultaC (TCola C);
