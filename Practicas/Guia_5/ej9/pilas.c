#include <stdio.h>
#include "pilas.h"

void poneP(TPila *P, TElementoP x) {
 if ( ((*P).tope)!= MAX-1)
 (*P).datos[++((*P).tope)] = x;
}

void sacaP(TPila *P, TElementoP* x) {
 if (((*P).tope) != -1) //if (P->tope != 1)
 *x = (*P).datos[(*P).tope--]; // *x = P->datos[P->tope--]
}

TElementoP consultaP(TPila P) {
 if (P.tope != -1)
    return P.datos[P.tope];
 else
    return -1;
}

int VaciaP(TPila P) {
 return (P.tope == -1);
}

void IniciaP (TPila *P) {
(*P).tope=-1;
}

void cargaP(TPila *P,char archivo[]) {

    TElementoP elem;
    FILE* arch = fopen(archivo,"rt");

    if(arch == NULL)
        printf("Error al abrir");
    else {
        printf("Muestro carga de primer archivo\n");
        while(fscanf(arch,"%c\n",&elem) == 1) {
            poneP(P,elem);
            printf("%c\n",elem);
        }
    }
}

void sumaP(TPila *P1,TPila *P2) {

    TPila Paux;
    IniciaP(&Paux);
    TElementoP cad1,cad2,aux;
    int num,prestado = 0;

    while(!VaciaP(*P1) && !VaciaP(*P2)) {
        sacaP(P1,&cad1);
        sacaP(P2,&cad2);

        num = cad1 - '0' + cad2 - '0' + prestado;

        prestado = num / 10;

        if(prestado != 0) { //es decir si la suma es mayor a 10
            num = num % 10; //me quedo con el resto
        }
        aux = num + '0';
        poneP(&Paux,aux);
    }
    //=== Aqui convenia mostrar en una funcion aparte, tambien hacer un solo procedimiento para terminar de cargar los numeros del numero mas grande
    //que deben cargarse directamente sin sumar. ===

    while(!VaciaP(*P1)) {

        sacaP(P1,&cad1);

        num = cad1 - '0' + prestado;
        prestado = 0;

        aux = num + '0';
        poneP(&Paux, aux);
    }

    while(!VaciaP(*P2)) {

        sacaP(P2,&cad2);

        num = cad2 - '0' + prestado;
        prestado = 0;

        aux = num + '0';
        poneP(&Paux, aux);
    }

    printf("Muestro la suma\n");
    while(!VaciaP(Paux)) {
        sacaP(&Paux,&aux);
        printf("%c\n",aux);
    }
}
