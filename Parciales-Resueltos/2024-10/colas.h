#ifndef COLAS_H_INCLUDED
#define COLAS_H_INCLUDED
#define ST5 6
#define ST7 8

typedef struct {
    char cod[ST5], pat[ST7], hora[ST5];
    unsigned int fecha, tp, tr; } TElementoC;

typedef struct nodo {
 TElementoC dato;
 struct nodo * sig;} nodo;

typedef struct {
nodo *pri, *ult;} TCola;

void IniciaC (TCola *C);
int VaciaC(TCola C);
void poneC (TCola *C, TElementoC X);
void sacaC (TCola *C, TElementoC *X);

TElementoC consultaC (TCola C);

#endif // COLAS_H_INCLUDED
