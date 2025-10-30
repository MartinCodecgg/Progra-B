#include <stdio.h>
#define N 10

int verMayorGrEntrada(TLista vec[], int n) {
    int i, vecAux[N] = {0}, max = -1, verticeMax;
    TLista act;

    for(i = 0; i < n; i++) {
        act = vec[i];
        while(act != NULL) {
            vecAux[act->vertice]++;
            act = act->sig;
        }
    }

    for(i = 0; i < n; i++)
        if(vecAux[i] > max) {
            max = vecAux[i];
            verticeMax = i;
        }
    return verticeMax;
}

int main() {
    return 0;
}
