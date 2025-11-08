
#include <stdio.h>
#include <stdlib.h>
#define N 6
#define INFINITO 9999
#define M {{0,0,1,0,1,0},{1,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,0},{0,0,0,0,0,1},{0,0,0,0,0,0}}

typedef struct nodo {
    int vertice;
    struct nodo * sig;} nodo;

typedef struct nodo * TLista;

void warshallYfloyd(int mat[][N], int n, int R[][N], int D[][N]) {
    int i, j, k;

    //Inicializaciones
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i == j) {
                R[i][j] = 1;
                D[i][j] = 0;
            }
            else
                if(mat[i][j] != 0) {
                    R[i][j] = 1;
                    D[i][j] = 0;
                }
                else {
                    R[i][j] = 0;
                    D[i][j] = INFINITO;
                }

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(R[i][k] == 1 && R[k][j] == 1)
                    R[i][j] = 1;
                if(D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
}
