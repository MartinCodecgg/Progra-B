#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === ALGORITMOS DE LISTA SIMPLEMENTE ENLAZADA === */

void muestraL(TLista L) { //verif
    while(L) {
        printf("%c ",L->dato);
        L = L->sig;
    }
}

TListaL buscaL(TLista L, char pal[]) { //verif
    while(L && strcmp(pal,L->pal) > 0)
        L = L->sig;
    return (L && strcmp(pal,L->pal) == 0) ? L : NULL;
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

/* === ALGORITMOS DE LISTA DOBLEMENTE ENLAZADA === */

void muestraLD(TListaD LD) { //verif
    Pnodo aux = LD.pri;
    while(aux) {
        printf("%c ", aux->dato);
        aux = aux->sig;
    }
}

Pnodo busca(TListaD LD, char pal[]) { //verif
    Pnodo actD = LD.pri;
    while(actD && strcmp(pal,actD->pal) > 0)
        actD = actD->sig;
    return (actD && strcmp(pal,actD->pal) == 0) ? actD : NULL;
}

void eliminaLD(TListaD *LD, char pal[]) { //verif
    Pnodo aux = LD->pri;
    while(aux && strcmp(pal,aux->pal) > 0)
        aux = aux->sig;
    if(aux && strcmp(pal,aux->pal) == 0) {
        if(LD->pri == LD->ult)
            LD->pri = LD->ult = NULL;
        else
            if(aux == LD->pri) {
                LD->pri->sig->ant = NULL;
                LD->pri = LD->pri->sig;
            }
        else
            if(aux == LD->ult) {
                LD->ult->ant->sig = NULL;
                LD->ult = LD->ult->ant;
            }
        else {
            aux->ant->sig = aux->sig;
            aux->sig->ant = aux->ant;
        }
        free(aux);
    }
}

void eliminaSucesiva(TListaD *LD) { //verif
    Pnodo act, elim;
        act = LD->pri;
        while(act != NULL) {
            if(act->cantDias == 0) {
                elim = act;
                if(LD->pri == LD->ult) {
                    LD->pri = NULL;
                    LD->ult = NULL;
                }
                else
                    if(act == LD->pri) {
                        LD->pri->sig->ant = NULL;
                        LD->pri = LD->pri->sig;
                    }
                    else
                        if(act == LD->ult) {
                            LD->ult->ant->sig = NULL;
                            LD->ult = LD->ult->ant;
                        }
                    else {
                        act->ant->sig = act->sig;
                        act->sig->ant = act->ant;
                    }
                act = act->sig;
                free(elim);
            }
            else
                act = act->sig;
        }
}

void insertaOrd(TListaD *LD, char pal[]) { //verif
    Pnodo new, aux;
    new = (Pnodo) malloc(sizeof(nodoD));
    //asignarle los datos
    aux = LD->pri;
    while(aux && strcmp(pal,aux->pal) > 0)
        aux = aux->sig;
    if(LD->pri == NULL) { //Lista vacia //no es valida la comparacion multiple en C
        new->sig = new->ant = NULL;
        LD->pri = LD->ult = new;
    }
    else
        if(strcmp(pal,LD->pri->pal) < 0) { //cabeza pri
            new->ant = NULL;
            new->sig = LD->pri;
            LD->pri->ant = new;
            LD->pri = new;
        }
        else
            if(strcmp(pal,LD->ult->pal) > 0) { //cabeza ult
                new->sig = NULL;
                new->ant = LD->ult;
                LD->ult->sig = new;
                LD->ult = new;
        }
        else { //otro
            new->sig = aux; //siempre tratar el nodo nuevo, y sus enlaces y luego recien los demas, aunque en este caso da igual, en otros casos el orden si importa y el orden correcto general es siempre tratar el nuevo primero
            new->ant = aux->ant;
            aux->ant->sig = new;
            aux->ant = new;
        }
}

/* === ALGORITMOS DE LISTA CIRCULAR === */

void muestraLC(TListaC LC) { //verif
    TListaC aux;
    if(LC) {
        aux = LC->sig;
        do {
            printf("%d", aux->dato);
            aux = aux->sig;
        } while(aux != LC->sig);
    }
}

TListaC busca(TListaC LC, char pal[]) { //verif
    TListaC aux;
    if(LC) {
        aux = LC->sig;
        while(aux != LC && strcmp(pal,aux->pal) != 0)
            aux = aux->sig;
    }
    return (LC && strcmp(pal, aux->pal) == 0) ? aux : NULL;
}

void insertaLC(TListaC *LC, char pal[]) { //verif
    TListaC actC, antC, new;
    new = (TListaC) malloc(sizeof(nodoC)); //(si corresponde)
    //copiar parametro a new
    if(*LC) {
        antC = (*LC);
        actC = (*LC)->sig;
        while(actC != *LC && strcmp(pal,actC->pal) > 0) {
            antC = actC;
            actC = actC->sig;
        }
        //new->sig = actC;
        if(strcmp(pal,(*LC)->pal) > 0) {//tengo que insertar en la cabeza
            new->sig = (*LC)->sig;
            (*LC)->sig = new;
            *LC = new;
        }
        else {
            antC->sig = new;
            new->sig = actC;
        }
    }
    else {
        *LC = new;
        new->sig = new;
    }
}

void elimina(TListaC *LC, char pal[]) { //verif
    TListaC actC, antC;
    if(*LC) {
        antC = (*LC);
        actC = (*LC)->sig;
        while(actC != *LC && strcmp(pal, actC->pal) != 0) {
            antC = actC;
            actC = actC->sig;
        }
        if(strcmp(pal,actC->pal) == 0) {
            if(*LC == (*LC)->sig) //unico
                *LC = NULL;
            else {
                antC->sig = actC->sig; //otro
                if(actC == *LC) //cabeza
                    *LC = antC;
            }
            free(actC);
        }
    }
}

void eliminaSucesiva(TListaC *LC, char pal[]) { //verif
    TListaC antC, actC, elim;
    if(*LC) {
        antC = (*LC);
        actC = (*LC)->sig;
        do {
            if(strcmp(pal, actC->pal) == 0) {
                elim = actC;
                if(*LC == (*LC)->sig)   // unico nodo
                    *LC = NULL;
                else {
                    antC->sig = actC->sig; //otro
                    if(actC == *LC)  // cabeza
                        *LC = antC;
                    actC = actC->sig;
                }
                free(elim);
            }
            else { //si no hay que eliminar nada
                antC = actC;
                actC = actC->sig;
            }
        } while(*LC && actC != (*LC)->sig);  // Termina cuando vuelve a ser el 1ero,
    }
}
//La ventaja del do while es q permite no repetir logica para el caso de la cabeza

int main() {
    TLista L;
    TListaD LD;
    TListaC LC;
    L = LD = LC = NULL;

    printf("Hello world!\n");
    return 0;
}
