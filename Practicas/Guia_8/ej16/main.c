#include <stdio.h>
#define N 4
#define MAX_VAL 99999

#define MATRIZ {{0, 30, 0, 13}, \
                {22, 0, 10, 12}, \
                {0, 25, 0, 0}, \
                {13, 6, 0, 0}}

int conjuntoCompleto(int S[], int n) {
    int i = 0;
    while(i < n && S[i] == 1)
        i++;
    return i == n;
}

void djikstraALL(int mat[][N], int n, int origen, int D[], int prede[]) {
    int j, v, min, pesoMin, S[N]; //aux[N]; // v = vertice
    
    //inicializaciones
    for(j = 0; j < n; j++) {
        D[j] = MAX_VAL;
        S[j] = 0;
    }
    D[origen] = 0;
    S[origen] = 1;
    prede[origen] = -1;
    v = origen;

    while(!conjuntoCompleto(S, n)) {//preguntar por ns y no llamar a una funcion
        pesoMin = MAX_VAL;
        for(j = 0; j < n; j++) {
            if(mat[v][j] != 0 && S[j] == 0 && mat[v][j] + D[v] < D[j]) {
                D[j] = mat[v][j] + D[v];
                prede[j] = v;
            }
            if(S[j] == 0 && D[j] < pesoMin) {
                min = j;
                pesoMin = D[j];
            }
        }
        if(pesoMin != MAX_VAL) {
            S[min] = 1;
            v = min;
        }
    }
    /* Algoritmo para mostrar camino mas corto entre un par de vertices teniendo como dato el destino
    printf("Camino minimo resultante:\n");
    v = destino;
    // con el valor del v q corresponde al ultimo elemento procesado:
    j = 0;
    while(v != -1) {
        aux[j] = v;
        j++;
        v = predecesores[v];
    }

    for(j = j-1; j >= 0; j--)
        printf("%d ",aux[j]);
        if(j > 0)
            printf("-> ");

    printf("\n");
    */
}

void caminoMasCortoEntrePares(int mat[][N], int n, int caminos[][N]) {
    int distancias[N], i, j, k, predecesores[N][N], prede[N], v, aux[N];

    for(i = 0; i < n; i++) {
        djikstraALL(mat, n, i, distancias, prede);
        for(k = 0; k < n; k++) {
            caminos[i][k] = distancias[k];
            predecesores[i][k] = prede[k];
        }
    }

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) {
            if(i != j) { //descarto si el destino y origen son iguales
                printf("De %d a %d: ", i, j);

                k = 0;
                v = j;
                while(v != -1) {
                    aux[k] = v;
                    k++;
                    v = predecesores[i][v];
                }

                for(k = k-1; k >= 0; k--) { //siempre debo hacer alguna asignacion aqui
                    printf("%d ",aux[k]);
                    if(k > 0)
                        printf(" -> ");
                }
                printf(" (costo minimo: %d)\n", caminos[i][j]);
                printf("\n");
            }
    }
}

void imprimirMatriz(int mat[][N], int n) {
    int i, j;
    printf("\nMatriz de distancias minimas:\n");
    printf("     ");
    for(j = 0; j < n; j++) {
        printf("%6d", j);
    }
    printf("\n");

    for(i = 0; i < n; i++) {
        printf("%4d:", i);
        for(j = 0; j < n; j++) {
            if(mat[i][j] == MAX_VAL)
                printf("   INF");
            else
                printf("%6d", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int grafo[N][N] = MATRIZ;
    int caminos[N][N];

    printf("Matriz de adyacencia original:\n");
    imprimirMatriz(grafo, N);

    printf("\n\nAplicando Dijkstra desde cada vertice...\n");
    caminoMasCortoEntrePares(grafo, N, caminos);

    printf("\n\nResultado - Caminos mas cortos entre todos los pares:\n");
    imprimirMatriz(caminos, N);

    printf("\n\nEjemplos de distancias:\n");
    printf("De vertice 0 a vertice 3: %d\n", caminos[0][3]);
    printf("De vertice 1 a vertice 2: %d\n", caminos[1][2]);
    printf("De vertice 3 a vertice 1: %d\n", caminos[3][1]);

    return 0;
}
