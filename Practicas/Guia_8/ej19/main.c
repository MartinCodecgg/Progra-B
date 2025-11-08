/*
//ignorar esto...
#ifdef __INTELLISENSE__
#pragma diag_suppress 3360
#pragma diag_suppress 3364
#endif
*/

#include <stdio.h>
#include <stdlib.h>
#define N 6
#define M {{0,0,1,0,1,0},{1,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,0},{0,0,0,0,0,1},{0,0,0,0,0,0}}

typedef struct nodo {
    int vertice;
    struct nodo * sig;} nodo;

typedef struct nodo * TLista;

void warshallFromMatriz(int mat[][N], int n, int R[][N]) {
    int i, j, k;

    //Inicializaciones
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i == j)
                R[i][j] = 1;
            else
                if(mat[i][j] != 0)
                    R[i][j] = 1;
                else
                    R[i][j] = 0;

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(R[i][k] == 1 && R[k][j] == 1)
                    R[i][j] = 1;
}
/*
 //INNECESARIA (y no funciona)
int existeIntermediario(TLista vec[], int origen,int destino,int intermediario) {
    TLista Lorigen = vec[origen], Linter = vec[intermediario];
    int existe = 0;

    while(Lorigen != NULL && !existe) {
        if(Lorigen->vertice == intermediario) {
            while(Linter != NULL && Linter->vertice != destino)
                Linter = Linter->sig;

            if(Linter != NULL)
                existe = 1;
        }
        Lorigen = Lorigen->sig;
    }
    return existe;
}
*/

void warshallFromLista(TLista vec[], int n, int R[][N]) {
    int i, j, k;
    TLista act;

    //Inicializaciones
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            if(i == j)
                R[i][j] = 1;
            else
                R[i][j] = 0;

        act = vec[i];
        while(act != NULL) {
            R[i][act->vertice] = 1;
            act = act->sig;
        }
    }

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(R[i][k] == 1 && R[k][j] == 1) 
                    R[i][j] = 1;
}

void imprimirMatriz(int mat[][N], int n, char vertices[]) {
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

void insertarArista(TLista vec[], int origen, int destino) {
    TLista nuevo = (TLista)malloc(sizeof(struct nodo));
    nuevo->vertice = destino;
    nuevo->sig = vec[origen];
    vec[origen] = nuevo;
}

void liberarListas(TLista vec[], int n) {
    TLista act, aux;
    for(int i = 0; i < n; i++) {
        act = vec[i];
        while(act != NULL) {
            aux = act;
            act = act->sig;
            free(aux);
        }
    }
}

int main() {
    int matriz[N][N] = M;
    int R1[N][N], R2[N][N];
    int n = 6;
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    TLista listaAdyacencia[N] = {NULL};
    
    // Construir lista de adyacencia desde matriz
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(matriz[i][j] != 0) {
                insertarArista(listaAdyacencia, i, j);
            }
        }
    }
    
    printf("========================================");
    printf("\nMATRIZ DE ADYACENCIA ORIGINAL:");
    printf("\n========================================");
    imprimirMatriz(matriz, n, vertices);
    
    // Probar Warshall desde matriz
    warshallFromMatriz(matriz, n, R1);
    printf("\n\n========================================");
    printf("\nMATRIZ DE ALCANCE (desde Matriz):");
    printf("\n========================================");
    imprimirMatriz(R1, n, vertices);
    
    // Probar Warshall desde lista
    warshallFromLista(listaAdyacencia, n, R2);
    printf("\n\n========================================");
    printf("\nMATRIZ DE ALCANCE (desde Lista):");
    printf("\n========================================");
    imprimirMatriz(R2, n, vertices);
    
    // Comparar resultados
    printf("\n\n========================================");
    printf("\nCOMPARACION DE RESULTADOS:");
    printf("\n========================================\n");
    int iguales = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(R1[i][j] != R2[i][j]) {
                printf("Diferencia en [%c][%c]: Matriz=%d, Lista=%d\n", 
                       vertices[i], vertices[j], R1[i][j], R2[i][j]);
                iguales = 0;
            }
        }
    }
    
    if(iguales)
        printf("Las matrices son IDENTICAS!\n");
    else
        printf("Las matrices son DIFERENTES!\n");
    
    liberarListas(listaAdyacencia, n);
    
    return 0;
}
