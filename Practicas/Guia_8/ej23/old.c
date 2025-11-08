#include <stdio.h>
#define N 50
#define INF 99999

void floyd(int D[][N], int P[][N], int n) {
    int i, j, k;

    // Inicializar matriz de predecesores
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i == j)
                P[i][j] = -1;  // Sin predecesor (es el mismo vértice)
            else if(D[i][j] != INF)
                P[i][j] = i;   // El predecesor directo es i
            else
                P[i][j] = -1;  // No hay camino
        }
    }

    // Algoritmo de Floyd
    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(D[i][k] != INF && D[k][j] != INF && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];  // El predecesor de j es el mismo que en el camino k->j
                }
            }
        }
    }
}

void muestraCamino(int P[][N], int v, int w) {
    int caminoInv[N], tam, k;

    tam = 0;
    while(w != v) {
        caminoInv[tam] = w;
        w = P[v][w]; //w varia pero v no, porque siempre el origen sera v
        tam++;
    }
    caminoInv[tam] = w; //si imprimo el camino contando el vertice inicial, entonces debe ir afuera el correspondiente al origen o usar un do while

    for(k = tam; k >= 0; k--) //si imprimo el origen entonces debo recorrer de 0 a tam para contar el origen que se asigna afuera
        printf("%d ",caminoInv[k]);
}

int main() {
    int D[N][N], P[N][N];
    int n = 5;  // Número de vértices
    int i, j;

    // Inicializar matriz de distancias
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i == j)
                D[i][j] = 0;
            else
                D[i][j] = INF;
        }
    }

    // Ejemplo de grafo: agregar aristas
    D[0][1] = 3;
    D[0][2] = 8;
    D[1][3] = 1;
    D[2][1] = 4;
    D[3][0] = 2;
    D[3][4] = 6;
    D[4][3] = 1;

    floyd(D, P, n);

    printf("Camino de 0 a 4: ");
    muestraCamino(P, 0, 4);
    printf("\n");

    return 0;
}
