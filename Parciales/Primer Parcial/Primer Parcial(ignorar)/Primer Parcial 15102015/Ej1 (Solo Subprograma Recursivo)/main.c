#include <stdio.h>
#include <stdlib.h>
#include "PilaEstatica.h"

void leerPila(TPila *);
void mostrarPila(TPila *);
void actPila(TPila *, TElementoP, int *);

int main(){
    TPila P;
    TElementoP x;
    int cant = 0;
    iniciaP(&P);
    leerPila(&P);
    scanf("%d", &x);
    mostrarPila(&P);
    actPila(&P, x, &cant);
    printf("Cantidad de eliminados de la pila: %d \n", cant);
    mostrarPila(&P);
    return 0;
}

void leerPila(TPila *P){
    TElementoP x;
    int i, n;
    printf("Ingrese n \n");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        printf("Ingrese un numero \n");
        scanf("%d", &x);
        poneP(P, x);
    }
}

void mostrarPila(TPila *P){
    TPila auxP;
    TElementoP x;
    iniciaP(&auxP);
    while(!vaciaP(*P)){
        sacaP(P, &x);
        printf("%d \n", x);
        poneP(&auxP, x);
    }
    while(!vaciaP(auxP)){
        sacaP(&auxP, &x);
        poneP(P, x);
    }
}

void actPila(TPila *P, TElementoP x, int *cant){
    TElementoP num;
    if(!vaciaP(*P)){
        sacaP(P, &num);
        actPila(P, x, cant);
        if(num == x)
            (*cant)++;
        else
            poneP(P, num);
    }
}
