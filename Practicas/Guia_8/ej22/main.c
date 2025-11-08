#include <stdio.h>
#include "Pilas.h"
#define N 50
#define INF 999

/*
void muestraCamino(int P[], int v) {
    int caminoInv[N], i, tam;

    if(P[v] == INF)
        printf("No existe camino\n");
    else {
        tam = 0;
        while(v != 0) {
            caminoInv[tam] = v;
            v = P[v];
            tam++;
        }
        caminoInv[tam] = v; // esto es para mostrar el origen ( 0  en este caso)

        for(i = tam; i >= 0; i--)
            printf("%d\t",caminoInv[i]);
    }
}
*/

void muestraCamino(int P[], int v) {
    TPila P;
    TelementoP elem;

    IniciaP(&P;)
    if(P[v] == INF)
        printf("No existe camino\n");
    else {
        while(v != 0) {
            PoneP(&P,v);
            v = P[v];
        }
        poneP(&P,v);// esto es para mostrar/apilar el origen (0  en este caso)

        for(i = tam; i >= 0; i--) {
            sacaP(&P,&elem)
            printf("%d\t",elem);
        }
    }
}

int main() { // P[2] = 2; recordar que se cuenta desde el cero
    int P[] = {INF,0,1,2}, v = 3; //camino de 0 a 3, camino es 0 -> 1 -> 2 -> 3 , 9 es cualquier valor
    muestraCamino(P,v);

    printf("\n");
    int Q[] = {INF,0,0,1}, w = 3; // camino de 0->1->3
    muestraCamino(Q,w);

    printf("\n");
    int R[] = {INF,0,0,INF}, x = 3; //no existe camino
    muestraCamino(R,w);
    return 0;
}
