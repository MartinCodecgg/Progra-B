//parcial controlado mediante prueba de escritorio de IA
#include <stdio.h>
#include <stdlib.h>
#include "colas.h"
#define ST30 31
//#define ST7 8 //ya declarado en colas.h
#include <string.h>

typedef struct nodito {
    char cod[ST7];
    int dest, cantS, cantE;
    struct nodito * sig; } nodito;

typedef nodito SubLista;

typedef struct nodoC{
    int idP, cantS;
    char nom[ST30];
    SubLista sub;
    struct nodoC *sig;} nodoC;

typedef nodoC * TLC;

typedef struct nodo{
    int idR, idP;
    TCola C;
    struct nodo * sig;} nodo;

typedef nodo * TL;

void procesaArch(TLC * LC) {
    FILE * arch = fopen("PEDIDOS.txt", "rt");
    TLC Ppuesto;
    int idP, cantP, dest, cant, i;
    char nom[ST30], cod[ST7];
    if(arch) {
        while(fscanf(arch, "%d %s %d", &idP, nom, &cantP) == 3) {
            hallaPuesto(LC, idP, nom, &Ppuesto);
            for(i = 0; i < cantP; i++) {
                fscanf(arch, "%d %s %d", &dest, cod, &cant);
                actualizaP(Ppuesto, cod, dest, cant);
            }
        }
        fclose(arch);
    }
}

TLC buscaPuesto(TLC LC, int idP) {
    TLC aux;
    if(LC) {
        aux = LC->sig;
        while(aux != LC && idP != aux->idP)
            aux = aux->sig;
    }
    return LC && idP == aux->idP ? aux : NULL;
}

void hallaPuesto(TLC *LC, int idP, char nom[], TLC * Ppuesto) {
    TLC actC, antC, nuevo;
    nuevo = (TLC) malloc(sizeof(nodoC));
    nuevo->cantS = 0;
    nuevo->idP = idP;
    nuevo->sub = NULL;
    strcpy(nuevo->nom, nom);

    if(*LC == NULL) {
        nuevo->sig = nuevo;
        *LC = *Ppuesto = nuevo;
    }
    else {
        if(idP > (*LC)->idP) {
            nuevo->sig = (*LC)->sig;
            *LC = *Ppuesto = nuevo;
        }
        else {
            antC = *LC;
            actC = (*LC)->sig;
            while(actC != *LC && idP > actC->idP) {
                antC = actC;
                actC = actC->sig;
            }
            if(idP != actC->idP) {
                nuevo->sig = actC;
                *Ppuesto = nuevo;
                antC->sig = nuevo;
            }
            else {
                free(nuevo);
                *Ppuesto = actC;
            }
        }
    }
}

void actualizaP(TLC Ppuesto, char cod[], int dest, int cant) {
    SubLista actS, antS, nuevo;

    actS = Ppuesto->sub;
    while(actS && (strcmp(cod, actS->cod) != 0 || dest != actS->dest)) {
        antS = actS;
        actS = actS->sig;
    }
        
    if(actS == NULL) {
        nuevo = (SubLista) malloc(sizeof(nodito));
        nuevo->cantS = 0;
        nuevo->cantE = 0;
        nuevo->dest = dest;
        strcpy(nuevo->cod, cod);

        nuevo->sig = NULL;
        if(Ppuesto->sub == NULL) //la sublista no esta ord entonces inserto al final
            Ppuesto->sub = nuevo;
        else
            antS->sig = nuevo;
        actS = nuevo;
    }
    actS->cantS += cant;
}

void actSub(TLC Ppuesto, TElementoC *elem) {
    SubLista actS;

    actS = Ppuesto->sub;
    while(actS && elem->cantD > 0) {
        if(strcmp(actS->cod, elem->cod) == 0) {
            if(elem->cantD >= actS->cantS) {
                actS->cantE += actS->cantS;
                elem->cantD -= actS->cantS;
                actS->cantS = 0;
            }
            else {
                actS->cantE += elem->cantD;
                actS->cantS -= elem->cantD;
                elem->cantD = 0;
            }
        }
        actS = actS->sig;
    }
}

void simular(TL L, TLC LC) {
    TL act;
    TLC Ppuesto;
    TElementoC elem, cent;
    strcpy(cent.cod, "ZZZZZZZ");
    act = L;
    while(act) {
        Ppuesto = buscaPuesto(LC, act->idP);
        if(Ppuesto) {
            poneC(&(act->C), cent);
            sacaC(&(act->C), &elem);
            while(strcmp(elem.cod, cent.cod) != 0) {
                actSub(Ppuesto, &elem);
                if(elem.cantD == 0)
                    sacaC(&(act->C), &elem);
                else {
                    poneC(&(act->C), elem);
                    sacaC(&(act->C), &elem);
                }
            }
        }
        act = act->sig;
    }
}

void elimina(TLC LC, char cod[], int x) {
    TLC actC;
    SubLista actS, elim, antS;

    if(LC) {
        actC = LC->sig;
        while(actC != LC && actC->idP < x) {
            actS = actC->sub;
            while(actS) {
                if(strcmp(cod, actS->cod) == 0) {
                    elim = actS;
                    if(actS == actC->sub)
                        actC->sub = actC->sub->sig;
                    else
                        antS->sig = actS->sig;
                    actS = actS->sig;
                    free(elim);
                }
                else {
                    antS = actS;
                    actS = actS->sig;
                }
            }
            actC = actC->sig;
        }
    }
}

int main() {
    TLC LC;
    char cod[ST7];
    TL L;
    int x;
    TCola C;

    cargaLC(&LC); cargaL(&L);
    procesaArch(&LC);
    simular(L, LC);
    printf("Ingrese el codigo del producto y x\n");
    scanf(" %s %d", cod, &x);
    elimina(LC, cod, x);
    return 0;
}
