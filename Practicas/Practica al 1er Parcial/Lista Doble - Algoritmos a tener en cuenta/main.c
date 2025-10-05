#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void muestraLD(TListaD LD) { //verif
    Pnodo aux;
    if(LD.pri) { //LD es simplemente un struct con dos campos, asi que accedo con .pri y no con flecha
        aux = LD.pri;       //Si pasase como referencia a LD si usaria flecha
        while(aux) {
            printf("%c ", aux->dato);
            aux = aux->sig;
        }
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

int main() {
    printf("Hello world!\n");
    return 0;
}
