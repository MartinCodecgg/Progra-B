#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colas.h"
#define ST8 9
#define N 5

typedef struct nodito {
    unsigned int nroC;
    char dni[ST8];
    struct nodito * sig; } nodito;

typedef nodito * SubLista;

typedef struct nodo {
    unsigned int nor;
    char tipo;
    SubLista sub;
    struct nodo * sig; } nodo;

typedef nodo * TL;

typedef struct nodoD {
    TElementoC cama;
    struct nodoD * sig, *ant; } nodoD;

typedef nodoD * Pnodo;

typedef struct {
    Pnodo pri, ult; } TLD;

int busca(char tipos[], char tipo) {
    int i = 0;
    while(i < N && tipos[i] != tipo)
        i++;
    return i;
}

void elimina(TL *L, TLD *LD, int cant[], char tipos[]) {
    TElementoC elem;
    int pos;
    SubLista actS, antS;
    TL act, elim;

    act = *L;
    while(act && act->nro < 100) //ciclar los pisos menores al 1ro
        act = act->sig;

    while(act && act->nro < 200) {
        actS = act->sub;
        while(actS) {
            if(strlen(actS->dni) != 0) {
                strcpy(elem.dni, actS->dni);
                elem.individual = 'N';
                elem.ingreso = 'N';
                elem.tipo = act->tipo;
                insertaLD(LD, elem);
                pos = busca(tipos, act->tipo);
                if(pos < N) //valido que el tipo de act->tipo sea valido // pos < N y no <= N, porque recordar que pos representa un indice en el vector
                    cant[pos]++;
                }

            antS = actS;
            actS = actS->sig;
            free(antS);
        }
        elim = act;
        if(act == *L) {
            *L = (*L)->sig;
            act = *L;
        }
        else
            act = act->sig; //recordar que si elimino el nodo al que apunta L, debere de actualizar L

        free(elim);
    }
}

char tipoMax(int cant[], char tipos[], int i, int iMax) {
    if(i < 0)
        return tipos[iMax];
    else {
        if(cant[i] > cant[iMax])
            iMax = i;
        return tipoMax(cant, i-1, iMax);
    }
}
//ant->sig = act?, una vez que act sea del 2do piso?

void procesaC(TL L, TLD *LD, TCola *C) {
    TL act;
    TElementoC elem;
    int OkPaciente, OkCama, pedidos = 0, completados = 0, vacia, cumple;
    SubLista actS, Pcama;

    while(!VaciaC(*C)) {
        sacaC(C, &elem);
        pedidos++;
        cumple = 0;
        act = L;
        while(act && !cumple) {
            if(act->tipo == elem.tipo) {
                vacia = elem.individual == 'S';
                actS = act->sub;
                OkCama = 0;
                while(actS && (!OkCama || vacia)) {
                    if(strlen(actS->dni) != 0)
                        vacia = 0;
                    else
                        if(!OkCama) {
                            OkCama = 1;
                            Pcama = actS;
                        }
                    actS = actS->sig;
                }
            }
            cumple = OkCama && (elem.individual == 'N' || vacia);
            act = act->sig;
        }
        if(cumple) {
            if(elem.ingreso == 'N') {
                act = L;
                OkPaciente = 0;
                while(act && !OkPaciente) {
                    actS = act->sub;
                    while(actS == Pcama || (actS && !OkPaciente && strcmp(elem.dni, actS->dni) != 0))
                        actS = actS->sig;
                    if(actS && strcmp(elem.dni, actS->dni) == 0)
                        OkPaciente = 1;
                    act = act->sig;
                }
            }
            else
                OkPaciente = 1;

            if(OkPaciente) {
                completados++;
                strcpy(Pcama->dni, elem.dni);
                if(elem.individual == 'S')
                    strcpy(actS->dni,"");
            }
        }
        if(!cumple || !OkPaciente)
            insertaLD(LD, elem);
    }

    if(pedidos)
        printf("El porcentaje de pedidos que se pudieron completar fue %3.2f\n", (float) completados/pedidos * 100);
}

int main() {
    TL L;
    TLD LD;
    TCOLA C;
    char tipos[N] = {'P','C','T','E','M'};
    int cont[N] = {0};
    cargaL(&L); cargaLD(&LD); cargaC(&C);
    procesaC(L, &LD, &C);
    elimina(&L, &LD, cont, tipos);
    printf("El tipo de habitaciones con mayor cantidad de pacientes a trasladar es %c\n", tiposMax(cont, tipos, N-1, N-1));
    return 0;
}
