#include <stdio.h>
#define N 50
#define INF 9999

void muestraCamino(int P[][N], int v, int w) {
    int caminoInv[N], tam, k;

    tam = 0;
    while(w != v) {
        caminoInv[tam] = w;
        w = P[v][w]; //w varia pero v no, porque siempre el origen sera v pero w es el que varia
        tam++;
    }
    caminoInv[tam] = w; //si imprimo el camino contando el vertice inicial, entonces debe ir afuera el correspondiente al origen o usar un do while

    for(k = tam; k >= 0; k--) //si imprimo el origen entonces debo recorrer de 0 a tam para contar el origen que se asigna afuera
        printf("%d ",caminoInv[k]);
}

int main() {
    return 0;
}
