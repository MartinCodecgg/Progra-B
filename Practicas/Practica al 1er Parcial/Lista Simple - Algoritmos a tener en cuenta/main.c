#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void muestraL(TLista L) { //verif
    while(L) {
        printf("%c ",L->dato);
        L = L->sig;
    }
}

TListaL buscaL(TLista L, char pal[]) { //verif
    while(L && strcmp(pal,L->pal) != 0)
        L = L->sig;
    return L;
}

void elimina(TLista *L, char pal[]) { //verif
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

void eliminaPos(TLista *L, unsigned int pos) { //verif
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

void eliminacionSucesiva(TLista *L, char pal[]) { //verif
    TLista actL, antL, elim;
    actL = *L;
    while(actL) {
        if(strcmp(pal,actL->pal) == 0) {
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

void insertaOrd(TLista *L, char pal[]) { //veri
    TLista actL, antL, new;
    new = (TLista) malloc(sizeof(nodo)); //(si corresponde)
    //asignar datos
    actL = *L;
    while(actL && strcmp(pal,actL->pal) > 0) {
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
