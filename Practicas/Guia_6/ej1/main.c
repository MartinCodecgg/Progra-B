#include <stdio.h>
#include "../TDA CREA_LISTA/Crea_Listas.h"
#include "../TDA CREA_LISTA/Crea_Listas.c"

typedef struct nodo{
 char dato;
 struct nodo * sig;} nodo;
typedef nodo * TLista; //Ya que los nodos se crean siempre de forma dinamica usando malloc, y malloc devuelve un puntero a nodo, justmamente un TLista

void muestraL(TLista L); //Si no voy a modificar entonces solo espero una copia.

int main() {
    TLista L;
    char array[] = {'1','2','3','4','5'};
    int n = 5;

    creaL(&L,array,n); //Como voy a modificar el puntero, entonces lo paso el puntero como referencia.
    muestraL(L);

    return 0;
}
void muestraL(TLista L) {
    TLista aux = L;

    while(aux != NULL) {
        printf("%c ",aux->dato);
        aux = aux->sig;
    }
}
