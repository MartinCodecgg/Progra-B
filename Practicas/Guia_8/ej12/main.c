#include <stdio.h>
#define N 10

//Funcion auxiliar
int verifVisitados(int visitados[], int n) {
    int i = 0;
    while(i < n && visitados[i] != 0)
        i++;
    //return visitados[i]; //acceso fuera de rango cuando el vector esta todo lleno
    return i == n;
}

void muestraProfundidad(TLista vec[], int n, int ini) {
    int VV[N], i, vertice;
    TLista act;
    TPila P;

    Inicia(&P);
    for(i = 0; i < n; i++)
        VV[i] = 0;
    poneP(&P,ini);
    VV[ini] = 1;
    printf("%d",ini);

    while(!verifVisitados(VV, n)) {
        vertice = consultaP(P);
        act = vec[vertice];
        while(act != NULL && VV[act->vertice] == 1)
              act = act->sig;
        if(act != NULL) {
            poneP(&P,act->vertice);
            printf("%d", act->vertice);
            VV[act->vertice] = 1;
        }
        else
            sacaP(&P,&vertice);
    }
}

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

void cantConexas(TLista vec[], int n,int *conexas) {
    TCola C;
    int visitados[N] = {0}, vertice, todosVisitados, i;
    TLista act;
    *conexas = 0;
    IniciaC(&C);

    todosVisitados = verifVisitados(visitados,n);
    while(!todosVisitados) {

        i = 0;
        while(visitados[i])
            i++;
        visitados[i] = 1;
        poneC(&C,i);

        while(!VaciaC(C)) {
            sacaC(&C, &vertice);
            act = vec[vertice];
            while(act != NULL) {
                if(visitados[act->vertice] == 0) {
                    poneC(&C,act->vertice);
                    visitados[act->vertice] = 1;
                }
                act = act->sig;
            }
        }
        (*conexas)++;
        todosVisitados = verifVisitados(visitados,n);
    }
}

int main() {
    return 0;
}
