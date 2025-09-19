#include <stdio.h>
#include "colas.h"

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

void cargaC(TCola *C) {

    FILE* arch = fopen("numeros.txt","rt");

    if(!arch)
        printf("Ocurrio un error al abrir el archivo");
    else {
        TElementoC elem;
        printf("Archivo abierto correctamente\n");

        while(fscanf(arch,"%d\n",&elem) == 1 ) {
            poneC(C,elem);
            //printf("%d\n",elem);
        }
    }
}

void muestraEnteros(TCola *C) {

    TElementoC elem;

    while(!VaciaC(*C)) {
        sacaC(C,&elem);
        printf("%d\n",elem);
    }

}

void muestraManteniendo(TCola *C) {

    TElementoC elem, centinela = 9999;
    poneC(C,centinela);
    sacaC(C,&elem);
    while(elem != centinela) {
        printf("%d\n",elem);
        poneC(C,elem);
        sacaC(C,&elem);
    }

}

