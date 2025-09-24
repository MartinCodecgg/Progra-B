#include <stdio.h>
#include <stdlib.h>
#include "Crea_Listas.h"

void creaL(TLista *L,TElementoL array[], int n) {
    TLista aux,ant;
    int i;
    if(n <= 0)
        printf("Cantidad de elementos del arreglo invalida\n");
    else {
        aux = (TLista) malloc(sizeof(nodo));
        aux->dato = array[0];
        aux->sig = NULL;
        *L = aux;
        for(i=1; i<n; ++i) {
            ant = aux;
            aux = (TLista) malloc(sizeof(nodo));
            aux->dato = array[i];
            ant->sig = aux;
        }
        aux->sig = NULL;
    }
}
