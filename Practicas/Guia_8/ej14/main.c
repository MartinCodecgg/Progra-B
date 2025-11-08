#include <stdio.h>
#include <stdlib.h>

#define N 5

void prim(int mat[][N], int n, int ini, int arbolGen[][N]) {
    int u[N], nu = 0, j, k, VV[N], pesoMin, fila, col;
    int Vmin, adyMin;

    for(j = 0; j < n; j++)
        VV[j] = 0;
    u[nu] = ini;
    nu++;
    VV[ini] = 1;

    while(nu < n) { //u debe tener la misma cantidad de vertices del grafo, es decir n
        pesoMin = 99999;
        for(k = 0; k < nu; k++)
            for(j = 0; j < n; j++) {

                if(u[k] < j) { //triangulo superior
                    fila = u[k];
                    col = j;
                }
                else { //estoy en el triangulo inferior ahora y paso a recorrer la columna del vertice actual
                    fila = j;
                    col = u[k];
                }

                if(mat[fila][col] != 0 && VV[col] == 0 && mat[fila][col] < pesoMin) {
                    pesoMin = mat[fila][col];
                    Vmin = fila;
                    adyMin = col;
                }
            }
        if(pesoMin != 99999) {
            u[nu] = adyMin;
            nu++;
            VV[adyMin] = 1;
            arbolGen[Vmin][adyMin] = pesoMin;
            arbolGen[adyMin][Vmin] = pesoMin;
        }
    }
}

void imprimirMediaMatriz(int mat[][N], int n) {
    printf("\n    ");
    for(int i = 0; i < n; i++)
        printf("L%d  ", i+1);
    printf("\n");

    for(int i = 0; i < n; i++) {
        printf("L%d  ", i+1);
        for(int j = 0; j < n; j++) {
            if(j <= i)
                printf("    ");
            else if(mat[i][j] == 0)
                printf("-   ");
            else
                printf("%-3d ", mat[i][j]);
        }
        printf("\n");
    }
}

void imprimirMatrizCompleta(int mat[][N], int n) {
    printf("\n    ");
    for(int i = 0; i < n; i++)
        printf("L%d  ", i+1);
    printf("\n");

    for(int i = 0; i < n; i++) {
        printf("L%d  ", i+1);
        for(int j = 0; j < n; j++) {
            if(mat[i][j] == 0)
                printf("-   ");
            else
                printf("%-3d ", mat[i][j]);
        }
        printf("\n");
    }
}

int calcularCostoTotal(int arbol[][N], int n) {
    int total = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(arbol[i][j] != 0)
                total += arbol[i][j];
        }
    }
    return total;
}

int main() {
    // MEDIA MATRIZ - Solo parte superior (como en el ejercicio)
    int mat[N][N] = {
        {0,  5,  50, 80, 90},  // L1
        {0,  0,  70, 60, 50},  // L2
        {0,  0,  0,  8,  20},  // L3
        {0,  0,  0,  0,  10},  // L4
        {0,  0,  0,  0,  0}    // L5
    };

    int arbolGen[N][N] = {0};

    printf("=== EJERCICIO 14: Tendido de vias ferroviarias ===\n");
    printf("\nMedia matriz de distancias (como en el ejercicio):");
    imprimirMediaMatriz(mat, N);

    // Ejecutar algoritmo de Prim desde L1 (índice 0)
    prim(mat, N, 0, arbolGen);

    printf("\n\nArbol Abarcador de Costo Minimo (Prim):");
    imprimirMatrizCompleta(arbolGen, N);

    int costoTotal = calcularCostoTotal(arbolGen, N);
    printf("\n*** Costo total del tendido: %d km ***\n", costoTotal);

    printf("\nConexiones en el AAM:\n");
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            if(arbolGen[i][j] != 0) {
                printf("L%d -- L%d: %d km\n", i+1, j+1, arbolGen[i][j]);
            }
        }
    }

    return 0;
}
