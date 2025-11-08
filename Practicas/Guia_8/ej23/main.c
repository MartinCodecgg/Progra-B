#include <stdio.h>
#define N 50
#define INF 9999

void muestraCamino(int P[][N], int v, int w) { //v = origen, w = destino
    int caminoInv[N], tam, k;

    if(P[v][w] == INF)
        printf("No existe camino de %d a %d\n", v, w);
    else
        if(v == w)
            printf("%d\n", v); //el origen es igual al destino
    else {
        tam = 0;
        while(w != v) {
            caminoInv[tam] = w;
            w = P[v][w]; //el origen siempre se mantiene fijo (v), en cambio el destino (w) es el que varia (mas bien el intermediario)
            tam++;
        }
        caminoInv[tam] = v;

        for(k = tam; k >= 0; k--)
            printf("%d ", caminoInv[k]);
        printf("\n");
    }
}

int main() {

    // Ejemplo: P[v][w] = predecesor de w en el camino desde v
    /*
        Grafo: 0 -> 1 -> 2 -> 3

        P[0][1] = 0  (para ir de 0 a 1, el predecesor de 1 es 0)
        P[0][2] = 1  (para ir de 0 a 2, el predecesor de 2 es 1)
        P[0][3] = 2  (para ir de 0 a 3, el predecesor de 3 es 2)
    */
    int P[4][N] = {
        {INF,   0,   1,   2},  // Desde 0: predecesores para llegar a 1,2,3
        {INF, INF,   1,   2},  // Desde 1: predecesores para llegar a 2,3
        {INF, INF, INF,   2},  // Desde 2: predecesor para llegar a 3
        {INF, INF, INF, INF}   // Desde 3
    };

    printf("Camino de 0 a 3: ");
    muestraCamino(P, 0, 3);  //0 1 2 3

    printf("Camino de 1 a 3: ");
    muestraCamino(P, 1, 3);  //1 2 3

    printf("Camino de 0 a 1: ");
    muestraCamino(P, 0, 1);  // 0 1

    printf("Camino de 3 a 0: ");
    muestraCamino(P, 3, 0);  // No existe camino

    return 0;
}
