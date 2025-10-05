#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void muestraL(TLista L) {
    while(L) {
        printf("%c ",L->dato);
        L = L->sig;
    }
}

TListaL buscaL(TLista L, char pal[]) {
    while(L && strcmp(pal,L->pal) != 0)
        L = L->sig;
    return L;
}

void elimina(TLista *L, char pal[]) {
    TLista actL, antL;
    actL = *L;
    while(actL && strcmp(pal,actL->pal) != 0) {
        antL = actL;
        actL = actL->sig;
    }
    if(actL && strcmp(pal,actL->pal) == 0) {
        if(actL == *L)
            *L = (*L)->sig;
        else
            antL->sig = actL->sig;
        free(actL);
    }
}

void eliminaPos(TLista *L, unsigned int pos) {
    TLista actL, antL;
    unsigned int aux = 0;
    actL = *L;
    while(actL && aux != pos) {
        antL = actL;
        actL = actL->sig;
        aux++;
    }
    if(actL && aux == pos) {
        if(actL == *L)
            *L = (*L)->sig;
        else
            antL->sig = actL->sig;
        free(actL);
    }
}

void eliminacionSucesiva(TLista *L, char pal[]) {
    TLista actL, antL, elim;
    actL = *L;
    while(actL) {
        if(strcmp(pal, actL->pal) == 0) {
            elim = actL;
            if(actL == *L)
                (*L) = (*L)->sig;
            else
                antL->sig = actL->sig;
            actL = actL->sig;
            free(elim);
        }
        else {
            antL = actL; //actualizar antL solo si no elimine nada
            actL = actL->sig;
        }
    }
}

void inserta(TLista L, char pal[]) {

    new = (TLista) malloc(sizeof(nodo)); //(si corresponde)
    act = *L;
    while(act && strcmp(pal,act->dato) {
        antL = actL;
        actL = actL->sig;
    }
    new->sig = actL;
    if(actL == *L)
        *L = new;
    else
        antL->sig = new;
}

int main() {






    return 0;
}
