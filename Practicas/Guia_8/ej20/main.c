#include <stdio.h>
#include <stdlib.h>
#define N 6
#define INFINITO 9999
#define M {{0,0,1,0,1,0},{1,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,0},{0,0,0,0,0,1},{0,0,0,0,0,0}}

typedef struct nodo {
    int vertice;
    struct nodo * sig;
} nodo;

typedef struct nodo * TLista;

//floyd cuenta aristas, asi que si solo quiero la cantidad de vertices intermedios tengo que restar 1 simplemente, porque para cada vertice intermedio corresponden dos aristas
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
                    D[i][j] = 1;  // Una arista directa
                }
                else {
                    R[i][j] = 0;
                    D[i][j] = INFINITO;
                }

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++) {
                if(R[i][k] == 1 && R[k][j] == 1)
                    R[i][j] = 1;
                if(D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
            }
}

void imprimirMatrizAlcance(int mat[][N], int n, char vertices[]) {
    printf("\n    ");
    for(int j = 0; j < n; j++)
        printf("%c ", vertices[j]);
    printf("\n");
    
    for(int i = 0; i < n; i++) {
        printf("%c | ", vertices[i]);
        for(int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void imprimirMatrizDistancias(int mat[][N], int n, char vertices[]) {
    printf("\n    ");
    for(int j = 0; j < n; j++)
        printf("%3c ", vertices[j]);
    printf("\n");
    
    for(int i = 0; i < n; i++) {
        printf("%c | ", vertices[i]);
        for(int j = 0; j < n; j++) {
            if(mat[i][j] == INFINITO)
                printf("INF ");
            else
                printf("%3d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matriz[N][N] = M;
    int R[N][N], D[N][N];
    int n = 6;
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    
    printf("========================================");
    printf("\nMATRIZ DE ADYACENCIA ORIGINAL:");
    printf("\n========================================");
    imprimirMatrizAlcance(matriz, n, vertices);
    
    warshallYfloyd(matriz, n, R, D);
    
    printf("\n\n========================================");
    printf("\nMATRIZ DE ALCANCE (Warshall):");
    printf("\n========================================");
    imprimirMatrizAlcance(R, n, vertices);
    
    printf("\n\n========================================");
    printf("\nMATRIZ DE DISTANCIAS (Floyd):");
    printf("\n========================================");
    printf("(Numero de aristas en el camino minimo)\n");
    imprimirMatrizDistancias(D, n, vertices);
    
    printf("\n\n========================================");
    printf("\nEJEMPLOS DE INTERPRETACION:");
    printf("\n========================================\n");
    printf("De A a F: ");
    if(D[0][5] == INFINITO)
        printf("No hay camino\n");
    else
        printf("vertices intermedios = %d (camino: A->E->F)\n", D[0][5] - 1);
    
    printf("De B a F: ");
    if(D[1][5] == INFINITO)
        printf("No hay camino\n");
    else
        printf("vertices intermedios = %d (camino: B->A->E->F)\n", D[1][5] - 1);
    
    printf("De C a D: ");
    if(D[2][3] == INFINITO)
        printf("No hay camino\n");
    else
        printf("vertices intermedios = %d (camino: C->E->? No directo)\n", D[2][3] - 1);
    
    return 0;
}
/*
```

**Salida esperada:**
```
MATRIZ DE DISTANCIAS (Floyd):
    A   B   C   D   E   F 
A |   0 INF   1 INF   1   2 
B |   1   0   2   1   2   3 
C | INF INF   0 INF   1   2 
D | INF INF INF   0 INF INF 
E | INF INF INF INF   0   1 
F | INF INF INF INF INF   0 

EJEMPLOS DE INTERPRETACION:
De A a F: Distancia = 2 aristas (camino: A->E->F)
De B a F: Distancia = 3 aristas (camino: B->A->E->F)
*/