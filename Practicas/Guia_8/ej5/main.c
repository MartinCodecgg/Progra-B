#include <stdio.h>
#define N 10

int gradoE(int mat[][N], int V) {
    unsigned int i, aux = 0;

    for(i = 0; i < N; i++)
        aux += mat[i][V];
    return aux;
}

int gradoS(int mat[][N], int V) {
    unsigned int j, aux = 0;

    for(j = 0; j < N; j++)
        aux += mat[V][j];
    return aux;
}

int gradoTot(int mat[][N], int V) {

    if(mat[V][V] == 1)
        return gradoE(mat, V) + gradoS(mat, V) -1;
    else
        return gradoE(mat, V) + gradoS(mat, V);
}

int main() {
    int mat[N][N] = {
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        // ... resto de la matriz
    };

    int v = 1;
    printf("Vértice %d:\n", v);
    printf("Grado entrada: %d\n", gradoE(mat, v));   // Aristas que llegan a v
    printf("Grado salida: %d\n", gradoS(mat, v));    // Aristas que salen de v
    printf("Grado total: %d\n", gradoTot(mat, v));   // Suma total

    return 0;
}
