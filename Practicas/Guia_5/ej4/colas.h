#ifndef COLAS_H_INCLUDED
#define COLAS_H_INCLUDED

#endif // COLAS_H_INCLUDED

#include <stdio.h>
#define MAX 50

typedef int TElementoC; //si voy a leer numeros grandes procurar usar long y no usar float, porque mierdo precision

typedef struct {
TElementoC datos[MAX];
 int pri, ult; } TCola;

void IniciaC (TCola *C);

int VaciaC(TCola C);

void poneC (TCola *C, TElementoC X);

void sacaC (TCola *C, TElementoC *X);

TElementoC consultaC (TCola C);

void cargaC(TCola C);
