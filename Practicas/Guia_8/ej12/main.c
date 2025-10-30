#include <stdio.h>
#define N 10

void muestraVAmplitud(TLista vec[], int n) {
    TCola C;
    int visitados[N] = {0}, vertice;
    TLista act;

    IniciaC(&C);
    poneC(&C, 0); //y no hay otra forma de hacerlo, vec[0]->vertice vendria a apuntar al primer elemento adyacente al primer vertice y no al primer vertice como tal
    visitados[0] = 1;

    while(!VaciaC(C)) {
        sacaC(&C, &vertice);
        act = vec[vertice];
        printf("%d",vertice);
        while(act != NULL) {
            if(visitados[act->vertice] == 0) {
                poneC(&C,act->vertice);
                visitados[act->vertice] = 1;
            }
            act = act->sig;
        }
    }
}

void cantConexas(TLista vec[], int n) {
    TCola C;
    int visitados[N] = {0}, vertice;
    TLista act;

    IniciaC(&C);
    poneC(&C, 0);
    visitados[0] = 1;

    while(!VaciaC(C)) {
        sacaC(&C, &vertice);
        act = vec[vertice];
        printf("%d",vertice);
        while(act != NULL) {
            if(visitados[act->vertice] == 0) {
                poneC(&C,act->vertice);
                visitados[act->vertice] = 1;
            }
            act = act->sig;
        }
    }
}

int main() {
    return 0;
}
