#include "colas.h"
#include <stdio.h>

void IniciaC (TCola *C) {
(*C).pri = (*C).ult=-1; // C->pri = C -> ult = -1;
}

int VaciaC(TCola C){
 return C.pri==-1;
}

void poneC (TCola *C, TElementoC X) {
 if ((*C).ult != MAX-1) {
 if ((*C).pri==-1)
 (*C).pri = 0;
 (*C).datos[++((*C).ult)]=X;
 }
}

void sacaC (TCola *C, TElementoC *X) {
 if ((*C).pri != -1) { // !vaciaC(*C)
 *X = (*C).datos[(*C).pri];
 if ((*C).pri == (*C).ult)
 IniciaC(C);
 else
 (*C).pri +=1;
 }
}
TElementoC consultaC (TCola C){
if (C.pri !=-1)
return C.datos[C.pri];
}

void cargaC(TCola *C){

    FILE* arch = fopen("Votantes.txt","rt");
    TElementoC elem;

    if(!arch)
        printf("Error al abrir el archivo\n");
    else {
        printf("Archivo de texto abierto correctamente\n");
        while(fscanf(arch,"%ld",&elem) == 1) {

            //printf("%8.0f\n",elem);
            poneC(C,elem);
        }
    }
}

void muestraC(TCola *C) {

    TElementoC elem;
    printf("Mostrando en el orden en el que sufragaron\n");
    while(!VaciaC(*C)) {
        sacaC(C,&elem);
        printf("%ld\n",elem);
    }
}
