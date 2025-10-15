#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOP 50

typedef struct nodoCAD {
    char dato[TOP];
    struct nodoCAD *izq, *der;
} nodoCAD;

typedef struct { //structs necesario para funcion int
    int nivel;
    int longitud;
} Resultado;

typedef nodoCAD * ArbolCAD;

void addnodoCAD(ArbolCAD *A2, const char *cad) {
    *A2 = (ArbolCAD)malloc(sizeof(nodoCAD));
    strcpy((*A2)->dato, cad);
    (*A2)->izq = NULL;
    (*A2)->der = NULL;
}

void cargaArbolCAD(ArbolCAD *A2) {
    addnodoCAD(A2, "casa");
    addnodoCAD(&(*A2)->izq, "ventana");
    addnodoCAD(&(*A2)->der, "asol");
    addnodoCAD(&(*A2)->izq->izq, "estrella");
    addnodoCAD(&(*A2)->izq->der, "flor");

    /* ArbolCAD en cuestion:
             casa
            /    \
        ventana   asol
         /   \
    estrella  flor
    */
}

void nivelMax(ArbolCAD A2, int *nivMax, int *longMax, int nivelActual) {
    if(A2 != NULL) {
        nivelActual++;
        if(strlen(A2->dato) > *longMax && A2->dato[0] == 'a') {
            *longMax = strlen(A2->dato);
            *nivMax = nivelActual;
        }
        nivelMax(A2->der, nivMax, longMax, nivelActual);
        nivelMax(A2->izq, nivMax, longMax, nivelActual);
    }
}

/*
typedef struct { //structs necesario para funcion int
    int nivel;
    int longitud;
} Resultado;
*/

Resultado nivelMaxINT(ArbolCAD A2,int nivelActual) {
    Resultado reg, regIzq, regDer;
    if(A2 == NULL)
        return (Resultado) { -1, -1 };
        //o tambien return res = { -1, -1 };
    else {
        reg = (Resultado) {-1,-1};
        nivelActual++;
        if(A2->dato[0] == 'a' || A2->dato[0] == 'A')
            reg = (Resultado) {nivelActual, strlen(A2->dato)};

        regIzq = nivelMaxINT(A2->izq, nivelActual);
        regDer = nivelMaxINT(A2->der, nivelActual);

        if(regIzq.longitud > reg.longitud)
            reg = regIzq;
        if(regDer.longitud > reg.longitud)
            reg = regDer;

        return reg;
    }
}

//Resultado res = {-1, -1};  ESTA ES UNA FORMA INTERESANTE DE ASIGNAR DATOS A UN STRUCT

int main() {
    ArbolCAD A2;
    cargaArbolCAD(&A2);
    int nivMax, longMax = 0;

    nivelMax(A2, &nivMax, &longMax, 0);
    printf("El nivel donde se encuentra la palabra con longitud maxima es %d\n", nivMax);

    Resultado aux = nivelMaxINT(A2, 0);
    printf("El nivel donde se encuentra la palabra con longitud maxima es %d",aux.nivel);

    return 0;
}
