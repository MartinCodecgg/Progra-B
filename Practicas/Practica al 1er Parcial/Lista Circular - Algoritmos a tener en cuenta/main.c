#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        return (strcmp(pal, aux->pal) == 0) ? aux : NULL;
    }
    else
        return NULL;
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

//IGNORAR (esta mal)

//void eliminaSucesiva(TListaC *LC, char pal[]) {
/*
    TListaC antC, actC, elim;
    if(*LC) {
        antC = (*LC);
        actC = (*LC)->sig;
        while(actC != *LC) {
            if(strcmp(pal, actC->pal) == 0) {
                elim = act;
                if(*LC == (*LC)->sig)
                    *LC = NULL;
                else {
                    antC->sig = actC->sig;
                    if(actC == *LC)
                        *LC = antC;
                    actC = actC->sig;
                }
                free(elim);
            }
            else {
                antC = actC;
                actC = actC->sig;
            }
        }
    }
}
*/

return 0;
}

    return 0;
}
