#ifndef COLAS_H_INCLUDED
#define COLAS_H_INCLUDED
#define MAX 50
#define ST5 6

typedef struct { //[PREGUNTAR, si voy a tener que usar una misma constante definida en el main, la dejo en el main o en el colas.h?]
    char cod[ST5];
    float cant; } TElementoC;

typedef struct {
TElementoC datos[MAX];
 int pri, ult; } TCola;

void IniciaC (TCola *C);

int VaciaC(TCola C);

void poneC (TCola *C, TElementoC X);

void sacaC (TCola *C, TElementoC *X);

//TElementoC consultaC (TCola C);

#endif // COLAS_H_INCLUDED




