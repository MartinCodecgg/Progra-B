#include <stdio.h>
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\IMPL_COLAESTATICACIRCULAR\colas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\IMPL_COLAESTATICACIRCULAR\colas.c"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\ej1 (marco para pila estatica)\pilas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\ej1 (marco para pila estatica)\pilas.c"
#define N 5

void cargaC(TCola *C);

void validaC(TCola *C);

int main() {
    TCola C;
    IniciaC(&C);
    cargaC(&C);
    validaC(&C);
    return 0;
}

void cargaC(TCola *C) {
    FILE* arch = fopen("palin.txt","rt");
    char cad;
    if(arch == NULL)
        printf("Error en la apertura del archivo");
    else {
        printf("Mostrando lectura de archivo\n");
        while(fscanf(arch,"%c",&cad) == 1) {
            printf("%c\n",cad);
            poneC(C,cad);
        }
    }
}

void validaC(TCola *C) {
    TPila P;
    IniciaP(&P);
    int i, OK = 1;
    char cad,caux;
    if(!VaciaC(*C)) {
        for(i=0; i<N; i++) {
            sacaC(C,&cad);
            poneC(C,cad);
            poneP(&P,cad);
        }
        i = 0;
        while(i<N && OK) {
            sacaC(C,&cad);
            sacaP(&P,&caux);
            if(cad != caux)
                OK = 0;
            i++;
        }
        if(OK)
            printf("La palabra es palindroma");
        else
            printf("La palabra no es palindroma");
    }
}
