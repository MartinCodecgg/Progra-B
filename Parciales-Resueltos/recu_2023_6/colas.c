#include "colas.h"
#include <stdio.h>
#include <stdlib.h> //para que funcione el exit()
#define MAX 50

void poneC (TCola *C, TElementoC X) {
 if (!((*C).ult==MAX-1 && (*C).pri==0 || (*C).ult+1==(*C).pri)) {
 if ((*C).pri==-1){
 (*C).pri = 0;
 (*C).ult = 0;
 }
 else
 if ((*C).ult == MAX-1)
 (*C).ult = 0;
 else
 (*C).ult += 1;
 (*C).datos[(*C).ult]=X;
 }
}
void sacaC (TCola *C, TElementoC *X) {
 if ((*C).pri != -1) {
 *X = (*C).datos[(*C).pri];
 if ((*C).pri == (*C).ult)
 IniciaC(C);
 else
 if ((*C).pri == MAX-1)
 (*C).pri = 0;
 else
 (*C).pri += 1;
 }
}

void IniciaC (TCola *C) {
(*C).pri = (*C).ult=-1; // C->pri = C -> ult = -1;
}

int VaciaC(TCola C){
 return C.pri==-1;
}

TElementoC consultaC(TCola C) {
    if (C.pri != -1)
        return C.datos[C.pri];
    else {
        fprintf(stderr, "Error: cola vacia\n");
        exit(1);
    }
}
